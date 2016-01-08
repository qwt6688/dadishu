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

	LoadingBar* _timeBar;  //��ʱ��������
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

	Label* _levelLabel;  //�ؿ�����label
	Label* _passLabel;   //���ط���
	Label* _scroeLabel;  //��ʾ����
	Label* _moleLabel;   //��ʾ��������
	int _scroe;          //����
	int _sucessScore;     //����Ŀ�����
	int _totalMole;       //��ǰ�ؿ�������ĵ�������
	

};

#endif