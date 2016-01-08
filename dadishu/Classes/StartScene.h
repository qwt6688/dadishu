#ifndef _StartScene_H_
#define _StartScene_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


#define BACKGrOUNDPLIST "background.plist"
#define RESOURCESPLIST "resources.plist"
#define LAUGHEFFECT "laugh.caf"
#define OWEFFECT  "ow.caf"
#define SECONDEFFECT "second.mp3"
#define BACKGROUNDMUSIC "whack.caf"

using namespace CocosDenshion;

USING_NS_CC;

class Start : public Layer
{
public:
    static Scene* createScene();
	virtual bool init();
	void startGame();
	Animation* getAnimationByName(std::string animName, float delay, int animNum);

	void menuCloseCallback(Ref* pSender);
	CREATE_FUNC(Start);


};

#endif