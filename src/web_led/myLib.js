/* laban.util namespace is defined in laban_util.js file */

Region = fabric.util.createClass(fabric.Group,  {
    type	: "region",
    objects	: [],

    _myCalcBounds: function(object) {
	object.__objectPosition = new fabric.Point(object.getLeft() - object.parentRegion.getLeft(), object.getTop() - object.parentRegion.getTop());
    },


    isInsideParent: function(object) {
	return (object.left >= this.left) && object.top >= this.top && (object.left + object.width) <= (this.left + this.width) && (object.top + object.height) <= (this.top + this.height);
    },
    
    _getRegionBounds: function() {

	objs1	= this.objects;
	objs2    = objs1.slice();
	this.backgroundObj && objs2.push(this.backgroundObj);
	group	= new fabric.Group(objs2);
	obj	= {
	    left	: Math.round(group.getLeft()),
	    top		: Math.round(group.getTop()),
	    height	: Math.round(group.getHeight()),
	    width	: Math.round(group.getWidth())
	};
	group.destroy();	
	return obj;
    },



    initialize: function (objects, options) {
	options = options || { }
	this.callSuper ("initialize", objects, options)
	this.objects = []
	this.on('moving', this.updateChildPositions);
	// this.on('moving', function(evt) {
	//     points		= new fabric.Point(this.getLeft(), this.getTop());
	//     var childObjs	= this.objects;
	//     laban.util.normalizeCoords(points, this.movx, this.movy);
	//     childObjs && childObjs.map(function (o) {
    	// 	leftCMove	= points.x + o.__objectPosition.x;
    	// 	rightCMove	= points.y + o.__objectPosition.y
    	// 	o.set({
    	// 	    left	: leftCMove,
    	// 	    top		: rightCMove
    	// 	});
	// 	o.setCoords();
	//     });
	// });
    },



    updateChildPositions: function(evt) {
	points		= new fabric.Point(this.getLeft(), this.getTop());
	var childObjs	= this.objects;
	laban.util.normalizeCoords(points, this.movx, this.movy);
	childObjs && childObjs.map(function (o) {
    	    leftCMove	= points.x + o.__objectPosition.x;
    	    rightCMove	= points.y + o.__objectPosition.y
    	    o.set({
    		left	: leftCMove,
    		top	: rightCMove
    	    });
	    o.setCoords();
	});
	
    },

    toObject: function() {
	this.callSuper("toObject")
    },
    _onChildMove: function(obj) {
	return function (e) {
	    obj.parentRegion && obj.parentRegion._myCalcBounds(obj);
	    !obj.parentRegion.isInsideParent(obj) && obj.parentRegion.removeObject(obj);
	}
    },
    

    addObject: function(obj) {
	if (obj.level <= this.level)
	    return;
	obj.on('moving', this._onChildMove(obj));
	obj.parentRegion = this;
	this.objects.push(obj)
	// this._updateRegionCoords();
	obj.bringToFront && obj.bringToFront();
	this._myCalcBounds(obj);
	// this._updateObjectCoords();
    },

    setCoords: function() {
	this.callSuper('setCoords');
	this.objects.forEach(this._myCalcBounds)
    },

    addMultiple: function(objs) {
	objs.map(this.addObject);
    },

    removeObject: function(obj) {
	this.objects = this.objects.filter(function (ob) {
	    return ob !== obj;
	});
	// this.objects.pop(obj);
	obj.off('moving');
	obj.parentRegion = undefined;
	delete obj.__objectPosition;
    }
});



Staff = fabric.util.createClass(Region, {
    type: "staff",
    blockSize: 50,
    strokeWidth: 3,
    height: 0,
    width: 0,
    defaultLines: 3,
    leftLines: 0,
    rightLines: 0, // Considering -1 because of centerLine
    
    getStaffLine: function (height, leftMargin, dashed, color) {
	var strokeDashArray = dashed ? [5,5] : [];
	var color = color || '#000'
	var centerLine = new fabric.Line([leftMargin, 0, leftMargin, height], { stroke: color, strokeWidth: this.strokeWidth, selectable: false, strokeDashArray: strokeDashArray})
	return centerLine;
    },

    initialize: function (objects, options) {
	objects = objects || []
	options = options || { }	
	this.callSuper ("initialize", objects,  options)
	this.movx = this.movx == undefined || this.movx == null ? this.blockSize : this.movx;
	this.movy = this.movy == undefined || this.movy == null ? this.blockSize : this.movy;
	this.generateStaff();
    },
    
    generateStaff: function(rightLines) {
	this.addMainLine();
	this.addComponentRight();
	this.addComponentLeft();
    },

    addMainLine: function() {
	staff = this;
	var negativeRatio =  staff.strokeWidth;
	negativeRatio = staff.getWidth() <= this.strokeWidth ? negativeRatio : staff.strokeWidth * 2
	var mLeft = staff.getLeft() + staff.getWidth() + (staff.blockSize * 2) - negativeRatio;
	staff.addWithUpdate(staff.getStaffLine(staff.getHeight(), mLeft, false, '#f00'));
	staff.setCoords();
    },

    addComponentRight: function() {
	staff = this;
	var negativeRatio =  staff.strokeWidth;
	negativeRatio = staff.getWidth() <= this.strokeWidth ? negativeRatio : staff.strokeWidth * 2
	var mLeft = staff.getLeft() + staff.getWidth() + (staff.blockSize * 2) - negativeRatio;
	staff.addWithUpdate(staff.getStaffLine(staff.getHeight(), mLeft, this.rightLines % 2 == 1));
	staff.setCoords();
	this.rightLines += 1;
    },

    addComponentLeft: function() {
	staff = this;
	var mLeft = staff.getLeft() - (staff.blockSize * 2) ;
	staff.addWithUpdate(staff.getStaffLine(staff.getHeight(), mLeft, this.leftLines % 2 == 1));
	staff.setCoords();
	this.leftLines += 1;
    },

    displayable: function() {
	self = this
	return( {
	    addCompRight: {
		func: this.addComponentRight.bind(this), 
		title: "Add Segment Right",
		args: [],
		input: {
		    type: 'button'
		}
	    },
	    addCompLeft: {
		func: this.addComponentLeft.bind(this),
		title: "Add Segment Left",
		args: [],
		input: {
		    type: 'button'
		}
	    }
	})
    }
});

laban.Canvas = fabric.util.createClass(fabric.Canvas, {
    margin: 100,
    strokeWidth: 3,
    addstaff: function() {	
	this.staves = this.staves || []
	var nleft = 50;
	this.staves.forEach(function(staff) {
	    nleft += staff.getWidth();
	});

	nleft += this.staves.length * this.margin * 2;
	nleft -= (this.staves.length) * this.strokeWidth * 2;
	var ntop = 0;
	var myStaff = new Staff([], {
    	    left: nleft,
    	    top: ntop,
	    strokeWidth: this.strokeWidth,
	    height: this.getHeight(),
    	    fill: 'transparent',
    	    originX: 'left',
    	    originY: 'top',
	    movx: 0,
    	    movy: 0,
	    lockMovementX: true,
	    lockMovementY: true,
    	    centeredRotation: true,
    	    name: "staff" + this.staves.length,
    	    level: 0
	});
	this.add(myStaff);
	myStaff.sendToBack();
	this.staves.push(myStaff);
	this.renderAll();
    },
    displayable: function() {
	self = this;
	return( {
	    addCompRight: {
		func: self.addstaff.bind(this), 
		title: "Add Staff",
		args: [],
		input: {
		    type: 'button'
		}
	    },
	});
    }
});