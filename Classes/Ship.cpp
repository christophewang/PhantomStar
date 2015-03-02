#include "Ship.h"
#include "GameScene.h"

USING_NS_CC;

Ship::Ship(Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	bullet = new Bullet(layer);
	bulletTimer = 0;

	std::srand(time(NULL));
	int shipIndex = rand() % 16 + 1;

	__String *shipString = __String::createWithFormat("Ships/ship%i.png", shipIndex);
	shipSprite = Sprite::create(shipString->getCString());

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

	shipSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	shipSprite->setScale(0.75);
	auto shipBody = PhysicsBody::createCircle(shipSprite->getContentSize().width / 2);
	
	shipBody->setCollisionBitmask(COLLISION_SHIP);
	shipBody->setContactTestBitmask(true);
	shipBody->setGravityEnable(false);
	shipBody->setRotationEnable(false);
	shipSprite->setPhysicsBody(shipBody);

	auto shipBlink = Blink::create(1, 10);
	shipSprite->runAction(shipBlink);
	layer->addChild(shipSprite, 1);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Ship::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Ship::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Ship::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(Ship::onTouchesEnded, this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
}

Ship::~Ship()
{
	delete bullet;
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
			this->touchOffset = this->shipSprite->getPosition() - this->touchToPoint(touch);
	}
}

void Ship::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
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
			if (position.x > visibleSize.width)
				position.x = visibleSize.width;
			if (position.y > visibleSize.height)
				position.y = visibleSize.height;
			this->shipSprite->setPosition(position);
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
			if (position.x > visibleSize.width)
				position.x = visibleSize.width;
			if (position.y > visibleSize.height)
				position.y = visibleSize.height;
			this->shipSprite->setPosition(position);
		}
	}
}

void Ship::update(float delta)
{
	bulletTimer += delta;
	if (bulletTimer > GameScene::frequencyBullet * visibleSize.width)
	{
		bulletTimer = 0;
		bullet->fireBullet(shipSprite->getPosition());
	}
	bullet->update(delta);
}

Bullet *Ship::getBullet()
{
	return this->bullet;
}