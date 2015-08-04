#include "Item.h"
#include "Definitions.h"
#include "GameScene.h"

void Item::runItem(Layer *layer, int index)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//TODO Randomize Items 
	type = REPAIR_ITEM;
	sprite = Sprite::createWithSpriteFrameName(RED_PILL);

	width = sprite->getContentSize().width;
	height = sprite->getContentSize().height;
	body = PhysicsBody::createCircle(width / 2);
	body->setCollisionBitmask(COLLISION_ITEM);
	body->setContactTestBitmask(true);
	body->setDynamic(false);
	body->setTag(index);
	sprite->setPhysicsBody(body);

	auto posX = (rand() % static_cast<int>(visibleSize.width)) + (width / 2);
	if (posX + width / 2 > visibleSize.width)
		posX = visibleSize.width - width / 2;

	auto itemMoveto = MoveTo::create(GameScene::speedItem * visibleSize.height,
		Point(posX + origin.x, -height + origin.y));

	auto itemRotateBy = RotateBy::create(GameScene::speedItem * visibleSize.height, 360);

	sprite->setPosition(Point(posX + origin.x, visibleSize.height + height + origin.y));
	sprite->runAction(Spawn::createWithTwoActions(itemRotateBy, itemMoveto));
	layer->addChild(sprite, 1, GAME_OBJECT);
}

void Item::resetItem()
{
	sprite->stopAllActions();
	sprite->removeFromParentAndCleanup(true);
}

void Item::displayItemEffect(Layer *layer)
{
	auto shipRepair = ParticleSystemQuad::create(SHIP_REPAIR);
	shipRepair->setPosition(getPosition());
	shipRepair->setAutoRemoveOnFinish(true);
	layer->addChild(shipRepair, 3);
	GameScene::playEffect(AUDIO_REPAIR);
}