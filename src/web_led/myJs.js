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
    fabricCanvas.setHeight( container.offsetHeight );
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


function addObjectEvent(canvas) {
    return (function (options) {
	target = options.target;
	checkForParent(canvas, target);
    });
}
function checkForParent(canvas, object) {
    var currentObjLevel = object.level || ENUM.INFI;
    currentObjLevel = object.level === 0 ? 0 : currentObjLevel;
    object.level = currentObjLevel;
    var objects = canvas.getObjects();
    // console.log(objects);
    objects = objects.filter(function (o) {
    	return o.level < currentObjLevel && o.isInsideParent;
    });
    // console.log("objs ", objects);
    objects.forEach(function (p) {
	// console.log("Adding Object here ", p.isInsideParent(object));
    	p.isInsideParent(object) && p.addObject(object);
    });
}


function handleObjectMoving(canvas) {
    return (function(options) {
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
	object.setCoords();
	
	checkForParent(canvas, object);
    })
}

var selectedElement = null;
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
    var toolbar = setupCanvas(mainContainerId, toolbarProperties);
    /* --------------------------------DOM SETUP ENDS---------------------------- */
    
    // Temp
    drawCanvasObjects(canvas);
    toolbarDraw(toolbar);
    
    
    // Initialize Events for canvas
    canvas.on('object:moving', handleObjectMoving(canvas));
    canvas.on('object:selected', getOptionsAdder(canvas));
    canvas.on('object:added', addObjectEvent(canvas));
    canvas.on('selection:cleared', function(e) {
	var target = canvas;
	clearOptionsBar();
	var displayables = target.displayable()
	manageOptions(displayables, target);
    });

    canvas.on('mouse:down', function (opt) {
	if (!selectedElement) return;
	toolbar.deactivateAll().renderAll();
	var height = selectedElement.getHeight() / 2;
	height = opt.e.clientY - height - 100;
	var width = selectedElement.getWidth() / 2;
	width = opt.e.clientX - width;
	op = {
	    target: selectedElement
	}
	selectedElement.set ({
	    left: width,
	    top: height 
	});
	selectedElement.setCoords();
	canvas.add(selectedElement);
	
	// console.log("left ", selectedElement.getLeft());
	canvas.setActiveObject(selectedElement);
	selectedElement = null;
    });
    // toolbar.on('object:selected', getOptionsAdder(toolbar));    
    toolbar.on('object:selected', function(opt) {
	// selectedElement = 
	opt.target.clone(function (clone) {
	    selectedElement = clone;
	    clone.set (
		{
		    lockMovementX: false,
		    lockMovementY: false,
		    lockScalingX: true,
    		    movx: 10,
    		    movy: 10,
		    scaleX: 0.4,
		    scaleY: 0.4,
		    hasControls: true,
		    level: 1
		}
	    );
	});
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

// function getOptionsAdder(canvas) {
//     return (function (opt) {
// 	console.log(opt.target);
// 	var target = opt.target;
//     });
// }


function getOptionsAdder(canvas) {
    return (function (opt) {
	var target = opt.target;
	// console.log(target);
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
    // var mObj2 = new fabric.Rect({
    // 	left: 100,
    // 	top: 50,
    // 	width: 50,
    // 	height: 50,
    // 	fill: 'transparent',
    // 	stroke: 'red',
    // 	strokeWidth: 3,
    // 	originX: 'left',
    // 	originY: 'top',
    // 	centeredRotation: true,
    // 	level: 1,
    // 	children: [],
    // 	movx: 50,
    // 	movy: 50,
    // 	name: "redOne"
    // });
    // canvas.add(mObj2);
}

function toolbarDraw(tcanvas) {
    // var tcanvas = new fabric.Canvas('toolbar', { selection: false });
    var loadedObjects = [];
    

    fabric.Image.fromURL("laban_notations/direction/left_forword_diagonal.svg",function(oImg) {
        loadedObjects[0] = oImg;
        loadedObjects[0].set({
            left: 10,
            top: 20,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[0]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/left_forword.svg",function(oImg)
    {
        loadedObjects[1] = oImg;
        loadedObjects[1].set({
            left: 30,
            top: 10,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[1]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/right_forword.svg",function(oImg)
    {
        loadedObjects[2] = oImg;
        loadedObjects[2].set({
            left: 50,
            top: 10,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[2]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/right_forword_diagonal.svg",function(oImg)
    {
        loadedObjects[3] = oImg;
        loadedObjects[3].set({
            left: 70,
            top: 20,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[3]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/left_side.svg",function(oImg)
    {
        loadedObjects[4] = oImg;
        loadedObjects[4].set({
            left: 10,
            top: 55,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[4]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/centre.svg",function(oImg)
    {
        loadedObjects[5] = oImg;
        loadedObjects[5].set({
            left: 40,
            top: 55,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[5]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/right_side.svg",function(oImg)
    {
        loadedObjects[6] = oImg;
        loadedObjects[6].set({
            left: 70,
            top: 55,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[6]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/left_backword_diagonal.svg",function(oImg)
    {
        loadedObjects[7] = oImg;
        loadedObjects[7].set({
            left: 10,
            top: 90,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[7]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/left_backword.svg",function(oImg)
    {
        loadedObjects[8] = oImg;
        loadedObjects[8].set({
            left: 30,
            top: 100,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[8]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/right_backword.svg",function(oImg)
    {
        loadedObjects[9] = oImg;
        loadedObjects[9].set({
            left: 50,
            top: 100,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[9]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/direction/right_backword_diagonal.svg",function(oImg)
    {
        loadedObjects[10] = oImg;
        loadedObjects[10].set({
            left: 70,
            top: 90,
            width:80,
            height:130,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[10]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_hip.svg",function(oImg)
    {
        loadedObjects[11] = oImg;
        loadedObjects[11].set({
            left: 105,
            top: 10,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[11]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_knee.svg",function(oImg)
    {
        loadedObjects[12] = oImg;
        loadedObjects[12].set({
            left: 120,
            top: 10,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[12]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_ankle.svg",function(oImg)
    {
        loadedObjects[13] = oImg;
        loadedObjects[13].set({
            left: 135,
            top: 10,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[13]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_foot.svg",function(oImg)
    {
        loadedObjects[14] = oImg;
        loadedObjects[14].set({
            left: 150,
            top: 10,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[14]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_toe.svg",function(oImg)
    {
        loadedObjects[15] = oImg;
        loadedObjects[15].set({
            left: 165,
            top: 10,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[15]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_hip.svg",function(oImg)
    {
        loadedObjects[16] = oImg;
        loadedObjects[16].set({
            left: 105,
            top: 40,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[16]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_knee.svg",function(oImg)
    {
        loadedObjects[17] = oImg;
        loadedObjects[17].set({
            left: 120,
            top: 40,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[17]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_ankle.svg",function(oImg)
    {
        loadedObjects[18] = oImg;
        loadedObjects[18].set({
            left: 135,
            top: 40,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[18]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_foot.svg",function(oImg)
    {
        loadedObjects[19] = oImg;
        loadedObjects[19].set({
            left: 150,
            top: 40,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[19]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_toe.svg",function(oImg)
    {
        loadedObjects[20] = oImg;
        loadedObjects[20].set({
            left: 165,
            top: 40,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[20]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/palm.svg",function(oImg)
    {
        loadedObjects[21] = oImg;
        loadedObjects[21].set({
            left: 115,
            top: 70,
            width:85,
            height:104,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[21]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/palm_upper_side.svg",function(oImg)
    {
        loadedObjects[22] = oImg;
        loadedObjects[22].set({
            left: 145,
            top: 70,
            width:82,
            height:104,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[22]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_shoulder.svg",function(oImg)
    {
        loadedObjects[11] = oImg;
        loadedObjects[11].set({
            left: 105,
            top: 100,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[11]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_elbow.svg",function(oImg)
    {
        loadedObjects[12] = oImg;
        loadedObjects[12].set({
            left: 120,
            top: 100,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[12]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_wrist.svg",function(oImg)
    {
        loadedObjects[13] = oImg;
        loadedObjects[13].set({
            left: 135,
            top: 100,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[13]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_finger.svg",function(oImg)
    {
        loadedObjects[14] = oImg;
        loadedObjects[14].set({
            left: 150,
            top: 100,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[14]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/right_fingers.svg",function(oImg)
    {
        loadedObjects[15] = oImg;
        loadedObjects[15].set({
            left: 165,
            top: 100,
            width:30,
            height:107,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[15]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_shoulder.svg",function(oImg)
    {
        loadedObjects[16] = oImg;
        loadedObjects[16].set({
            left: 105,
            top: 130,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[16]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_elbow.svg",function(oImg)
    {
        loadedObjects[17] = oImg;
        loadedObjects[17].set({
            left: 120,
            top: 130,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[17]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_wrist.svg",function(oImg)
    {
        loadedObjects[18] = oImg;
        loadedObjects[18].set({
            left: 135,
            top: 130,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[18]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_finger.svg",function(oImg)
    {
        loadedObjects[19] = oImg;
        loadedObjects[19].set({
            left: 150,
            top: 130,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[19]);
        tcanvas.renderAll();
    });

    fabric.Image.fromURL("laban_notations/body/left_fingers.svg",function(oImg)
    {
        loadedObjects[20] = oImg;
        loadedObjects[20].set({
            left: 165,
            top: 130,
            width:34,
            height:123,
            movx: 0,
            movy: 0,
            scaleX: 0.2,
            scaleY: 0.2,
            lockMovementX: true,
            lockMovementY: true,
            lockScalingX: true,
            lockScalingY: true,
            hasBorders: true,
            hasControls: false,
            hasRotatingPoint: false
        });
        tcanvas.add(loadedObjects[20]);
        tcanvas.renderAll();
    });
}
