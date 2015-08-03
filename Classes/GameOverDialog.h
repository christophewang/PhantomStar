#pragma once

#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "NativeUtils.h"

using namespace cocos2d;

class GameOverDialog : public Layer
{
public:
	CREATE_FUNC(GameOverDialog);

	virtual bool init() override;
	void blockPassingTouch();
	void setupUI();
	void goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type);
	void goToGameScene(Ref *sender, ui::Widget::TouchEventType type);
	int checkHighScore();
};
