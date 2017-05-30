// Global Declarations (Move values to config)
var defaultMoveX = 50;
var defaultMoveY = 50;
var mainContainerId = 'main-container'
var optionsContainer = 'option-bar';
var optionsbar = optionsbar || undefined;
// console.log("Require ", require);
var ENUM = {
    STAFF: 0,
    DIRN:  1,
    INFI:  100000
}


var Notations = {
    body: {
	pathbase: "laban_notations/body/",
	files: [
	    "chest.svg",
	    "down__middle_arm_gesture.svg",
	    "left_ankle.svg",
	    "left_elbow.svg",
	    "left_fingers.svg",
	    "left_finger.svg",
	    "left_foot.svg",
	    "left_high_arm_gesture.svg",
	    "left_hip.svg",
	    "left_knee.svg",
	    "left_low_leg_gesture.svg",
	    "left_middle_arm_gesture.svg",
	    "left_shoulder.svg",
	    "left_toe.svg",
	    "left_whole_foot.svg",
	    "left_wrist.svg",
	    "palm.svg",
	    "palm_upper_side.svg",
	    "up__middle_arm_gesture.svg"
	]
    },
    finger: {
	pathbase: "laban_notations/body/",
	files: [
	    "right_ankle.svg",
	    "right_elbow.svg",
	    "right_fingers.svg",
	    "right_finger.svg",
	    "right_foot.svg",
	    "right_high_arm_gesture.svg",
	    "right_hip.svg",
	    "right_knee.svg",
	    "right_low_leg_gesture.svg",
	    "right_middle_arm_gesture.svg",
	    "right_shoulder.svg",
	    "right_toe.svg",
	    "right_whole_foot.svg",
	    "right_wrist.svg"
	]
    },
    direction: {
	pathbase: "laban_notations/direction/",
	files: [
        "centre.svg",
        "left_backword_diagonal.svg",
        "left_backword.svg",
        "left_forword_diagonal.svg",
        "left_forword.svg",
        "left_side.svg",
        "right_backword_diagonal.svg",
        "right_backword.svg",
        "right_forword_diagonal.svg",
        "right_forword.svg",
        "right_side.svg"
    ]
    },
    intensity: {
        pathbase: "laban_notations/intensity/",
        files: [
            "long_1.svg",
            "long_4.svg",
            "short_1.svg",
            "short_4.svg"
        ]
    },
    others: {
        pathbase: "laban_notations/others/",
        files: [
            "inward_undulation.svg",
            "outword_undulation.svg",
            "path_back.svg",
            "path_front.svg",
            "tambaurine.svg",
            "trill.svg",
            "Untitled-18 copy.svg",
            "Untitled-19.svg",
            "Untitled-20 copy.svg",
            "Untitled-21 copy.svg",
            "Untitled-23 copy.svg",
            "Untitled-24 copy.svg",
            "Untitled-3 copy.svg",
            "Untitled-47 copy.svg",
            "Untitled-5 copy.svg",
            "Untitled-6 copy.svg",
            "Untitled-70.svg",
            "Untitled-72 copy.svg"
        ]
    },
    rotation: {
        pathbase: "laban_notations/rotation/",
        files: [
            "back_left_of_audiance.svg",
            "back_of_audiance.svg",
            "back_right_of_audiance.svg",
            "cartwheeling_left.svg",
            "cartwheeling_right.svg",
            "front_left_of_audiance.svg",
            "front_of_audiance.svg",
            "front_right_of_audiance.svg",
            "left_of_audiance.svg",
            "right_of_audiance.svg",
            "somersaulting_backward.svg",
            "somersaulting_forward.svg"
        ]
    },
    turning: {
        pathbase: "laban_notations/turning/",
        files: [
            "anticlockwise_turning.svg",
            "clockwise_turning.svg",
            "degrees_of_rotation_anticlockwise_135.svg",
            "degrees_of_rotation_anticlockwise_180.svg",
            "degrees_of_rotation_anticlockwise_225.svg",
            "degrees_of_rotation_anticlockwise_270.svg",
            "degrees_of_rotation_anticlockwise_315.svg",
            "degrees_of_rotation_anticlockwise_360.svg",
            "degrees_of_rotation_anticlockwise_45.svg",
            "degrees_of_rotation_anticlockwise_90.svg",
            "degrees_of_rotation_clockwise_135.svg",
            "degrees_of_rotation_clockwise_180.svg",
            "degrees_of_rotation_clockwise_225.svg",
            "degrees_of_rotation_clockwise_270.svg",
            "degrees_of_rotation_clockwise_315.svg",
            "degrees_of_rotation_clockwise_360.svg",
            "degrees_of_rotation_clockwise_45.svg",
            "degrees_of_rotation_clockwise_90.svg",
            "no_turn.svg"
        ]
    },
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
    console.log("objs ", objects);
    objects.forEach(function (p) {
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
	// var height = selectedElement.getHeight() / 2;
	// height = opt.e.clientY - height - 100;
	// var width = selectedElement.getWidth() / 2;
	// width = opt.e.clientX - width;
	var pointer = canvas.getPointer(opt.e);
	width = pointer.x;
	height = pointer.y;
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
    var xScale = 0.2;
    var yScale = 0.2;
    var twidth = 80;
    var theight = 130;

    var mtop = 10;
    var notationsToAdd = [];
    for (notation in Notations) {
	var pathBase = Notations[notation].pathbase;
	var mleft = 10;
	var text = tcanvas.add(new fabric.Text(notation, {
	    left: 0, //Take the block's position
	    top: mtop,
	    fontSize:30,
	    fill: 'black'
	}));
	mtop += 40;
	for(var i = 0; i < Notations[notation].files.length; ++i) {
	    var file = pathBase + Notations[notation].files[i];
	    var newNotation = {
		img: file,
		props: {
		    left: mleft,
		    top: mtop,
		    width: twidth,
		    height: theight,
		    movx: 0,
		    movy: 0,
		    scaleX: xScale,
		    scaleY: yScale,
		    lockMovementX: true,
		    lockMovementY: true,
		    lockScalingX: true,
		    lockScalingY: true,
		    hasBorders: true,
		    hasControls: false,
		    hasRotatingPoint: false
		}
	    }
	    notationsToAdd.push(newNotation);
	    mleft += 30;
	    (mleft+(80*xScale) >= tcanvas.getWidth() &&
	     (mleft = 10) &&
	     (mtop += 40));
	    (mtop + (theight * yScale) >= tcanvas.getHeight() &&
	     (tcanvas.setHeight(tcanvas.getHeight() + theight)));
	}
	mtop += 80;
    }
    notationsToAdd.forEach(function(notation) {
	fabric.Image.fromURL(notation.img, function(oImg) {
	    oImg.set(notation.props);
	    tcanvas.add(oImg);
	    tcanvas.renderAll();
	    loadedObjects.push(oImg);
	});
    });
	
    // fabric.Image.fromURL("laban_notations/direction/left_forword_diagonal.svg",function(oImg) {
    //     loadedObjects[0] = oImg;
    //     loadedObjects[0].set({
    //         left: 10,
    //         top: 20,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[0]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/left_forword.svg",function(oImg)
    // {
    //     loadedObjects[1] = oImg;
    //     loadedObjects[1].set({
    //         left: 30,
    //         top: 10,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[1]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/right_forword.svg",function(oImg)
    // {
    //     loadedObjects[2] = oImg;
    //     loadedObjects[2].set({
    //         left: 50,
    //         top: 10,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[2]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/right_forword_diagonal.svg",function(oImg)
    // {
    //     loadedObjects[3] = oImg;
    //     loadedObjects[3].set({
    //         left: 70,
    //         top: 20,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[3]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/left_side.svg",function(oImg)
    // {
    //     loadedObjects[4] = oImg;
    //     loadedObjects[4].set({
    //         left: 10,
    //         top: 55,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[4]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/centre.svg",function(oImg)
    // {
    //     loadedObjects[5] = oImg;
    //     loadedObjects[5].set({
    //         left: 40,
    //         top: 55,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[5]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/right_side.svg",function(oImg)
    // {
    //     loadedObjects[6] = oImg;
    //     loadedObjects[6].set({
    //         left: 70,
    //         top: 55,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[6]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/left_backword_diagonal.svg",function(oImg)
    // {
    //     loadedObjects[7] = oImg;
    //     loadedObjects[7].set({
    //         left: 10,
    //         top: 90,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[7]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/left_backword.svg",function(oImg)
    // {
    //     loadedObjects[8] = oImg;
    //     loadedObjects[8].set({
    //         left: 30,
    //         top: 100,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[8]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/right_backword.svg",function(oImg)
    // {
    //     loadedObjects[9] = oImg;
    //     loadedObjects[9].set({
    //         left: 50,
    //         top: 100,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[9]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/direction/right_backword_diagonal.svg",function(oImg)
    // {
    //     loadedObjects[10] = oImg;
    //     loadedObjects[10].set({
    //         left: 70,
    //         top: 90,
    //         width:80,
    //         height:130,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[10]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_hip.svg",function(oImg)
    // {
    //     loadedObjects[11] = oImg;
    //     loadedObjects[11].set({
    //         left: 105,
    //         top: 10,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[11]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_knee.svg",function(oImg)
    // {
    //     loadedObjects[12] = oImg;
    //     loadedObjects[12].set({
    //         left: 120,
    //         top: 10,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[12]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_ankle.svg",function(oImg)
    // {
    //     loadedObjects[13] = oImg;
    //     loadedObjects[13].set({
    //         left: 135,
    //         top: 10,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[13]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_foot.svg",function(oImg)
    // {
    //     loadedObjects[14] = oImg;
    //     loadedObjects[14].set({
    //         left: 150,
    //         top: 10,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[14]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_toe.svg",function(oImg)
    // {
    //     loadedObjects[15] = oImg;
    //     loadedObjects[15].set({
    //         left: 165,
    //         top: 10,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[15]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_hip.svg",function(oImg)
    // {
    //     loadedObjects[16] = oImg;
    //     loadedObjects[16].set({
    //         left: 105,
    //         top: 40,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[16]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_knee.svg",function(oImg)
    // {
    //     loadedObjects[17] = oImg;
    //     loadedObjects[17].set({
    //         left: 120,
    //         top: 40,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[17]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_ankle.svg",function(oImg)
    // {
    //     loadedObjects[18] = oImg;
    //     loadedObjects[18].set({
    //         left: 135,
    //         top: 40,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[18]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_foot.svg",function(oImg)
    // {
    //     loadedObjects[19] = oImg;
    //     loadedObjects[19].set({
    //         left: 150,
    //         top: 40,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[19]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_toe.svg",function(oImg)
    // {
    //     loadedObjects[20] = oImg;
    //     loadedObjects[20].set({
    //         left: 165,
    //         top: 40,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[20]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/palm.svg",function(oImg)
    // {
    //     loadedObjects[21] = oImg;
    //     loadedObjects[21].set({
    //         left: 115,
    //         top: 70,
    //         width:85,
    //         height:104,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[21]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/palm_upper_side.svg",function(oImg)
    // {
    //     loadedObjects[22] = oImg;
    //     loadedObjects[22].set({
    //         left: 145,
    //         top: 70,
    //         width:82,
    //         height:104,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[22]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_shoulder.svg",function(oImg)
    // {
    //     loadedObjects[11] = oImg;
    //     loadedObjects[11].set({
    //         left: 105,
    //         top: 100,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[11]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_elbow.svg",function(oImg)
    // {
    //     loadedObjects[12] = oImg;
    //     loadedObjects[12].set({
    //         left: 120,
    //         top: 100,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[12]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_wrist.svg",function(oImg)
    // {
    //     loadedObjects[13] = oImg;
    //     loadedObjects[13].set({
    //         left: 135,
    //         top: 100,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[13]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_finger.svg",function(oImg)
    // {
    //     loadedObjects[14] = oImg;
    //     loadedObjects[14].set({
    //         left: 150,
    //         top: 100,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[14]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/right_fingers.svg",function(oImg)
    // {
    //     loadedObjects[15] = oImg;
    //     loadedObjects[15].set({
    //         left: 165,
    //         top: 100,
    //         width:30,
    //         height:107,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[15]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_shoulder.svg",function(oImg)
    // {
    //     loadedObjects[16] = oImg;
    //     loadedObjects[16].set({
    //         left: 105,
    //         top: 130,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[16]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_elbow.svg",function(oImg)
    // {
    //     loadedObjects[17] = oImg;
    //     loadedObjects[17].set({
    //         left: 120,
    //         top: 130,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[17]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_wrist.svg",function(oImg)
    // {
    //     loadedObjects[18] = oImg;
    //     loadedObjects[18].set({
    //         left: 135,
    //         top: 130,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[18]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_finger.svg",function(oImg)
    // {
    //     loadedObjects[19] = oImg;
    //     loadedObjects[19].set({
    //         left: 150,
    //         top: 130,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[19]);
    //     tcanvas.renderAll();
    // });

    // fabric.Image.fromURL("laban_notations/body/left_fingers.svg",function(oImg)
    // {
    //     loadedObjects[20] = oImg;
    //     loadedObjects[20].set({
    //         left: 165,
    //         top: 130,
    //         width:34,
    //         height:123,
    //         movx: 0,
    //         movy: 0,
    //         scaleX: 0.2,
    //         scaleY: 0.2,
    //         lockMovementX: true,
    //         lockMovementY: true,
    //         lockScalingX: true,
    //         lockScalingY: true,
    //         hasBorders: true,
    //         hasControls: false,
    //         hasRotatingPoint: false
    //     });
    //     tcanvas.add(loadedObjects[20]);
    //     tcanvas.renderAll();
    // });
}