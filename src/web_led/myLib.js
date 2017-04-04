/* laban.util namespace is defined in laban_util.js file */

Region = fabric.util.createClass(fabric.Rect, {
    type	: "region",
    objects	: [],

    _calcBounds: function(object) {
	object.__objectPosition = new fabric.Point(object.left - object.parentRegion.left, object.top - object.parentRegion.top);
    },


    isInsideParent: function(object) {
	return (object.left >= this.left) && object.top >= this.top && (object.left + object.width) <= (this.left + this.width) && (object.top + object.height) <= (this.top + this.height);
    },
    
    _getRegionBounds: function() {
	objs	= this.objects;
	group	= new fabric.Group(objs);

	obj	= {
	    left	: Math.round(group.getLeft()),
	    top		: Math.round(group.getTop()),
	    height	: Math.round(group.getHeight()),
	    width	: Math.round(group.getWidth())
	};
	group.destroy();
	return obj;
    },

    initialize: function (options) {
	options = options || { }
	this.callSuper ("initialize", options)
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

    toObject			: function() {
	this.callSuper("toObject")
    },

    setBackgroundObj: function(obj) {
	this.backgroundObj		= obj;
	this.backgroundObj.selectable	= false;
	this.add(obj);
	obj.sendToBack && obj.sendToBack();
    },

    _updateRegionCoords: function() {
	regionCoords = this._getRegionBounds();
	this.set(regionCoords).setCoords();
	this._updateObjectCoords();
    },

    _updateObjectCoords: function() {
	objs = this.objects;
	objs.map(this._calcBounds);
    },

    _onChildMove: function(obj) {
	return function (e) {
	    obj.parentRegion && obj.parentRegion._calcBounds(obj);
	    !obj.parentRegion.isInsideParent(obj) && obj.parentRegion.remove(obj);
	}
    },

    addObject: function(obj) {
	obj.level > this.level && this.add(obj);
    },
    add: function (obj) {
	obj.on('moving', this._onChildMove(obj));
	obj.parentRegion = this;
	this.objects.push(obj)
	this._updateRegionCoords();
	obj.bringToFront();
    },

    addMultiple: function(objs) {
	objs.map(this.addObject);
    },
    shouldDestroy: function() {
	// mycanvas = this._cacheCanvas;
	// this.objects.length === 0 && mycanvas.remove(this);
    },

    remove: function(obj) {
	this.objects = this.objects.filter(function (ob) {
	    return ob !== obj;
	});
	// this.objects.pop(obj);
	obj.off('moving');
	obj.parentRegion = undefined;
	delete obj.__objectPosition;
	this.shouldDestroy();
    }
});



Staff = fabric.util.createClass(Region, {
    type: "staff",
    initialize		: function (options) {
	options = options || { }
	this.callSuper ("initialize", options)
    },

    addComponentRight	: function() {
	
    }
});
