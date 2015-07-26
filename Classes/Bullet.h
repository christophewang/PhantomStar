#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Bullet : public Entity
{
public:
	Bullet(Layer *layer, Point pos, int type);
	virtual ~Bullet() {}
public:
	void displayBulletImpact(Layer *layer);
	virtual int getType() const override;
	virtual float getWidth() const override;
	virtual float getHeight() const override;
	virtual Sprite* getSprite() const override;
	virtual Point getPosition() const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
};

#endif // __BULLET_H__