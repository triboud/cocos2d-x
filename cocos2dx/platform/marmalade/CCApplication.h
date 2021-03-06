/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_APPLICATION_MARMALADE_H__
#define __CC_APPLICATION_MARMALADE_H__

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"

#include "cocoa/CCGeometry.h"
#include "CCDirector.h"
#include "IwUtil.h"
#include "IwUtilInitTerm.h"
#include "CCProtocols.h"
NS_CC_BEGIN


class CCRect;

class CC_DLL CCApplication : public CCApplicationProtocol, CCDirectorDelegate
{
public:

    CCApplication();
    virtual ~CCApplication();

    /**
    @brief    Callback by CCDirector for limit FPS.
    @interval       The time, which expressed in second in second, between current frame and next. 
    */
	void setAnimationInterval(double interval);
	
	typedef enum
	{
		/// Device oriented vertically, home button on the bottom
		kOrientationPortrait = 0,
		/// Device oriented vertically, home button on the top
		kOrientationPortraitUpsideDown = 1,
		/// Device oriented horizontally, home button on the right
		kOrientationLandscapeLeft = 2,
		/// Device oriented horizontally, home button on the left
		kOrientationLandscapeRight = 3,
	} Orientation;
	
	
    /**
	 @brief	Callback by CCDirector for change device orientation.
	 @orientation    The defination of orientation which CCDirector want change to.
	 @return         The actual orientation of the application.
	 */
    Orientation setOrientation(Orientation orientation);

    /**
    @brief    Run the message loop.
    */
    int run();

	void ccAccelerationUpdate();
    /**
    @brief    Get current applicaiton instance.
    @return Current application instance pointer.
    */
    static CCApplication& sharedApplication();

    /**
    @brief Get current language config
    @return Current language config
    */
    virtual ccLanguageType getCurrentLanguage();
	void updateProjection(void);
protected:
	uint64       m_nAnimationInterval;

	static CCApplication * sm_pSharedApplication;
};

NS_CC_END;
#endif	// end of __CC_APPLICATION_MARMALADE_H__
