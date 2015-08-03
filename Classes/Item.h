#pragma once

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Item : public Entity
{
public:
	Item() {}
	virtual ~Item() {}

	void runItem(Layer *layer, int index);
	void resetItem();
	void displayItemEffect(Layer *layer);

	virtual int getType() const override { return type; }
	virtual float getWidth() const override { return width; }
	virtual float getHeight() const override { return height; }
	virtual Sprite *getSprite() const override { return sprite; }
	virtual Point getPosition() const override { return sprite->getPosition(); }
	virtual float getPositionX() const override { return sprite->getPositionX(); }
	virtual float getPositionY() const override{ return sprite->getPositionY(); }
};