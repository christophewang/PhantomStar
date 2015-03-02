#pragma once
#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Star
{
private:
	Size visibleSize;
	Vec2 origin;
	Layer *layer;
	std::vector<Sprite *> stars;
public:
	Star(Layer *layer);
	~Star();
	void spawnStarBronze(Point pos);
	void spawnStarSilver(Point pos);
	void spawnStarGold(Point pos);
	void update(float delta);
	void removeStar(Sprite *starSprite);
};

