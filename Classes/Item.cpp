#include "Item.h"
#include "Definitions.h"
#include "GameScene.h"

Item::Item(Layer* layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//TODO Randomize Items 
	this->type = REPAIR_ITEM;
	this->sprite = Sprite::createWithSpriteFrameName(RED_PILL);

	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->body = PhysicsBody::createCircle(this->width / 2);
	this->body->setCollisionBitmask(COLLISION_ITEM);
	this->body->setContactTestBitmask(true);
	this->body->setDynamic(false);
	this->sprite->setPhysicsBody(this->body);

	auto posX = (rand() % static_cast<int>(visibleSize.width)) + (this->width / 2);
	if (posX + this->width / 2 > visibleSize.width)
		posX = visibleSize.width - this->width / 2;
	this->sprite->setPosition(Point(posX + origin.x, visibleSize.height + this->height + origin.y));

	auto itemMoveto = MoveTo::create(GameScene::speedItem * visibleSize.height,
		Point(posX + origin.x, -this->height + origin.y));

	auto itemRotateBy = RotateBy::create(GameScene::speedItem * visibleSize.height, 360);
	this->sprite->runAction(Spawn::createWithTwoActions(itemRotateBy, itemMoveto));
	layer->addChild(this->sprite, 1, GAME_OBJECT);
}

int Item::getType() const
{
	return this->type;
}

float Item::getWidth() const
{
	return this->width;
}

float Item::getHeight() const
{
	return this->height;
}

Sprite* Item::getSprite() const
{
	return this->sprite;
}

Point Item::getPosition() const
{
	return this->sprite->getPosition();
}

float Item::getPositionX() const
{
	return this->sprite->getPositionX();
}

float Item::getPositionY() const
{
	return this->sprite->getPositionY();
}
