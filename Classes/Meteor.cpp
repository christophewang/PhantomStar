#include "Meteor.h"
#include "GameScene.h"

Meteor::Meteor(Layer *layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto meteorIndex = 0;

	if (GameScene::scorePoints < 10000)
		meteorIndex = rand() % 8 + 1;
	else
		meteorIndex = rand() % 16 + 1;

	if (meteorIndex > 0 && meteorIndex <= 4)
		this->type = 3;
	else if (meteorIndex > 4 && meteorIndex <= 6)
		this->type = 2;
	else if (meteorIndex > 6 && meteorIndex <= 8)
		this->type = 1;
	else
		this->type = 0;
	__String *meteorString = __String::createWithFormat(METEOR, meteorIndex);

	this->sprite = Sprite::createWithSpriteFrameName(meteorString->getCString());
	this->body = PhysicsBody::createCircle(this->sprite->getContentSize().width / 2);
	this->body->setCollisionBitmask(COLLISION_METEOR);
	this->body->setContactTestBitmask(true);
	this->body->setDynamic(false);
	this->sprite->setPhysicsBody(this->body);
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;

	float posX = (rand() % static_cast<int>(visibleSize.width)) + (this->width / 2);
	if (posX + this->width / 2 > visibleSize.width)
		posX = visibleSize.width - this->width / 2;
	this->sprite->setPosition(Point(posX + origin.x, visibleSize.height + this->height + origin.y));

	auto meteorMoveTo = MoveTo::create(GameScene::speedMeteor * visibleSize.height,
		Point(posX + origin.x, -this->height + origin.y));
	auto meteorRotateBy = RotateBy::create(GameScene::speedMeteor * visibleSize.height, 360);
	this->sprite->runAction(Spawn::createWithTwoActions(meteorRotateBy, meteorMoveTo));
	layer->addChild(this->sprite, 1, GAME_OBJECT);
}

Meteor::Meteor(Layer *layer, float speed)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto meteorIndex = rand() % 16 + 1;

	if (meteorIndex > 0 && meteorIndex <= 4)
		this->type = 3;
	else if (meteorIndex > 4 && meteorIndex <= 6)
		this->type = 2;
	else if (meteorIndex > 6 && meteorIndex <= 8)
		this->type = 1;
	else
		this->type = 0;
	__String *meteorString = __String::createWithFormat(METEOR, meteorIndex);

	this->sprite = Sprite::createWithSpriteFrameName(meteorString->getCString());
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;

	auto posX = (rand() % static_cast<int>(visibleSize.width)) + (this->width / 2);
	if (posX + this->width / 2 > visibleSize.width)
		posX = visibleSize.width - this->width / 2;
	this->sprite->setPosition(Point(posX + origin.x, visibleSize.height + this->height + origin.y));

	auto meteorMoveTo = MoveTo::create(speed * visibleSize.height,
		Point(posX + origin.x, -this->height + origin.y));
	auto meteorRotateBy = RotateBy::create(speed * visibleSize.height, 360);
	this->sprite->runAction(Spawn::createWithTwoActions(meteorRotateBy, meteorMoveTo));
	layer->addChild(this->sprite, 1, GAME_OBJECT);
}

void Meteor::displayExplosion(Layer *layer)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_EXPLOSION);
	auto explosion = ParticleSystemQuad::create(METEOR_EXPLOSION);
	explosion->setPosition(this->getPosition());
	explosion->setAutoRemoveOnFinish(true);
	layer->addChild(explosion, 1);
}

int Meteor::getType() const
{
	return this->type;
}

float Meteor::getWidth() const
{
	return this->width;
}

float Meteor::getHeight() const
{
	return this->height;
}

Sprite* Meteor::getSprite() const
{
	return this->sprite;
}

Point Meteor::getPosition() const
{
	return this->sprite->getPosition();
}

float Meteor::getPositionX() const
{
	return this->sprite->getPositionX();
}

float Meteor::getPositionY() const
{
	return this->sprite->getPositionY();
}