#pragma once
#include "cocos2d.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

class GameOverScene : public Layer
{
private:
	void goToGameScene(Ref* sender);
	void goToMainMenuScene(Ref *sender);
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOverScene);
	int checkHighScore();
};

