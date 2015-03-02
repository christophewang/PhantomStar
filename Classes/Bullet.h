#pragma once
#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Bullet
{
private:
	Size visibleSize;
	Vec2 origin;
	Layer *layer;
	std::vector<Sprite *> bullets;
public:
	Bullet(Layer *layer);
	~Bullet();
	void fireBullet(Vec2 shipPosition);
	void removeBullet(Sprite *bulletSprite);
	void update(float delta);
};

