#include "MusicD.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "Settings.h"
#include "Play.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //creating background sprite
    auto background = Sprite::create( "MAIN.png" );
    background->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    this->addChild( background);

    //creating menu buttons and setting callbacks
    auto PlayB=MenuItemFont::create("Play",CC_CALLBACK_1(MainMenu::GoToPlay,this));
    auto SettingsB=MenuItemFont::create("Settings",CC_CALLBACK_1(MainMenu::GoToSettings,this));
    auto Exit=MenuItemFont::create("Exit",CC_CALLBACK_1(MainMenu::GoToClose,this));

    //setting positions of menu buttons
    PlayB->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*3));
    SettingsB->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*2));
    Exit->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*1));

    //setting colors of menu buttons
    PlayB->setColor(Color3B(0,0,0));
    PlayB->setFontSizeObj(40.0);
    SettingsB->setColor(Color3B(0,0,0));
    SettingsB->setFontSizeObj(40.0);
    Exit->setColor(Color3B(0,0,0));
    Exit->setFontSizeObj(40.0);

    //adding actual menu
    auto *menu=Menu::create(PlayB,SettingsB,Exit,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu,2);

    //music will play, unless disabled in settings or pause layers
    MusicD& md=MusicD::getHandle();
    if(!md.GetIsMusicPlaying() && md.GetShouldMusicPlay()){
    	CocosDenshion::SimpleAudioEngine::getInstance( )->playBackgroundMusic( "Music.mp3",true );
    	md.SetIsMusicPlaying(true);
    	md.SetShouldMusicPlay(false);
    	}

    return true;
}

//implementing callback functions for menu buttons
void MainMenu::GoToPlay(Ref *Sender)
{
	auto scene=Play::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::GoToSettings(Ref *Sender)
{
	auto set=Settings::createScene();
	Director::getInstance()->pushScene(set);
}

void MainMenu::GoToClose(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
