// Global Declarations (Move values to config)
var defaultMoveX = 50;
var defaultMoveY = 50;
var mainContainerId = 'main-container'
var optionsContainer = 'option-bar';
var optionsbar = optionsbar || undefined;
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
    fabricCanvas = new laban.Canvas(properties['canvasid'], { selection: false });
    fabricCanvas.setWidth( container.offsetWidth  );
    fabricCanvas.setHeight( container.offsetHeight  );
    fabricCanvas.renderAll();
    return fabricCanvas;
}

function generateStaff(width, height, blockSize) {
    var leftLine = new fabric.Line([ 0, 0, 0, height], { stroke: '#000', strokeWidth: 5, selectable: false });
    var rightLine = new fabric.Line([blockSize * 4, 0, blockSize * 4, height], { stroke: '#000', strokeWidth: 5, selectable: false });
    var centerLine = new fabric.Line([blockSize * 2, 0, blockSize * 2, height], { stroke: '#000', strokeWidth: 5, selectable: false })
    var staffGroup = new fabric.Group([leftLine, rightLine, centerLine], {movx: 50, movy: 50, selectable: false});
    return staffGroup;
}



function handleObjectMoving(options) {
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
}

window.onload = function() {
    /* --------------------------------DOM SETUP STARTS---------------------------- */    // setup
    var properties = {
	canvasid	: 'laban-editor',
	containerclass	: 'container led'
    }
    var canvas = setupCanvas('main-container', properties);

    var toolbarProperties = {
	canvasid	: 'toolbar',
	containerclass	: 'container toolbar'
    }

    optionsbar = document.getElementById('option-container');
    setupCanvas(mainContainerId, toolbarProperties);
    /* --------------------------------DOM SETUP ENDS---------------------------- */
    
    // Temp
    drawCanvasObjects(canvas);
    // toolbarDraw();
    
    // Initialize Events for canvas
    canvas.on('object:moving', handleObjectMoving);
    canvas.on('object:selected', getOptionsAdder(canvas));    
    canvas.on('selection:cleared', function(e) {
	var target = canvas;
	clearOptionsBar();
	var displayables = target.displayable()
	manageOptions(displayables, target);
    });


    // Explicit fire event 'selection:cleared'
    // to generate options for canvas at load time
    canvas.fire('selection:cleared');
   
}



var selectedObject = null;

function clearOptionsBar() {
    while(optionsbar.firstChild) {
	optionsbar.removeChild(optionsbar.firstChild);
    }
}

function manageOptions(options, canvas) {
    for(var option in options) {
	var object = options[option];
	var input = document.createElement('input');
	input.setAttribute('type', object.input.type);
	input.setAttribute('value', object.title);
	input.setAttribute('id', option);
	input.setAttribute('class', 'btnflt4');
	input.clickFunc = object.func;
	input.addEventListener('click', function(e) {
	    e.target.clickFunc  && e.target.clickFunc();
	    canvas.renderAll();
	});
	optionsbar.appendChild(input);
    }
}
function getOptionsAdder(canvas) {

    return (function (opt) {
	var target = opt.target;
	console.log("Selected Object ", target.name);
	clearOptionsBar();
	if (!target.displayable)
	    return;
	var displayables = target.displayable && target.displayable();
	displayables && manageOptions(displayables, canvas);
	// for(var option in displayables) {
	//     var object = displayables[option];
	//     var input = document.createElement('input');
	//     input.setAttribute('type', object.input.type);
	//     input.setAttribute('value', object.title);
	//     input.setAttribute('id', option);
	//     input.clickFunc = object.func;
	//     input.addEventListener('click', function(e) {
	// 	e.target.clickFunc  && e.target.clickFunc();
	// 	canvas.renderAll();
	//     });
	//     optionsbar.appendChild(input);
	// }
    });
}

function drawCanvasObjects(canvas) {
    var mObj2 = new fabric.Rect({
    	left: 100,
    	top: 50,
    	width: 50,
    	height: 50,
    	fill: 'transparent',
    	stroke: 'red',
    	strokeWidth: 3,
    	originX: 'left',
    	originY: 'top',
    	centeredRotation: true,
    	level: 1,
    	children: [],
    	movx: 50,
    	movy: 50,
    	name: "redOne"
    });
    canvas.add(mObj2);
}

// function toolbarDraw() {
//     var tcanvas = new fabric.Canvas('toolbar', { selection: false });
//     var loadedObjects = [];

//     fabric.Image.fromURL("laban_notations/Direction/left_forword_diagonal.svg",function(oImg) {
//         loadedObjects[0] = oImg;
//         loadedObjects[0].set({
//             left: 10,
//             top: 20,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[0]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/right_forword.svg",function(oImg)
//     {
//         loadedObjects[1] = oImg;
//         loadedObjects[1].set({
//             left: 30,
//             top: 10,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[1]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/left_forword.svg",function(oImg)
//     {
//         loadedObjects[2] = oImg;
//         loadedObjects[2].set({
//             left: 50,
//             top: 10,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[2]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/right_forword_diagonal.svg",function(oImg)
//     {
//         loadedObjects[3] = oImg;
//         loadedObjects[3].set({
//             left: 70,
//             top: 20,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[3]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/left_side.svg",function(oImg)
//     {
//         loadedObjects[4] = oImg;
//         loadedObjects[4].set({
//             left: 10,
//             top: 55,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[4]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/centre.svg",function(oImg)
//     {
//         loadedObjects[5] = oImg;
//         loadedObjects[5].set({
//             left: 35,
//             top: 47,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.3,
//             scaleY: 0.3,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[5]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/right_side.svg",function(oImg)
//     {
//         loadedObjects[6] = oImg;
//         loadedObjects[6].set({
//             left: 70,
//             top: 55,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[6]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/left_backword_diagonal.svg",function(oImg)
//     {
//         loadedObjects[7] = oImg;
//         loadedObjects[7].set({
//             left: 10,
//             top: 90,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[7]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/right_backword.svg",function(oImg)
//     {
//         loadedObjects[8] = oImg;
//         loadedObjects[8].set({
//             left: 30,
//             top: 100,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[8]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/left_backword.svg",function(oImg)
//     {
//         loadedObjects[9] = oImg;
//         loadedObjects[9].set({
//             left: 50,
//             top: 100,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[9]);
//         tcanvas.renderAll();
//     });

//     fabric.Image.fromURL("laban_notations/Direction/right_backword_diagonal.svg",function(oImg)
//     {
//         loadedObjects[10] = oImg;
//         loadedObjects[10].set({
//             left: 70,
//             top: 90,
//             width:80,
//             height:130,
//             movx: 0,
//             movy: 0,
//             scaleX: 0.2,
//             scaleY: 0.2,
//             lockMovementX: true,
//             lockMovementY: true,
//             lockScalingX: true,
//             lockScalingY: true,
//             hasBorders: true,
//             hasControls: true,
//             hasRotatingPoint: false
//         });
//         tcanvas.add(loadedObjects[10]);
//         tcanvas.renderAll();
//     });
// }
