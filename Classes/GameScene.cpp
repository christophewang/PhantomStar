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
	def = UserDefault::getInstance();
	ship = new Ship(this);
}

GameScene::~GameScene()
{
	delete this->ship;
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();

	layer->sceneWorld = scene->getPhysicsWorld();
	/* Debug Mode */
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	highScore << "Best: " << def->getIntegerForKey(HIGHSCORE_KEY, 0);
	highScoreLabel = Label::createWithTTF(highScore.str(), FONT, visibleSize.height / 40);
	highScoreLabel->setAlignment(TextHAlignment::CENTER);
	highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x,
		visibleSize.height - visibleSize.height / 40 + origin.y));
	soundBGMButton = ui::Button::create();
	this->checkBGMSettings();
	soundBGMButton->setPosition(Point(visibleSize.width - soundBGMButton->getContentSize().width / 2 + origin.x,
		visibleSize.height - soundBGMButton->getContentSize().height / 2 + origin.y));
	soundBGMButton->addTouchEventListener(CC_CALLBACK_2(GameScene::BGMListener, this));

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto keybackListener = EventListenerKeyboard::create();
	keybackListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keybackListener, this);

	this->setParallaxBackground();
	this->scheduleUpdate();
	this->addChild(soundBGMButton, 3);
	this->addChild(scoreLabel, 3);
	this->addChild(highScoreLabel, 3);
	return true;
}

void GameScene::checkBGMSettings()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	if (!def->getBoolForKey(BGM_KEY, false))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
		soundBGMButton->loadTextures(MUSIC_ON, MUSIC_ON);
	}
	else
		soundBGMButton->loadTextures(MUSIC_OFF, MUSIC_OFF);
}

void GameScene::BGMListener(Ref *Sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		if (!def->getBoolForKey(BGM_KEY, false))
		{
			def->setBoolForKey(BGM_KEY, true);
			soundBGMButton->loadTextures(MUSIC_OFF, MUSIC_OFF);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		}
		else
		{
			def->setBoolForKey(BGM_KEY, false);
			soundBGMButton->loadTextures(MUSIC_ON, MUSIC_ON);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
		}
	}
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

	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_SHIP && b->getCollisionBitmask() == COLLISION_METEOR)
		this->shipCollision(aSprite);
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_SHIP && a->getCollisionBitmask() == COLLISION_METEOR)
		this->shipCollision(bSprite);

	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_METEOR && b->getCollisionBitmask() == COLLISION_BULLET)
	{
		this->meteorCollision(aSprite);
		this->bulletCollision(bSprite);
	}

	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_METEOR && a->getCollisionBitmask() == COLLISION_BULLET)
	{
		this->meteorCollision(bSprite);
		this->bulletCollision(bSprite);
	}

	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_STAR && b->getCollisionBitmask() == COLLISION_SHIP)
		this->starCollision(aSprite);
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_STAR && a->getCollisionBitmask() == COLLISION_SHIP)
		this->starCollision(bSprite);

	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_ITEM && b->getCollisionBitmask() == COLLISION_SHIP)
		this->itemCollision(aSprite);
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_ITEM && a->getCollisionBitmask() == COLLISION_SHIP)
		this->itemCollision(bSprite);
	return true;
}

void GameScene::shipCollision(Sprite *ship)
{
	this->ship->reduceLife(this);
	if (this->ship->getLife() <= 0)
	{
		this->ship->displayExplosion(this);
		this->ship->getSprite()->removeFromParentAndCleanup(true);
		this->getEventDispatcher()->removeAllEventListeners();
		this->unscheduleAllCallbacks();
		this->scheduleOnce(schedule_selector(GameScene::displayGameOver), 2.0f);
	}
}

void GameScene::meteorCollision(Sprite *meteor)
{
	for (unsigned int i = 0; i < this->meteorArray.size(); ++i)
	{
		if (this->meteorArray[i]->getSprite() == meteor && this->meteorArray[i]->getType())
		{
			this->meteorArray[i]->displayExplosion(this);
			starArray.push_back(new Star(this, this->meteorArray[i]->getPosition(), this->meteorArray[i]->getType()));
			this->meteorArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->meteorArray[i];
			this->meteorArray.erase(this->meteorArray.begin() + i);
		}
	}
}

void GameScene::bulletCollision(Sprite *bullet)
{
	for (unsigned int i = 0; i < this->bulletArray.size(); ++i)
	{
		if (this->bulletArray[i]->getSprite() == bullet)
		{
			this->bulletArray[i]->displayBulletImpact(this);
			this->bulletArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->bulletArray[i];
			this->bulletArray.erase(this->bulletArray.begin() + i);
		}
	}
}

void GameScene::starCollision(Sprite *star)
{
	for (unsigned int i = 0; i < this->starArray.size(); ++i)
	{
		if (this->starArray[i]->getSprite() == star)
		{
			auto type = this->starArray[i]->getType();
			if (type == 1)
				GameScene::incrementScore(50);
			else if (type == 2)
				GameScene::incrementScore(100);
			else if (type == 3)
				GameScene::incrementScore(200);
			this->starArray[i]->displayStarEffect(this);
			this->starArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->starArray[i];
			this->starArray.erase(this->starArray.begin() + i);
		}
	}
}

void GameScene::itemCollision(Sprite* item)
{
	for (unsigned int i = 0; i < this->itemArray.size(); ++i)
	{
		if (this->itemArray[i]->getSprite() == item)
		{
			auto type = this->itemArray[i]->getType();
			if (type == REPAIR_ITEM)
				this->ship->incrementLife(this);
			this->itemArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->itemArray[i];
			this->itemArray.erase(this->itemArray.begin() + i);
		}
	}
}

void GameScene::meteorUpdate()
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

void GameScene::bulletUpdate()
{
	for (unsigned int i = 0; i < this->bulletArray.size(); ++i)
	{
		if (this->bulletArray[i]->getPositionY() > this->visibleSize.height + origin.y)
		{
			this->bulletArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->bulletArray[i];
			this->bulletArray.erase(this->bulletArray.begin() + i);
		}
	}
}

void GameScene::starUpdate()
{
	for (unsigned int i = 0; i < this->starArray.size(); ++i)
	{
		if (this->starArray[i]->getPositionY() < origin.y)
		{
			this->starArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->starArray[i];
			this->starArray.erase(this->starArray.begin() + i);
		}
	}
}

void GameScene::itemUpdate()
{
	for (unsigned int i = 0; i < this->itemArray.size(); ++i)
	{
		if (this->itemArray[i]->getPositionY() < origin.y)
		{
			this->itemArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->itemArray[i];
			this->itemArray.erase(this->itemArray.begin() + i);
		}
	}
}

void GameScene::update(float delta)
{
	this->timerMeteor += delta;
	if (this->timerMeteor > GameScene::frequencyMeteor / this->visibleSize.width)
	{
		this->timerMeteor = 0;
		meteorArray.push_back(new Meteor(this));
		this->meteorUpdate();
		this->starUpdate();
	}

	this->timerBullet += delta;
	if (this->timerBullet > GameScene::frequencyBullet / this->visibleSize.height)
	{
		this->timerBullet = 0;
		bulletArray.push_back(new Bullet(this, this->ship->getPosition(), this->ship->getType()));
		this->bulletUpdate();
	}

	this->timerItem += delta;
	if (this->timerItem > GameScene::frequencyItem / this->visibleSize.height)
	{
		this->timerItem = 0;
		itemArray.push_back(new Item(this));
		this->itemUpdate();
	}

	std::stringstream score;
	score << GameScene::scorePoints;
	this->scoreLabel->setString(score.str());
	this->parallaxBg->updateWithVelocity(Point(0, GameScene::speedBackground * visibleSize.height), delta);
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
	if (GameScene::speedMeteor <= 0.0020f)
		GameScene::speedMeteor = 0.0020f;
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
	if (!def->getBoolForKey(BGM_KEY, false))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_GAMEOVER, true);
	}

	this->scoreLabel->setVisible(false);
	this->highScoreLabel->setVisible(false);
	auto gameOverDialog = GameOverDialog::create();
	this->addChild(gameOverDialog, 4, DIALOG_OBJECT);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		if (!Director::getInstance()->isPaused())
		{
			Director::getInstance()->pause();
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
			auto gameDialog = GameDialog::create();
			this->addChild(gameDialog, 4, DIALOG_OBJECT);
		}
		else if (Director::getInstance()->isPaused())
		{
			this->removeChildByTag(DIALOG_OBJECT, true);
			Director::getInstance()->resume();
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
		}
	}
}