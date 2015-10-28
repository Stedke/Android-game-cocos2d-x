#include "MainMenu.h"
#include "GameOver.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

int GameOver::points=0;

Scene* GameOver::createScene(int pointst)
{
	points=pointst;
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Creating score display
    __String *str=__String::createWithFormat("%i",points);
    auto label=Label::create(str->getCString(),"Helvetica", 30);
    label->setColor(Color3B::BLACK);
    label->setPosition(Point(visibleSize.width-100,visibleSize.height-30));
    this->addChild(label,5);

    //adding background sprite
    auto background = Sprite::create( "PLAY.png" );
    background->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    this->addChild( background );

    //adding foreground sprite
	auto sprite0 = Sprite::create("LEVEL0.png");
    sprite0->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    this->addChild( sprite0 );

    //adding menu ok button
    auto Ok=MenuItemFont::create("Ok",CC_CALLBACK_0(GameOver::Ok,this));
    Ok->setPosition(Point(300,300));
    Ok->setColor(Color3B(255,255,255));
    Ok->setFontSizeObj(40.0);
    auto *menu=Menu::create(Ok,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    return true;
}

void GameOver::Ok()
{
	auto scene=MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
