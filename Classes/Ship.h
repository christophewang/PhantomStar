#pragma once
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"

USING_NS_CC;

class Ship : public Entity
{
private:
	int life;
	Size visibleSize;
	Point origin;
	Point touchOffset;
	Sprite *lifeOne;
	Sprite *lifeTwo;
	Sprite *lifeThree;
public:
	Ship(Layer *layer);
	virtual ~Ship() {}
public:
	int getLife() const;
	void displayLife(Layer *layer, int shipIndex);
	void reduceLife();
	void showDamageOne();
	void showDamageTwo();
	void showDamageThree();
	void displayExplosion(Layer *layer);
	Point touchToPoint(Touch* touch);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
	virtual int getType() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual Sprite* getSprite() const;
	virtual Point getPosition() const;
	virtual float getPositionX() const;
	virtual float getPositionY() const;
};
