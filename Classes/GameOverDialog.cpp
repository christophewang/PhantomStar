#include "GameOverDialog.h"

bool GameOverDialog::init()
{
	if (!Layer::init())
		return false;
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	this->blockPassingTouch();
	this->setupUI();
	return true;
}

void GameOverDialog::blockPassingTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event){
		if (event->getCurrentTarget()->isVisible() == false)
			return false;
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameOverDialog::setupUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto gameOverDialog = CSLoader::createNode(GAMEOVER_DIALOG);
	auto dialogBackground = gameOverDialog->getChildByName("dialogBackground");
	dialogBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	ui::Text *highScoreLabel = static_cast<ui::Text *>(dialogBackground->getChildByName("highScoreLabel"));
	highScoreLabel->setString(String::createWithFormat("Best: %d", this->checkHighScore())->getCString());

	ui::Text *scoreLabel = static_cast<ui::Text *>(dialogBackground->getChildByName("scoreLabel"));
	scoreLabel->setString(String::createWithFormat("Current: %d", GameScene::scorePoints)->getCString());

	ui::Button *resumeButton = static_cast<ui::Button*>(dialogBackground->getChildByName("retryButton"));
	resumeButton->setTouchEnabled(true);
	resumeButton->addTouchEventListener(CC_CALLBACK_2(GameOverDialog::goToGameScene, this));

	ui::Button *menuButton = static_cast<ui::Button*>(dialogBackground->getChildByName("menuButton"));
	menuButton->setTouchEnabled(true);
	menuButton->addTouchEventListener(CC_CALLBACK_2(GameOverDialog::goToMainMenuScene, this));
	this->addChild(gameOverDialog, 4);
}

void GameOverDialog::goToGameScene(Ref *sender, ui::Widget::TouchEventType type)
{
	this->removeFromParentAndCleanup(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_CLICK);
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInB::create(DELAY_TRANSITION, scene));
}

void GameOverDialog::goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type)
{
	this->removeFromParentAndCleanup(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_CLICK);
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(DELAY_TRANSITION, scene));
}

int GameOverDialog::checkHighScore()
{
	UserDefault *def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey(HIGHSCORE_KEY, 0);
	if (GameScene::scorePoints > highScore)
	{
		highScore = GameScene::scorePoints;
		def->setIntegerForKey(HIGHSCORE_KEY, highScore);
	}
	return highScore;
}