#pragma once
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"

USING_NS_CC;

class Bullet : public Entity
{
public:
	Bullet(Layer *layer, Point pos, int type);
	virtual ~Bullet() {}
public:
	void displayBulletImpact(Layer *layer);
	virtual int getType() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual Sprite* getSprite() const;
	virtual Point getPosition() const;
	virtual float getPositionX() const;
	virtual float getPositionY() const;
};
