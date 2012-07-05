var flareEffect = function (parent, target, callback) {
    cc.log("flareEffect 1.................");
    var flare = cc.Sprite.create(s_flare);
    flare.setBlendFunc(new cc.BlendFunc(cc.GL_SRC_ALPHA,cc.GL_ONE));
    parent.addChild(flare, 10);
    flare.setOpacity(0);
    flare.setPosition(cc.ccp(-30, 297));
    flare.setRotation(-120);
    flare.setScale(0.2);
cc.log("flareEffect 2................");
    var opacityAnim = cc.FadeTo.create(0.5, 255);
    cc.log("flareEffect 21................");
    var opacDim = cc.FadeTo.create(1, 0);
    cc.log("flareEffect 22................");
    var biggeAnim = cc.ScaleBy.create(0.7, 1.2, 1.2);
    cc.log("flareEffect 23................");
    var biggerEase = cc.EaseSineOut.create(biggeAnim);
    cc.log("flareEffect 24................");
    var moveAnim = cc.MoveBy.create(0.5, cc.ccp(328, 0));
    cc.log("flareEffect 25................");
    var easeMove = cc.EaseSineOut.create(moveAnim);
    cc.log("flareEffect 26................");
    var rotateAnim = cc.RotateBy.create(2.5, 90);
    cc.log("flareEffect 27................");
    var rotateEase = cc.EaseExponentialOut.create(rotateAnim);
    cc.log("flareEffect 28................");
    var bigger = cc.ScaleTo.create(0.5, 1);
cc.log("flareEffect 3.................");
    var onComplete = cc.CallFunc.create(target, callback);
    var killflare = cc.CallFunc.create(flare, function () {
        this.getParent().removeChild(this, true);
    });
    cc.log("flareEffect 4.................");
    flare.runAction(cc.Sequence.create(opacityAnim, biggerEase, opacDim, killflare, onComplete));
    flare.runAction(easeMove);
    flare.runAction(rotateEase);
    flare.runAction(bigger);
    cc.log("flareEffect 5.................");

}


var spark = function (ccpoint, parent, scale, duration) {
    cc.log("spark 0.....................");
    scale = scale || 0.3;
    duration = duration || 0.5;
    var one = cc.Sprite.create(s_explode1);
    one.setBlendFunc(new cc.BlendFunc(cc.GL_SRC_ALPHA,cc.GL_ONE));
    var two = cc.Sprite.create(s_explode2);
    two.setBlendFunc(new cc.BlendFunc(cc.GL_SRC_ALPHA,cc.GL_ONE));
    var three = cc.Sprite.create(s_explode3);
    three.setBlendFunc(new cc.BlendFunc(cc.GL_SRC_ALPHA,cc.GL_ONE));
    one.setPosition(ccpoint);
    two.setPosition(ccpoint);
    three.setPosition(ccpoint);
    //parent.addChild(one);
    parent.addChild(two);
    parent.addChild(three);
    one.setScale(scale);
    two.setScale(scale);
    three.setScale(scale);
    three.setRotation(Math.random() * 360);
    var left = cc.RotateBy.create(duration, -45);
    var right = cc.RotateBy.create(duration, 45);
    var scaleBy = cc.ScaleBy.create(duration, 3, 3);
    var fadeOut = cc.FadeOut.create(duration);
    one.runAction(left);
    two.runAction(right);
    one.runAction(scaleBy);
    cc.log("spark 1.....................");
    two.runAction(scaleBy.copy());
    cc.log("spark 11.....................");
    three.runAction(scaleBy.copy());
    one.runAction(fadeOut);
    two.runAction(fadeOut.copy());
    three.runAction(fadeOut.copy());
    cc.log("setTimeout1");
    cc.Scheduler.sharedScheduler().scheduleSelector(
        function (dt) {
            cc.log("setTimeout");
            cc.Scheduler.sharedScheduler().unscheduleAllSelectorsForTarget(this);
            parent.removeChild(one, true);
            parent.removeChild(two, true);
            parent.removeChild(three, true);
        }
        , this, duration, false);
    /*
    setTimeout(function () {
        cc.log("setTimeout callback-----------------");
        parent.removeChild(one);
        parent.removeChild(two);
        parent.removeChild(three);
    }, duration * 1000);
*/
    cc.log("after set timeout");
}