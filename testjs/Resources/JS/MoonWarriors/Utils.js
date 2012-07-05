/*
 * showcasing actions
 */

/**
 * simple wrappers
 */
cc.Point.create = function (x, y) {
	var pt = new cc.Point();
	pt.x = x;
	pt.y = y;
	return pt;
};

cc.Size.create = function (w, h) {
	var sz = new cc.Size();
	sz.width = w;
	sz.height = h;
	return sz;
};

cc.Color3B.create = function(r, g, b) {
	var ret = new cc.Color3B();
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return ret;
};

cc.SizeMake = function (w, h)
{
	return cc.Size.create(w, h);
}

cc.RectMake = function (x, y, w, h) {
	var ret = new cc.Rect();
	ret.origin = cc.Point.create(x, y);
	ret.size = cc.Size.create(w, h);
	return ret;
}

/**
 * Returns the smallest rectangle that contains the two source rectangles.
 * @function
 * @param {cc.Rect}　rectA
 * @param {cc.Rect}　rectB
 * @return {cc.Rect}
 * Constructor
 */
cc.Rect.CCRectUnion = function (rectA, rectB) {
    var rect = new cc.Rect(0, 0, 0, 0);
    rect.origin.x = Math.min(rectA.origin.x, rectB.origin.x);
    rect.origin.y = Math.min(rectA.origin.y, rectB.origin.y);
    rect.size.width = Math.max(rectA.origin.x + rectA.size.width, rectB.origin.x + rectB.size.width) - rect.origin.x;
    rect.size.height = Math.max(rectA.origin.y + rectA.size.height, rectB.origin.y + rectB.size.height) - rect.origin.y;
    return rect
};

cc.BLEND_DST=771;
cc.GL_ONE=1;
cc.GL_SRC_ALPHA=770;

/**
 * text alignment : left
 * @constant
 * @type Number
 */
cc.TEXT_ALIGNMENT_LEFT = 0;

/**
 * text alignment : center
 * @constant
 * @type Number
 */
cc.TEXT_ALIGNMENT_CENTER = 1;

/**
 * text alignment : right
 * @constant
 * @type Number
 */
cc.TEXT_ALIGNMENT_RIGHT = 2;

cc.ArrayRemoveObject = function (arr, delObj) {
    for (var i = 0; i < arr.length; i++) {
        if (arr[i] == delObj) {
            arr.splice(i, 1);
        }
    }
};

cc.PointZero = function () {
	return cc.Point.create(0, 0);
}

cc.SizeZero = function () {
	return cc.Size.create(0, 0);
}


/**
 * helper macro that creates an ccColor3B type
 * @function
 * @param {Number} r red value (0 to 255)
 * @param {Number} g green value (0 to 255)
 * @param {Number} b blue value (0 to 255)
 * @return {cc.Color3B}
 */
cc.ccc3 = function (r, g, b) {
    return new cc.Color3B(r, g, b);
};


//ccColor3B predefined colors
/**
 *  White color (255,255,255)
 * @function
 * @return {cc.Color3B}
 */
cc.WHITE = function () {
    return new cc.Color3B(255, 255, 255);
};

/**
 *  Yellow color (255,255,0)
 * @function
 * @return {cc.Color3B}
 */
cc.YELLOW = function () {
    return new cc.Color3B(255, 255, 0);
};

/**
 *  Blue color (0,0,255)
 * @function
 * @return {cc.Color3B}
 */
cc.BLUE = function () {
    return new cc.Color3B(0, 0, 255);
};

/**
 *  Green Color (0,255,0)
 * @function
 * @return {cc.Color3B}
 */
cc.GREEN = function () {
    return new cc.Color3B(0, 255, 0);
};

/**
 *  Red Color (255,0,0,)
 * @function
 * @return {cc.Color3B}
 */
cc.RED = function () {
    return new cc.Color3B(255, 0, 0);
};

/**
 *  Magenta Color (255,0,255)
 * @function
 * @return {cc.Color3B}
 */
cc.MAGENTA = function () {
    return new cc.Color3B(255, 0, 255);
};

/**
 *  Black Color (0,0,0)
 * @function
 * @return {cc.Color3B}
 */
cc.BLACK = function () {
    return new cc.Color3B(0, 0, 0);
};

/**
 *  Orange Color (255,127,0)
 * @function
 * @return {cc.Color3B}
 */
cc.ORANGE = function () {
    return new cc.Color3B(255, 127, 0);
};

/**
 *  Gray Color (166,166,166)
 * @function
 * @return {cc.Color3B}
 */
cc.GRAY = function () {
    return new cc.Color3B(166, 166, 166);
};
