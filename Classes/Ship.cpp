#include "Ship.h"

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
	__String *shipString = __String::createWithFormat(SHIP, shipIndex);
	this->sprite = Sprite::createWithSpriteFrameName(shipString->getCString());
	this->sprite->setScale(0.75);
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->sprite->setPosition(Point(this->visibleSize.width / 2 + this->origin.x, 
		this->visibleSize.height / 4 + this->origin.y));
	auto speed = Sprite::createWithSpriteFrameName(EMITTER);
	speed->setAnchorPoint(Point(0.5, 1));
	speed->setPosition(Point(this->width / 2, 0));
	this->sprite->addChild(speed, 1, GAME_OBJECT);

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
	layer->addChild(this->sprite, 2);
}

void Ship::displayLife(Layer *layer, int shipIndex)
{
	/*__String *shipLifeString = __String::createWithFormat(SHIP_LIFE, shipIndex);
	this->lifeOne = Sprite::createWithSpriteFrameName(shipLifeString->getCString());
	this->lifeTwo = Sprite::createWithSpriteFrameName(shipLifeString->getCString());
	this->lifeThree = Sprite::createWithSpriteFrameName(shipLifeString->getCString());*/

	this->lifeOne = Sprite::createWithSpriteFrameName(RED_PILL);
	this->lifeTwo = Sprite::createWithSpriteFrameName(RED_PILL);
	this->lifeThree = Sprite::createWithSpriteFrameName(RED_PILL);

	float width = this->lifeOne->getContentSize().width;
	float height = this->lifeOne->getContentSize().height;

	this->lifeOne->setPosition(Point(width + this->origin.x, this->visibleSize.height - height + this->origin.x));
	this->lifeTwo->setPosition(Point(width * 2 + this->origin.x, this->visibleSize.height - height + this->origin.x));
	this->lifeThree->setPosition(Point(width * 3 + this->origin.x, this->visibleSize.height - height + this->origin.x));
	layer->addChild(this->lifeOne, 3);
	layer->addChild(this->lifeTwo, 3);
	layer->addChild(this->lifeThree, 3);
}

void Ship::reduceLife(Layer *layer)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_COLLISION);

	//TODO SHIP COLLISION PARTICLE
	auto shipCollision = ParticleSystemQuad::create(SHIP_COLLISION);
	shipCollision->setPosition(Point(this->getPositionX(), this->getPositionY() - this->getHeight() / 2));
	shipCollision->setAutoRemoveOnFinish(true);
	layer->addChild(shipCollision, 2);
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

void Ship::scalingEffect()
{
	this->sprite->stopAllActions();
	this->sprite->runAction(Sequence::create(
		ScaleBy::create(0.125f, 1.2f),
		ScaleBy::create(0.125f, 0.9f),
		nullptr
		));
	this->sprite->setScale(0.75);
}

void Ship::showDamageOne()
{
	Sprite *damage = nullptr;
	if (this->type == 1)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_1_1);
	else if (this->type == 2)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_2_1);
	else if (this->type == 3)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_3_1);
	damage->setPosition(Point(this->width / 2, this->height / 2));
	this->sprite->addChild(damage, 2);
}

void Ship::showDamageTwo()
{
	Sprite *damage;
	if (this->type == 1)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_1_2);
	else if (this->type == 2)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_2_2);
	else if (this->type == 3)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_3_2);
	damage->setPosition(Point(this->width / 2, this->height / 2));
	this->sprite->addChild(damage, 2);
}

void Ship::showDamageThree()
{
	Sprite *damage;
	if (this->type == 1)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_1_3);
	else if (this->type == 2)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_2_3);
	else if (this->type == 3)
		damage = Sprite::createWithSpriteFrameName(DAMAGE_3_3);
	damage->setPosition(Point(this->width / 2, this->height / 2));
	this->sprite->addChild(damage, 2);
}

void Ship::displayExplosion(Layer *layer)
{
	auto shipExplosion = ParticleSystemQuad::create(SHIP_EXPLOSION);
	shipExplosion->setPosition(this->getPosition());
	shipExplosion->setAutoRemoveOnFinish(true);
	layer->addChild(shipExplosion, 2);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHIP_EXPLOSION);
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
			this->scalingEffect();
		}
	}
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