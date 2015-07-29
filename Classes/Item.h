#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Item : public Entity
{
public:
	Item(Layer *layer);
	~Item() {}
public:
	virtual int getType() const override;
	virtual float getWidth() const override;
	virtual float getHeight() const override;
	virtual Sprite* getSprite() const override;
	virtual Point getPosition() const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
};

#endif // __ITEM_H__