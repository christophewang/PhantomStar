#include "Bullet.h"
#include "GameScene.h"

USING_NS_CC;

Bullet::Bullet(Layer *layer)
{
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->layer = layer;
}

Bullet::~Bullet()
{
}

void Bullet::fireBullet(Vec2 shipPosition)
{
	auto bulletSprite = Sprite::create("Lasers/laserRed01.png");

	bulletSprite->setScaleY(2);
	bulletSprite->setPosition(Point(shipPosition.x, shipPosition.y + bulletSprite->getContentSize().height));
	
	auto bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize());

	bulletBody->setCollisionBitmask(COLLISION_BULLET);
	bulletBody->setContactTestBitmask(true);
	bulletBody->setRotationEnable(false);
	bulletSprite->setPhysicsBody(bulletBody);

	bullets.push_back(bulletSprite);
	layer->addChild(bulletSprite);
	auto bulletMoveBy = MoveBy::create(GameScene::speedBullet * visibleSize.height, Point(0, visibleSize.height));
	bulletSprite->runAction(bulletMoveBy);
}

void Bullet::removeBullet(Sprite *bulletSprite)
{
	bullets.erase(std::remove(bullets.begin(), bullets.end(), bulletSprite), bullets.end());
}

void Bullet::update(float delta)
{
	for (unsigned int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i]->getPosition().y > visibleSize.height + origin.y)
		{
			bullets[i]->removeFromParentAndCleanup(true);
			this->removeBullet(bullets[i]);
		}
	}
	//CCLOG("Bullet size: %i", bullets.size());
}
