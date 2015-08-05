#pragma once

#include "cocos2d.h"
#include "Definitions.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;

class OptionDialog : public Layer
{
private:
	ui::CheckBox *bgmCheckBox;
	ui::CheckBox *effectCheckBox;
	UserDefault* userData;
public:
	CREATE_FUNC(OptionDialog);
	virtual bool init() override;

	void blockPassingTouch();
	void setupUI();
	void bgmListener(Ref *sender, ui::Widget::TouchEventType type);
	void effectListener(Ref *sender, ui::Widget::TouchEventType type);
	void closeDialog(Ref *sender, ui::Widget::TouchEventType type);
};