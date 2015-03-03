#include "Star.h"

USING_NS_CC;

Star::Star(Layer *layer)
{
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->layer = layer;
	std::srand(time(NULL));
}

Star::~Star()
{
}

void Star::spawnStarBronze(Point pos)
{
	auto starSprite = Sprite::create("Power-ups/star_bronze.png");
	auto starBody = PhysicsBody::createCircle(starSprite->getContentSize().width / 2);

	starBody->setCollisionBitmask(COLLISION_STAR_BRONZE);
	starBody->setContactTestBitmask(true);
	starBody->setDynamic(false);
	starSprite->setPhysicsBody(starBody);

	starSprite->setPosition(Point(pos.x + origin.x, pos.y + origin.y));
	this->stars.push_back(starSprite);
	this->layer->addChild(starSprite);

	ccBezierConfig bezier;
	if (pos.x >= visibleSize.width / 2)
	{
		bezier.controlPoint_1 = Point(pos.x / 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x * 2 + origin.x, -starSprite->getContentSize().height + origin.y);
	}
	else
	{
		bezier.controlPoint_1 = Point(pos.x * 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x / 2 + origin.x, -starSprite->getContentSize().height + origin.y);
	}
	auto starBezierTo = BezierTo::create(SPEED_STARS * visibleSize.height, bezier);
	starSprite->runAction(starBezierTo);
}

void Star::spawnStarSilver(Point pos)
{
	auto starSprite = Sprite::create("Power-ups/star_silver.png");
	auto starBody = PhysicsBody::createCircle(starSprite->getContentSize().width / 2);

	starBody->setCollisionBitmask(COLLISION_STAR_SILVER);
	starBody->setContactTestBitmask(true);
	starBody->setDynamic(false);
	starSprite->setPhysicsBody(starBody);

	starSprite->setPosition(Point(pos.x + origin.x, pos.y + origin.y));
	this->stars.push_back(starSprite);
	this->layer->addChild(starSprite);

	ccBezierConfig bezier;
	if (pos.x >= visibleSize.width / 2)
	{
		bezier.controlPoint_1 = Point(pos.x / 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x * 2 + origin.x, -starSprite->getContentSize().height + origin.y);
	}
	else
	{
		bezier.controlPoint_1 = Point(pos.x * 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x / 2 + origin.x, -starSprite->getContentSize().height + origin.y);
	}
	auto starBezierTo = BezierTo::create(SPEED_STARS * visibleSize.height, bezier);
	starSprite->runAction(starBezierTo);
}

void Star::spawnStarGold(Point pos)
{
	auto starSprite = Sprite::create("Power-ups/star_gold.png");
	auto starBody = PhysicsBody::createCircle(starSprite->getContentSize().width / 2);

	starBody->setCollisionBitmask(COLLISION_STAR_GOLD);
	starBody->setContactTestBitmask(true);
	starBody->setDynamic(false);
	starSprite->setPhysicsBody(starBody);

	starSprite->setPosition(Point(pos.x + origin.x, pos.y + origin.y));
	this->stars.push_back(starSprite);
	this->layer->addChild(starSprite);

	ccBezierConfig bezier;
	if (pos.x >= visibleSize.width / 2)
	{
		bezier.controlPoint_1 = Point(pos.x / 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x * 2 + origin.x, -starSprite->getContentSize().height + origin.y);
	}
	else
	{
		bezier.controlPoint_1 = Point(pos.x * 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x / 2 + origin.x, -starSprite->getContentSize().height + origin.y);
	}
	auto starBezierTo = BezierTo::create(SPEED_STARS * visibleSize.height, bezier);
	starSprite->runAction(starBezierTo);
}

void Star::removeStar(Sprite *starSprite)
{
	stars.erase(std::remove(stars.begin(), stars.end(), starSprite), stars.end());
}

void Star::update(float delta)
{
	for (unsigned int i = 0; i < stars.size(); ++i)
	{
		if (stars[i]->getPosition().y < origin.y)
		{
			stars[i]->removeFromParentAndCleanup(true);
			this->removeStar(stars[i]);
		}
	}
	//CCLOG("Star size: %i", stars.size());
}