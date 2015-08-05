#include "GameOverDialog.h"
#include "GooglePlayServices.h"

bool GameOverDialog::init()
{
	if (!Layer::init())
		return false;
	
	blockPassingTouch();
	setupUI();
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

	auto highScoreLabel = static_cast<ui::Text *>(dialogBackground->getChildByName("highScoreLabel"));
	highScoreLabel->setString(String::createWithFormat("Best: %d", checkHighScore())->getCString());

	auto scoreLabel = static_cast<ui::Text *>(dialogBackground->getChildByName("scoreLabel"));
	scoreLabel->setString(String::createWithFormat("Current: %d", GameScene::scorePoints)->getCString());

	auto resumeButton = static_cast<ui::Button*>(dialogBackground->getChildByName("retryButton"));
	resumeButton->addTouchEventListener(CC_CALLBACK_2(GameOverDialog::goToGameScene, this));

	auto menuButton = static_cast<ui::Button*>(dialogBackground->getChildByName("menuButton"));
	menuButton->addTouchEventListener(CC_CALLBACK_2(GameOverDialog::goToMainMenuScene, this));
	this->addChild(gameOverDialog, 4);
	
	//Google Play Input Score
	if (NativeUtils::isSignedIn())
		NativeUtils::submitScore(RANKING, GameScene::scorePoints);
}

void GameOverDialog::goToGameScene(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		removeFromParentAndCleanup(true);
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(TransitionSlideInB::create(DELAY_TRANSITION, scene));
	}
}

void GameOverDialog::goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		removeFromParentAndCleanup(true);
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(DELAY_TRANSITION, scene));
	}
}

int GameOverDialog::checkHighScore()
{
	auto userData = UserDefault::getInstance();

	auto highScore = userData->getIntegerForKey(HIGHSCORE_KEY, 0);
	if (GameScene::scorePoints > highScore)
	{
		highScore = GameScene::scorePoints;
		userData->setIntegerForKey(HIGHSCORE_KEY, highScore);
	}
	return highScore;
}