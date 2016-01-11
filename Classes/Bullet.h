#pragma once

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Bullet : public Entity
{
public:
	Bullet() {}
	virtual ~Bullet() {}

    void runBullet(Layer *layer, int index, const cocos2d::Point &pos, int _type);
	void resetBullet();
	void displayBulletImpact(Layer *layer);

	virtual int getType() const override { return type; }
	virtual float getWidth() const override { return width; }
	virtual float getHeight() const override { return height; }
	virtual Sprite *getSprite() const override { return sprite; }
    virtual cocos2d::Point getPosition() const override { return sprite->getPosition(); }
	virtual float getPositionX() const override { return sprite->getPositionX(); }
	virtual float getPositionY() const override{ return sprite->getPositionY(); }
};