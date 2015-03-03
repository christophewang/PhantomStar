#include "Meteor.h"
#include "GameScene.h"

USING_NS_CC;

Meteor::Meteor(Layer *layer)
	: type(0), life(0), width(0), height(0), sprite(nullptr), body(nullptr)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	int meteorIndex = rand() % 8 + 1;

	if (meteorIndex > 0 && meteorIndex <= 4)
	{
		this->type = 3;
		this->life = 3;
	}
	else if (meteorIndex > 4 && meteorIndex <= 6)
	{
		this->type = 2;
		this->life = 2;
	}
	else if (meteorIndex > 6 && meteorIndex <= 8)
	{
		this->type = 1;
		this->life = 1;
	}
	__String *meteorString = __String::createWithFormat("Meteors/meteor%i.png", meteorIndex);
	
	this->sprite = Sprite::create(meteorString->getCString());
	this->body = PhysicsBody::createCircle(this->sprite->getContentSize().width / 2);
	this->body->setCollisionBitmask(COLLISION_METEOR);
	this->body->setContactTestBitmask(true);
	this->body->setDynamic(false);
	this->sprite->setPhysicsBody(this->body);

	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;

	float posX = (rand() % (int)visibleSize.width) + (this->width / 2);

	if (posX + this->width / 2 > visibleSize.width)
		posX = visibleSize.width - this->width / 2;

	this->sprite->setPosition(Point(posX + origin.x, visibleSize.height + this->height + origin.y));

	auto meteorMoveTo = MoveTo::create(GameScene::speedMeteor * visibleSize.height, 
		Point(posX + origin.x, -this->height + origin.y));
	auto meteorRotateBy = RotateBy::create(GameScene::speedMeteor * visibleSize.height, 360);
	this->sprite->runAction(Spawn::createWithTwoActions(meteorRotateBy, meteorMoveTo));

	layer->addChild(this->sprite);
}

int Meteor::getType() const
{
	return this->type;
}

int Meteor::getLife() const
{
	return this->life;
}

void Meteor::reduceLife()
{
	this->life--;
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

Sprite* Meteor::getSprite() const
{
	return this->sprite;
}