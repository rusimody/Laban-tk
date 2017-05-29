/* laban.util namespace is defined in laban_util.js file */

Region = fabric.util.createClass(fabric.Group,  {
    type	: "region",
    objects	: [],

    _myCalcBounds: function(object) {
	object.__objectPosition = new fabric.Point(object.getLeft() - object.parentRegion.getLeft(), object.getTop() - object.parentRegion.getTop());
    },

    isContainedWithinObject: function(other) {
	var boundingRect = other.getBoundingRect(),
	    point1 = new fabric.Point(boundingRect.left, boundingRect.top),
	    point2 = new fabric.Point(boundingRect.left + boundingRect.width, boundingRect.top + boundingRect.height);

	return this.isContainedWithinRect(point1, point2);
    },

    isInsideParent: function(object) {
	var rect = this.getBoundingRect();
	var res = (object.getLeft() >= rect.left) && object.getTop() >= rect.top && (object.getLeft()+object.getWidth() <= (rect.left+rect.width)) && (object.getTop() + object.getHeight() <= (rect.top + rect.height));
	return res;
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
	if (obj.level <= this.level) {
	    return;
	}
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
    blockSize: 30,
    strokeWidth: 3,
    height: 0,
    width: 0,
    defaultLines: 3,
    leftLines: 0,
    blockSizeY: 50,
    rightLines: 0,
    timebars: [],
    lineHeight: 0,
    lines: [],
    updateSibs: null,
    getStaffLine: function (height, leftMargin, dashed, color) {
	var strokeDashArray = dashed ? [5,5] : [];
	var color = color || '#000'
	var centerLine = new fabric.Line([leftMargin, 0, leftMargin, height], { stroke: color,
										strokeWidth: this.strokeWidth,
										selectable: false,
										strokeDashArray: strokeDashArray})
	return centerLine;
    },

    getTimeBars: function(height, leftMargin, width, dashed, color) {
	var strokeDashArray = dashed ? [5,5] : [];
	// console.log(width,leftMargin, "Width");
	var color = color || '#000'
	var bars = []
	for (var i = 0; i < height; i += this.blockSizeY*2) {
	    // console.log(leftMargin, i, width, i);
	    var strokeWidth = i == 1 ? 5 : 1;
	    color = i == 1 ? "#000" : color;
	    var bar = new fabric.Line([leftMargin, i, width, i], { stroke: color,
								   strokeWidth: strokeWidth,
								   selectable: false,
								   strokeDashArray: strokeDashArray});
	    this.timebars.push(bar);
	    this.addWithUpdate(bar);
	    this.setCoords();
	    
	    bar.currentLeft = bar.getLeft();
	}
    },

    initialize: function (objects, options) {
	objects = objects || [];
	options = options || { };
	this.callSuper ("initialize", objects,  options)
	this.movx = this.movx == undefined || this.movx == null ? this.blockSize : this.movx;
	this.movy = this.movy == undefined || this.movy == null ? this.blockSize : this.movy;
	this.lineHeight = this.height;
	this.generateStaff();
    },
    
    generateStaff: function() {
	this.addMainLine();
	this.addComponentRight();
	this.addComponentLeft();
	var staff = this;
	var negativeRatio =  staff.strokeWidth;
	negativeRatio = staff.getWidth() <= this.strokeWidth ? negativeRatio : staff.strokeWidth * 2;
	var mLeft = staff.getLeft() + staff.getWidth() - negativeRatio;
	this.getTimeBars(this.getHeight(), staff.getLeft(), mLeft, false, '#000');
    },

    addMainLine: function(height) {
	height = this.lineHeight;
	staff = this;
	var negativeRatio =  staff.strokeWidth;
	negativeRatio = staff.getWidth() <= this.strokeWidth ? negativeRatio : staff.strokeWidth * 2;
	var mLeft = staff.getLeft() + staff.getWidth() + (staff.blockSize * 2) - negativeRatio;
	var line = staff.getStaffLine(height, mLeft, false, '#f00');
	this.lines.push(line);
	staff.addWithUpdate(line);
	staff.setCoords();
    },

    updateTimeBars: function() {
	self = this;
	var left = self.getLeft();
	self.timebars.forEach(function (bar) {
	    bar.set ({
	    	left: bar.currentLeft - self.blockSize,
		width: self.getWidth() - (self.strokeWidth * 2)
	    });
	    bar.setCoords();
	    bar.currentLeft = bar.getLeft();
	});
    },

    checkCanvasSize: function() {
	var staff = this;
	if (staff.getLeft() <= 0) {
	    staff.set({
		left: 0
	    });
	}
	staff.setCoords();
	if (staff.canvas && staff.getLeft() + staff.getWidth() > staff.canvas.getWidth())
	    staff.canvas.setWidth(staff.getLeft()+staff.getWidth());
	staff.canvas && staff.canvas.checkSiblings && staff.canvas.checkSiblings(staff);
    },

    addComponentRight: function(height) {
	height = this.lineHeight;
	staff = this;
	var negativeRatio =  staff.strokeWidth;
	negativeRatio = staff.getWidth() <= this.strokeWidth ? negativeRatio : staff.strokeWidth * 2
	var mLeft = staff.getLeft() + staff.getWidth() + (staff.blockSize * 2) - negativeRatio;
	var line = staff.getStaffLine(height, mLeft, this.rightLines % 2 == 1);
	this.lines.push(line);
	staff.addWithUpdate(line);
	staff.setCoords();
	this.rightLines += 1;
	this.updateTimeBars();
	this.checkCanvasSize();
    },

    addComponentLeft: function(height) {
	height = this.lineHeight;
	staff = this;
	var mLeft = staff.getLeft() - (staff.blockSize * 2) ;
	var line = staff.getStaffLine(height, mLeft, this.leftLines % 2 == 1);
	this.lines.push(line);
	staff.addWithUpdate(line);
	this.leftLines += 1;
	this.updateTimeBars();
	this.checkCanvasSize();
    },

    updateLineHeight: function(lineHeight) {
	var plh = this.lineHeight;
	this.lineHeight = lineHeight;
	var scaleFactor = lineHeight / this.getHeight();
	this.set({
	    height: lineHeight
	});
	this.lines.forEach(function(line) {
	    line.set({
		"y2": 1000
	    });
	    line.setCoords();
	    // console.log(line.getTop());
	    // currentHeight = line.getHeight();
	    // var mtop = (plh - lineHeight)/2+ line.getTop();
	    // line.setHeight(lineHeight);
	    // line.setTop(mtop);
	    // line.setCoords();
	    // console.log(line);
	});

	this.objects.forEach(function(object) {
	    // object.setTop((plh-lineHeight)/2 + object.getTop())
	    object.setCoords();
	});
	this.setCoords();
    },
    
    removeComponent: function() {
	this.canvas.removeObj(this);
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
	    },
	    removeStaff: {
		func: this.removeComponent.bind(this),
		title: "Remove",
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
    heightIncreaseFactor: 200,
    addstaff: function() {
	this.staves = this.staves || []
	var nleft = 50;
	this.staves.forEach(function(staff) {
	    nleft += staff.getWidth();
	});

	nleft += 200 + this.staves.length * this.margin * 2;
	nleft -= (this.staves.length) * this.strokeWidth * 2;
	var ntop = this.getHeight()-this.getHeight();
	var myStaff = new Staff([], {
    	    left: nleft,
    	    top: ntop,
	    strokeWidth: this.strokeWidth,
	    height: this.getHeight(),
    	    fill: 'transparent',
    	    originX: 'left',
    	    originY: 'bottom',
	    movx: 50,
    	    movy: 50,
	    timebars: [],
	    lockMovementX: true,
	    lockMovementY: false,
    	    centeredRotation: true,
    	    name: "staff" + this.staves.length,
    	    level: 0,
	    index: this.staves.length
	});
	this.add(myStaff);
	myStaff.sendToBack();
	this.staves.push(myStaff);
	this.renderAll();
    },
    removeObj: function(obj) {
	this.remove(obj);
	var index = this.staves.indexOf(obj);
 	var children = obj.objects;
	self = this;
	children.forEach(function (ob) {
	    self.remove(ob);
	});
	this.staves.splice(index, 1);
	prevLeft = obj.getLeft();
	for(var i = index; i < this.staves.length; ++i) {
	    tPrevLeft = this.staves[i].getLeft();
	    this.staves[i].set({
		left: prevLeft
	    });
	    prevLeft = tPrevLeft;
	    this.staves[i].setCoords();
	}
    },
    showDump: function() {
	console.log(this._objects)
    },
    zoomIn: function() {
	zoomCounter = this.zoomCounter || 1
	zoomCounter ++;
	this.zoomCounter = zoomCounter;
	this.setZoom(zoomCounter);
    },
    zoomOut: function() {
	var height = this.getHeight();
	var newHeight = height + this.heightIncreaseFactor;
	this.setHeight( newHeight);
	this.staves.forEach(function(staff) {
	    staff.setTop(newHeight);
	    staff.updateLineHeight(newHeight);
	});
    },
    checkSiblings: function(staff) {
	var currentIndex = 0;
	for (var i = currentIndex + 1; i < this.staves.length; ++i) {
	    if(this.staves[i].getLeft() - (this.staves[i-1].getLeft() + this.staves[i-1].getWidth()) <= this.margin) {
		this.staves[i].setLeft(this.staves[i].getLeft() + this.margin);
		this.staves[i].setCoords();
	    }
	    
	}
	var lastStaff = this.staves[this.staves.length-1];
	var maxWidth = lastStaff.getLeft() + lastStaff.getWidth();
	(maxWidth > this.getWidth() && (this.setWidth(maxWidth)));
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
	    // zoomOut: {
	    // 	func: self.zoomOut.bind(this),
	    // 	title: "Zoom Out",
	    // 	args: [],
	    // 	input: {
	    // 	    type: 'button'
	    // 	}
	    // },
	    // zoomIn: {
	    // 	func: self.zoomIn.bind(this),
	    // 	title: "ZoomIn",
	    // 	args: [],
	    // 	input: {
	    // 	    type: 'button'
	    // 	}
	    // },
	    showObjectsDump: {
		func: self.showDump.bind(this),
		title: "Show Dump",
		args: [],
		input: {
		    type: 'button'
		}
	    }
	});
    }
});
