#include "StartScene.h"
#include "GameScene.h"

Scene* Start::createScene()
{
	auto scene =Scene::create();
	auto layer = Start::create();
	scene->addChild(layer);

	return scene;
}

bool Start:: init()
{
    if (!Layer::init())
	{
	    return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto dirt = Sprite::create("bg_dirt.png");
	dirt->setScale(2.0);
	dirt->setAnchorPoint(Vec2::ZERO);
	dirt->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(dirt,-2);

	auto upper =Sprite::create("grass_upper.png");
	upper->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	upper->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(upper,-1);

	auto lower =Sprite::create("grass_lower.png");
	lower->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	lower->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(lower,1);

	auto leftMple = Sprite::create("mole_1.png");
	leftMple->setPosition(168,visibleSize.height/2-60);
	this->addChild(leftMple,0);

	auto centerMole = Sprite::create("mole_thump4.png");
	centerMole->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(centerMole,0);

	auto rightMole = Sprite::create("mole_laugh1.png");
	rightMole->setPosition(visibleSize.width - 168,visibleSize.height/2);
	this->addChild(rightMole,0);

	auto mallet = Sprite::create("mallet2.png");
	mallet->setScale(0.8f);
	mallet->setPosition(visibleSize.width/2 +80,visibleSize.height/2 +80);
	this->addChild(mallet,0);

	auto labell = Label::createWithSystemFont("·è¿ñ´òµØÊó","Arial-BoldMT",80);
	labell->setPosition(visibleSize.width/2,visibleSize.height*0.88);
	labell->setColor(Color3B(255,0,0));
	this->addChild(labell,1);

	auto playItem = MenuItemImage::create("btn-start.png","btn-start.png",CC_CALLBACK_0(Start::startGame,this));
	playItem->setPosition(visibleSize.width/2,visibleSize.height*0.3);

	auto menu = Menu::create(playItem,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	SimpleAudioEngine::getInstance()->playBackgroundMusic("whack.caf",true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);

	return true;

}

void Start::startGame()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BACKGrOUNDPLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RESOURCESPLIST);

	SimpleAudioEngine::getInstance()->preloadEffect(LAUGHEFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(OWEFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(SECONDEFFECT);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUNDMUSIC);

	Animation* laughAnimation = getAnimationByName("mole_laugh",0.5f,3);
	Animation* hitAnimation = getAnimationByName("mole_thump",0.3f,4);
	Animation* malletAnimation = getAnimationByName("mallet",0.15f,3);

	AnimationCache::getInstance()->addAnimation(laughAnimation,"laughAnimation");
	AnimationCache::getInstance()->addAnimation(hitAnimation,"hitAnimation");
	AnimationCache::getInstance()->addAnimation(malletAnimation,"malletAnimation");

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(Game::createScene());
}

Animation* Start:: getAnimationByName(std::string animName, float delay, int animNum) 
 {
	 Animation* animation = Animation::create();

	 for (unsigned int i = 1; i<= animNum;i++)
	 {
		std:: string franame = animName;
		 franame.append(StringUtils::format("%d",i).append(".png"));
		 animation->addSpriteFrameWithFile(franame.c_str());
		 
	 }
	 animation->setDelayPerUnit(delay);
	 animation->setRestoreOriginalFrame(true);
	 return animation;
 }

void Start:: menuCloseCallback(Ref* pSender)
{
	

}