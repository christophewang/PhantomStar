#ifndef __STAR_H__
#define __STAR_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Star : public Entity
{
public:
	Star(Layer *layer, Point pos, int type);
	~Star() {}
public:
	void displayStarEffect(Layer *layer);
	virtual int getType() const override;
	virtual float getWidth() const override;
	virtual float getHeight() const override;
	virtual Sprite* getSprite() const override;
	virtual Point getPosition() const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
};

#endif // __STAR_H__
