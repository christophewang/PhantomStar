#pragma once

#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Star : public Entity
{
public:
	Star() {}
	virtual ~Star() {}

	void runStar(Layer *layer, int index, const Point &pos, int _type);
	void resetStar();
	void displayStarEffect(Layer *layer);

	virtual int getType() const override { return type; }
	virtual float getWidth() const override { return width; }
	virtual float getHeight() const override { return height; }
	virtual Sprite *getSprite() const override { return sprite; }
	virtual Point getPosition() const override { return sprite->getPosition(); }
	virtual float getPositionX() const override { return sprite->getPositionX(); }
	virtual float getPositionY() const override{ return sprite->getPositionY(); }
};