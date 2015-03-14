#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

class AppDelegate : private Application
{
public:
    virtual void initGLContextAttrs();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};

#endif // __APPDELEGATE_H__