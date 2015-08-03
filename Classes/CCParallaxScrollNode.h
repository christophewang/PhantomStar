#pragma once

#include "cocos2d.h"
#include "CCParallaxScrollOffset.h"

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif

using namespace cocos2d;

class CCParallaxScrollNode : public Layer
{
public:
	virtual bool init() override;
	CREATE_FUNC(CCParallaxScrollNode);

	Size _range;

	Vector<CCParallaxScrollOffset *> _scrollOffsets;

	void addChild(Sprite *node, int z, Point r, Point p, Point so);
	void addChild(Sprite *node, int z, Point r, Point p, Point so, Point v);

	void removeChild(Sprite *node, bool cleanup);
	void updateWithVelocity(Point vel, float dt);
	void updateWithYPosition(float y, float dt);

	void addInfiniteScrollXWithZ(int z, Point ratio, Point pos, Sprite* firstObject, ...);
	void addInfiniteScrollYWithZ(int z, Point ratio, Point pos, Sprite* firstObject, ...);

	void addInfiniteScrollWithObjects(const Vector<Sprite *>& objects, int z, Point ratio, Point pos, Point dir);
	void addInfiniteScrollWithObjects(const Vector<Sprite *>& objects, int z, Point ratio, Point pos, Point dir, Point relVel);
	void addInfiniteScrollWithObjects(const Vector<Sprite *>& objects, int z, Point ratio, Point pos, Point dir, Point relVel, Point padding);

};