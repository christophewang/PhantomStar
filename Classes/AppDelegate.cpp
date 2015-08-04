#include "AppDelegate.h"

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview)
	{
		//Computer Resolution
		glview = GLViewImpl::create("Phantom Star");
		glview->setFrameSize(480, 800);
		director->setOpenGLView(glview);
		director->setAnimationInterval(1.0 / 120);
		director->setDisplayStats(true);
	}
	glview->setDesignResolutionSize(540, 960, ResolutionPolicy::FIXED_HEIGHT);

	//TODO Sprite resolution
	//Preload Sound Effects and BGM
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_STAR);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_REPAIR);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_METEOR_EXPLOSION);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_SHIP_COLLISION);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_SHIP_EXPLOSION);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACKGROUND);

	//Preload Sprite in Cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spriteSheet.plist", "spriteSheet.png");

	auto scene = MainMenuScene::createScene();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}
