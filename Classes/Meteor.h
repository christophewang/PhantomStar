#pragma once
#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Meteor
{
private:
	Size visibleSize;
	Vec2 origin;
	Layer *layer;
	std::vector<Sprite *> meteors;
public:
	Meteor(Layer *layer);
	~Meteor();
	void spawnMeteor();
	void update(float delta);
	void removeMeteor(Sprite *meteorSprite);
};

