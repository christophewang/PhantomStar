#include "Ship.h"
#include "GameScene.h"

USING_NS_CC;

Ship::Ship(Layer *layer)
{
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	int shipIndex = rand() % 12 + 1;
	this->life = 4;
	if (shipIndex > 0 && shipIndex <= 4)
		this->type = 1;
	else if (shipIndex > 4 && shipIndex <= 8)
		this->type = 2;
	else
		this->type = 3;
	this->displayLife(layer, shipIndex);
	__String *shipString = __String::createWithFormat("Ships/ship%i.png", shipIndex);
	this->sprite = Sprite::create(shipString->getCString());
	this->sprite->setScale(0.75);
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->sprite->setPosition(Point(this->visibleSize.width / 2 + this->origin.x, this->visibleSize.height / 4 + this->origin.y));
	
	/*auto shield = Sprite::create("Effects/shield1.png");
	shield->setPosition(Point(shipSprite->getContentSize().width / 2, shipSprite->getContentSize().height / 2));
	shipSprite->addChild(shield, 1);*/

	/*auto speed = Sprite::create("Effects/fire13.png");
	speed->setAnchorPoint(Point(0.5, 1));
	speed->setPosition(Point(shipSprite->getContentSize().width / 2, 0));
	shipSprite->addChild(speed, 1);*/

	/*auto emitter = ParticleSystemQuad::create("Effects/firejet.plist");
	emitter->setDuration(ParticleSystem::DURATION_INFINITY);
	emitter->setPosition(shipSprite->getContentSize().width / 2, -10);
	shipSprite->addChild(emitter, 1);*/

	this->body = PhysicsBody::createCircle((this->width * 0.75) / 2);
	this->body->setCollisionBitmask(COLLISION_SHIP);
	this->body->setContactTestBitmask(true);
	this->body->setGravityEnable(false);
	this->body->setRotationEnable(false);
	this->sprite->setPhysicsBody(this->body);

	auto shipBlink = Blink::create(1, 10);
	this->sprite->runAction(shipBlink);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Ship::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Ship::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Ship::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(Ship::onTouchesEnded, this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);

	layer->addChild(this->sprite, 1);
}

int Ship::getType() const
{
	return this->type;
}

int Ship::getLife() const
{
	return this->life;
}

float Ship::getWidth() const
{
	return this->width;
}

float Ship::getHeight() const
{
	return this->height;
}

Sprite* Ship::getSprite() const
{
	return this->sprite;
}

Point Ship::getPosition() const
{
	return this->sprite->getPosition();
}

float Ship::getPositionX() const
{
	return this->sprite->getPositionX();
}

float Ship::getPositionY() const
{
	return this->sprite->getPositionY();
}

void Ship::displayLife(Layer *layer, int shipIndex)
{
	__String *shipLifeString = __String::createWithFormat("Ships/ship%i_life.png", shipIndex);
	this->lifeOne = Sprite::create(shipLifeString->getCString());
	this->lifeTwo = Sprite::create(shipLifeString->getCString());
	this->lifeThree = Sprite::create(shipLifeString->getCString());

	float width = this->lifeOne->getContentSize().width;
	float height = this->lifeOne->getContentSize().height;

	this->lifeOne->setPosition(Point(width + this->origin.x, this->visibleSize.height - height + this->origin.x));
	this->lifeTwo->setPosition(Point(width * 2 + this->origin.x, this->visibleSize.height - height + this->origin.x));
	this->lifeThree->setPosition(Point(width * 3 + this->origin.x, this->visibleSize.height - height + this->origin.x));
	layer->addChild(this->lifeOne, 2);
	layer->addChild(this->lifeTwo, 2);
	layer->addChild(this->lifeThree, 2);
}

void Ship::reduceLife()
{
	this->life--;
	if (this->life == 3)
	{
		this->showDamageOne();
		this->lifeThree->removeFromParentAndCleanup(true);
	}
	else if (this->life == 2)
	{
		this->showDamageTwo();
		this->lifeTwo->removeFromParentAndCleanup(true);
	}
	else if (this->life == 1)
	{
		this->showDamageThree();
		this->lifeOne->removeFromParentAndCleanup(true);
	}
}

void Ship::showDamageOne()
{
	CCLOG("DAMAGE ONEEEEEEEEEEEE");
	Sprite *damage;
	if (this->type == 1)
		damage = Sprite::create("Damage/playerShip1_damage1.png");
	else if (this->type == 2)
		damage = Sprite::create("Damage/playerShip2_damage1.png");
	else if (this->type == 3)
		damage = Sprite::create("Damage/playerShip3_damage1.png");
	damage->setPosition(Point(this->width / 2, this->height / 2));
	this->sprite->addChild(damage, 2);
}

void Ship::showDamageTwo()
{
	CCLOG("DAMAGE TWOOOOOOOOOOO");
	Sprite *damage;
	if (this->type == 1)
		damage = Sprite::create("Damage/playerShip1_damage2.png");
	else if (this->type == 2)
		damage = Sprite::create("Damage/playerShip2_damage2.png");
	else if (this->type == 3)
		damage = Sprite::create("Damage/playerShip3_damage2.png");
	damage->setPosition(Point(this->width / 2, this->height / 2));
	this->sprite->addChild(damage, 2);
}

void Ship::showDamageThree()
{
	CCLOG("DAMAGE THREEEEEEEEEE");
	Sprite *damage;
	if (this->type == 1)
		damage = Sprite::create("Damage/playerShip1_damage3.png");
	else if (this->type == 2)
		damage = Sprite::create("Damage/playerShip2_damage3.png");
	else if (this->type == 3)
		damage = Sprite::create("Damage/playerShip3_damage3.png");
	damage->setPosition(Point(this->width / 2, this->height / 2));
	this->sprite->addChild(damage, 2);
}

Point Ship::touchToPoint(Touch* touch)
{
	return Director::getInstance()->convertToGL(touch->getLocationInView());
}

void Ship::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	this->touchOffset = Point::ZERO;
	for (auto touch : touches)
	{
		if (touch)
			this->touchOffset = this->sprite->getPosition() - this->touchToPoint(touch);
	}
}

void Ship::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	for (auto touch : touches)
	{
		if (touch && this->touchOffset.x && this->touchOffset.y)
		{
			auto position = this->touchToPoint(touch) + this->touchOffset;
			if (position.x < 0)
				position.x = 0;
			if (position.y < 0)
				position.y = 0;
			if (position.x > this->visibleSize.width)
				position.x = this->visibleSize.width;
			if (position.y > this->visibleSize.height)
				position.y = this->visibleSize.height;
			this->sprite->setPosition(position);
		}
	}
}

void Ship::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			auto position = this->touchToPoint(touch) + this->touchOffset;
			if (position.x < 0)
				position.x = 0;
			if (position.y < 0)
				position.y = 0;
			if (position.x > this->visibleSize.width)
				position.x = this->visibleSize.width;
			if (position.y > this->visibleSize.height)
				position.y = this->visibleSize.height;
			this->sprite->setPosition(position);
		}
	}
}