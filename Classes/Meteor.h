#pragma once
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"

USING_NS_CC;

class Meteor : public Entity
{
private:
	int life;
public:
	Meteor(Layer *layer);
	virtual ~Meteor() {}
public:
	int getLife() const;
	void reduceLife();
	void displayExplosion(Layer *layer);
	virtual int getType() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual cocos2d::Sprite *getSprite() const;
	virtual Point getPosition() const;
	virtual float getPositionX() const;
	virtual float getPositionY() const;
};
