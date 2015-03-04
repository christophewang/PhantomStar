#include "Star.h"

USING_NS_CC;

Star::Star(Layer *layer, Point pos, int type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	this->type = type;

	__String *starPath = __String::createWithFormat("Effects/starPoint%i.png", this->type);
	this->sprite = Sprite::create(starPath->getCString());
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->body = PhysicsBody::createCircle(this->width / 2);
	this->body->setCollisionBitmask(COLLISION_STAR);
	this->body->setContactTestBitmask(true);
	this->body->setDynamic(false);
	this->sprite->setPhysicsBody(this->body);
	this->sprite->setPosition(Point(pos.x + origin.x, pos.y + origin.y));

	ccBezierConfig bezier;
	if (pos.x >= visibleSize.width / 2)
	{
		bezier.controlPoint_1 = Point(pos.x / 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x * 2 + origin.x, -this->height + origin.y);
	}
	else
	{
		bezier.controlPoint_1 = Point(pos.x * 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x / 2 + origin.x, -this->height + origin.y);
	}
	auto starBezierTo = BezierTo::create(SPEED_STARS * visibleSize.height, bezier);
	this->sprite->runAction(starBezierTo);
	layer->addChild(this->sprite, 1);
}

void Star::displayStarEffect(Layer *layer)
{
	__String *starPath = __String::createWithFormat("Particles/star%i.plist", this->type);
	auto starEffect = ParticleSystemQuad::create(starPath->getCString());
	starEffect->setPosition(this->getPosition());
	starEffect->setAutoRemoveOnFinish(true);
	layer->addChild(starEffect, 1);
}

int Star::getType() const
{
	return this->type;
}

float Star::getWidth() const
{
	return this->width;
}

float Star::getHeight() const
{
	return this->height;
}

Sprite* Star::getSprite() const
{
	return this->sprite;
}

Point Star::getPosition() const
{
	return this->sprite->getPosition();
}

float Star::getPositionX() const
{
	return this->sprite->getPositionX();
}

float Star::getPositionY() const
{
	return this->sprite->getPositionY();
}