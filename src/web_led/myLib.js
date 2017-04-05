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
	this.on('moving', function(evt) {
	    points		= new fabric.Point(this.getLeft(), this.getTop());
	    var childObjs	= this.objects;
	    laban.util.normalizeCoords(points, this.movx, this.movy);
	    childObjs && childObjs.map(function (o) {
    		leftCMove	= points.x + o.__objectPosition.x;
    		rightCMove	= points.y + o.__objectPosition.y
    		o.set({
    		    left	: leftCMove,
    		    top		: rightCMove
    		});
		o.setCoords();
	    });
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
    strokeWidth: 5,
    height: 0,
    width: 0,
    defaultLines: 3,
    
    getStaffLine: function (height, leftMargin, cnter) {
	var centerLine = new fabric.Line([leftMargin, 0, leftMargin, height], { stroke: '#f00', strokeWidth: 5, selectable: false })
	return centerLine;
    },

    initialize: function (objects, options) {
	objects = objects || []
	options = options || { }	
	this.callSuper ("initialize", objects,  options)
	this.movx = this.blockSize;
	this.generateStaff(this.defaultLines)
    },

    generateStaff: function(minStaff) {
	for (i = 0; i < minStaff; ++i)
	    this.addComponentRight()
    },

    addComponentRight: function() {
	staff = this;
	var negativeRatio =  staff.strokeWidth;
	negativeRatio = staff.getWidth() <= 5 ? negativeRatio : staff.strokeWidth * 2
	var mLeft = staff.getLeft() + staff.getWidth() + (staff.blockSize * 2) - negativeRatio;
	staff.addWithUpdate(staff.getStaffLine(staff.getHeight(), mLeft));
	staff.setCoords();
    },

    addComponentLeft: function() {
	staff = this;
	var mLeft = staff.getLeft() - (staff.blockSize * 2) ;
	staff.addWithUpdate(staff.getStaffLine(staff.getHeight(), mLeft));
	staff.setCoords();
    }

});
