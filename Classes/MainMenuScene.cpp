#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();

	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("Backgrounds/menu.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto playButton = MenuItemImage::create("UI/playButton.png", "UI/playButtonClicked.png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
	playButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playButton, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	return true;
}

void MainMenuScene::goToGameScene(Ref* sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInB::create(DELAY_TRANSITION, scene));
}