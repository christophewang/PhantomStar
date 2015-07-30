#ifndef __SHIP_H__
#define __SHIP_H__

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
public:
	int getLife() const;
	void displayLife(Layer *layer, int shipIndex);
	void shakeScreen(Layer *layer, float intensity);
	void updateLife(Layer *layer);
	void incrementLife(Layer *layer);
	void reduceLife(Layer *layer);
	void resetContact();
	void scalingEffect();
	void displayExplosion(Layer *layer);
	Point touchToPoint(Touch* touch);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
	virtual int getType() const override;
	virtual float getWidth() const override;
	virtual float getHeight() const override;
	virtual Sprite* getSprite() const override;
	virtual Point getPosition() const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
};

#endif // __SHIP_H__