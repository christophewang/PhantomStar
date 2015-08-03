#include "Bullet.h"
#include "GameScene.h"

void Bullet::runBullet(Layer *layer, int index, const Point &pos, int _type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	type = _type;
	if (type == 1)
		sprite = Sprite::createWithSpriteFrameName(LASER_1);
	else if (type == 2)
		sprite = Sprite::createWithSpriteFrameName(LASER_2);
	else if (type == 3)
		sprite = Sprite::createWithSpriteFrameName(LASER_3);
	sprite->setScaleY(1.5);
	width = sprite->getContentSize().width;
	height = sprite->getContentSize().height;

	body = PhysicsBody::createBox(sprite->getContentSize());
	body->setCollisionBitmask(COLLISION_BULLET);
	body->setContactTestBitmask(true);
	body->setRotationEnable(false);
	body->setGravityEnable(false);
	body->setTag(index);
	sprite->setPhysicsBody(body);

	auto bulletMoveTo = MoveTo::create(GameScene::speedBullet * visibleSize.height,
		Point(pos.x + origin.x, height * 2 + visibleSize.height + origin.y));

	auto sequence = Sequence::create(
		bulletMoveTo,
		CallFunc::create(CC_CALLBACK_0(Bullet::resetBullet, this)),
		NULL);

	sprite->setPosition(Point(pos.x, pos.y + height));
	sprite->runAction(sequence);
	layer->addChild(sprite, 2, GAME_OBJECT);
}

void Bullet::resetBullet()
{
	sprite->stopAllActions();
	sprite->removeFromParentAndCleanup(true);
}

void Bullet::displayBulletImpact(Layer *layer)
{
	auto bulletCollision = ParticleSystemQuad::create(BULLET_COLLISION);
	bulletCollision->setPosition(getPosition());
	bulletCollision->setAutoRemoveOnFinish(true);
	layer->addChild(bulletCollision, 2);
}