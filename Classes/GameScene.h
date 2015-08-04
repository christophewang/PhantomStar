#pragma once

#include "cocos2d.h"
#include "Entity.h"
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
	Ship  *ship;

	// Working on Pool Management
	int meteorPoolIndex;
	int bulletPoolIndex;
	int starPoolIndex;
	int itemPoolIndex;
	std::vector<Meteor *> meteorPool;
	std::vector<Bullet *> bulletPool;
	std::vector<Star *> starPool;
	std::vector<Item *> itemPool;

	// Settings
	ui::Button *settingsButton;
	UserDefault *userData;
public:
	GameScene();
	~GameScene();

	static Scene *createScene();
	virtual bool init() override;
	virtual void update(float delta) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent) override;
	CREATE_FUNC(GameScene);

	void createPools();
	void deletePools();
	void displayMeteor();
	void displayBullet();
	void displayStar(const Point &pos, int type);
	void displayItem();

	void checkSoundsSettings();
	void onClickSettings(Ref *sender, ui::Widget::TouchEventType type);
	void showGameDialog();
	void setParallaxBackground();
	void displayGameOver(float delta);
	bool onContactBegin(PhysicsContact &contact);
	void shipCollision(Sprite *shipSprite);
	void meteorCollision(int index);
	void bulletCollision(int index);
	void starCollision(int index);
	void itemCollision(int index);
	
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
	static void playEffect(const char *path);
};