#pragma once
#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Meteor
{
private:
	int type;
	int life;
	float width;
	float height;
	Sprite *sprite;
	PhysicsBody *body;
public:
	Meteor(Layer *layer);
	~Meteor() {}
	int getType() const;
	int getLife() const;
	void reduceLife();
	Point getPosition() const;
	float getPositionX() const;
	float getPositionY() const;
	Sprite *getSprite() const;
};
