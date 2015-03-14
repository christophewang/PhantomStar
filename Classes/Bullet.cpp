#include "Bullet.h"
#include "GameScene.h"

Bullet::Bullet(Layer *layer, Point pos, int type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	this->type = type;
	if (this->type == 1)
		this->sprite = Sprite::createWithSpriteFrameName(LASER_1);
	else if (this->type == 2)
		this->sprite = Sprite::createWithSpriteFrameName(LASER_2);
	else if (type == 3)
		this->sprite = Sprite::createWithSpriteFrameName(LASER_3);
	this->sprite->setScaleY(1.5);
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->sprite->setPosition(Point(pos.x, pos.y + height));

	this->body = PhysicsBody::createBox(this->sprite->getContentSize());

	this->body->setCollisionBitmask(COLLISION_BULLET);
	this->body->setContactTestBitmask(true);
	this->body->setRotationEnable(false);
	this->body->setGravityEnable(false);
	this->sprite->setPhysicsBody(this->body);

	auto bulletMoveTo = MoveTo::create(GameScene::speedBullet * visibleSize.height, 
		Point(pos.x + origin.x, this->height * 2 + visibleSize.height + origin.y));
	this->sprite->runAction(bulletMoveTo);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHOOT);
	layer->addChild(this->sprite, 2, GAME_OBJECT);
}

void Bullet::displayBulletImpact(Layer *layer)
{
	auto bulletCollision = ParticleSystemQuad::create(BULLET_COLLISION);
	bulletCollision->setPosition(this->getPosition());
	bulletCollision->setAutoRemoveOnFinish(true);
	layer->addChild(bulletCollision, 2);
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