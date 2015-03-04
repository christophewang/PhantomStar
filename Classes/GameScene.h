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
	Size visibleSize;
	Point origin;
	PhysicsWorld *sceneWorld;
	CCParallaxScrollNode *parallaxBg;
	Ship *ship;
	
	Label *scoreLabel;
	float timerMeteor;
	float timerBullet;

	Star *star;
	std::vector<Meteor *> meteorArray;
	std::vector<Bullet *> bulletArray;
public:
	GameScene();
	~GameScene();
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
	void bulletUpdate();
	void meteorUpdate();
	
	void spawnStar(int type, Point pos);
	void goToGameOverScene();

	static int scorePoints;
	static float speedBullet;
	static float speedMeteor;
	static float speedBackground;
	static float frequencyMeteor;
	static float frequencyBullet;
	static void incrementScore(int value);
	static void setDifficulty();
	static void setDefaultValue();
};

