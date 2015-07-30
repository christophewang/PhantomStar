#include "Ship.h"
#include "BodyParser.h"

Ship::Ship(Layer *layer)
{
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	int shipIndex = rand() % 12 + 1;
	this->life = 4;

	if (shipIndex > 0 && shipIndex <= 4)
	{
		this->type = 1;
		BodyParser::getInstance()->parseJsonFile(BODY_SHIP1);
		this->damageOne = Sprite::createWithSpriteFrameName(DAMAGE_1_1);
		this->damageTwo = Sprite::createWithSpriteFrameName(DAMAGE_1_2);
		this->damageThree = Sprite::createWithSpriteFrameName(DAMAGE_1_3);
	}
	else if (shipIndex > 4 && shipIndex <= 8)
	{
		this->type = 2;
		BodyParser::getInstance()->parseJsonFile(BODY_SHIP2);
		this->damageOne = Sprite::createWithSpriteFrameName(DAMAGE_2_1);
		this->damageTwo = Sprite::createWithSpriteFrameName(DAMAGE_2_2);
		this->damageThree = Sprite::createWithSpriteFrameName(DAMAGE_2_3);
	}
	else
	{
		this->type = 3;
		BodyParser::getInstance()->parseJsonFile(BODY_SHIP3);
		this->damageOne = Sprite::createWithSpriteFrameName(DAMAGE_3_1);
		this->damageTwo = Sprite::createWithSpriteFrameName(DAMAGE_3_2);
		this->damageThree = Sprite::createWithSpriteFrameName(DAMAGE_3_3);
	}

	this->displayLife(layer, shipIndex);
	auto shipString = __String::createWithFormat(SHIP, shipIndex);
	this->sprite = Sprite::createWithSpriteFrameName(shipString->getCString());
	this->width = this->sprite->getContentSize().width;
	this->height = this->sprite->getContentSize().height;
	this->sprite->setPosition(Point(this->visibleSize.width / 2 + this->origin.x, 
		this->visibleSize.height / 4 + this->origin.y));

	/*auto speed = Sprite::createWithSpriteFrameName(EMITTER);
	speed->setAnchorPoint(Point(0.5, 1));
	speed->setPosition(Point(this->width / 2, 0));
	this->sprite->addChild(speed, 1, GAME_OBJECT);*/

	this->body = BodyParser::getInstance()->bodyFormJson(this->sprite, "Ship");
	this->body->setCollisionBitmask(COLLISION_SHIP);
	this->body->setContactTestBitmask(true);
	this->body->setGravityEnable(false);
	this->body->setRotationEnable(false);
	this->sprite->setPhysicsBody(this->body);

	auto shipBlink = Blink::create(1, 10);
	this->sprite->runAction(shipBlink);

	this->damageOne->setPosition(Point(this->width / 2, this->height / 2));
	this->damageTwo->setPosition(Point(this->width / 2, this->height / 2));
	this->damageThree->setPosition(Point(this->width / 2, this->height / 2));
	this->damageOne->setVisible(false);
	this->damageTwo->setVisible(false);
	this->damageThree->setVisible(false);
	this->sprite->addChild(damageOne, 2);
	this->sprite->addChild(damageTwo, 2);
	this->sprite->addChild(damageThree, 2);

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
	auto shipLifeString = __String::createWithFormat(SHIP_LIFE, shipIndex);
	this->lifeOne = Sprite::createWithSpriteFrameName(shipLifeString->getCString());
	this->lifeTwo = Sprite::createWithSpriteFrameName(shipLifeString->getCString());
	this->lifeThree = Sprite::createWithSpriteFrameName(shipLifeString->getCString());

	auto width = this->lifeOne->getContentSize().width;
	auto height = this->lifeOne->getContentSize().height;

	this->lifeOne->setPosition(Point(width + this->origin.x, this->visibleSize.height - height + this->origin.x));
	this->lifeTwo->setPosition(Point(width * 2 + this->origin.x, this->visibleSize.height - height + this->origin.x));
	this->lifeThree->setPosition(Point(width * 3 + this->origin.x, this->visibleSize.height - height + this->origin.x));
	layer->addChild(this->lifeOne, 3);
	layer->addChild(this->lifeTwo, 3);
	layer->addChild(this->lifeThree, 3);
}

void Ship::shakeScreen(Layer *layer, float intensity)
{
	// Shake Effect
	layer->setPosition(0.0f, 0.0f);
	layer->stopAllActions();
	auto shakeUp = MoveBy::create(0.05f, Point(0.0f, intensity));
	auto shakeDown = shakeUp->reverse();
	auto shakeEffect = Sequence::create(shakeUp, shakeDown, nullptr);
	auto shakeRepeatForever = RepeatForever::create(shakeEffect);
	layer->runAction(shakeRepeatForever);
}

void Ship::updateLife(Layer *layer)
{
	if (this->life == 4)
	{
		layer->setPosition(0.0f, 0.0f);
		layer->stopAllActions();
		this->damageOne->setVisible(false);
		this->damageTwo->setVisible(false);
		this->damageThree->setVisible(false);
		this->lifeOne->setVisible(true);
		this->lifeTwo->setVisible(true);
		this->lifeThree->setVisible(true);
	}
	else if (this->life == 3)
	{
		this->damageOne->setVisible(true);
		this->damageTwo->setVisible(false);
		this->damageThree->setVisible(false);
		this->lifeOne->setVisible(true);
		this->lifeTwo->setVisible(true);
		this->lifeThree->setVisible(false);
		this->shakeScreen(layer, LEVEL_ONE);
	}
	else if (this->life == 2)
	{
		this->damageOne->setVisible(false);
		this->damageTwo->setVisible(true);
		this->damageThree->setVisible(false);
		this->lifeOne->setVisible(true);
		this->lifeTwo->setVisible(false);
		this->lifeThree->setVisible(false);
		this->shakeScreen(layer, LEVEL_TWO);
	}
	else if (this->life == 1)
	{
		this->damageOne->setVisible(false);
		this->damageTwo->setVisible(false);
		this->damageThree->setVisible(true);
		this->lifeOne->setVisible(false);
		this->lifeTwo->setVisible(false);
		this->lifeThree->setVisible(false);
		this->shakeScreen(layer, LEVEL_THREE);
	}
	else
	{
		layer->setPosition(0.0f, 0.0f);
		layer->stopAllActions();
	}
}

void Ship::incrementLife(Layer* layer)
{
	if (this->life == 4)
		return;

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_REPAIR);
	auto shipRepair = ParticleSystemQuad::create(SHIP_REPAIR);
	shipRepair->setPosition(Point(this->getPositionX(), this->getPositionY() - this->getHeight() / 2));
	shipRepair->setAutoRemoveOnFinish(true);
	layer->addChild(shipRepair, 3);
	this->life++;
	this->updateLife(layer);
}

void Ship::reduceLife(Layer *layer)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_COLLISION);
	auto shipCollision = ParticleSystemQuad::create(SHIP_COLLISION);
	shipCollision->setPosition(Point(this->getPositionX(), this->getPositionY() - this->getHeight() / 2));
	shipCollision->setAutoRemoveOnFinish(true);
	layer->addChild(shipCollision, 3);
	this->life--;
	this->updateLife(layer);
	if (this->life > 0)
	{
		// Ship in Blink Mode - Contact inactive
		this->body->setContactTestBitmask(false);
		this->sprite->runAction(
			Spawn::createWithTwoActions(
			Blink::create(1.0f, 10),
			Sequence::create(
			DelayTime::create(1.0f), 
			CallFunc::create(CC_CALLBACK_0(Ship::resetContact, this)),
			nullptr)));
	}
}

void Ship::resetContact()
{
	this->body->setContactTestBitmask(true);
}

void Ship::scalingEffect()
{
	this->sprite->stopAllActions();
	this->sprite->runAction(Sequence::create(
		ScaleBy::create(0.125f, 1.2f),
		ScaleBy::create(0.125f, 0.9f),
		nullptr
		));
	this->sprite->setScale(1.0f);
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