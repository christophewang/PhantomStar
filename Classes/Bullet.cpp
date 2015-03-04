#include "Bullet.h"
#include "GameScene.h"

USING_NS_CC;

Bullet::Bullet(Layer *layer, Point pos, int type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	this->type = type;

	if (this->type == 1)
		this->sprite = Sprite::create("Lasers/laser1.png");
	else if (this->type == 2)
		this->sprite = Sprite::create("Lasers/laser2.png");
	else if (type == 3)
		this->sprite = Sprite::create("Lasers/laser3.png");
	this->sprite->setScaleY(2);
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->sprite->setPosition(Point(pos.x, pos.y + height));

	this->body = PhysicsBody::createBox(this->sprite->getContentSize());

	this->body->setCollisionBitmask(COLLISION_BULLET);
	this->body->setContactTestBitmask(true);
	this->body->setRotationEnable(false);
	this->sprite->setPhysicsBody(this->body);

	auto bulletMoveTo = MoveTo::create(GameScene::speedBullet * visibleSize.height, 
		Point(pos.x + origin.x, this->height * 2 + visibleSize.height + origin.y));
	this->sprite->runAction(bulletMoveTo);

	layer->addChild(this->sprite);
}

void Bullet::displayBulletImpact(Layer *layer)
{
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Lasers/laserImpact1.png");
	animation->addSpriteFrameWithFile("Lasers/laserImpact2.png");
	animation->setDelayPerUnit(0.1);
	auto animate = Animate::create(animation);
	this->sprite->runAction(animate);
	layer->addChild(sprite, 1);
}

int Bullet::getType() const
{
	return this->type;
}

float Bullet::getWidth() const
{
	return this->width;
}

float Bullet::getHeight() const
{
	return this->height;
}

Sprite* Bullet::getSprite() const
{
	return this->sprite;
}

Point Bullet::getPosition() const
{
	return this->sprite->getPosition();
}

float Bullet::getPositionX() const
{
	return this->sprite->getPositionX();
}

float Bullet::getPositionY() const
{
	return this->sprite->getPositionY();
}