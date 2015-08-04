#include "GameDialog.h"

bool GameDialog::init()
{
	if (!Node::init())
		return false;
	userData = UserDefault::getInstance();
	blockPassingTouch();
	setupUI();
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

	bgmCheckBox = static_cast<ui::CheckBox*>(dialogBackground->getChildByName("bgmCheck"));
	bgmCheckBox->setSelected(userData->getBoolForKey(BGM_KEY));
	bgmCheckBox->addTouchEventListener(CC_CALLBACK_2(GameDialog::bgmListener, this));

	effectCheckBox = static_cast<ui::CheckBox*>(dialogBackground->getChildByName("effectCheck"));
	effectCheckBox->setSelected(userData->getBoolForKey(EFFECT_KEY));
	effectCheckBox->addTouchEventListener(CC_CALLBACK_2(GameDialog::effectListener, this));

	auto resumeButton = static_cast<ui::Button*>(dialogBackground->getChildByName("resumeButton"));
	resumeButton->addTouchEventListener(CC_CALLBACK_2(GameDialog::closeDialog, this));

	auto menuButton = static_cast<ui::Button*>(dialogBackground->getChildByName("menuButton"));
	menuButton->addTouchEventListener(CC_CALLBACK_2(GameDialog::goToMainMenuScene, this));
	addChild(gameDialog, 4);
}

void GameDialog::bgmListener(Ref* sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (bgmCheckBox->isSelected())
			userData->setBoolForKey(BGM_KEY, false);
		else
			userData->setBoolForKey(BGM_KEY, true);
	}
}

void GameDialog::effectListener(Ref* sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (effectCheckBox->isSelected())
			userData->setBoolForKey(EFFECT_KEY, false);
		else
			userData->setBoolForKey(EFFECT_KEY, true);
	}
}

void GameDialog::closeDialog(Ref *sender, ui::Widget::TouchEventType type)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		removeFromParentAndCleanup(true);
		Director::getInstance()->resume();

		if (userData->getBoolForKey(BGM_KEY))
		{
			if (audio->isBackgroundMusicPlaying())
				audio->resumeBackgroundMusic();
			else
				audio->playBackgroundMusic(AUDIO_BACKGROUND, true);
		}
		else
			audio->stopBackgroundMusic();
		
		if (userData->getBoolForKey(EFFECT_KEY))
			audio->resumeAllEffects();
		else
			audio->stopAllEffects();
	}
}

void GameDialog::goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		auto scene = MainMenuScene::createScene();

		audio->stopBackgroundMusic(true);
		audio->stopAllEffects();
		if (userData->getBoolForKey(EFFECT_KEY))
			audio->playEffect(AUDIO_SHIP_EXPLOSION);

		Director::getInstance()->replaceScene(TransitionCrossFade::create(DELAY_TRANSITION, scene));
	}
}

