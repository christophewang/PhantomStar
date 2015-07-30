#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Meteor.h"
#include "Bullet.h"
#include "Ship.h"
#include "Star.h"
#include "Item.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "CCParallaxScrollNode.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameDialog.h"
#include "GameOverDialog.h"

using namespace cocos2d;

class GameScene : public Layer
{
private:
	Point origin;
	Size visibleSize;
	PhysicsWorld *sceneWorld;
	CCParallaxScrollNode *parallaxBg;
	Label *scoreLabel;
	Label *highScoreLabel;
	float timerMeteor;
	float timerBullet;
	float timerItem;
	Ship *ship;
	std::vector<Meteor *> meteorArray;
	std::vector<Bullet *> bulletArray;
	std::vector<Star *> starArray;
	std::vector<Item *> itemArray;
	ui::Button *settingsButton;
	//ui::Button *soundBGMButton;
	UserDefault *def;
public:
	GameScene();
	~GameScene();
public:
	static Scene *createScene();
	virtual bool init() override;
	virtual void update(float delta) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent) override;
	CREATE_FUNC(GameScene);

	void checkBGMSettings();
	void showSettings(Ref *sender, ui::Widget::TouchEventType type);
	//void BGMListener(Ref *sender, ui::Widget::TouchEventType type);
	void setParallaxBackground();
	void displayGameOver(float delta);

	bool onContactBegin(PhysicsContact &contact);
	void shipCollision(Sprite *ship);
	void meteorCollision(Sprite *meteor);
	void bulletCollision(Sprite *bullet);
	void starCollision(Sprite *star);
	void itemCollision(Sprite *item);
	void bulletUpdate();
	void meteorUpdate();
	void starUpdate();
	void itemUpdate();
	
	/* Static Game Proprieties */
	static int scorePoints;
	static int backgroundType;
	static float speedBullet;
	static float speedMeteor;
	static float speedItem;
	static float speedBackground;
	static float frequencyBullet;
	static float frequencyMeteor;
	static float frequencyItem;
	static void incrementScore(int value);
	static void scaleDifficulty(Layer *layer);
	static void setDefaultValue();
};

#endif // __GAMESCENE_H__