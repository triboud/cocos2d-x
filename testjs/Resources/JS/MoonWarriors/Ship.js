var Ship = function () {
    var selfPointer = this;
    this.model = null;
    this._timeTick = 0;
    this.speed = 220;
    this.bulletSpeed = 900;
    this.HP = 10;
    this.bulletTypeValue = 1;
    this.bulletPowerValue = 1;
    this.throwBombing = false;
    this.canBeAttack = true;
    this.isThrowingBomb = false;
    this.zOrder = 3000;
    this.maxBulletPowerValue = 4;
    this.appearPosition = cc.ccp(160, 60);
    this._hurtColorLife = 0;
    this.active = true;
    this.ctor = function () {
        //init life
        cc.log("Ship 1....................");
        var shipTexture = cc.TextureCache.sharedTextureCache().addImage(s_ship01);
        this.model = cc.Sprite.create(shipTexture, cc.RectMake(0, 0, 60, 38));
        //this.model.initWithTexture(shipTexture, cc.RectMake(0, 0, 60, 38));
        this.model.setTag(this.zOrder);
        this.model.setPosition(this.appearPosition);
cc.log("Ship 2....................");
        // set frame
        var animation = cc.Animation.create(null, 0.1);
        cc.log("Ship 21....................");
        animation.addSpriteFrameWithTexture(shipTexture, cc.RectMake(0, 0, 60, 38));
        animation.addSpriteFrameWithTexture(shipTexture, cc.RectMake(60, 0, 60, 38));
cc.log("Ship 22....................");
        // ship animate
        var action = cc.Animate.create(animation);
        this.model.runAction(cc.RepeatForever.create(action));
        cc.Scheduler.sharedScheduler().scheduleSelector(this.shoot, this, 1 / 6, false);
cc.log("Ship 3....................");
        //revive effect
        this.canBeAttack = false;
        var ghostSprite = cc.Sprite.create(shipTexture, cc.RectMake(0, 45, 60, 38));
        cc.log("Ship 31....................");
        this.model.setBlendFunc(new cc.BlendFunc(cc.GL_SRC_ALPHA, cc.GL_ONE));
        ghostSprite.setScale(8);
        cc.log("Ship 32....................");
        ghostSprite.setPosition(cc.ccp(this.model.getContentSize().width / 2, 12));
        this.model.addChild(ghostSprite, 3000, 99999);
        cc.log("Ship 33....................");
        ghostSprite.runAction(cc.ScaleTo.create(0.5, 1, 1));
        cc.log("Ship 34....................");
        var blinks = cc.Blink.create(3, 9);
        cc.log("Ship 35....................");
        var makeBeAttack = cc.CallFunc.create(this, function (t) {
            selfPointer.canBeAttack = true;
            selfPointer.model.setIsVisible(true);
            selfPointer.model.removeChild(ghostSprite, true);
        });
        cc.log("Ship 4....................");
        this.model.runAction(cc.Sequence.create(cc.DelayTime.create(0.5), blinks, makeBeAttack));
    };
    this.update = function (dt) {
        cc.log("ship update dt = "+dt);
        if (this.HP <= 0) {
            this.active = false;
        }
        this._timeTick += dt;
        if (this._timeTick > 0.1) {
            this._timeTick = 0;
            if (this._hurtColorLife > 0) {
                this._hurtColorLife--;
            }
            if (this._hurtColorLife == 1) {
                cc.log("ship set color");
                this.model.setColor(new cc.Color3B(255, 255, 255));
                cc.log("ship set color end");
            }
        }
    };
    this.shoot = function (dt) {
        if (this.model.getParent()) {
            var offset = 13;
            var a = new Bullet(this.bulletSpeed, "W1.png", global.AttackMode.Normal);
            global.sbulletContainer.push(a);
            this.model.getParent().addChild(a.model, a.zOrder, global.Tag.ShipBullet);
            a.model.setPosition(cc.ccp(this.model.getPosition().x + offset, this.model.getPosition().y + 3 + this.model.getContentSize().height * 0.3));

            var b = new Bullet(this.bulletSpeed, "W1.png", global.AttackMode.Normal);
            global.sbulletContainer.push(b);
            this.model.getParent().addChild(b.model, b.zOrder, global.Tag.ShipBullet);
            b.model.setPosition(cc.ccp(this.model.getPosition().x - offset, this.model.getPosition().y + 3 + this.model.getContentSize().height * 0.3));
        }
    };
    this.destroy = function () {
        cc.log("ship destroy...1");
        (global.life > 0) ? global.life-- : 0;
        cc.log("ship destroy...2");
        if (this.model.getParent()) {
            cc.log("ship destroy...3");
            var exp = new Explosion(this.model.getPosition().x, this.model.getPosition().y);
            this.model.getParent().addChild(exp.model);
            cc.log("ship destroy...4");
            this.model.getParent().removeChild(this.model, true);
            cc.log("ship destroy...5");
        }
        if (global.sound) {
            cc.AudioManager.sharedEngine().playEffect(s_shipDestroyEffect);
        }
        cc.Scheduler.sharedScheduler().unscheduleAllSelectorsForTarget(this);
    };
    this.hurt = function () {
        if (this.canBeAttack) {
            this._hurtColorLife = 2;
            selfPointer.HP--;
            this.model.setColor(cc.RED());
        }
    };
    this.collideRect = function () {
        var a = this.model.getContentSize();
        var r = cc.RectMake(this.model.getPositionX() - a.width / 2, this.model.getPositionY() - a.height / 2, a.width, a.height / 2);
        return r;
    };
    this.ctor();
};
