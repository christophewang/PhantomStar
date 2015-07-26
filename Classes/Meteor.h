#ifndef __METEOR_H__
#define __METEOR_H__

#include <cstdlib>
#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Meteor : public Entity
{
public:
	Meteor(Layer *layer);
	Meteor(Layer *layer, float speed);
	virtual ~Meteor() {}
public:
	void displayExplosion(Layer *layer);
	virtual int getType() const override;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual cocos2d::Sprite *getSprite() const;
	virtual Point getPosition() const;
	virtual float getPositionX() const;
	virtual float getPositionY() const;
};

#endif // __METEOR_H__
