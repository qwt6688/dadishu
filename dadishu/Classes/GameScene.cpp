#include "GameScene.h"

int Game::_level = 1;
Scene* Game:: createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);

	return scene;

}

bool Game::init()
{
	  if (!Layer::init())
	   {
	      return false;
	   }

	  Size visibleSize = Director::getInstance()->getVisibleSize();
	  _screenWidth = visibleSize.width;
	  _screenHeight = visibleSize.height;

	  	_sucessScore = 15;
	    _totalMole = 20;

	_sucessScore = 15 + (_level*5 - 5);
	_totalMole = 20 + (_level*10 -10);
	_timeBarInterval = 100 /_totalMole;
	_popDelay = 0.5 - (_level*0.05 - 0.05);

	  auto dirt = Sprite::createWithSpriteFrameName("bg_dirt.png");
	dirt->setScale(2.0);
	dirt->setAnchorPoint(Vec2::ZERO);
	dirt->setPosition(_screenWidth/2,_screenHeight/2);
	this->addChild(dirt,-2);

	auto upper =Sprite::createWithSpriteFrameName("grass_upper.png");
	upper->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	upper->setPosition(_screenWidth/2,_screenHeight/2);
	this->addChild(upper,-1);

	auto lower =Sprite::createWithSpriteFrameName("grass_lower.png");
	lower->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	lower->setPosition(_screenWidth/2,_screenHeight/2);
	this->addChild(lower,1);

	auto leftMple = Sprite::createWithSpriteFrameName("mole_1.png");
	leftMple->setPosition(168,visibleSize.height/2-160);
	this->addChild(leftMple,0);
	_molesVector.pushBack(leftMple);

	auto centerMole = Sprite::createWithSpriteFrameName("mole_thump4.png");
	centerMole->setPosition(visibleSize.width/2,visibleSize.height/2-160);
	this->addChild(centerMole,0);
	_molesVector.pushBack(centerMole);

	auto rightMole = Sprite::createWithSpriteFrameName("mole_laugh1.png");
	rightMole->setPosition(visibleSize.width - 168,visibleSize.height/2-160);
	this->addChild(rightMole,0);
	_molesVector.pushBack(rightMole);

	this->schedule(schedule_selector(Game::andomPopMoles),_popDelay);
	this->schedule(schedule_selector(Game::gameOver),_popDelay);

	  // 创建单点触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *touch, Event *unused_event){
        // 把touch坐标转换成Node坐标
        Point touchLocation = this->convertTouchToNodeSpace(touch);
        // 遍历地鼠集合
        for (Sprite* mole : _molesVector) {
            // 如果当前这只地鼠的tag标记为0，表示不可以敲打，那么就直接检查下一个地鼠
            if (mole->getTag() == 0 ) continue;
            // 如果touch触碰范围是地鼠时
            if (mole->getBoundingBox().containsPoint(touchLocation)) {
                // 创建木槌，将木槌显示在中间的地鼠头上
                auto mallet = Sprite::createWithSpriteFrameName("mallet1.png");
                // 获得木槌动画
                auto malletAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("malletAnimation"));
                mallet->setScale(0.8f);
                mallet->setPosition(mole->getPosition().x+100, mole->getPosition().y+60);
                this->addChild(mallet, 0);
                // 播放木槌动画
                mallet->runAction(Sequence::create(malletAnimation,
                                                   CallFunc::create([=]{
                    // 播放地鼠被打中音效
                    SimpleAudioEngine::getInstance()->playEffect("ow.caf");
                    // 地鼠被打中后播放粒子效果
                    auto aswoon = ParticleSystemQuad::create("aswoon.plist");
                    aswoon->setPosition(mole->getPosition().x, mole->getPosition().y);
                    this->addChild(aswoon);

                    // 删除木槌
                    this->removeChild(mallet);
                }), NULL));
                // 地鼠被打中后，修改tag标记为0，表示地鼠已经被打中，不能重复敲打
                mole->setTag(0);
                // 分数加1
				_scroe += 1;
                // 地鼠被打中后，停止所有动作，即不能再执行大笑和眨眼的动作
                mole->stopAllActions();
                // 播放地鼠被打中动画
                auto hitAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("hitAnimation"));
                // 地鼠缩回地洞动作
                MoveBy* moveDown = MoveBy::create(0.2f, Point(0, -mole->getContentSize().height));
                EaseInOut* easeMoveDown = EaseInOut::create(moveDown, 3.0f);
                // 地鼠顺序执行播放被打中动画和缩回地洞动作
                mole->runAction(Sequence::create(hitAnimate, easeMoveDown, NULL));
            }
        }
        return true;
    };
    // 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	std::string levelString = StringUtils::format("关卡：%i",_level);
	_levelLabel = Label::createWithSystemFont(levelString,"fonts/Marker Felt.ttf",36);
	_levelLabel ->setPosition(visibleSize.width*0.10,visibleSize.height - 30);
	this->addChild(_levelLabel,3);

	_scroeLabel =Label::createWithSystemFont("本关得分: 0","fonts/marker Felt.ttf",36);
	_scroeLabel->setPosition(visibleSize.width*0.30,visibleSize.height - 30);
	this->addChild(_scroeLabel,10);

	std::string molelabelString = StringUtils::format("本关地鼠：%i",_totalMole);
	_moleLabel = Label::createWithSystemFont(molelabelString,"fonts/Marker Felt.ttf",36);
	_moleLabel->setPosition(visibleSize.width*0.55,visibleSize.height-30);
	this->addChild(_moleLabel,10);

	std::string passLabelString = StringUtils::format("过关目标分： %i",_sucessScore);
	_passLabel = Label::createWithSystemFont(passLabelString,"fonts/Marker Felt.ttf",36);
	_passLabel->setPosition(visibleSize.width*0.85,visibleSize.height - 30);
	this->addChild(_passLabel);

	_timeBarInterval = 100 /_totalMole;
	auto clock = Sprite::createWithSpriteFrameName("clock.png");
	clock->setScale(0.3);
	clock->setPosition(_screenWidth*0.2, _screenHeight *0.1);
	this->addChild(clock,2);

	_timeBar = LoadingBar::create("bar.png");
	_timeBar->setScale(0.7f);
	_timeBar->setDirection(LoadingBar::Direction::LEFT);
	_timeBar->setPercent(100);
	_timeBar->setPosition(Vec2(_screenWidth*0.55,_screenHeight*0.1));
	this->addChild(_timeBar,2);



	return true;
}

void Game:: andomPopMoles(float delta)
{
	for ( auto mole : _molesVector)
	{
		int temp = CCRANDOM_0_1()*10000;
		if (temp %3 == 0)
		{
		    if (mole->getNumberOfRunningActions() == 0)
			{
				popMole(mole);
				float percentage = _timeBarInterval*_totalMole;

				if (_totalMole == 9)
				{
					_timeBar->setColor(Color3B(255,0,0));
					SimpleAudioEngine::getInstance()->playEffect("second.mp3",true);
				
				}
				_timeBar->setPercent(percentage);
				if (_totalMole <= 0) return;
				_totalMole--;
			}
		
		}
	
	
	}
	_scroeLabel->setString(StringUtils::format("本关得分： %d",_scroe));
}

void Game::popMole(Sprite* mole)
{
	auto moveUp = MoveBy::create(0.2f,Vec2(0,mole->getContentSize().height));

	auto easeMoveUp = EaseInOut::create(moveUp,3.0f);
	auto easeMoveDown = easeMoveUp->reverse();

	mole->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_1.png"));

	auto laughaAnimate =Animate::create(AnimationCache::getInstance()->getAnimation("laughAnimation"));
	mole->runAction(Sequence::create(easeMoveUp,CallFuncN::create(CC_CALLBACK_1(Game::setHit,this)),laughaAnimate,
		easeMoveDown,CallFuncN::create(CC_CALLBACK_1(Game::unHit,this)),NULL));
	
}

void  Game::setHit(Ref* pSender)
{
	Sprite* mole =(Sprite*)pSender;
	mole->setTag(1);

	SimpleAudioEngine::getInstance()->playEffect("laugh.caf");

}

void Game::unHit(Ref* pSender)
{
	Sprite* mole = (Sprite*)pSender;
	mole->setTag(0);

}

void Game::gameOver(float delta)
{
	if (_totalMole <= 0)
	{
	    bool flag = true;
		for (Sprite* mole : _molesVector)
		{
			if (mole->getNumberOfRunningActions() != 0)
			{
			    flag = false;
				break;
			
			}
		
		}
	  if (flag)
	  {
		  _gameOver = true;
		  MenuItemImage* goItem = nullptr;
		  if (_scroe < _sucessScore)
		  {
			  goItem = MenuItemImage::create("btn-continue.png","btn-continue.png",[&](Ref *sender){
				  Director::getInstance()->replaceScene(Game::createScene());
			  
			  }); 
		  }
		  else
		  {
			  goItem = MenuItemImage::create("btn-next.png","btn-next.png",[&](Ref* sender){
				                                    _level = _level + 1;
													Director::getInstance()->replaceScene(Game::createScene());
			  
			  });
		  }
		  goItem->setPosition(Vec2(_screenWidth /2,_screenHeight /2 + 100));
		  auto againItem = MenuItemImage::create("btn-again.png","btn-again.png",[&](Ref *sender){
			  Director::getInstance()->replaceScene(Start::createScene());
		  });
		  againItem->setPosition(Vec2(_screenWidth /2, _screenHeight / 2 -100));
		  SimpleAudioEngine::getInstance()->stopAllEffects();
		  SimpleAudioEngine::getInstance()->stopBackgroundMusic();

		  auto menu = Menu::create(goItem,againItem,NULL);
		  menu->setPosition(Point::ZERO);
		  this->addChild(menu,1);

		  return;

	  }
	
	}

}