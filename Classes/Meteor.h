#ifndef __METEOR_H__
#define __METEOR_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Meteor : public Entity
{
private:
	int life;
public:
	Meteor(Layer *layer);
	Meteor(Layer *layer, float speed);
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

#endif // __METEOR_H__
