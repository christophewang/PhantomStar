#ifndef __GAMEOVERDIALOG_H__
#define __GAMEOVERDIALOG_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameOverDialog : public Layer
{
public:
	CREATE_FUNC(GameOverDialog);
	virtual bool init();
	void blockPassingTouch();
	void setupUI();
	void goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type);
	void goToGameScene(Ref *sender, ui::Widget::TouchEventType type);
	int checkHighScore();
};

#endif // __GAMEOVERDIALOG_H__
