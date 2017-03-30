// Global Declarations (Move values to config)
var defaultMoveX = 50;
var defaultMoveY = 50;


// Region: Extends Rectangle Object
// Work:   Parent for multiple objects in canvas, children moves along with the parent
// TODO:::::::
// 1. Move moving logic from common inside region - P4 - Done
// 2. Handle Overlap Conditions - P3
// 3. JSON Generation - P1 - Test
// 4. Subscribe to parent - P0 - Done
// 5. leave parent region and look for new one - P0 - Done
// 6. Region should be deleted if there's no children left inside region - P4
// 7. Moving objects should not go outside of the canvas - P3 - Done (bad code, but working)
// 8. Create Toolbar

var ENUM = {
    STAFF: 0,
    DIRN:  1,
    INFI:  100000
}
Region = fabric.util.createClass(fabric.Rect, {
    type: "region",
    objects: [],

    _calcBounds: function(object) {
	object.__objectPosition = new fabric.Point(object.left - object.parentRegion.left, object.top - object.parentRegion.top);
    },

    isInsideParent: function(object) {

	return (object.left >= this.left) && object.top >= this.top && (object.left + object.width) <= (this.left + this.width) && (object.top + object.height) <= (this.top + this.height);
    },
    _getRegionBounds: function() {
	objs = this.objects;

	group = new fabric.Group(objs);

	obj = {
	    left: Math.round(group.getLeft()),
	    top: Math.round(group.getTop()),
	    height:Math.round(group.getHeight()),
	    width: Math.round(group.getWidth())
	};
	group.destroy();
	return obj;
    },

    initialize: function (options) {
	options = options || { }
	this.callSuper ("initialize", options)
	this.objects = []

	this.on('moving', function(evt) {

	    var xMoveRate = defaultMoveX;
	    var yMoveRate = defaultMoveY;
	    leftMove = Math.round(this.left / xMoveRate) * xMoveRate;
	    topMove = Math.round(this.top / yMoveRate) * yMoveRate;
	    var childObjs = this.objects;
	    childObjs && childObjs.map(function (o) {
    		leftCMove = leftMove + o.__objectPosition.x;
    		rightCMove = topMove + o.__objectPosition.y
    		o.set({
    		    left: leftCMove,
    		    top: rightCMove
    		});
		o.setCoords();
	    });
	});
    },

    toObject: function() {
	this.callSuper("toObject")
    },

    _updateRegionCoords: function() {
	regionCoords = this._getRegionBounds();
	this.set(regionCoords).setCoords();
	// canvas.renderAll();
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


// Staff = fabric.util.createClass(fabric.Region, {
//     type: "staff",
//     objects: [],
//     initialize: function (options) {
// 	options = options || { }
// 	this.callSuper ("initialize", options)
//     }
// };

var canvas = new fabric.Canvas('c', { selection: false });


// To-do: Remove this method and add objects to canvas by default from region's code
function generateStaff(width, height, blockSize) {
    var leftLine = new fabric.Line([ 0, 0, 0, height], { stroke: '#000', strokeWidth: 5, selectable: false });
    var rightLine = new fabric.Line([blockSize * 4, 0, blockSize * 4, height], { stroke: '#000', strokeWidth: 5, selectable: false });
    var centerLine = new fabric.Line([blockSize * 2, 0, blockSize * 2, height], { stroke: '#000', strokeWidth: 5, selectable: false })
    var staffGroup = new fabric.Group([leftLine, rightLine, centerLine], {movx: 50, movy: 50, selectable: false});
    return staffGroup;
}


var staff = generateStaff(canvas.getWidth(), canvas.getHeight(), 50);
canvas.add(staff);


var mObj2 = new fabric.Rect({
    left: 100,
    top: 50,
    width: 50,
    height: 50,
    fill: 'transparent',
    stroke: 'red',
    strokeWidth: 5,
    originX: 'left',
    originY: 'top',
    centeredRotation: true,
    movx: 10,
    movy: 10,
    level: 1,
    children: [],
    name: "redOne"
});




var group2 = new Region({
    left: 50,
    top: 50,
    width: 500,
    height: 500,
    fill: 'transparent',
    stroke: 'green',
    strokeWidth: 5,
    originX: 'left',
    originY: 'top',
    centeredRotation: true,
    movx: 50,
    movy: 0,
    name: "region",
    level: 0
});

canvas.add(group2);
canvas.add(mObj2);
group2.add(staff);
group2.add(mObj2);
// canvas.add(mObj2);
// canvas.add(mObj3);
// group2.addObject(mObj3);
// group2.addObject(mObj2);



canvas.on('object:mouseup', function(options) {

});

// snap to grid
canvas.on('object:moving', function(options) {
    var xMoveRate = options.target.movx || defaultMoveX;
    var yMoveRate = options.target.movy || defaultMoveY;
    leftMove = options.target.movx == 0 ? 0 : Math.round(options.target.left / xMoveRate) * xMoveRate;
    topMove = options.target.movy == 0 ? 0 : Math.round(options.target.top / yMoveRate) * yMoveRate;
    //


    var canvasObj = new fabric.Canvas('c', { selection: false });
    cnvWidth = canvasObj.getWidth();
    cnvHeight = canvasObj.getHeight();
    targetHeight = options.target.height;
    targetWidth = options.target.width;
    if(leftMove < 0)
	leftMove = 0
    if(leftMove > cnvWidth - targetWidth)
	leftMove = cnvWidth - targetWidth - 10; // -10 is for considering border
    if(topMove < 0)
	topMove = 0
    if(topMove > cnvHeight - targetWidth){
	topMove = cnvHeight - targetHeight -10; // -10 is for considering border
    }
    console.log(cnvWidth, leftMove, cnvHeight, topMove);
    console.log(targetWidth, targetHeight);
    
    //
    options.target.set({
	left: leftMove,
	top: topMove
    });

    if(options.target.parentRegion) {
	return;
    }
    var currentObjLevel = options.target.level || ENUM.INFI;
    currentObjLevel = options.target.level === 0 ? 0 : currentObjLevel;
    var objects = canvas.getObjects();
    objects = objects.filter(function (o) {
	return o.level < currentObjLevel
    });
    obj = options.target;
    objects.forEach(function (p) {
	p.isInsideParent(obj) && p.addObject(obj);
    });
});





























//////////////////////////////////////////////            TOOLBAR             /////////////////////////////////////////////
var tcanvas = new fabric.Canvas('tCanvas', { selection: false });
cWidth = tcanvas.getWidth();
cHeight = tcanvas.getHeight();

tWidth = cWidth * 0.9;
tHeight = cHeight;
tLeft = cWidth - tWidth - 5;
tTop = cHeight - tHeight;
var Toolbar = new Region({
    left: tLeft,
    top: tTop,
    width: tWidth,
    height: tHeight,
    fill: 'transparent',
    stroke: 'green',
    strokeWidth: 5,
    originX: 'left',
    originY: 'top',
    centeredRotation: true,
    movx: 0,
    movy: 0,
    name: "region"
});

var toolWindow = new Region({

});

tcanvas.add(Toolbar);
var mObj3 = new fabric.Rect({
    left: 200,
    top: 50,
    width: 50,
    height: 50,
    fill: 'transparent',
    stroke: 'black',
    strokeWidth: 5,
    originX: 'left',
    originY: 'top',
    centeredRotation: true,
    movx: 10,
    movy: 10,
    level: 0,
    children: [],
    name: "blackOne"
});
tcanvas.add(mObj3);

/* canvas.on('mouse:down', function(options) {
    selectedObject = tcanvas.getActiveObject();

    if(!selectedObject)
	return;
    left = options.e.pageX;
    topx = options.e.pageY;
    canvas.add(tcanvas.getActiveObject());
    selectedObject.set({
	left: left,
	top: topx
    });
    selectedObject.setCoords();

    tcanvas.deactivateAll().renderAll();

}); */
