#include "MusicD.h"
#include "Settings.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"


USING_NS_CC;

Scene* Settings::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Settings::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Settings::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //adding background sprite (the same is in the main menu)
    auto background = Sprite::create( "MAIN.png" );
    background->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    this->addChild( background );

    //creating labels that will explain menu's option graphics
    auto MusicT=Label::create();
    auto AudioT=Label::create();
    MusicT->setString("Music");
    AudioT->setString("Audio");
    MusicT->setSystemFontSize(40.0);
    AudioT->setSystemFontSize(40.0);
    MusicT->setColor(Color3B(0,0,0));
    AudioT->setColor(Color3B(0,0,0));//pink: 255,102,178,100 :)
    MusicT->setPosition(Point(visibleSize.width/2-50,(visibleSize.height/4)*3));
    AudioT->setPosition(Point(visibleSize.width/2-50,(visibleSize.height/4)*2));
    this->addChild(MusicT);
    this->addChild(AudioT);

    //creating menu's graphic 'buttons'
    auto MusicON=MenuItemImage::create("MUSICON.png","MUSICON.png");
    auto MusicOFF=MenuItemImage::create("MUSICOFF.png","MUSICOFF.png");
    auto AudioON=MenuItemImage::create("MUSICON.png","MUSICON.png");
    auto AudioOFF=MenuItemImage::create("MUSICOFF.png","MUSICOFF.png");
    auto Exit=MenuItemFont::create("Back",CC_CALLBACK_1(Settings::Back,this));

    //creating menu's toggles to control two-state nature of buttons
    auto ToggleM=MenuItemToggle::createWithCallback(CC_CALLBACK_1(Settings::SwitchMusic,this),MusicON,MusicOFF,NULL);
    auto ToggleA=MenuItemToggle::createWithCallback(CC_CALLBACK_1(Settings::SwitchAudio,this),AudioON,AudioOFF,NULL);

    //other properties
    ToggleM->setPosition(Point(visibleSize.width/2+50,(visibleSize.height/4)*3));
    ToggleA->setPosition(Point(visibleSize.width/2+50,(visibleSize.height/4)*2));
    Exit->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*1));
    Exit->setColor(Color3B(0,0,0));
    Exit->setFontSizeObj(40.0);

    //this ensures that starting buttons' graphics will be displayed properly when music, or audio was disabled earlier
	MusicD& md=MusicD::getHandle();
    if(!md.GetIsMusicPlaying())
    {
    	ToggleM->setSelectedIndex(1);
    }
    if(!md.GetIsAudioPlaying())
    {
    	ToggleA->setSelectedIndex(1);
    }

    //creating menu
    auto *menu=Menu::create(ToggleM,ToggleA,Exit,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    return true;
}

//Music/audio on/off
void Settings::SwitchMusic(Ref *Sender)
{
	//algorithm will play the music/audio if needed and properly switched
	MusicD& md=MusicD::getHandle();

	MenuItemToggle *toggleItem = (MenuItemToggle *)Sender;

	if(toggleItem->getSelectedIndex()==0)
	{
		if(!md.GetIsMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music.mp3",true);
		}

		md.SetIsMusicPlaying(true);
		md.SetShouldMusicPlay(false);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		md.SetIsMusicPlaying(false);
		md.SetShouldMusicPlay(false);
	}
}

void Settings::SwitchAudio(Ref *Sender)
{
	//algorithm will play the music/audio if needed and properly switched
	MusicD& md=MusicD::getHandle();

	MenuItemToggle *toggleItem = (MenuItemToggle *)Sender;

	if(toggleItem->getSelectedIndex()==0)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
		md.SetIsAudioPlaying(true);
		md.SetShouldAudioPlay(false);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		md.SetIsAudioPlaying(false);
		md.SetShouldAudioPlay(false);
	}
}

void Settings::Back(Ref *Sender)
{
	Director::getInstance()->popScene();
}
