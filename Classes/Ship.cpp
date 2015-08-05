#include "Ship.h"
#include "BodyParser.h"
#include "GameScene.h"

Ship::Ship(Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	life = 4;
	auto shipIndex = rand() % 12 + 1;
	if (shipIndex > 0 && shipIndex <= 4)
	{
		type = 1;
		BodyParser::getInstance()->parseJsonFile(BODY_SHIP1);
		damageOne = Sprite::createWithSpriteFrameName(DAMAGE_1_1);
		damageTwo = Sprite::createWithSpriteFrameName(DAMAGE_1_2);
		damageThree = Sprite::createWithSpriteFrameName(DAMAGE_1_3);
	}
	else if (shipIndex > 4 && shipIndex <= 8)
	{
		type = 2;
		BodyParser::getInstance()->parseJsonFile(BODY_SHIP2);
		damageOne = Sprite::createWithSpriteFrameName(DAMAGE_2_1);
		damageTwo = Sprite::createWithSpriteFrameName(DAMAGE_2_2);
		damageThree = Sprite::createWithSpriteFrameName(DAMAGE_2_3);
	}
	else
	{
		type = 3;
		BodyParser::getInstance()->parseJsonFile(BODY_SHIP3);
		damageOne = Sprite::createWithSpriteFrameName(DAMAGE_3_1);
		damageTwo = Sprite::createWithSpriteFrameName(DAMAGE_3_2);
		damageThree = Sprite::createWithSpriteFrameName(DAMAGE_3_3);
	}

	displayLife(layer, shipIndex);
	auto shipString = __String::createWithFormat(SHIP, shipIndex);
	sprite = Sprite::createWithSpriteFrameName(shipString->getCString());
	width = sprite->getContentSize().width;
	height = sprite->getContentSize().height;
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, 
		visibleSize.height / 4 + origin.y));

	body = BodyParser::getInstance()->bodyFormJson(sprite, "Ship");
	body->setCollisionBitmask(COLLISION_SHIP);
	body->setContactTestBitmask(true);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	sprite->setPhysicsBody(body);

	sprite->runAction(
		Sequence::createWithTwoActions(Blink::create(1.0f, 10),
		CallFunc::create(CC_CALLBACK_0(Ship::resetShip, this))));

	damageOne->setPosition(Point(width / 2, height / 2));
	damageTwo->setPosition(Point(width / 2, height / 2));
	damageThree->setPosition(Point(width / 2, height / 2));
	damageOne->setVisible(false);
	damageTwo->setVisible(false);
	damageThree->setVisible(false);
	sprite->addChild(damageOne, 2);
	sprite->addChild(damageTwo, 2);
	sprite->addChild(damageThree, 2);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Ship::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Ship::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Ship::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(Ship::onTouchesEnded, this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
	layer->addChild(sprite, 2);
}

int Ship::getLife() const
{
	return life;
}

void Ship::displayLife(Layer *layer, int shipIndex)
{
	auto shipLifeString = __String::createWithFormat(SHIP_LIFE, shipIndex);
	lifeOne = Sprite::createWithSpriteFrameName(shipLifeString->getCString());
	lifeTwo = Sprite::createWithSpriteFrameName(shipLifeString->getCString());
	lifeThree = Sprite::createWithSpriteFrameName(shipLifeString->getCString());

	auto width = lifeOne->getContentSize().width;
	auto height = lifeOne->getContentSize().height;

	lifeOne->setPosition(Point(width + origin.x, visibleSize.height - height + origin.x));
	lifeTwo->setPosition(Point(width * 2 + origin.x, visibleSize.height - height + origin.x));
	lifeThree->setPosition(Point(width * 3 + origin.x, visibleSize.height - height + origin.x));
	layer->addChild(lifeOne, 3);
	layer->addChild(lifeTwo, 3);
	layer->addChild(lifeThree, 3);
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
	if (life == 4)
	{
		layer->setPosition(0.0f, 0.0f);
		layer->stopAllActions();
		damageOne->setVisible(false);
		damageTwo->setVisible(false);
		damageThree->setVisible(false);
		lifeOne->setVisible(true);
		lifeTwo->setVisible(true);
		lifeThree->setVisible(true);
	}
	else if (life == 3)
	{
		damageOne->setVisible(true);
		damageTwo->setVisible(false);
		damageThree->setVisible(false);
		lifeOne->setVisible(true);
		lifeTwo->setVisible(true);
		lifeThree->setVisible(false);
		shakeScreen(layer, LEVEL_ONE);
	}
	else if (life == 2)
	{
		damageOne->setVisible(false);
		damageTwo->setVisible(true);
		damageThree->setVisible(false);
		lifeOne->setVisible(true);
		lifeTwo->setVisible(false);
		lifeThree->setVisible(false);
		shakeScreen(layer, LEVEL_TWO);
	}
	else if (life == 1)
	{
		damageOne->setVisible(false);
		damageTwo->setVisible(false);
		damageThree->setVisible(true);
		lifeOne->setVisible(false);
		lifeTwo->setVisible(false);
		lifeThree->setVisible(false);
		shakeScreen(layer, LEVEL_THREE);
	}
	else
	{
		layer->setPosition(0.0f, 0.0f);
		layer->stopAllActions();
	}
}

void Ship::incrementLife(Layer* layer)
{
	if (life < 4)
	{
		life++;
		updateLife(layer);
	}
}

void Ship::reduceLife(Layer *layer)
{
	life--;
	updateLife(layer);
	displayCollision(layer);
	if (life > 0)
	{
		// Ship in Blink Mode - Contact inactive
		body->setContactTestBitmask(false);
		sprite->runAction(
			Sequence::createWithTwoActions(Blink::create(0.5f, 10),
			CallFunc::create(CC_CALLBACK_0(Ship::resetShip, this))));
	}
}

void Ship::resetShip()
{
	body->setContactTestBitmask(true);
	sprite->runAction(Show::create());
}

void Ship::scalingEffect()
{
	sprite->runAction(
		Sequence::createWithTwoActions(
		ScaleBy::create(0.125f, 1.2f),
		ScaleBy::create(0.125f, 0.9f)));
	sprite->setScale(1.0f);
}

void Ship::displayCollision(Layer *layer)
{
	auto shipCollision = ParticleSystemQuad::create(SHIP_COLLISION);
	shipCollision->setPosition(Point(getPositionX(), getPositionY() - getHeight() / 2));
	shipCollision->setAutoRemoveOnFinish(true);
	layer->addChild(shipCollision, 2);
	GameScene::playEffect(AUDIO_SHIP_COLLISION);
}

void Ship::displayExplosion(Layer *layer)
{
	auto shipExplosion = ParticleSystemQuad::create(SHIP_EXPLOSION);
	shipExplosion->setPosition(getPosition());
	shipExplosion->setAutoRemoveOnFinish(true);
	layer->addChild(shipExplosion, 2);
	GameScene::playEffect(AUDIO_SHIP_EXPLOSION);
}

Point Ship::touchToPoint(Touch* touch)
{
	return Director::getInstance()->convertToGL(touch->getLocationInView());
}

void Ship::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	touchOffset = Point::ZERO;
	for (auto touch : touches)
	{
		if (touch)
			touchOffset = sprite->getPosition() - touchToPoint(touch);
	}
}

void Ship::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			auto position = touchToPoint(touch) + touchOffset;
			if (position.x < 0)
				position.x = 0;
			if (position.y < 0)
				position.y = 0;
			if (position.x > visibleSize.width)
				position.x = visibleSize.width;
			if (position.y > visibleSize.height)
				position.y = visibleSize.height;
			sprite->setPosition(position);
		}
	}
}

void Ship::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			auto position = touchToPoint(touch) + touchOffset;
			if (position.x < 0)
				position.x = 0;
			if (position.y < 0)
				position.y = 0;
			if (position.x > visibleSize.width)
				position.x = visibleSize.width;
			if (position.y > visibleSize.height)
				position.y = visibleSize.height;
			sprite->setPosition(position);
			scalingEffect();
		}
	}
}