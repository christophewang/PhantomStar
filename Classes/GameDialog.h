#ifndef __GAMEDIALOG_H__
#define __GAMEDIALOG_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameDialog : public Layer
{
public:
	CREATE_FUNC(GameDialog);
	virtual bool init();
	void blockPassingTouch();
	void setupUI();
	void goToMainMenuScene(Ref *sender, ui::Widget::TouchEventType type);
	void closeDialog(Ref *sender, ui::Widget::TouchEventType type);
};

#endif // __GAMEDIALOG_H__
