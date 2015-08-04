#pragma once

#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameDialog : public Layer
{
private:
	ui::CheckBox *bgmCheckBox;
	ui::CheckBox *effectCheckBox;
	UserDefault* userData;
public:
	CREATE_FUNC(GameDialog);
	virtual bool init() override;

	void blockPassingTouch();
	void setupUI();
	void bgmListener(Ref *sender, ui::Widget::TouchEventType type);
	void effectListener(Ref *sender, ui::Widget::TouchEventType type);
	void goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type);
	void closeDialog(Ref *sender, ui::Widget::TouchEventType type);
};
