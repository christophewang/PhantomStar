#pragma once

#include <cstdlib>
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Ship : public Entity
{
private:
	Size visibleSize;
	Point origin;
	int life;
	Sprite *lifeOne;
	Sprite *lifeTwo;
	Sprite *lifeThree;
	Sprite *damageOne;
	Sprite *damageTwo;
	Sprite *damageThree;
	Point touchOffset;
public:
	Ship(Layer *layer);
	virtual ~Ship() {}

	int getLife() const;
	void displayLife(Layer *layer, int shipIndex);
	void shakeScreen(Layer *layer, float intensity);
	void updateLife(Layer *layer);
	void incrementLife(Layer *layer);
	void reduceLife(Layer *layer);
	void resetShip();
	void scalingEffect();
	void displayCollision(Layer *layer);
	void displayExplosion(Layer *layer);

	//Ship Touch Control
	Point touchToPoint(Touch* touch);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

	virtual int getType() const override { return type; }
	virtual float getWidth() const override { return width; }
	virtual float getHeight() const override { return height; }
	virtual Sprite *getSprite() const override { return sprite; }
	virtual Point getPosition() const override { return sprite->getPosition(); }
	virtual float getPositionX() const override { return sprite->getPositionX(); }
	virtual float getPositionY() const override{ return sprite->getPositionY(); }
};