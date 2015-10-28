#include "Loading.h"
#include "Definitions.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Loading::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Loading::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Loading::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //preload Music
    CocosDenshion::SimpleAudioEngine::getInstance( )->preloadBackgroundMusic( "Music.mp3" );

    //create background sprite
    auto background = Sprite::create( "LOAD.png" );
    background->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    this->addChild( background );

    //after LOADINGTIME will go to Main Menu
    this->scheduleOnce( schedule_selector( Loading::GoToMainMenu ), LOADINGTIME );

    return true;
}

void Loading::GoToMainMenu(float dt)
{
    auto scene = MainMenu::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITIONTIME, scene ) );
}
