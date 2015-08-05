#include "OptionDialog.h"

bool OptionDialog::init()
{
	if (!Node::init())
		return false;
	userData = UserDefault::getInstance();
	blockPassingTouch();
	setupUI();
	return true;
}

void OptionDialog::blockPassingTouch()
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

void OptionDialog::setupUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto optionDialog = CSLoader::createNode(OPTION_DIALOG);
	auto dialogBackground = optionDialog->getChildByName("dialogBackground");

	dialogBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2.8 + origin.y));

	bgmCheckBox = static_cast<ui::CheckBox*>(dialogBackground->getChildByName("bgmCheck"));
	bgmCheckBox->setSelected(userData->getBoolForKey(BGM_KEY, true));
	bgmCheckBox->addTouchEventListener(CC_CALLBACK_2(OptionDialog::bgmListener, this));

	effectCheckBox = static_cast<ui::CheckBox*>(dialogBackground->getChildByName("effectCheck"));
	effectCheckBox->setSelected(userData->getBoolForKey(EFFECT_KEY, true));
	effectCheckBox->addTouchEventListener(CC_CALLBACK_2(OptionDialog::effectListener, this));

	auto returnButton = static_cast<ui::Button*>(dialogBackground->getChildByName("returnButton"));
	returnButton->addTouchEventListener(CC_CALLBACK_2(OptionDialog::closeDialog, this));

	addChild(optionDialog, 5);
}

void OptionDialog::bgmListener(Ref* sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (bgmCheckBox->isSelected())
			userData->setBoolForKey(BGM_KEY, false);
		else
			userData->setBoolForKey(BGM_KEY, true);
	}
}

void OptionDialog::effectListener(Ref* sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (effectCheckBox->isSelected())
			userData->setBoolForKey(EFFECT_KEY, false);
		else
			userData->setBoolForKey(EFFECT_KEY, true);
	}
}

void OptionDialog::closeDialog(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		removeFromParentAndCleanup(true);
	}
}