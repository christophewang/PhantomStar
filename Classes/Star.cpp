#include "Star.h"
#include "GameScene.h"

void Star::runStar(Layer *layer, int index, const Point &pos, int _type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	type = _type;
	auto starPath = __String::createWithFormat(STAR, type);
	sprite = Sprite::createWithSpriteFrameName(starPath->getCString());
	width = sprite->getContentSize().width;
	height = sprite->getContentSize().height;

	body = PhysicsBody::createCircle(width / 2);
	body->setCollisionBitmask(COLLISION_STAR);
	body->setContactTestBitmask(true);
	body->setDynamic(false);
	body->setTag(index);
	sprite->setPhysicsBody(body);

	ccBezierConfig bezier;
	if (pos.x >= visibleSize.width / 2)
	{
		bezier.controlPoint_1 = Point(pos.x / 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x * 2 + origin.x, -height + origin.y);
	}
	else
	{
		bezier.controlPoint_1 = Point(pos.x * 2 + origin.x, pos.y * 0.75 + origin.y);
		bezier.controlPoint_2 = Point(pos.x + origin.x, pos.y * 0.25 + origin.y);
		bezier.endPosition = Point(pos.x / 2 + origin.x, -height + origin.y);
	}

	auto starBezierTo = BezierTo::create(GameScene::speedMeteor * visibleSize.height, bezier);

	auto sequence = Sequence::create(
		starBezierTo,
		CallFunc::create(CC_CALLBACK_0(Star::resetStar, this)),
		NULL);

	sprite->setPosition(Point(pos.x + origin.x, pos.y + origin.y));
	sprite->runAction(sequence);
	layer->addChild(sprite, 2, GAME_OBJECT);
}

void Star::resetStar()
{
	sprite->stopAllActions();
	sprite->removeFromParentAndCleanup(true);
}

void Star::displayStarEffect(Layer *layer)
{
	auto starPath = __String::createWithFormat(STAR_EFFECT, type);
	auto starEffect = ParticleSystemQuad::create(starPath->getCString());
	starEffect->setPosition(getPosition());
	starEffect->setAutoRemoveOnFinish(true);
	layer->addChild(starEffect, 2);
	GameScene::playEffect(AUDIO_STAR);
}