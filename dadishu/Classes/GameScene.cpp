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

	  // �������㴥��������
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *touch, Event *unused_event){
        // ��touch����ת����Node����
        Point touchLocation = this->convertTouchToNodeSpace(touch);
        // �������󼯺�
        for (Sprite* mole : _molesVector) {
            // �����ǰ��ֻ�����tag���Ϊ0����ʾ�������ô���ô��ֱ�Ӽ����һ������
            if (mole->getTag() == 0 ) continue;
            // ���touch������Χ�ǵ���ʱ
            if (mole->getBoundingBox().containsPoint(touchLocation)) {
                // ����ľ鳣���ľ���ʾ���м�ĵ���ͷ��
                auto mallet = Sprite::createWithSpriteFrameName("mallet1.png");
                // ���ľ鳶���
                auto malletAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("malletAnimation"));
                mallet->setScale(0.8f);
                mallet->setPosition(mole->getPosition().x+100, mole->getPosition().y+60);
                this->addChild(mallet, 0);
                // ����ľ鳶���
                mallet->runAction(Sequence::create(malletAnimation,
                                                   CallFunc::create([=]{
                    // ���ŵ��󱻴�����Ч
                    SimpleAudioEngine::getInstance()->playEffect("ow.caf");
                    // ���󱻴��к󲥷�����Ч��
                    auto aswoon = ParticleSystemQuad::create("aswoon.plist");
                    aswoon->setPosition(mole->getPosition().x, mole->getPosition().y);
                    this->addChild(aswoon);

                    // ɾ��ľ�
                    this->removeChild(mallet);
                }), NULL));
                // ���󱻴��к��޸�tag���Ϊ0����ʾ�����Ѿ������У������ظ��ô�
                mole->setTag(0);
                // ������1
				_scroe += 1;
                // ���󱻴��к�ֹͣ���ж�������������ִ�д�Ц��գ�۵Ķ���
                mole->stopAllActions();
                // ���ŵ��󱻴��ж���
                auto hitAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("hitAnimation"));
                // �������صض�����
                MoveBy* moveDown = MoveBy::create(0.2f, Point(0, -mole->getContentSize().height));
                EaseInOut* easeMoveDown = EaseInOut::create(moveDown, 3.0f);
                // ����˳��ִ�в��ű����ж��������صض�����
                mole->runAction(Sequence::create(hitAnimate, easeMoveDown, NULL));
            }
        }
        return true;
    };
    // ��Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	std::string levelString = StringUtils::format("�ؿ���%i",_level);
	_levelLabel = Label::createWithSystemFont(levelString,"fonts/Marker Felt.ttf",36);
	_levelLabel ->setPosition(visibleSize.width*0.10,visibleSize.height - 30);
	this->addChild(_levelLabel,3);

	_scroeLabel =Label::createWithSystemFont("���ص÷�: 0","fonts/marker Felt.ttf",36);
	_scroeLabel->setPosition(visibleSize.width*0.30,visibleSize.height - 30);
	this->addChild(_scroeLabel,10);

	std::string molelabelString = StringUtils::format("���ص���%i",_totalMole);
	_moleLabel = Label::createWithSystemFont(molelabelString,"fonts/Marker Felt.ttf",36);
	_moleLabel->setPosition(visibleSize.width*0.55,visibleSize.height-30);
	this->addChild(_moleLabel,10);

	std::string passLabelString = StringUtils::format("����Ŀ��֣� %i",_sucessScore);
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
	_scroeLabel->setString(StringUtils::format("���ص÷֣� %d",_scroe));
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