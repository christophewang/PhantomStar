#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();

	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("Backgrounds/gameover.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto retryItem = MenuItemImage::create("UI/play.png", "UI/playClicked.png", CC_CALLBACK_1(GameOverScene::goToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));

	auto menu = Menu::create(retryItem, NULL);
	menu->setPosition(Point::ZERO);

	auto highScoreLabel = Label::createWithTTF("High Score : " + std::to_string(this->checkHighScore()), 
		"Fonts/kenvector_future_thin.ttf", visibleSize.height / 20);
	highScoreLabel->setAlignment(TextHAlignment::CENTER);
	highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + visibleSize.height / 20 + origin.y));

	auto scoreLabel = Label::createWithTTF("Score : " + std::to_string(GameScene::scorePoints), 
		"Fonts/kenvector_future_thin.ttf", visibleSize.height / 20);
	scoreLabel->setAlignment(TextHAlignment::CENTER);
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - visibleSize.height / 20 + origin.y));

	this->addChild(menu);
	this->addChild(scoreLabel, 1);
	this->addChild(highScoreLabel, 1);
	return true;
}

/*void GameOverScene::goToMainMenuScene(Ref *sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(DELAY_TRANSITION, scene));
}*/

void GameOverScene::goToGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInB::create(DELAY_TRANSITION, scene));
}

int GameOverScene::checkHighScore()
{
	UserDefault *def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
	if (GameScene::scorePoints > highScore)
	{
		highScore = GameScene::scorePoints;
		def->setIntegerForKey("HIGHSCORE", highScore);
	}
	return highScore;
}