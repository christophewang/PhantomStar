#include "Meteor.h"
#include "GameScene.h"

USING_NS_CC;

Meteor::Meteor(Layer *layer)
{
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->layer = layer;
	std::srand(time(NULL));
}

Meteor::~Meteor()
{
}

void Meteor::spawnMeteor()
{
	int meteorIndex = rand() % 20 + 1;

	__String *meteorString = __String::createWithFormat("Meteors/meteor%i.png", meteorIndex);
	auto meteorSprite = Sprite::create(meteorString->getCString());
	auto meteorBody = PhysicsBody::createCircle(meteorSprite->getContentSize().width / 2);

	meteorBody->setCollisionBitmask(COLLISION_METEOR);
	meteorBody->setContactTestBitmask(true);
	meteorBody->setDynamic(false);
	meteorSprite->setPhysicsBody(meteorBody);

	float posX = (rand() % (int)visibleSize.width) + (meteorSprite->getContentSize().width / 2);

	if (posX + meteorSprite->getContentSize().width / 2 > visibleSize.width)
		posX = visibleSize.width - meteorSprite->getContentSize().width / 2;

	meteorSprite->setPosition(Point(posX + origin.x, visibleSize.height + meteorSprite->getContentSize().height + origin.y));
	meteorSprite->setScale(0.75);
	meteors.push_back(meteorSprite);
	layer->addChild(meteorSprite);
	auto meteorMoveTo = MoveTo::create(GameScene::speedMeteor * visibleSize.height, 
		Point(posX + origin.x, -meteorSprite->getContentSize().height + origin.y));
	auto meteorRotateBy = RotateBy::create(GameScene::speedMeteor * visibleSize.height, 360);
	meteorSprite->runAction(Spawn::createWithTwoActions(meteorRotateBy, meteorMoveTo));
}

void Meteor::removeMeteor(Sprite *meteorSprite)
{
	meteors.erase(std::remove(meteors.begin(), meteors.end(), meteorSprite), meteors.end());
}

void Meteor::update(float delta)
{
	for (unsigned int i = 0; i < meteors.size(); ++i)
	{
		if (meteors[i]->getPosition().y < origin.y)
		{
			meteors[i]->removeFromParentAndCleanup(true);
			this->removeMeteor(meteors[i]);
		}
	}
	CCLOG("Meteor size: %i", meteors.size());
}