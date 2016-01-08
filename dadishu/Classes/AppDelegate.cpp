#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto designSize = Size(960,640);
	glview->setDesignResolutionSize(designSize.width,designSize.height,ResolutionPolicy::FIXED_WIDTH);
	Size frameSize = glview->getFrameSize();
	if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		if (frameSize.width > 960)
		{
		   Size resourceSize = Size(1136,640);

		   director->setContentScaleFactor(MIN(resourceSize.height/designSize.height,resourceSize.width/designSize.width));
		
		}
	
	}
	else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		
		   Size resourceSize = Size(480,800);

		   if (frameSize.width == 1280 && frameSize.height == 720)
		   {
			   resourceSize = Size(1280,720);
		   }

		   director->setContentScaleFactor(MIN(resourceSize.height/designSize.height,resourceSize.width/designSize.width));
		
		
	
	}
    // create a scene. it's an autorelease object
    auto scene = Start::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
