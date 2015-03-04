#pragma once
#include "cocos2d.h"
#include "Meteor.h"
#include "Bullet.h"
#include "Ship.h"
#include "Star.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "CCParallaxScrollNode.h"

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
public:
	GameScene();
	~GameScene() {}
public:
	static Scene *createScene();
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(GameScene);
	void setPhysicsWorld(PhysicsWorld *world);
	void setParallaxBackground();
	bool onContactBegin(PhysicsContact &contact);
	void shipCollision(Sprite *ship);
	void meteorCollision(Sprite *meteor);
	void bulletCollision(Sprite *bullet);
	void starCollision(Sprite *star);
	void bulletUpdate();
	void meteorUpdate();
	void starUpdate();
	void goToGameOverScene(float delta);
	static int scorePoints;
	static float speedBullet;
	static float speedMeteor;
	static float speedBackground;
	static float frequencyMeteor;
	static float frequencyBullet;
	static void incrementScore(int value);
	static void scaleDifficulty(Layer *layer);
	static void setDefaultValue();
};

