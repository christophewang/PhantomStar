#pragma once
#include "cocos2d.h"
#include "Meteor.h"
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
	Vec2 origin;
	PhysicsWorld *sceneWorld;
	CCParallaxScrollNode *parallaxBg;
	Ship *ship;
	
	Label *scoreLabel;
	float timerMeteor;

	Star *star;
	std::vector<Meteor *> meteorArray;
public:
	~GameScene();
	static Scene *createScene();
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(GameScene);

	void setPhysicsWorld(PhysicsWorld *world);
	void setParallaxBackground();
	bool onContactBegin(PhysicsContact &contact);

	void meteorCollision(Sprite *meteor);
	void meteorUpdate();

	void spawnStar(int type, Point pos);

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

