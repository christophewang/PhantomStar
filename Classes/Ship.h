#pragma once
#include "cocos2d.h"
#include "Definitions.h"
#include "Bullet.h"

USING_NS_CC;

class Ship
{
private:
	Size visibleSize;
	Vec2 origin;
	Sprite *shipSprite;
	Point touchOffset;
	Bullet *bullet;
	float bulletTimer;
public:
	Ship(Layer *layer);
	~Ship();

	Point touchToPoint(Touch* touch);
	bool isTouchingSprite(Touch* touch);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
	void update(float delta);
	Bullet *getBullet();
};

