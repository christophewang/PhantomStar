#include "FirstScene.h"

USING_NS_CC;

Scene* FirstScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FirstScene::create();

	scene->addChild(layer);
	return scene;
}

bool FirstScene::init()
{
	if (!Layer::init())
		return false;
	return true;
}