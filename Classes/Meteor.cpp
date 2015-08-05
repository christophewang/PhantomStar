#include "Meteor.h"
#include "GameScene.h"

void Meteor::runMeteor(Layer *layer, int index, float speed)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto meteorIndex = 0;
	if (GameScene::scorePoints < 10000)
		meteorIndex = rand() % 8 + 1;
	else
		meteorIndex = rand() % 14 + 1;

	if (meteorIndex > 0 && meteorIndex <= 4)
		type = 3;
	else if (meteorIndex > 4 && meteorIndex <= 6)
		type = 2;
	else if (meteorIndex > 6 && meteorIndex <= 8)
		type = 1;
	else
		type = 0;

	auto meteorString = __String::createWithFormat(METEOR, meteorIndex);
	sprite = Sprite::createWithSpriteFrameName(meteorString->getCString());
	width = sprite->getContentSize().width;
	height = sprite->getContentSize().height;

	body = PhysicsBody::createCircle(width / 2);
	body->setCollisionBitmask(COLLISION_METEOR);
	body->setContactTestBitmask(true);
	body->setDynamic(false);
	body->setTag(index);
	sprite->setPhysicsBody(body);

	auto posX = (rand() % static_cast<int>(visibleSize.width)) + (width / 2);
	if (posX + width / 2 > visibleSize.width)
		posX = visibleSize.width - width / 2;

	auto offX = (rand() % static_cast<int>(visibleSize.width)) + (width / 2);
	if (offX + width / 2 > visibleSize.width)
		offX = visibleSize.width - width / 2;

	auto meteorMoveTo = MoveTo::create(speed * visibleSize.height,
		Point(offX + origin.x, -height + origin.y));
	auto meteorRotateBy = RepeatForever::create(
		RotateBy::create(speed * visibleSize.height, 360));

	auto sequence = Sequence::create(
		meteorMoveTo,
		CallFunc::create(CC_CALLBACK_0(Meteor::resetMeteor, this)),
		nullptr);

	sprite->setPosition(Point(posX + origin.x, visibleSize.height + height + origin.y));
	sprite->runAction(meteorRotateBy);
	sprite->runAction(sequence);
	layer->addChild(sprite, 2, GAME_OBJECT);
}

void Meteor::resetMeteor()
{
	sprite->stopAllActions();
	sprite->removeFromParentAndCleanup(true);
}

void Meteor::displayExplosion(Layer *layer)
{
	auto explosion = ParticleSystemQuad::create(METEOR_EXPLOSION);
	explosion->setPosition(getPosition());
	explosion->setAutoRemoveOnFinish(true);
	layer->addChild(explosion, 2);
	GameScene::playEffect(AUDIO_METEOR_EXPLOSION);
}