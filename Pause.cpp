#include "MusicD.h"
#include "Pause.h"
#include "Definitions.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

LayerColor* Pause::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = Pause::create();

    // return the scene
    return layer;
}

// on "init" you need to initialize your instance
bool Pause::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0,0,0,50),800,480) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //adding menu items
    auto Exit=MenuItemFont::create("Exit",CC_CALLBACK_1(Pause::Exit,this));
    auto Resume=MenuItemFont::create("Resume",CC_CALLBACK_1(Pause::Resume,this));
    Exit->setColor(Color3B(0,0,0));
    Exit->setFontSizeObj(40.0);
    Resume->setColor(Color3B(0,0,0));
    Resume->setFontSizeObj(40.0);

    //adding labels that will clarify graphic buttons' meanings
    auto MusicT=Label::create();
    auto AudioT=Label::create();
    MusicT->setString("Music");
    AudioT->setString("Audio");
    MusicT->setSystemFontSize(40.0);
    AudioT->setSystemFontSize(40.0);
    MusicT->setColor(Color3B(0,0,0));
    AudioT->setColor(Color3B(0,0,0));
    MusicT->setPosition(Point(visibleSize.width/2-50,(visibleSize.height/5)*4));
    AudioT->setPosition(Point(visibleSize.width/2-50,(visibleSize.height/5)*3));
    this->addChild(MusicT);
    this->addChild(AudioT);

    //creating grahic buttons
    auto MusicON=MenuItemImage::create("MUSICON.png","MUSICON.png");
    auto MusicOFF=MenuItemImage::create("MUSICOFF.png","MUSICOFF.png");
    auto AudioON=MenuItemImage::create("MUSICON.png","MUSICON.png");
    auto AudioOFF=MenuItemImage::create("MUSICOFF.png","MUSICOFF.png");

    //adding toggles to support two-state graphic buttons
    auto ToggleM=MenuItemToggle::createWithCallback(CC_CALLBACK_1(Pause::SwitchMusic,this),MusicON,MusicOFF,NULL);
    auto ToggleA=MenuItemToggle::createWithCallback(CC_CALLBACK_1(Pause::SwitchAudio,this),AudioON,AudioOFF,NULL);

    //setting items' positions
    ToggleM->setPosition(Point(visibleSize.width/2+50,(visibleSize.height/5)*4));
    ToggleA->setPosition(Point(visibleSize.width/2+50,(visibleSize.height/5)*3));
    Resume->setPosition(Point(visibleSize.width/2+50,(visibleSize.height/5)*2));
    Exit->setPosition(Point(visibleSize.width/2+50,(visibleSize.height/5)*1));

    //making sure that graphics will be displayed properly for disabled music/audio
    MusicD& md=MusicD::getHandle();

    if(!md.GetIsMusicPlaying())
    {
    	ToggleM->setSelectedIndex(1);
    }
    if(!md.GetIsAudioPlaying())
    {
    	ToggleA->setSelectedIndex(1);
    }

    //adding menu
    auto *menu=Menu::create(ToggleA,ToggleM,Resume,Exit,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    //adding touch swallowing event listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=CC_CALLBACK_2(Pause::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

//menu buttons' callbacks
void Pause::Exit(Ref *Sender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Pause::Resume(Ref *Sender)
{
    EventCustom event("event2");
    _eventDispatcher->dispatchEvent(&event);
}

void Pause::SwitchAudio(Ref *Sender)
{
	//this code makes sure that music is being enabled when needed and disabled properly
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

void Pause::SwitchMusic(Ref *Sender)
{
	//this code makes sure that audio is being enabled when needed and disabled properly
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

//touch swallowing function
bool Pause::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
	return true;
}
