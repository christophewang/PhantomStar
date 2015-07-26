#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

using namespace cocos2d;

class AppDelegate : private Application
{
public:
	virtual void initGLContextAttrs() override;
	virtual bool applicationDidFinishLaunching() override;
	virtual void applicationDidEnterBackground() override;
	virtual void applicationWillEnterForeground() override;
};

#endif // __APPDELEGATE_H__