#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene : public Layer
{
private:
	void goToGameScene(Ref* sender);
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenuScene);
};

