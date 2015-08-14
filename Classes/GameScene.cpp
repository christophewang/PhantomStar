#include "GameScene.h"

int GameScene::scorePoints = 0;
int GameScene::backgroundType = 1;
float GameScene::speedBullet = 0.0f;
float GameScene::speedMeteor = 0.0f;
float GameScene::speedItem = 0.0f;
float GameScene::speedBackground = 0.0f;
float GameScene::frequencyBullet = 0.0f;
float GameScene::frequencyMeteor = 0.0f;
float GameScene::frequencyItem = 0.0f;

GameScene::GameScene()
	: timerMeteor(0), timerBullet(0), timerItem(0)
{
	GameScene::setDefaultValue();
	userData = UserDefault::getInstance();
	ship = new Ship(this);
	createPools();
}

GameScene::~GameScene() 
{
	delete ship;
	deletePools();
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	auto director = Director::getInstance();

	layer->sceneWorld = scene->getPhysicsWorld();
	/* Debug Mode */
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//director->setDisplayStats(true);
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	std::stringstream score;
	score << GameScene::scorePoints;
	scoreLabel = Label::createWithTTF(score.str(), FONT, visibleSize.height / 15);
	scoreLabel->setAlignment(TextHAlignment::CENTER);
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x,
		visibleSize.height - visibleSize.height / 15 + origin.y));

	std::stringstream highScore;
	highScore << "Best: " << userData->getIntegerForKey(HIGHSCORE_KEY, 0);
	highScoreLabel = Label::createWithTTF(highScore.str(), FONT, visibleSize.height / 40);
	highScoreLabel->setAlignment(TextHAlignment::CENTER);
	highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x,
		visibleSize.height - visibleSize.height / 40 + origin.y));

	settingsButton = ui::Button::create();
	settingsButton->loadTextures(OPTION, OPTION);
	settingsButton->setPosition(Point(visibleSize.width - settingsButton->getContentSize().width / 2 + origin.x,
		visibleSize.height - settingsButton->getContentSize().height / 2 + origin.y));
	settingsButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onClickSettings, this));

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto keybackListener = EventListenerKeyboard::create();
	keybackListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keybackListener, this);

	checkSoundsSettings();
	setParallaxBackground();
	scheduleUpdate();
	addChild(settingsButton, 3);
	addChild(scoreLabel, 3);
	addChild(highScoreLabel, 3);

	return true;
}

void GameScene::createPools()
{
	meteorPoolIndex = 0;
	bulletPoolIndex = 0;
	starPoolIndex = 0;
	itemPoolIndex = 0;

	meteorPool.reserve(OBJECT_POOL_SIZE);
	bulletPool.reserve(OBJECT_POOL_SIZE);
	starPool.reserve(OBJECT_POOL_SIZE);
	itemPool.reserve(OBJECT_POOL_SIZE);

	for (unsigned int i = 0; i < OBJECT_POOL_SIZE; i++)
	{
		meteorPool.push_back(new Meteor());
		bulletPool.push_back(new Bullet());
		starPool.push_back(new Star());
		itemPool.push_back(new Item());
	}
}

void GameScene::deletePools()
{
	for (unsigned int i = 0; i < OBJECT_POOL_SIZE; i++)
	{
		delete meteorPool.at(i);
		delete bulletPool.at(i);
		delete starPool.at(i);
		delete itemPool.at(i);
	}
}

void GameScene::playEffect(const char *path)
{
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_KEY, true))
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect(path, false, 1.0f, 0.0f, 0.5f);
	}
}

void GameScene::checkSoundsSettings()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	if (userData->getBoolForKey(BGM_KEY, true))
		audio->playBackgroundMusic(AUDIO_BACKGROUND, true);
	else
		audio->stopBackgroundMusic(true);
}

void GameScene::setParallaxBackground()
{
	auto backgroundString = __String::createWithFormat(BACKGROUND, GameScene::backgroundType);
	auto bg1 = Sprite::create(backgroundString->getCString());
	auto bg2 = Sprite::create(backgroundString->getCString());

	bg1->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
	bg1->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
	bg2->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));

	parallaxBg = CCParallaxScrollNode::create();
	parallaxBg->addInfiniteScrollYWithZ(-1, Point(1, 1), Point(0, 0), bg1, bg2, NULL);
	this->addChild(parallaxBg);
}

bool GameScene::onContactBegin(PhysicsContact &contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();
	auto aSprite = static_cast<Sprite *>(a->getNode());
	auto bSprite = static_cast<Sprite *>(b->getNode());

	if (aSprite && bSprite &&
		a->getCollisionBitmask() == COLLISION_SHIP &&
		b->getCollisionBitmask() == COLLISION_METEOR)
	{
		shipCollision(aSprite);
	}
	else if (aSprite && bSprite &&
		b->getCollisionBitmask() == COLLISION_SHIP &&
		a->getCollisionBitmask() == COLLISION_METEOR)
	{
		shipCollision(bSprite);
	}

	if (aSprite && bSprite && 
		a->getCollisionBitmask() == COLLISION_METEOR && 
		b->getCollisionBitmask() == COLLISION_BULLET)
	{
		meteorCollision(a->getTag());
		bulletCollision(b->getTag());
	}
	else if (aSprite && bSprite && 
		b->getCollisionBitmask() == COLLISION_METEOR && 
		a->getCollisionBitmask() == COLLISION_BULLET)
	{
		meteorCollision(b->getTag());
		bulletCollision(a->getTag());
	}

	if (aSprite && bSprite &&
		a->getCollisionBitmask() == COLLISION_STAR &&
		b->getCollisionBitmask() == COLLISION_SHIP)
	{
		starCollision(a->getTag());
	}
	else if (aSprite && bSprite &&
		b->getCollisionBitmask() == COLLISION_STAR &&
		a->getCollisionBitmask() == COLLISION_SHIP)
	{
		starCollision(b->getTag());
	}
		
	if (aSprite && bSprite &&
		a->getCollisionBitmask() == COLLISION_ITEM &&
		b->getCollisionBitmask() == COLLISION_SHIP)
	{
		itemCollision(a->getTag());
	}
	else if (aSprite && bSprite &&
		b->getCollisionBitmask() == COLLISION_ITEM &&
		a->getCollisionBitmask() == COLLISION_SHIP)
	{
		itemCollision(b->getTag());
	}
	return true;
}

void GameScene::shipCollision(Sprite *shipSprite)
{
	ship->reduceLife(this);
	if (ship->getLife() <= 0)
	{
		ship->displayExplosion(this);
		ship->getSprite()->removeFromParentAndCleanup(true);
		getEventDispatcher()->removeAllEventListeners();
		unscheduleAllCallbacks();
		scheduleOnce(schedule_selector(GameScene::displayGameOver), 2.0f);
	}
}

void GameScene::meteorCollision(int index)
{
	auto meteor = meteorPool.at(index);
	if (meteor->getType() != 0)
	{
		displayStar(meteor->getPosition(), meteor->getType());
		meteor->displayExplosion(this);
		meteor->resetMeteor();
	}
}

void GameScene::bulletCollision(int index)
{
	auto bullet = bulletPool.at(index);
	bullet->displayBulletImpact(this);
	bullet->resetBullet();
}

void GameScene::starCollision(int index)
{
	auto star = starPool.at(index);
	switch (star->getType())
	{
	case 1:
		GameScene::incrementScore(50);
		break;
	case 2:
		GameScene::incrementScore(100);
		break;
	case 3:
		GameScene::incrementScore(200);
		break;
	}
	star->displayStarEffect(this);
	star->resetStar();
}

void GameScene::itemCollision(int index)
{
	auto item = itemPool.at(index);
	if (item->getType() == REPAIR_ITEM)
	{
		ship->incrementLife(this);
		item->displayItemEffect(this);
		item->resetItem();
	}
}

void GameScene::displayMeteor()
{
	auto meteor = meteorPool.at(meteorPoolIndex);
	meteor->runMeteor(this, meteorPoolIndex, GameScene::speedMeteor);
	meteorPoolIndex++;
	if (meteorPoolIndex == meteorPool.size())
		meteorPoolIndex = 0;
}

void GameScene::displayBullet()
{
	auto bullet = bulletPool.at(bulletPoolIndex);
	bullet->runBullet(this, bulletPoolIndex, ship->getPosition(), ship->getType());
	bulletPoolIndex++;
	if (bulletPoolIndex == bulletPool.size())
		bulletPoolIndex = 0;
}

void GameScene::displayStar(const Point &pos, int type)
{
	auto star = starPool.at(starPoolIndex);
	star->runStar(this, starPoolIndex, pos, type);
	starPoolIndex++;
	if (starPoolIndex == starPool.size())
		starPoolIndex = 0;
}

void GameScene::displayItem()
{
	auto item = itemPool.at(itemPoolIndex);
	item->runItem(this, itemPoolIndex);
	itemPoolIndex++;
	if (itemPoolIndex == itemPool.size())
		itemPoolIndex = 0;
}

void GameScene::update(float delta)
{
	timerMeteor += delta;
	if (timerMeteor > GameScene::frequencyMeteor / visibleSize.width)
	{
		timerMeteor = 0;
		displayMeteor();
	}

	timerBullet += delta;
	if (timerBullet > GameScene::frequencyBullet / visibleSize.height)
	{
		timerBullet = 0;
		displayBullet();
	}

	timerItem += delta;
	if (timerItem > GameScene::frequencyItem / visibleSize.height)
	{
		timerItem = 0;
		displayItem();
	}

	std::stringstream score;
	score << GameScene::scorePoints;
	scoreLabel->setString(score.str());
	parallaxBg->updateWithVelocity(
		Point(0, GameScene::speedBackground * visibleSize.height), delta);
	GameScene::scaleDifficulty(this);
}

void GameScene::incrementScore(int value)
{
	scorePoints += value;
}

void GameScene::scaleDifficulty(Layer *layer)
{
	//Speed Background
	if (GameScene::speedBackground <= -0.05f)
		GameScene::speedBackground = -0.05f;
	else
		GameScene::speedBackground = -0.01f - (GameScene::scorePoints / 200000.0f);

	//Speed Meteors
	if (GameScene::speedMeteor <= 0.0025f)
		GameScene::speedMeteor = 0.0025f;
	else
		GameScene::speedMeteor = 0.005f - (GameScene::scorePoints / 3000000.0f);

	//Frequency Meteors
	if (GameScene::frequencyMeteor <= 100.0f)
		GameScene::frequencyMeteor = 100.0f;
	else
		GameScene::frequencyMeteor = 200.0f - (GameScene::scorePoints / 50.0f);
}

void GameScene::setDefaultValue()
{
	GameScene::scorePoints = 0;
	GameScene::speedBullet = 0.001f;
	GameScene::speedMeteor = 0.005f;
	GameScene::speedItem = 0.005f;
	GameScene::speedBackground = -0.01f;
	GameScene::frequencyBullet = 200.0f;
	GameScene::frequencyMeteor = 200.0f;
	GameScene::frequencyItem = 10000.0f;
}

void GameScene::displayGameOver(float delta)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	audio->stopAllEffects();
	audio->stopBackgroundMusic();
	scoreLabel->setVisible(false);
	highScoreLabel->setVisible(false);
	auto gameOverDialog = GameOverDialog::create();
	addChild(gameOverDialog, 4, DIALOG_OBJECT);
}

void GameScene::showGameDialog()
{
	if (!Director::getInstance()->isPaused())
	{
		Director::getInstance()->pause();

		if (userData->getBoolForKey(BGM_KEY, true))
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		if (userData->getBoolForKey(EFFECT_KEY, true))
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

		auto gameDialog = GameDialog::create();
		addChild(gameDialog, 4, DIALOG_OBJECT);
	}
	else if (Director::getInstance()->isPaused())
	{
		removeChildByTag(DIALOG_OBJECT, true);
		Director::getInstance()->resume();

		if (userData->getBoolForKey(BGM_KEY, true))
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		if (userData->getBoolForKey(EFFECT_KEY, true))
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}

void GameScene::onClickSettings(Ref* sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		showGameDialog();
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		showGameDialog();
	}
}