var laban = laban || { version : '0' }

laban.util = {
    normalizeCoords: function(points, movx, movy) {
	var xMoveRate	= movx || 0;
	var yMoveRate	= movy || 0;
	movx		= movx || 0;
	movy		= movy || 0;
	points.x	= movx === 0 ? 0 : Math.round(points.x / xMoveRate) * xMoveRate;
	points.y	= movy === 0 ? 0 : Math.round(points.y / yMoveRate) * yMoveRate;
	return points;
    }
};
