var SysMenu = function () {
    this._ship = null;
    this._layer = cc.Layer.create();
    this.init = function () {
        var bRet = false;
        {
cc.log("0-------------------");            
            winSize = cc.Director.sharedDirector().getWinSize();
            cc.log("01-------------------");  
            var sp = cc.Sprite.create(s_loading);
            cc.log("02-------------------");  
            sp.setAnchorPoint(cc.PointZero());
            cc.log("03-------------------");  
            this._layer.addChild(sp, 0, 1);

            cc.log("1-------------------");
            var logo = cc.Sprite.create(s_logo);
            logo.setAnchorPoint(cc.ccp(0, 0));
            logo.setPosition(cc.ccp(0, 250));
            this._layer.addChild(logo, 10, 1);
cc.log("2-------------------");
            var newGameNormal = cc.Sprite.create(s_menu, cc.RectMake(0, 0, 126, 33));
            var newGameSelected = cc.Sprite.create(s_menu, cc.RectMake(0, 33, 126, 33));
            var newGameDisabled = cc.Sprite.create(s_menu, cc.RectMake(0, 33 * 2, 126, 33));
cc.log("3-------------------");
            var gameSettingsNormal = cc.Sprite.create(s_menu, cc.RectMake(126, 0, 126, 33));
            var gameSettingsSelected = cc.Sprite.create(s_menu, cc.RectMake(126, 33, 126, 33));
            var gameSettingsDisabled = cc.Sprite.create(s_menu, cc.RectMake(126, 33 * 2, 126, 33));
cc.log("4-------------------");
            var aboutNormal = cc.Sprite.create(s_menu, cc.RectMake(252, 0, 126, 33));
            var aboutSelected = cc.Sprite.create(s_menu, cc.RectMake(252, 33, 126, 33));
            var aboutDisabled = cc.Sprite.create(s_menu, cc.RectMake(252, 33 * 2, 126, 33));
cc.log("5-------------------");
            var newGame = cc.MenuItemSprite.create(newGameNormal, newGameSelected, newGameDisabled, this, function () {
                this.onButtonEffect();
                flareEffect(this._layer, this._layer, this.onNewGame);
            });
cc.log("51-------------------");
            var gameSettings = cc.MenuItemSprite.create(gameSettingsNormal, gameSettingsSelected, gameSettingsDisabled, this, this.onSettings);
            var about = cc.MenuItemSprite.create(aboutNormal, aboutSelected, aboutDisabled, this, this.onAbout);
cc.log("52-------------------");
            var menu = cc.Menu.create(newGame, gameSettings, about);
            menu.alignItemsVerticallyWithPadding(10);
cc.log("53-------------------");
            this._layer.addChild(menu, 1, 2);
cc.log("54-------------------");            
            menu.setPosition(cc.ccp(winSize.width / 2, winSize.height / 2 - 80));
cc.log("55-------------------");
            cc.Scheduler.sharedScheduler().scheduleSelector(this.update, this, 0.1, false);
cc.log("6-------------------");
            var tmp = cc.TextureCache.sharedTextureCache().addImage(s_ship01);
cc.log("61-------------------");            
            this._ship = cc.Sprite.create(tmp, cc.RectMake(0, 45, 60, 38));
cc.log("62-------------------");            
            this._layer.addChild(this._ship, 0, 4);
cc.log("63-------------------");
            this._ship.setPosition(cc.ccp(Math.random() * winSize.width, 0));
cc.log("64-------------------");            
            this._ship.runAction(cc.MoveBy.create(2, cc.ccp(Math.random() * winSize.width, this._ship.getPosition().y + winSize.height + 100)));
cc.log("65-------------------");
            if (global.sound) {
                cc.log("651-------------------");
                cc.AudioManager.sharedEngine().setBackgroundMusicVolume(0.7);
                cc.log("652-------------------");
                cc.AudioManager.sharedEngine().playBackgroundMusic(s_mainMainMusic, true);
                cc.log("653-------------------");
            }
cc.log("7-------------------");
            bRet = true;
        }
        return bRet;
    };
    this.onNewGame = function (pSender) {
        cc.log("new game 1...");
        var scene = cc.Scene.create();
        cc.log("new game 2...");
        scene.addChild(GameLayer.create());
        cc.log("new game 3...");
        scene.addChild(GameControlMenu.create());
        cc.log("new game 4...");
        cc.Director.sharedDirector().replaceScene(cc.TransitionFade.create(1.2, scene));
    };
    this.onSettings = function (pSender) {
        this.onButtonEffect();
        var scene = cc.Scene.create();
        scene.addChild(SettingsLayer.create());
        cc.Director.sharedDirector().replaceScene(cc.TransitionFade.create(1.2, scene));
    };
    this.onAbout = function (pSender) {
        cc.log("onAbout 1--------------");
        this.onButtonEffect();
        cc.log("onAbout 2--------------");
        var scene = cc.Scene.create();
        cc.log("onAbout 3--------------");
        scene.addChild(AboutLayer.create());
        cc.log("onAbout 4--------------");
        cc.Director.sharedDirector().replaceScene(cc.TransitionFade.create(1.2, scene));
        cc.log("onAbout 5--------------");
    };
    this.update = function () {
        if (this._ship.getPosition().y > 480) {
            this._ship.setPosition(cc.ccp(Math.random() * winSize.width, 10));
            this._ship.runAction(cc.MoveBy.create(parseInt(5 * Math.random()), cc.ccp(Math.random() * winSize.width, this._ship.getPosition().y + 480)));
        }
    };
    this.onButtonEffect = function () {
        if (global.sound) {
            var s = cc.AudioManager.sharedEngine().playEffect(s_buttonEffect);
        }
    };
};

SysMenu.create = function () {
    var sg = new SysMenu();
    if (sg && sg.init()) {
        return sg._layer;
    }
    return null;
};

SysMenu.scene = function () {
    cc.log("sysmenu 1----------------");
    var scene = cc.Scene.create();
    cc.log("sysmenu 2----------------");
    var layer = SysMenu.create();
    cc.log("sysmenu 3----------------");
    scene.addChild(layer);
    cc.log("sysmenu 4----------------");
    return scene;
};
