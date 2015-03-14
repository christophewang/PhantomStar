#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Meteor.h"
#include "Bullet.h"
#include "Ship.h"
#include "Star.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "CCParallaxScrollNode.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameDialog.h"
#include "GameOverDialog.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
	Point origin;
	Size visibleSize;
	PhysicsWorld *sceneWorld;
	CCParallaxScrollNode *parallaxBg;
	Label *scoreLabel;
	float timerMeteor;
	float timerBullet;
	Ship *ship;
	std::vector<Meteor *> meteorArray;
	std::vector<Bullet *> bulletArray;
	std::vector<Star *> starArray;
	ui::Button *soundBGMButton;
	UserDefault *def;
public:
	GameScene();
	~GameScene();
public:
	static Scene *createScene();
	virtual bool init();
	virtual void update(float delta);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
	CREATE_FUNC(GameScene);

	void checkBGMSettings();
	void BGMListener(Ref *sender, ui::Widget::TouchEventType type);
	void setParallaxBackground();
	void displayGameOver(float delta);

	bool onContactBegin(PhysicsContact &contact);
	void shipCollision(Sprite *ship);
	void meteorCollision(Sprite *meteor);
	void bulletCollision(Sprite *bullet);
	void starCollision(Sprite *star);
	void bulletUpdate();
	void meteorUpdate();
	void starUpdate();
	
	/* Static Game Proprieties */
	static int scorePoints;
	static int backgroundType;
	static float speedBullet;
	static float speedMeteor;
	static float speedBackground;
	static float frequencyMeteor;
	static float frequencyBullet;
	static void incrementScore(int value);
	static void scaleDifficulty(Layer *layer);
	static void setDefaultValue();
};

#endif // __GAMESCENE_H__