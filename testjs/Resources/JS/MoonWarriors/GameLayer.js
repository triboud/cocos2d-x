var screenRect = null;
var GameLayer = function () {
    this._layer = cc.Layer.create();
    this._time = null;
    this._ship = null;
    this._backSky = null;
    this._backSkyHeight = 0;
    this._backSkyRe = null;
    this._backTileMap = null;
    this._backTileMapHeight = 0;
    this._backTileMapRe = null;
    this._levelManager = null;
    this._tmpScore = 0;
    this._isBackSkyReload = false;
    this._isBackTileReload = false;
    this.lbScore = null;
    this.isMouseDown = false;
    this._beginPos = cc.PointZero();
    this.init = function () {
        var bRet = false;
        {
            cc.log("GameLayer 1-----------------");
            global.bulletNum = 0;
            global.enemyNum = 0;
            Explosion.sharedExplosion();
            cc.log("GameLayer 2-----------------");
            Enemy.sharedEnemy();
            cc.log("GameLayer 3-----------------");
            winSize = cc.Director.sharedDirector().getWinSize();
            cc.log("GameLayer 4-----------------");
            this._levelManager = new LevelManager(this);
            cc.log("GameLayer 41-----------------");
            this.initBackground();
            cc.log("GameLayer 42-----------------");
            screenRect = new cc.Rect(0, 0, winSize.width, winSize.height + 10);
            cc.log("GameLayer 5-----------------");
            // score
            this.lbScore = cc.LabelTTF.create("Score: 0", cc.SizeMake(winSize.width / 2, 50), cc.TEXT_ALIGNMENT_RIGHT, "Arial", 14);
            this._layer.addChild(this.lbScore, 1000);
            this.lbScore.setPosition(cc.ccp(winSize.width - 100, winSize.height - 15));
cc.log("GameLayer 6-----------------");
            // ship life
            var shipTexture = cc.TextureCache.sharedTextureCache().addImage(s_ship01);
            var life = cc.Sprite.create(shipTexture, cc.RectMake(0, 0, 60, 38));
            life.setScale(0.6);
            life.setPosition(cc.ccp(30, 460));
            this._layer.addChild(life, 1, 5);
cc.log("GameLayer 7-----------------");
            // ship Life count
            this._lbLife = cc.LabelTTF.create("0", "Arial", 20);
            this._lbLife.setPosition(cc.ccp(60, 463));
            this._lbLife.setColor(cc.RED());
            this._layer.addChild(this._lbLife, 1000);
cc.log("GameLayer 8-----------------");
            // ship
            this._ship = new Ship();
            this._layer.addChild(this._ship.model, this._ship.zOrder, global.Tag.Ship);
cc.log("GameLayer 9-----------------");
            // accept touch now!
            this._layer.isTouchEnabled = true;

            // schedule
            cc.Scheduler.sharedScheduler().scheduleSelector(this.update, this, 0, false);
            cc.Scheduler.sharedScheduler().scheduleSelector(this.scoreCounter, this, 1, false);
cc.log("GameLayer 10-----------------");
            if (global.sound) {
                cc.AudioManager.sharedEngine().playBackgroundMusic(s_bgMusic, true);
            }

            bRet = true;
        }
        return bRet;
    };
    this.scoreCounter = function () {
        this._time++;

        var minute = 0 | (this._time / 60);
        var second = this._time % 60;
        minute = minute > 9 ? minute : "0" + minute;
        second = second > 9 ? second : "0" + second;
        var curTime = minute + ":" + second;
        this._levelManager.loadLevelResource(this._time);
    };
    this._layer.ccTouchesBegan = function (touches, event) {
        cc.log("js ccTouchesBegan...........");
        if (!this.isMouseDown) {
            var touch = touches[0];
            this._beginPos = touch.locationInView();
        }
        this.isMouseDown = true;
    };
    this._layer.ccTouchesMoved = function (touches, event) {
        cc.log("js ccTouchesMoved...........");
        if (this.isMouseDown) {
            var ship = this.getChildByTag(global.Tag.Ship);
            if (ship) {
                cc.log("----------------------");
                cc.log("ship exist.....");
                cc.log("----------------------");
                var curPos = ship.getPosition();
                if (cc.Rect.CCRectIntersectsRect(ship.boundingBox(), screenRect)) {
                    var touch = touches[0];
                    var location = touch.locationInView();

                    var move = cc.ccpSub(location, this._beginPos);
                    var nextPos = cc.ccpAdd(curPos, move);
                    ship.setPosition(nextPos);
                    this._beginPos = location;
                    curPos = nextPos;
                }
            }
        }
    };
    this._layer.ccTouchesEnded = function () {
        cc.log("js ccTouchesEnded...........");
        this.isMouseDown = false;
    };
    this.update = function (dt) {
        
        this.checkIsCollide(dt);
        this.removeInactiveUnit(dt);
        this.checkIsReborn();
        this.updateUI();
        //cc.$("#cou").innerHTML = "Ship:" + 1 + ", Enemy: " + global.enemyContainer.length
        //    + ", Bullet:" + global.ebulletContainer.length + "," + global.sbulletContainer.length + " all:" + this._layer.getChildren().length;
    };
    this.checkIsCollide = function (dt) {
        var selChild, bulletChild;
        //check collide
        for (var i = 0; i < global.enemyContainer.length; i++) {
            selChild = global.enemyContainer[i];
            for (var j = 0; j < global.sbulletContainer.length; j++) {
                bulletChild = global.sbulletContainer[j];
                if (this.collide(selChild, bulletChild)) {
                    bulletChild.hurt();
                    selChild.hurt();
                }
                if (!cc.Rect.CCRectIntersectsRect(screenRect, bulletChild.model.boundingBox())) {
                    bulletChild.destroy();
                }
            }
            if (this._ship) {
                if (this.collide(selChild, this._ship)) {
                    if (this._ship.active) {
                        selChild.hurt();
                        this._ship.hurt();
                    }
                }
            }
            if (!cc.Rect.CCRectIntersectsRect(screenRect, selChild.model.boundingBox())) {
                selChild.destroy();
            }
        }

        for (var i = 0; i < global.ebulletContainer.length; i++) {
            selChild = global.ebulletContainer[i];
            if (this._ship) {
                if (this.collide(selChild, this._ship)) {
                    if (this._ship.active) {
                        selChild.hurt();
                        this._ship.hurt();
                    }
                }
            }
            if (!cc.Rect.CCRectIntersectsRect(screenRect, selChild.model.boundingBox())) {
                selChild.destroy();
            }

        }
    };
    this.removeInactiveUnit = function (dt) {
        for (var i = 0; i < global.enemyContainer.length; i++) {
            var selChild = global.enemyContainer[i];
            if (selChild) {
                selChild.update(dt);
                if (selChild && !selChild.active) {
                    selChild.destroy();
                }
            }
        }
        for (var i = 0; i < global.sbulletContainer.length; i++) {
            var selChild = global.sbulletContainer[i];
            if (selChild) {
                selChild.update(dt);
                if (selChild && !selChild.active) {
                    selChild.destroy();
                }
            }
        }

        for (var i = 0; i < global.ebulletContainer.length; i++) {
            var selChild = global.ebulletContainer[i];
            if (selChild) {
                selChild.update(dt);
                if (selChild && !selChild.active) {
                    selChild.destroy();
                }
            }
        }
        if (this._ship) {
            this._ship.update(dt);
            cc.log("this._ship.active = "+ this._ship.active);
            if (this._ship && !this._ship.active) {
                this._ship.destroy();
            }
        }
        /*var selChild, layerChildren = this._layer.getChildren();
         for (var i in layerChildren) {
         selChild = layerChildren[i];
         if (selChild) {
         selChild.update(dt);
         if ((selChild.getTag() == global.Tag.Ship) || (selChild.getTag() == global.Tag.ShipBullet) ||
         (selChild.getTag() == global.Tag.Enemy) || (selChild.getTag() == global.Tag.EnemyBullet)) {
         if (selChild && !selChild.active) {
         selChild.destroy();
         }
         }
         }
         }*/

    };
    this.checkIsReborn = function () {
        if (global.life > 0 && !this._ship.active) {
            cc.log("checkIsReborn... new ship");
            // ship
            this._ship = new Ship();
            this._layer.addChild(this._ship.model, this._ship.zOrder, global.Tag.Ship);
        }
        else if (global.life <= 0 && this._ship) {
            cc.log("checkIsReborn...");
            if (!this._ship.active) {
                cc.log("checkIsReborn..active.");
                this._layer.runAction(cc.Sequence.create(
                    cc.DelayTime.create(3),
                    cc.CallFunc.create(this, this.onGameOver)))
            }
        }
    };
    this.updateUI = function () {
        if (this._tmpScore < global.score) {
            this._tmpScore += 5;
        }
        cc.log("updateUI 1");
        cc.log("global.life = "+global.life);
        this._lbLife.setString(global.life);
        this.lbScore.setString("Score: " + this._tmpScore);
        cc.log("updateUI 2");
    };
    this.checkEnemyAndBulletIsInBound = function () {
        var layerChildren = this.getChildren();
        cc.log("layerChildren num = "+layerChildren.length);
        for (var i = 0; i < layerChildren.length; i++) {
            var selChild = layerChildren[i];
            if ((selChild.getTag() == global.Tag.Enemy) || (selChild.getTag() == global.Tag.EnemyBullet) || (selChild.getTag() == global.Tag.ShipBullet)) {
                var childRect = selChild.boundingBox();
                if (!cc.Rect.CCRectIntersectsRect(screenRect, childRect)) {
                    // cjh add
                    if (selChild instanceof cc.Sprite)
                    {
                        cc.log("child is sprite");
                    }
                    else if (selChild instanceof cc.Node)
                    {
                        cc.log("child is node");
                    }
                    else
                    {
                        cc.log("error..................");
                    }
                    // cjh add end
                    selChild.destroy();
                    cc.log("must go here.........");
                }
            }
        }
    };
    this.collide = function (a, b) {
        var aRect = a.collideRect();
        var bRect = b.collideRect();
        if (cc.Rect.CCRectIntersectsRect(aRect, bRect)) {
            return true;
        }
    };
    this.initBackground = function () {
        // bg
        cc.log("initBackground 0");
        this._backSky = cc.Sprite.create(s_bg01);
        this._backSky.setAnchorPoint(cc.PointZero());
        this._backSkyHeight = this._backSky.getContentSize().height;
        this._layer.addChild(this._backSky, -10);
cc.log("initBackground 1");
        //tilemap
        this._backTileMap = cc.TMXTiledMap.create(s_level01);
        this._layer.addChild(this._backTileMap, -9);
        this._backTileMapHeight = this._backTileMap.getMapSize().height * this._backTileMap.getTileSize().height;
cc.log("initBackground 2");
        this._backSkyHeight -= 48;
        this._backTileMapHeight -= 200;
        this._backSky.runAction(cc.MoveBy.create(3, new cc.Point(0, -48)));
        this._backTileMap.runAction(cc.MoveBy.create(3, new cc.Point(0, -200)));
cc.log("initBackground 3");
        cc.Scheduler.sharedScheduler().scheduleSelector(this.movingBackground, this, 3, false);
        cc.log("initBackground 4");
    };
    this.movingBackground = function () {
        this._backSky.runAction(cc.MoveBy.create(3, new cc.Point(0, -48)));
        this._backTileMap.runAction(cc.MoveBy.create(3, new cc.Point(0, -200)));
        this._backSkyHeight -= 48;
        this._backTileMapHeight -= 200;

        if (this._backSkyHeight <= winSize.height) {
            if (!this._isBackSkyReload) {
                this._backSkyRe = cc.Sprite.create(s_bg01);
                this._backSkyRe.setAnchorPoint(cc.PointZero());
                this._layer.addChild(this._backSkyRe, -10);
                this._backSkyRe.setPosition(new cc.Point(0, winSize.height));
                this._isBackSkyReload = true;
            }
            this._backSkyRe.runAction(cc.MoveBy.create(3, new cc.Point(0, -48)));
        }
        if (this._backSkyHeight <= 0) {
            this._backSkyHeight = this._backSky.getContentSize().height;
            this._layer.removeChild(this._backSky, true);
            this._backSky = this._backSkyRe;
            this._backSkyRe = null;
            this._isBackSkyReload = false;
        }

        if (this._backTileMapHeight <= winSize.height) {
            if (!this._isBackTileReload) {
                this._backTileMapRe = cc.TMXTiledMap.create(s_level01);
                this._layer.addChild(this._backTileMapRe, -9);
                this._backTileMapRe.setPosition(new cc.Point(0, winSize.height));
                this._isBackTileReload = true;
            }
            this._backTileMapRe.runAction(cc.MoveBy.create(3, new cc.Point(0, -200)));
        }
        if (this._backTileMapHeight <= 0) {
            this._backTileMapHeight = this._backTileMapRe.getMapSize().height * this._backTileMapRe.getTileSize().height;
            this._layer.removeChild(this._backTileMap, true);
            this._backTileMap = this._backTileMapRe;
            this._backTileMapRe = null;
            this._isBackTileReload = false;
        }
    };
    this.onGameOver = function () {
        cc.log("onGameOver 1");
        var scene = cc.Scene.create();
        cc.log("onGameOver 2");
        scene.addChild(GameOver.create());
        cc.log("onGameOver 3");
        cc.Director.sharedDirector().replaceScene(cc.TransitionFade.create(1.2, scene));
        cc.log("onGameOver 4");
        this._layer.getParent().removeChild(this._layer, true);
        cc.log("onGameOver 5");
        cc.Scheduler.sharedScheduler().unscheduleAllSelectorsForTarget(this);
        cc.log("onGameOver 6");
    }
};

GameLayer.create = function () {
    var sg = new GameLayer();
    if (sg && sg.init()) {
        return sg._layer;
    }
    return null;
};

GameLayer.scene = function () {
    var scene = cc.Scene.create();
    var layer = GameLayer.create();
    scene.addChild(layer, 1);
    return scene;
};