#include "GameDialog.h"

bool GameDialog::init()
{
	if (!Node::init())
		return false;
	this->blockPassingTouch();
	this->setupUI();
	return true;
}

void GameDialog::blockPassingTouch()
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

void GameDialog::setupUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto gameDialog = CSLoader::createNode(GAME_DIALOG);
	auto dialogBackground = gameDialog->getChildByName("dialogBackground");
	
	dialogBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	ui::Button *resumeButton = static_cast<ui::Button*>(dialogBackground->getChildByName("resumeButton"));
	resumeButton->setTouchEnabled(true);
	resumeButton->addTouchEventListener(CC_CALLBACK_2(GameDialog::closeDialog, this));
	
	ui::Button *menuButton = static_cast<ui::Button*>(dialogBackground->getChildByName("menuButton"));
	menuButton->setTouchEnabled(true);
	menuButton->addTouchEventListener(CC_CALLBACK_2(GameDialog::goToMainMenuScene, this));
	this->addChild(gameDialog, 4);
}

void GameDialog::closeDialog(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}

void GameDialog::goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		auto scene = MainMenuScene::createScene();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHIP_EXPLOSION);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(DELAY_TRANSITION, scene));
	}
}

