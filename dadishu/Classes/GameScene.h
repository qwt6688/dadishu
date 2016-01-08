#ifndef _GameScene_H_
#define _GameScene_H_

#include "cocos2d.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

using namespace CocosDenshion;
USING_NS_CC;
using namespace ui;

class Game : public Layer
{
private:
	int _screenWidth, _screenHeight;
	Vector<Sprite*> _molesVector;

	LoadingBar* _timeBar;  //计时器进度条
	float _timeBarInterval;

	float _popDelay;
	bool _gameOver;

	static int _level;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Game);

	void andomPopMoles(float delta);
    void popMole(Sprite* mole);
	void setHit(Ref* pSender);
	void unHit(Ref* pSender);
	void gameOver(float delta);

	Label* _levelLabel;  //关卡数的label
	Label* _passLabel;   //过关分数
	Label* _scroeLabel;  //显示分数
	Label* _moleLabel;   //显示地鼠总数
	int _scroe;          //分数
	int _sucessScore;     //过关目标分数
	int _totalMole;       //当前关卡总钻出的地鼠数量
	

};

#endif