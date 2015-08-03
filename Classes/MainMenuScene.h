#pragma once

#include <cstdlib>
#include "cocos2d.h"
#include "Definitions.h"
#include "GameScene.h"
#include "Meteor.h"
#include "CCParallaxScrollNode.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "NativeUtils.h"

using namespace cocos2d;

class MainMenuScene : public Layer
{
private:
	Point origin;
	Size visibleSize;
	float timer;
	int meteorPoolIndex;
	std::vector<Meteor *> meteorPool;
	CCParallaxScrollNode *parallaxBg;
public:
	static Scene* createScene();
	virtual bool init() override;
	virtual void update(float delta) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent) override;
	CREATE_FUNC(MainMenuScene);
	
	void createPools();
	void deletePools();
	void displayMeteor();
	void setParallaxBackground();
	void rate(Ref *sender, ui::Widget::TouchEventType type);
	void ranking(Ref *sender, ui::Widget::TouchEventType type);
	void donation(Ref *sender, ui::Widget::TouchEventType type);
	void goToGameScene(Ref* sender, ui::Widget::TouchEventType type);
};