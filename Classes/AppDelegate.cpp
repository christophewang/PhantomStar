#include "AppDelegate.h"
#include "SplashScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview) 
	{
        glview = GLViewImpl::create("Phantom Star");
		glview->setFrameSize(480, 800);
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    auto scene = SplashScene::createScene();
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();
}
