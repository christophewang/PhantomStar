#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "GameScene.h"
#include "Meteor.h"
#include "CCParallaxScrollNode.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class MainMenuScene : public Layer
{
private:
	Point origin;
	Size visibleSize;
	float timer;
	std::vector<Meteor *> meteorArray;
	CCParallaxScrollNode *parallaxBg;
public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float delta);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
	CREATE_FUNC(MainMenuScene);
	
	void meteorUpdate();
	void setParallaxBackground();
	void rate(Ref *sender);
	void ranking(Ref *sender);
	void donation(Ref *sender);
	void goToGameScene(Ref* sender);
};

#endif // __MAINMENUSCENE_H__
