#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class CCParallaxScrollOffset : public Layer
{
public:
	virtual bool init() override;

	CREATE_FUNC(CCParallaxScrollOffset);
    CC_SYNTHESIZE(Point, scrollOffset, ScrollOffset);
    CC_SYNTHESIZE(Point, origPosition, OrigPosition);
    CC_SYNTHESIZE(Point, relVelocity, RelVelocity);
    CC_SYNTHESIZE(Point, ratio, Ratio);
    CC_SYNTHESIZE(Point, buffer, Buffer);
    CC_SYNTHESIZE(Node*, theChild, TheChild);
    
    static CCParallaxScrollOffset* scrollWithNode(Node *node, Point r, Point p, Point s);
    static CCParallaxScrollOffset* scrollWithNode(Node *node, Point r, Point p, Point s, Point v);
    CCParallaxScrollOffset* initWithNode(Node *node, Point r, Point p, Point s, Point v);
    CCParallaxScrollOffset* initWithNode(Node *node, Point r, Point p, Point s);
};
