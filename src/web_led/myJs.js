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
    fabricCanvas = new fabric.Canvas(properties['canvasid'], { selection: false });
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
    // setupCanvas(mainContainerId, toolbarProperties);
    /* --------------------------------DOM SETUP ENDS---------------------------- */
    
    // Temp
    drawCanvasObjects(canvas);
    
    // Event on canvas, for moving object
    canvas.on('object:moving', handleObjectMoving);
}


function drawCanvasObjects(canvas) {

    // myStaff.addComponentRight();
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
    	level: 1,
    	children: [],
	movx: 50,
	movy: 50,
    	name: "redOne"
    });
    
    var myStaff = new Staff([], {
    	left: 0,
    	top: 0,
	height: canvas.getHeight(),
    	fill: 'transparent',
    	originX: 'left',
    	originY: 'top',
	movx: 10,
    	movy: 0,
    	centeredRotation: true,
    	name: "region",
    	level: 0
    });

    canvas.add(myStaff);
    canvas.add(mObj2);
    myStaff.addObject(mObj2);


    // Button Event Handler, currently working on a static staff
    var btn = document.getElementById('add-line-left');
    btn.addEventListener('click', function() {
	myStaff.addComponentLeft();
	canvas.renderAll();
    });

    var btnright = document.getElementById('add-line-right');
    btnright.addEventListener('click', function() {
	myStaff.addComponentRight();
	canvas.renderAll();
    });

    

}
