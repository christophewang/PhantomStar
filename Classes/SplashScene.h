#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SplashScene : public Layer
{
private:
	void goToMainMenuScene(float delta);
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(SplashScene);
};

