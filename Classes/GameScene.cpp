#include "GameScene.h"

USING_NS_CC;

int GameScene::scorePoints = 0;
float GameScene::speedBullet = 0.001f;
float GameScene::speedMeteor = 0.005f;
float GameScene::speedBackground = -0.01f;
float GameScene::frequencyMeteor = 0.001f;
float GameScene::frequencyBullet = 0.0005f;

GameScene::GameScene()
	: timerMeteor(0), timerBullet(0)
{
	GameScene::setDefaultValue();
	ship = new Ship(this);
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();

	layer->setPhysicsWorld(scene->getPhysicsWorld());
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
	scoreLabel = Label::createWithTTF(std::to_string(GameScene::scorePoints), "Fonts/kenvector_future_thin.ttf", visibleSize.height / 15);
	scoreLabel->setAlignment(TextHAlignment::CENTER);
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - visibleSize.height / 15 + origin.y));

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->addChild(scoreLabel, 3);
	this->setParallaxBackground();
	this->scheduleUpdate();
	return true;
}

void GameScene::setPhysicsWorld(PhysicsWorld *world)
{
	this->sceneWorld = world;
}

void GameScene::setParallaxBackground()
{
	std::srand(time(NULL));
	int backgroundIndex = rand() % 4 + 1;

	__String *backgroundString = __String::createWithFormat("Backgrounds/background%i.png", backgroundIndex);
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
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	Sprite *aSprite = (Sprite *)a->getNode();
	Sprite *bSprite = (Sprite *)b->getNode();
	Point aPos;
	Point bPos;

	if (aSprite && bSprite)
	{
		aPos = aSprite->getPosition();
		bPos = bSprite->getPosition();
	}
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_SHIP && b->getCollisionBitmask() == COLLISION_METEOR)
		this->shipCollision(aSprite);
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_SHIP && a->getCollisionBitmask() == COLLISION_METEOR)
		this->shipCollision(bSprite);
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_METEOR && b->getCollisionBitmask() == COLLISION_BULLET)
	{
		GameScene::incrementScore(1);
		this->meteorCollision(aSprite);
		this->bulletCollision(bSprite);
	}
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_METEOR && a->getCollisionBitmask() == COLLISION_BULLET)
	{
		GameScene::incrementScore(1);
		this->meteorCollision(bSprite);
		this->bulletCollision(bSprite);
	}
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_STAR && b->getCollisionBitmask() == COLLISION_SHIP)
		this->starCollision(aSprite);
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_STAR && a->getCollisionBitmask() == COLLISION_SHIP)
		this->starCollision(bSprite);
	return true;
}

void GameScene::shipCollision(Sprite *ship)
{
	this->ship->reduceLife();
	if (this->ship->getLife() <= 0)
	{
		this->ship->displayExplosion(this);
		this->ship->getSprite()->removeFromParentAndCleanup(true);
		this->getEventDispatcher()->removeAllEventListeners();
		this->unscheduleAllCallbacks();
		delete this->ship;
		this->schedule(schedule_selector(GameScene::goToGameOverScene), 2.0f);
	}
}

void GameScene::meteorCollision(Sprite *meteor)
{
	for (unsigned int i = 0; i < this->meteorArray.size(); ++i)
	{
		if (this->meteorArray[i]->getSprite() == meteor)
		{
			this->meteorArray[i]->reduceLife();
			if (this->meteorArray[i]->getLife() <= 0)
			{
				this->meteorArray[i]->displayExplosion(this);
				starArray.push_back(new Star(this, this->meteorArray[i]->getPosition(), this->meteorArray[i]->getType()));
				this->meteorArray[i]->getSprite()->removeFromParentAndCleanup(true);
				delete this->meteorArray[i];
				this->meteorArray.erase(this->meteorArray.begin() + i);
			}
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
				GameScene::incrementScore(10);
			else if (type == 2)
				GameScene::incrementScore(50);
			else if (type == 3)
				GameScene::incrementScore(100);
			this->starArray[i]->displayStarEffect(this);
			this->starArray[i]->getSprite()->removeFromParentAndCleanup(true);
			delete this->starArray[i];
			this->starArray.erase(this->starArray.begin() + i);
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

void GameScene::update(float delta)
{
	this->timerMeteor += delta;
	if (this->timerMeteor > GameScene::frequencyMeteor * this->visibleSize.width)
	{
		this->timerMeteor = 0;
		meteorArray.push_back(new Meteor(this));
		this->meteorUpdate();
		this->starUpdate();
	}
	this->timerBullet += delta;
	if (this->timerBullet > GameScene::frequencyBullet * this->visibleSize.width)
	{
		this->timerBullet = 0;
		bulletArray.push_back(new Bullet(this, this->ship->getPosition(), this->ship->getType()));
		this->bulletUpdate();
	}
	this->scoreLabel->setString(std::to_string(GameScene::scorePoints));
	this->parallaxBg->updateWithVelocity(Point(0, GameScene::speedBackground * visibleSize.height), delta);
	GameScene::scaleDifficulty(this);
}

void GameScene::goToGameOverScene(float delta)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(DELAY_TRANSITION, scene));
}

void GameScene::incrementScore(int value)
{
	scorePoints += value;
}

void GameScene::scaleDifficulty(Layer *layer)
{
	if (GameScene::scorePoints > 100 && GameScene::scorePoints < 500)
	{
		GameScene::speedMeteor = 0.004f;
		GameScene::speedBackground = -0.02f;
		GameScene::frequencyMeteor = 0.0009f;
	}
	else if (GameScene::scorePoints > 500 && GameScene::scorePoints < 1000)
	{
		GameScene::speedMeteor = 0.003f;
		GameScene::speedBackground = -0.03f;
		GameScene::frequencyMeteor = 0.0008f;
	}
	else if (GameScene::scorePoints > 1000 && GameScene::scorePoints < 2000)
	{
		GameScene::speedMeteor = 0.002f;
		GameScene::speedBackground = -0.04f;
		GameScene::frequencyMeteor = 0.0007f;
	}
	else if (GameScene::scorePoints > 2000)
	{
		GameScene::speedMeteor = 0.0015f;
		GameScene::speedBackground = -0.05f;
		GameScene::frequencyMeteor = 0.0006f;
	}
}

void GameScene::setDefaultValue()
{
	GameScene::scorePoints = 0;
	GameScene::speedBullet = 0.001f;
	GameScene::speedMeteor = 0.005f;
	GameScene::speedBackground = -0.01f;
	GameScene::frequencyMeteor = 0.001f;
	GameScene::frequencyBullet = 0.0005f;
}