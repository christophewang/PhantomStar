#pragma once

#include <cstdlib>
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Meteor : public Entity
{
public:
	Meteor() {}
	virtual ~Meteor() {}

	void runMeteor(Layer *layer, int index, float speed);
	void resetMeteor();
	void displayExplosion(Layer *layer);

	virtual int getType() const override { return type; }
	virtual float getWidth() const override { return width; }
	virtual float getHeight() const override { return height; }
	virtual Sprite *getSprite() const override { return sprite; }
	virtual Point getPosition() const override { return sprite->getPosition(); }
	virtual float getPositionX() const override { return sprite->getPositionX(); }
	virtual float getPositionY() const override{ return sprite->getPositionY(); }
};
