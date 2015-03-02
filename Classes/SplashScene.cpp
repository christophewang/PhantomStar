#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();

	scene->addChild(layer);
	return scene;
}

bool SplashScene::init()
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(schedule_selector(SplashScene::goToMainMenuScene), DELAY_SPLASH_SCENE);
	auto splashScreen = Sprite::create("Backgrounds/splash.png");
	splashScreen->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(splashScreen);

	return true;
}

void SplashScene::goToMainMenuScene(float delta)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(DELAY_TRANSITION, scene));
}