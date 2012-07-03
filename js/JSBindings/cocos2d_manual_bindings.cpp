#include "cocos2d_generated.hpp"

// MenuItemSelector
MenuItemSelector::MenuItemSelector()
: m_pCallBackFuncObj(NULL)
, m_pThisJsObj(NULL)
{
}

void MenuItemSelector::menuCallBack(CCObject* pSender)
{
    JSContext* cx  = ScriptingCore::getInstance().getGlobalContext();
    CCAssert(JS_ValueToFunction(cx, OBJECT_TO_JSVAL(m_pCallBackFuncObj)), "Should be a function");
    CCObject* pSenderFromJs = NULL; JSGET_PTRSHELL(CCObject, pSenderFromJs, m_pSender);
    CCAssert(pSenderFromJs == pSender, "");
    jsval rval;
    jsval val = OBJECT_TO_JSVAL(m_pSender);

    JS_CallFunctionValue(cx, m_pThisJsObj, OBJECT_TO_JSVAL(m_pCallBackFuncObj), 1, &val, &rval);
}

void MenuItemSelector::setJsCallBack(JSObject* pThisJsObj, JSObject* pCallBackFuncObj, JSObject* pSender)
{
    m_pCallBackFuncObj = pCallBackFuncObj;
    m_pThisJsObj = pThisJsObj;
    m_pSender = pSender;
}

// CallFuncSelector
CallFuncSelector::CallFuncSelector()
: m_pCallBackFuncObj(NULL)
, m_pThisJsObj(NULL)
{
}

void CallFuncSelector::callBack()
{
    JSContext* cx  = ScriptingCore::getInstance().getGlobalContext();
    CCAssert(JS_ValueToFunction(cx, OBJECT_TO_JSVAL(m_pCallBackFuncObj)), "Should be a function");
    jsval rval;
    JS_CallFunctionValue(cx, m_pThisJsObj, OBJECT_TO_JSVAL(m_pCallBackFuncObj), 0, NULL, &rval);
}

void CallFuncSelector::setJsCallBack(JSObject* pThisJsObj, JSObject* pCallBackFuncObj)
{
    m_pCallBackFuncObj = pCallBackFuncObj;
    m_pThisJsObj = pThisJsObj;
}


JSBool S_CCNode::jsaddChild(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc >= 1) {
        JSObject *arg0;
        int zorder = 0;
        int tag = 0;
        JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o/ii", &arg0, &zorder, &tag);
        CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
        // call the proper method
        if (argc == 1) {
            self->addChild(narg0);
        } else if (argc == 2) {
            self->addChild(narg0, zorder);
        } else {
            self->addChild(narg0, zorder, tag);
        }

        JS_SET_RVAL(cx, vp, JSVAL_TRUE);
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCMenuItemSprite::jsinitWithNormalSprite(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCMenuItemSprite* self = NULL; JSGET_PTRSHELL(S_CCMenuItemSprite, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc >= 2) {
        JSObject *arg0;
        JSObject *arg1;
        JSObject *arg2 = NULL;
        JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "oo/o", &arg0, &arg1, &arg2);
        CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
        CCNode* narg1; JSGET_PTRSHELL(CCNode, narg1, arg1);
        CCNode* narg2 = NULL; if (argc == 3) JSGET_PTRSHELL(CCNode, narg2, arg2);
        bool ret = self->initWithNormalSprite(narg0, narg1, narg2, self, menu_selector(S_CCMenuItemSprite::menuAction));
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCMenuItemSprite::jscreate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 2 && argc <= 5) {
        JSObject *arg0 = NULL;
        JSObject *arg1 = NULL;
        JSObject *arg2 = NULL;
        JSObject *arg3 = NULL;
        JSObject *arg4 = NULL;
        JSObject *pThisObj = NULL;
        JSObject *pCallBackObj = NULL;

        CCNode* narg0 = NULL;
        CCNode* narg1 = NULL; 
        CCNode* narg2 = NULL; 

        if (argc == 2)
        {
            JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
            JSGET_PTRSHELL(CCNode, narg0, arg0);
            JSGET_PTRSHELL(CCNode, narg1, arg1);
        }
        else if (argc == 3)
        {
            JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ooo", &arg0, &arg1, &arg2);
            JSGET_PTRSHELL(CCNode, narg0, arg0);
            JSGET_PTRSHELL(CCNode, narg1, arg1);
            JSGET_PTRSHELL(CCNode, narg2, arg2);
        }
        else if (argc == 4)
        {
            JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "oooo", &arg0, &arg1, &arg2, &arg3);
            JSGET_PTRSHELL(CCNode, narg0, arg0);
            JSGET_PTRSHELL(CCNode, narg1, arg1);
            pThisObj = arg2;
            pCallBackObj = arg3;
        }
        else
        {
            JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "ooooo", &arg0, &arg1, &arg2, &arg3, &arg4);
            JSGET_PTRSHELL(CCNode, narg0, arg0);
            JSGET_PTRSHELL(CCNode, narg1, arg1);
            JSGET_PTRSHELL(CCNode, narg2, arg2);
            pThisObj = arg3;
            pCallBackObj = arg4;
        }
     
        S_CCMenuItemSprite* ret = new S_CCMenuItemSprite(NULL);
        if (ret)
        {
            if (pThisObj && pCallBackObj)
            {
                ret->m_pMenuItemSelector = new MenuItemSelector();
                if (!ret->initWithNormalSprite(narg0, narg1, narg2, ret->m_pMenuItemSelector, menu_selector(MenuItemSelector::menuCallBack)))
                {
                    CC_SAFE_DELETE(ret->m_pMenuItemSelector);
                    CC_SAFE_DELETE(ret);
                }
            }
            else
            {
                if (!ret->initWithNormalSprite(narg0, narg1, narg2, NULL, NULL))
                {
                    CC_SAFE_DELETE(ret);
                }
            }
        }

        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        do {
            JSObject *tmp = JS_NewObject(cx, S_CCMenuItemSprite::jsClass, S_CCMenuItemSprite::jsObject, NULL);
            ret->m_jsobj = tmp;
            if (ret->m_pMenuItemSelector)
            {
                ret->m_pMenuItemSelector->setJsCallBack(pThisObj, pCallBackObj, tmp);
            }
            
            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = 0;//FIXME: ? kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while (0);

        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCCallFunc::jscreate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 2) {
        JSObject *arg0 = NULL;
        JSObject *arg1 = NULL;

        CCObject* narg0 = NULL;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);

        
        S_CCCallFunc* ret = new S_CCCallFunc(NULL);
        if (ret)
        {
            ret->m_pCallFuncSelector = new CallFuncSelector();
            if (ret->initWithTarget(ret->m_pCallFuncSelector))
            {
                ret->m_pCallFunc = callfunc_selector(CallFuncSelector::callBack);
            }
            else
            {
                CC_SAFE_DELETE(ret->m_pCallFuncSelector);
                CC_SAFE_DELETE(ret);
            }
        }
        
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        do {
            JSObject *tmp = JS_NewObject(cx, S_CCMenuItemSprite::jsClass, S_CCMenuItemSprite::jsObject, NULL);
            ret->m_jsobj = tmp;
            if (ret->m_pCallFuncSelector)
            {
                ret->m_pCallFuncSelector->setJsCallBack(arg0, arg1);
            }

            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = 0;//kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while (0);

        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}


JSBool S_CCMenuItemImage::jsinitWithNormalImage(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCMenuItemImage* self = NULL; JSGET_PTRSHELL(S_CCMenuItemImage, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc >= 2) {
        JSString *arg0;
        JSString *arg1;
        JSString *arg2 = NULL;
        JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "SS/S", &arg0, &arg1, &arg2);
        char *narg0 = JS_EncodeString(cx, arg0);
        char *narg1 = JS_EncodeString(cx, arg1);
        char *narg2 = (arg2) ? JS_EncodeString(cx, arg2) : NULL;
        bool ret = self->initWithNormalImage(narg0, narg1, narg2, self, menu_selector(S_CCMenuItemImage::menuAction));
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCSequence::jscreate(JSContext *cx, uint32_t argc, jsval *vp) {
    // just like CCSequence::actions
    if (argc > 0) {
        do {
            if (argc == 1) {
                JSObject *arg0;
                JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
                CCObject* tmpArg; JSGET_PTRSHELL(CCObject, tmpArg, arg0);
                CCArray* narg0 = dynamic_cast<CCArray*>(tmpArg);
                if (narg0 == NULL) break;
                
                CCFiniteTimeAction* ret = CCSequence::create(narg0);
                if (ret == NULL) {
                    JS_SET_RVAL(cx, vp, JSVAL_NULL);
                    return JS_TRUE;
                }
                do {
                    ret->retain();
                    JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
                    pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
                    pt->flags = kPointerTemporary;
                    pt->data = (void *)ret;
                    JS_SetPrivate(tmp, pt);
                    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
                } while (0);

                return JS_TRUE;
            }
        } while(0);

        jsval* argv = JS_ARGV(cx, vp);
        // get first element
        S_CCSequence* prev;
        JSGET_PTRSHELL(S_CCSequence, prev, JSVAL_TO_OBJECT(argv[0]));
        for (int i=1; i < argc; i++) {
            CCFiniteTimeAction *next; JSGET_PTRSHELL(CCFiniteTimeAction, next, JSVAL_TO_OBJECT(argv[i]));
            prev = (S_CCSequence *)CCSequence::create(prev, next);
        }
        prev->retain();
        // wrap prev in an action
        // temporary because it's just a wrapper for an autoreleased object
        // or worst case, it's an already binded object (if it's just one item in the array)
        pointerShell_t* pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
        pt->flags = 0;//FIXME: why shall we use kPointerTemporary?; by James Chen
        pt->data = prev;
        JSObject* out = JS_NewObject(cx, S_CCSequence::jsClass, S_CCSequence::jsObject, NULL);
        prev->jsObject = out;
        JS_SetPrivate(out, pt);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(out));
        return JS_TRUE;
    }
    JS_ReportError(cx, "must call with at least one element");
    return JS_FALSE;
}

JSBool S_CCParticleSystem::jsparticleWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 1) {
        JSString *arg0;
        JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
        char *narg0 = JS_EncodeString(cx, arg0);
        CCParticleSystem* ret = CCParticleSystemQuad::particleWithFile(narg0);
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        do {
            JSObject *tmp = JS_NewObject(cx, S_CCParticleSystem::jsClass, S_CCParticleSystem::jsObject, NULL);
            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while (0);
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCFileUtils::jsgetFileData(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 2) {
        JSString *arg0;
        JSString *arg1;
        unsigned long len;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
        char *narg0 = JS_EncodeString(cx, arg0);
        char *narg1 = JS_EncodeString(cx, arg1);
        unsigned char *ret = CCFileUtils::sharedFileUtils()->getFileData(narg0, narg1, &len);
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        JSString *str = JS_NewStringCopyN(cx, (const char *)ret, len);
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCFileUtils::jsfullPathFromRelativePath(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 1) {
        JSString *arg0;
        JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
        char *narg0 = JS_EncodeString(cx, arg0);
        const char *ret = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(narg0);
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        JSString *str = JS_NewStringCopyN(cx, ret, strlen(ret));
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCFileUtils::jsfullPathFromRelativeFile(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 2) {
        JSString *arg0;
        JSString *arg1;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
        char *narg0 = JS_EncodeString(cx, arg0);
        char *narg1 = JS_EncodeString(cx, arg1);
        const char *ret = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(narg0, narg1);
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        JSString *str = JS_NewStringCopyN(cx, ret, strlen(ret));
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));        
        return JS_TRUE;
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCLabelTTF::jscreate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 5) {
        JSString *arg0;
        JSObject *arg1;
        int arg2;
        JSString *arg3;
        double arg4;
        JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SoiSd", &arg0, &arg1, &arg2, &arg3, &arg4);
        char *narg0 = JS_EncodeString(cx, arg0);
        CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
        char *narg3 = JS_EncodeString(cx, arg3);
        CCLabelTTF *ret = CCLabelTTF::create(narg0, *narg1, (CCTextAlignment)arg2, narg3, arg4);
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        do {
            ret->retain();
            JSObject *tmp = JS_NewObject(cx, S_CCLabelTTF::jsClass, S_CCLabelTTF::jsObject, NULL);
            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while (0);
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCLabelTTF::jsinitWithString(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCLabelTTF* self = NULL; JSGET_PTRSHELL(S_CCLabelTTF, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 5) {
        JSString *arg0;
        JSObject *arg1;
        int arg2;
        JSString *arg3;
        double arg4;
        JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SoiSd", &arg0, &arg1, &arg2, &arg3, &arg4);
        char *narg0 = JS_EncodeString(cx, arg0);
        CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
        char *narg3 = JS_EncodeString(cx, arg3);
        bool ret = self->initWithString(narg0, *narg1, (CCTextAlignment)arg2, narg3, arg4);
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCMenuItem::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 0) {
        bool ret = self->initWithTarget(self, menu_selector(S_CCMenuItem::menuAction));
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCRenderTexture::jsrenderTextureWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc == 2) {
        int arg0;
        int arg1;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
        CCRenderTexture* ret = CCRenderTexture::renderTextureWithWidthAndHeight(arg0, arg1);
        do {
            JSObject *tmp = JS_NewObject(cx, S_CCRenderTexture::jsClass, S_CCRenderTexture::jsObject, NULL);
            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while (0);
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCRenderTexture::jsinitWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 2) {
        int arg0;
        int arg1;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
        bool ret = self->initWithWidthAndHeight(arg0, arg1, kCCTexture2DPixelFormat_RGBA8888);
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCMenuItemLabel::jsitemWithLabel(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 1) {
        JSObject *arg0;
        JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
        CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
        CCMenuItemLabel *ret = CCMenuItemLabel::itemWithLabel(narg0, self, menu_selector(S_CCMenuItemLabel::menuAction));
        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        do {
            JSObject *tmp = JS_NewObject(cx, S_CCMenuItemLabel::jsClass, S_CCMenuItemLabel::jsObject, NULL);
            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while(0);
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCMenuItemLabel::jsinitWithLabel(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 1) {
        JSObject *arg0;
        JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
        CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
        bool ret = self->initWithLabel(narg0, self, menu_selector(S_CCMenuItemLabel::menuAction));
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCApplication::jsgetCurrentLanguage(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    CCApplication* self = NULL; JSGET_PTRSHELL(CCApplication, self, obj);
    if (self == NULL) return JS_FALSE;
    jsval result; JS_NewNumberValue(cx, self->getCurrentLanguage(), &result);
    JS_SET_RVAL(cx, vp, result);
    return JS_TRUE;
}

JSBool S_CCUserDefault::jsgetStringForKey(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 2) {
        JSString *arg0;
        JSString *arg1;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
        char *narg0 = JS_EncodeString(cx, arg0);
        std::string narg1(JS_EncodeString(cx, arg1));
        std::string ret = self->getStringForKey(narg0, narg1);
        JSString *jsret = JS_NewStringCopyZ(cx, ret.c_str());
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsret));
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSBool S_CCUserDefault::jssetStringForKey(JSContext *cx, uint32_t argc, jsval *vp) {
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
    if (self == NULL) return JS_FALSE;
    if (argc == 2) {
        JSString *arg0;
        JSString *arg1;
        JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
        char *narg0 = JS_EncodeString(cx, arg0);
        std::string narg1(JS_EncodeString(cx, arg1));
        self->setStringForKey(narg0, narg1);
        
        JS_SET_RVAL(cx, vp, JSVAL_TRUE);
        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}

JSClass* S_CCColor3B::jsClass = NULL;
JSObject* S_CCColor3B::jsObject = NULL;

JSBool S_CCColor3B::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_NewObject(cx, S_CCColor3B::jsClass, S_CCColor3B::jsObject, NULL);
    S_CCColor3B *cobj = new S_CCColor3B(obj);
    pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
    pt->flags = 0; pt->data = cobj;
    JS_SetPrivate(obj, pt);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    return JS_TRUE;
}

void S_CCColor3B::jsFinalize(JSContext *cx, JSObject *obj)
{
    pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
    if (pt) {
        if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCColor3B *)pt->data;
        JS_free(cx, pt);
    }
}

JSBool S_CCColor3B::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
    int32_t propId = JSID_TO_INT(_id);
    S_CCColor3B *cobj; JSGET_PTRSHELL(S_CCColor3B, cobj, obj);
    if (!cobj) return JS_FALSE;
    switch(propId) {
    case kR:
        do { jsval tmp; JS_NewNumberValue(cx, cobj->r, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
        break;
    case kG:
        do { jsval tmp; JS_NewNumberValue(cx, cobj->g, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
        break;
    case kB:
        do { jsval tmp; JS_NewNumberValue(cx, cobj->b, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
        break;
    default:
        break;
    }
    return JS_TRUE;
}

JSBool S_CCColor3B::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
    int32_t propId = JSID_TO_INT(_id);
    S_CCColor3B *cobj; JSGET_PTRSHELL(S_CCColor3B, cobj, obj);
    if (!cobj) return JS_FALSE;
    switch(propId) {
    case kR:
        do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->r = tmp; } while (0);
        break;
    case kG:
        do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->g = tmp; } while (0);
        break;
    case kB:
        do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->b = tmp; } while (0);
    default:
        break;
    }
    return JS_TRUE;
}

void S_CCColor3B::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
{
    jsClass = (JSClass *)calloc(1, sizeof(JSClass));
    jsClass->name = name;
    jsClass->addProperty = JS_PropertyStub;
    jsClass->delProperty = JS_PropertyStub;
    jsClass->getProperty = JS_PropertyStub;
    jsClass->setProperty = JS_StrictPropertyStub;
    jsClass->enumerate = JS_EnumerateStub;
    jsClass->resolve = JS_ResolveStub;
    jsClass->convert = JS_ConvertStub;
    jsClass->finalize = jsFinalize;
    jsClass->flags = JSCLASS_HAS_PRIVATE;
    static JSPropertySpec properties[] = {
        {"r", kR, JSPROP_PERMANENT | JSPROP_SHARED, S_CCColor3B::jsPropertyGet, S_CCColor3B::jsPropertySet},
        {"g", kG, JSPROP_PERMANENT | JSPROP_SHARED, S_CCColor3B::jsPropertyGet, S_CCColor3B::jsPropertySet},
        {"b", kB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCColor3B::jsPropertyGet, S_CCColor3B::jsPropertySet},
        {0, 0, 0, 0, 0}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };

    jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCColor3B::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSClass* S_CCMenuItemToggle::jsClass = NULL;
JSObject* S_CCMenuItemToggle::jsObject = NULL;

JSBool S_CCMenuItemToggle::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_NewObject(cx, S_CCMenuItemToggle::jsClass, S_CCMenuItemToggle::jsObject, NULL);
    S_CCMenuItemToggle *cobj = new S_CCMenuItemToggle(obj);
    pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
    pt->flags = 0; pt->data = cobj;
    JS_SetPrivate(obj, pt);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    return JS_TRUE;
}

void S_CCMenuItemToggle::jsFinalize(JSContext *cx, JSObject *obj)
{
    pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
    if (pt) {
        if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMenuItemToggle *)pt->data)->release();
        JS_free(cx, pt);
    }
}

void S_CCMenuItemToggle::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
{
    jsClass = (JSClass *)calloc(1, sizeof(JSClass));
    jsClass->name = name;
    jsClass->addProperty = JS_PropertyStub;
    jsClass->delProperty = JS_PropertyStub;
    jsClass->getProperty = JS_PropertyStub;
    jsClass->setProperty = JS_StrictPropertyStub;
    jsClass->enumerate = JS_EnumerateStub;
    jsClass->resolve = JS_ResolveStub;
    jsClass->convert = JS_ConvertStub;
    jsClass->finalize = jsFinalize;
    jsClass->flags = JSCLASS_HAS_PRIVATE;
    static JSPropertySpec properties[] = {
        {0, 0, 0, 0, 0}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", S_CCMenuItemToggle::jscreate, 2, JSPROP_PERMANENT | JSPROP_SHARED),
        JS_FS_END
    };

    jsObject = JS_InitClass(cx,globalObj, NULL,jsClass,S_CCMenuItemToggle::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItemToggle::jscreate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 2) {
        jsval* argvp = JS_ARGV(cx, vp);
        JSObject *arg0 = NULL;
        JSObject *arg1 = NULL;

        JS_ValueToObject( cx, *argvp++, &arg0);
        JS_ValueToObject( cx, *argvp++, &arg1);

        CCArray* pMenuItemArray = new CCArray(argc-2);
        
        for (uint32_t i = 0; i < argc-2; ++i)
        {
            JSObject* arg0 = NULL;
            JS_ValueToObject( cx, *argvp++, &arg0);
            CCObject* narg0; JSGET_PTRSHELL(CCObject, narg0, arg0);
            if (dynamic_cast<CCMenuItem*>(narg0) != NULL)
            {
                pMenuItemArray->addObject(narg0);
            }
            else
            {
                CCAssert(0, "must add CCMenuItem to CCMenuItemToggle");
            }
        }


        S_CCMenuItemToggle* ret = new S_CCMenuItemToggle(NULL);
        if (ret)
        {
            ret->m_pMenuItemSelector = new MenuItemSelector();
            if (!ret->initWithTarget(ret->m_pMenuItemSelector, menu_selector(MenuItemSelector::menuCallBack), pMenuItemArray))
            {
                CC_SAFE_DELETE(ret->m_pMenuItemSelector);
                CC_SAFE_DELETE(ret);
            }
        }

        pMenuItemArray->release();

        if (ret == NULL) {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
            return JS_TRUE;
        }
        do {
            JSObject *tmp = JS_NewObject(cx, S_CCMenuItemToggle::jsClass, S_CCMenuItemToggle::jsObject, NULL);
            ret->m_jsobj = tmp;
            if (ret->m_pMenuItemSelector)
            {
                ret->m_pMenuItemSelector->setJsCallBack(arg0, arg1, tmp);
            }

            pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
            pt->flags = 0;//kPointerTemporary;
            pt->data = (void *)ret;
            JS_SetPrivate(tmp, pt);
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        } while (0);

        return JS_TRUE;
    }
    JS_SET_RVAL(cx, vp, JSVAL_TRUE);
    return JS_TRUE;
}
