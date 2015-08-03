#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Entity
{
protected:
	int type;
	float width;
	float height;
	Sprite *sprite;
	PhysicsBody *body;
public:
	Entity() : type(0), width(0), height(0), sprite(nullptr), body(nullptr) {}
	virtual ~Entity() {}

	virtual int getType() const = 0;
	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;
	virtual Sprite* getSprite() const = 0;
	virtual Point getPosition() const = 0;
	virtual float getPositionX() const = 0;
	virtual float getPositionY() const = 0;
};
