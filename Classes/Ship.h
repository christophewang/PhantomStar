#ifndef __SHIP_H__
#define __SHIP_H__

#include <cstdlib>
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Ship : public Entity
{
private:
	Size visibleSize;
	Point origin;
	int life;
	Sprite *lifeOne;
	Sprite *lifeTwo;
	Sprite *lifeThree;
	Point touchOffset;
public:
	Ship(Layer *layer);
	virtual ~Ship() {}
public:
	int getLife() const;
	void displayLife(Layer *layer, int shipIndex);
	void reduceLife(Layer *layer);
	void scalingEffect();
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

#endif // __SHIP_H__