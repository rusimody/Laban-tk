// Global Declarations (Move values to config)
var defaultMoveX = 50;
var defaultMoveY = 50;
var mainContainerId = 'main-container'

var ENUM = {
    STAFF: 0,
    DIRN:  1,
    INFI:  100000
}


// static code
function setupCanvas(mContainerId, properties) {
    mainContainer = document.getElementById(mContainerId);
    container = document.createElement('div');
    canvas = document.createElement('canvas');
    container.setAttribute('class', properties['containerclass']);
    canvas.setAttribute('id', properties['canvasid']);
    container.appendChild(canvas);
    mainContainer.appendChild(container);
    canvas.width = container.offsetWidth - 20;
    canvas.height = container.offsetHeight - 20;
}

function generateStaff(width, height, blockSize) {
    var leftLine = new fabric.Line([ 0, 0, 0, height], { stroke: '#000', strokeWidth: 5, selectable: false });
    var rightLine = new fabric.Line([blockSize * 4, 0, blockSize * 4, height], { stroke: '#000', strokeWidth: 5, selectable: false });
    var centerLine = new fabric.Line([blockSize * 2, 0, blockSize * 2, height], { stroke: '#000', strokeWidth: 5, selectable: false })
    var staffGroup = new fabric.Group([leftLine, rightLine, centerLine], {movx: 50, movy: 50, selectable: false});
    return staffGroup;
}


window.onload = function() {
    /* --------------------------------DOM SETUP STARTS---------------------------- */    // setup
    var properties = {
	canvasid	: 'laban-editor',
	containerclass	: 'container led'
    }
    setupCanvas('main-container', properties);

    var toolbarProperties = {
	canvasid	: 'toolbar',
	containerclass	: 'container toolbar'
    }
    setupCanvas(mainContainerId, toolbarProperties);
    /* --------------------------------DOM SETUP ENDS---------------------------- */

    /* Get Canvas */
    var canvas = new fabric.Canvas('laban-editor', { selection: false });

    // Temp
    drawCanvasObjects(canvas);
   

    canvas.on('object:moving', function(options) {
	var object = options.target;
	points = new fabric.Point(object.getLeft(), object.getTop());
	points = laban.util.normalizeCoords(points, object.movx, object.movy);	
	object.set({
	    left: points.x,
	    top: points.y
	});

	if(object.parentRegion) {
	    return;
	}
	
	var currentObjLevel = object.level || ENUM.INFI;
	currentObjLevel = object.level === 0 ? 0 : currentObjLevel;
	object.level = currentObjLevel;
	var objects = this.getObjects();
	objects = objects.filter(function (o) {
	    return o.level < currentObjLevel && o.isInsideParent
	});
	
	objects.forEach(function (p) {
	    p.isInsideParent(object) && p.addObject(object);
	});
    });
}


function drawCanvasObjects(canvas) {
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
}

function toolbarDraw() {
    
    //////////////////////////////////////////////            TOOLBAR             /////////////////////////////////////////////
    // var tcanvas = new fabric.Canvas('toolbar', { selection: false });
    // cWidth = tcanvas.getWidth();
    // cHeight = tcanvas.getHeight();

    // tWidth = cWidth * 0.9;
    // tHeight = cHeight;
    // tLeft = cWidth - tWidth - 5;
    // tTop = cHeight - tHeight;
    // var Toolbar = new Region({
    // 	left: tLeft,
    // 	top: tTop,
    // 	width: tWidth,
    // 	height: tHeight,
    // 	fill: 'transparent',
    // 	stroke: 'green',
    // 	strokeWidth: 5,
    // 	originX: 'left',
    // 	originY: 'top',
    // 	centeredRotation: true,
    // 	movx: 0,
    // 	movy: 0,
    // 	name: "region"
    // });

    // var toolWindow = new Region({

    // });

    // tcanvas.add(Toolbar);
    // var mObj3 = new fabric.Rect({
    // 	left: 200,
    // 	top: 50,
    // 	width: 50,
    // 	height: 50,
    // 	fill: 'transparent',
    // 	stroke: 'black',
    // 	strokeWidth: 5,
    // 	originX: 'left',
    // 	originY: 'top',
    // 	centeredRotation: true,
    // 	movx: 10,
    // 	movy: 10,
    // 	level: 0,
    // 	children: [],
    // 	name: "blackOne"
    // });
    // tcanvas.add(mObj3);

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


    /* 
     */
}
