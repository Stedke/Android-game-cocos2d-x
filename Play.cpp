#include "Play.h"
#include "Pause.h"
#include "Level.h"
#include "Definitions.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

Scene* Play::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    
    // 'layer' is an autorelease object
    auto layer = Play::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Play::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //adding a label that displays current score
    points=0;
    __String *str=__String::createWithFormat("%i",points);
    label=Label::create(str->getCString(),"Helvetica", 30);
    label->setColor(Color3B::BLACK);
    label->setPosition(Point(visibleSize.width-100,visibleSize.height-30));
    this->addChild(label,5);

    //adding background sprite
    auto background = Sprite::create( "PLAY.png" );
    background->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    this->addChild( background );

    //setting first level during playthrough's start
    Level::SetLevel(1);

    //creating symbolic menu
    auto pause=MenuItemImage::create("PAUSE.png","PAUSE.png","PAUSE.png",CC_CALLBACK_0(Play::Pause,this));
    pause->setPosition(Point(visibleSize.width-30,visibleSize.height-30));
    menu=Menu::create(pause,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    //handling touch
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=CC_CALLBACK_2(Play::onTouchBegan,this);
    listener->onTouchMoved=CC_CALLBACK_2(Play::onTouchMoved,this);
    listener->onTouchEnded=CC_CALLBACK_2(Play::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);


    //handling custom events - continuing after a pause or level layer
    auto listener1 = EventListenerCustom::create("event1",std::bind(&Play::ContinueL, this, std::placeholders::_1));  //const std::function< void(EventCustom *)>  &callback
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
    auto listener2 = EventListenerCustom::create("event2",std::bind(&Play::ContinueP, this, std::placeholders::_1));  //const std::function< void(EventCustom *)>  &callback
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,this);

    //scheduling level layers constructions
    Director::getInstance()->getScheduler()->schedule(schedule_selector(Play::Level),this,10,5,0.1,false);

    //handling physics contact events and creating edge box
    auto EdgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    EdgeBody->setCollisionBitmask(EDGE_COLLISION_BITMASK);
    EdgeBody->setContactTestBitmask(true);

    auto EdgeNode = Node::create();
    EdgeNode->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    EdgeNode->setPhysicsBody(EdgeBody);
    this->addChild(EdgeNode);

    //scheduling target spawn actions
    this->schedule(schedule_selector(Play::SpawnTargetP),2.5);

    //physics contact listener
    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( Play::onContactBegin, this );
    _eventDispatcher->addEventListenerWithSceneGraphPriority( contactListener, this );

    return true;
}

//starting a pause, or level layer

void Play::Pause()
{
	//pausing the game to access a menu: music, audio
	auto layerp=Pause::createLayer();
	this->addChild(layerp,1,2);
	layerp->setPosition(Point(0,0));

	this->Stop();
}

void Play::Level(float dt)
{
	//creating a layer announcing harder difficulty (next level)
	auto layer=Level::createLayer();
	layer->setPosition(Point(0,0));
	this->addChild(layer,1,1);

	this->Stop();
}

//handling touch

bool Play::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
	if(Bullet::getbulletcount()-100 < BULLET_LIMIT)
	{
		auto P=touch->getLocationInView();
		bullet.SpawnBullet(this,P);
	}
	return true;
}

void Play::onTouchMoved(cocos2d::Touch *touch,cocos2d::Event *event)
{

}

void Play::onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *event)
{

}

//continuing playthrough after a pause or level layer (enabling all play screen's features)

void Play::ContinueL(EventCustom *event)
{
	//after a level layer
	this->setTouchEnabled(true);
	this->menu->setEnabled(true);
	this->reorderChild(this->getChildByTag(1),-1);
	this->removeChildByTag(1,true);
	Director::getInstance()->getScheduler()->resumeTarget(this);

	for(int i=10;i<Target::getcount();i++)
	{
		this->getChildByTag(i)->resumeSchedulerAndActions();
	}

	for(int i=100;i<Bullet::getbulletcount();i++)
	{
		this->getChildByTag(i)->resumeSchedulerAndActions();
	}
}

void Play::ContinueP(EventCustom *event)
{
	//after a pause
	this->setTouchEnabled(true);
	this->menu->setEnabled(true);
	this->reorderChild(this->getChildByTag(2),-1);
	this->removeChildByTag(2,true);
	Director::getInstance()->getScheduler()->resumeTarget(this);

	for(int i=10;i<Target::getcount();i++)
	{
		this->getChildByTag(i)->resumeSchedulerAndActions();
	}

	for(int i=100;i<Bullet::getbulletcount();i++)
	{
		this->getChildByTag(i)->resumeSchedulerAndActions();
	}
}

//spawning targets
void Play::SpawnTargetP(float dt)
{
	target.SpawnTarget(this);
}

//stopping the layer if pause or level layer are enabled
void Play::Stop()
{
	for(int i=10;i<Target::getcount();i++)
	{
		this->getChildByTag(i)->pauseSchedulerAndActions();
	}

	for(int i=100;i<Bullet::getbulletcount();i++)
	{
		this->getChildByTag(i)->pauseSchedulerAndActions();
	}

	this->setTouchEnabled(false);
	this->menu->setEnabled(false);
	Director::getInstance()->getScheduler()->pauseTarget(this);
}

//implementing collision actions
bool Play::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();

    Size visibleSize = Director::getInstance()->getVisibleSize();

    //edge & target -> game over
    if (EDGE_COLLISION_BITMASK == a->getCollisionBitmask( ) && TARGET_COLLISION_BITMASK == b->getCollisionBitmask())
    {
    	if(b->getPosition().x<60 && (b->getPosition().y>31 && b->getPosition().y < visibleSize.height-31))
    	{
    		int tag=b->getNode()->getTag();
    		this->removeChild(b->getNode(),true);
    		for(int i=tag+1;i<Target::getcount();i++)
    		{
    			this->getChildByTag(i)->setTag(i-1);

    		}
    		Target::reducecount();

    		this->GameOver();
    	}
    }
    if(TARGET_COLLISION_BITMASK == a->getCollisionBitmask( ) && EDGE_COLLISION_BITMASK == b->getCollisionBitmask())
    {
    	if(a->getPosition().x<60 && (a->getPosition().y>31 && a->getPosition().y < visibleSize.height-31))
    	{
    		int tag=a->getNode()->getTag();
    		this->removeChild(a->getNode(),true);
    		for(int i=tag+1;i<Target::getcount();i++)
    		{
    			this->getChildByTag(i)->setTag(i-1);

    		}
    		Target::reducecount();

    		this->GameOver();
    	}
    }


    //bullet & edge -> bullet destroyed
    if (BULLET_COLLISION_BITMASK == a->getCollisionBitmask( ) && EDGE_COLLISION_BITMASK == b->getCollisionBitmask())
    {
    	int tag=a->getNode()->getTag();
    	this->removeChild(a->getNode(),true);
    	for(int i=tag+1;i<Bullet::getbulletcount();i++)
    	{
    		this->getChildByTag(i)->setTag(i-1);

    	}
    	Bullet::reducebulletcount();
    }
    if(EDGE_COLLISION_BITMASK == a->getCollisionBitmask( ) && BULLET_COLLISION_BITMASK == b->getCollisionBitmask())
    {
    	int tag=b->getNode()->getTag();
    	this->removeChild(b->getNode(),true);
    	for(int i=tag+1;i<Bullet::getbulletcount();i++)
    	{
    		this->getChildByTag(i)->setTag(i-1);

    	}
    	Bullet::reducebulletcount();
    }


    //bullet & target -> both destroyed, point gained
    if (BULLET_COLLISION_BITMASK == a->getCollisionBitmask( ) && TARGET_COLLISION_BITMASK == b->getCollisionBitmask())
    {
    	int tag=a->getNode()->getTag();
    	this->removeChild(a->getNode(),true);
    	for(int i=tag+1;i<Bullet::getbulletcount();i++)
    	{
    		this->getChildByTag(i)->setTag(i-1);

    	}
    	Bullet::reducebulletcount();

		int tag1=b->getNode()->getTag();
		this->removeChild(b->getNode(),true);
		for(int i=tag1+1;i<Target::getcount();i++)
		{
			this->getChildByTag(i)->setTag(i-1);

		}
		Target::reducecount();


		//point display update
		++points;
	    __String *str=__String::createWithFormat("%i",points);
	    label->setString(str->getCString());


    }
    if(TARGET_COLLISION_BITMASK == a->getCollisionBitmask( ) && BULLET_COLLISION_BITMASK == b->getCollisionBitmask())
    {
    	int tag=b->getNode()->getTag();
    	this->removeChild(b->getNode(),true);
    	for(int i=tag+1;i<Bullet::getbulletcount();i++)
    	{
    		this->getChildByTag(i)->setTag(i-1);

    	}
    	Bullet::reducebulletcount();

		int tag1=a->getNode()->getTag();
		this->removeChild(a->getNode(),true);
		for(int i=tag1+1;i<Target::getcount();i++)
		{
			this->getChildByTag(i)->setTag(i-1);

		}
		Target::reducecount();

		//point display update
		++points;
	    __String *str=__String::createWithFormat("%i",points);
	    label->setString(str->getCString());

    }

    return true;
}

void Play::GameOver()
{
	auto scene = GameOver::createScene(points);
	Director::getInstance()->replaceScene(scene);
}

//unused code
/*void Play::onEnterTransitionDidFinish()
{
	//auto scene=Level::createScene();
	//Director::getInstance()->pushScene(scene);
	Node::onEnterTransitionDidFinish();
}*/
