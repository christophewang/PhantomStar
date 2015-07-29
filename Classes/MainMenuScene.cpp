#include "MainMenuScene.h"
#include "GooglePlayServices.h"

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
		return false;
	timer = 0.0f;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	auto menu = CSLoader::createNode(GAME_MENU);
	menu->setAnchorPoint(Point(0.5, 0.5));
	menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto playButton = static_cast<ui::Button*>(menu->getChildByName("playButton"));
	playButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::goToGameScene, this));

	auto rateButton = static_cast<ui::Button*>(menu->getChildByName("rateButton"));
	rateButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::rate, this));

	auto rankingButton = static_cast<ui::Button*>(menu->getChildByName("rankingButton"));
	rankingButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::ranking, this));

	auto donationButton = static_cast<ui::Button*>(menu->getChildByName("donationButton"));
	donationButton->setVisible(false);
	donationButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::donation, this));

	auto keybackListener = EventListenerKeyboard::create();
	keybackListener->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keybackListener, this);

	this->setParallaxBackground();
	this->scheduleUpdate();
	this->addChild(menu, 4);
	return true;
}

void MainMenuScene::setParallaxBackground()
{
	std::srand(time(nullptr));
	GameScene::backgroundType = rand() % 4 + 1;
	auto backgroundString = __String::createWithFormat(BACKGROUND, GameScene::backgroundType);

	auto bg1 = Sprite::create(backgroundString->getCString());
	auto bg2 = Sprite::create(backgroundString->getCString());

	bg1->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
	bg1->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
	bg2->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));

	parallaxBg = CCParallaxScrollNode::create();
	parallaxBg->addInfiniteScrollYWithZ(-1, Point(1, 1), Point(0, 0), bg1, bg2, NULL);

	this->addChild(parallaxBg, 1);
}

void MainMenuScene::meteorUpdate()
{
	for (unsigned int i = 0; i < this->meteorArray.size(); ++i)
	{
		if (this->meteorArray[i]->getPositionY() < origin.y)
		{
			this->meteorArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->meteorArray[i];
			this->meteorArray.erase(this->meteorArray.begin() + i);
		}
	}
}

void MainMenuScene::update(float delta)
{
	this->timer += delta;
	if (this->timer > 200.0f / this->visibleSize.width)
	{
		this->timer = 0;
		meteorArray.push_back(new Meteor(this, 0.002f));
		this->meteorUpdate();
	}
	this->parallaxBg->updateWithVelocity(Point(0, -0.01f * visibleSize.height), delta);
}

void MainMenuScene::goToGameScene(Ref* sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->removeFromParentAndCleanup(true);
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(TransitionSlideInB::create(DELAY_TRANSITION, scene));
	}
}

void MainMenuScene::rate(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
		Application::getInstance()->openURL(LINK);
}

void MainMenuScene::ranking(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		// Google Play Sign In
		if (!NativeUtils::isSignedIn())
			NativeUtils::signIn();
		if (NativeUtils::isSignedIn())
			NativeUtils::showLeaderboard(RANKING);
	}
}

void MainMenuScene::donation(Ref *sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		//TODO IAP Link donation
	}
}

void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		_eventDispatcher->removeAllEventListeners();
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->getOpenGLView()->end();
		Director::getInstance()->end();
	}
}

