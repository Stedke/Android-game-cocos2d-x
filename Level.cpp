#include "Level.h"
#include "Definitions.h"

USING_NS_CC;

//static initialization
int Level::ALevel=1;

LayerColor* Level::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = Level::create();
    ALevel+=1;
    // return the scene
    return layer;
}

// on "init" you need to initialize your instance
bool Level::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0,0,0,50),800,480) )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //switch instruction creates a proper version of the layer based on actual level
    switch (Level::ALevel)
	{
    case 1:
    {	//adding a simple 'welcome' sprite
    	auto sprite0 = Sprite::create("LEVEL0.png");
    	//sprite0->initWithFile("LEVEL0.png");
        sprite0->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
        this->addChild( sprite0 );
    	break;}
    case 2:
        {//adding an animation
        SpriteFrameCache* cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("LEVEL1.plist");

        Animation *anim = Animation::create();
        for (int i = 1; i <= 3; i ++)
        {
            std::ostringstream filenameStream;
            filenameStream << "LEVEL1_" << i << ".png";
            SpriteFrame *frame = cache->getSpriteFrameByName(filenameStream.str().c_str());
            anim->addSpriteFrame(frame);
        }
        anim->setDelayPerUnit(0.2f);
        Animate *animateAction = Animate::create(anim);

        auto sprite1 = Sprite::createWithSpriteFrameName("LEVEL1_1.png");
        sprite1->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
        this->addChild( sprite1,1);
        sprite1->runAction(RepeatForever::create(animateAction));

    	break;}

        //next levels not implemented due to the lack of time
    default:
    	break;
	}

    //setting up a menu for Ok button
    auto Ok=MenuItemFont::create("Ok",CC_CALLBACK_1(Level::Ok,this));
    Ok->setPosition(Point(300,300));
    Ok->setColor(Color3B(255,255,255));
    Ok->setFontSizeObj(40.0);
    auto *menu=Menu::create(Ok,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    //handling touch, so it can be disabled on background layers
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=CC_CALLBACK_2(Level::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

void Level::Ok(Ref* Sender)
{
	//sending event to a parent layer that will resume the game and destroy the layer
    EventCustom event("event1");
    _eventDispatcher->dispatchEvent(&event);
}

//swallowing touch
bool Level::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
	return true;
}
