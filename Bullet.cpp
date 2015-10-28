#include "Bullet.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

int Bullet::bcount=100;

Bullet::Bullet()
{
	visibleSize=Director::getInstance()->getVisibleSize();
	origin=Director::getInstance()->getVisibleOrigin();
	//bullets tags are counted from 101 to 'infinity'
	bcount=100;
}

void Bullet::SpawnBullet(cocos2d::Layer* layer, Vec2 &aim)
{
	//setting up bullet't physics body and collision bitmasks
	auto bulletBody = PhysicsBody::createBox(Size(10,10));
    bulletBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
    bulletBody->setContactTestBitmask(true);
	bulletBody->setDynamic(true);

	auto bullet = Sprite::create("BULLET.png");

	bullet->setPhysicsBody(bulletBody);

	bullet->setPosition(Point(10,visibleSize.height/2));

	layer->addChild(bullet,0,Bullet::bcount);

	//adding bullet's move action
	float a=((visibleSize.height/2)-aim.y)/(10-aim.x);

	auto action =MoveBy::create(0.1*visibleSize.width,Point(visibleSize.width*5,-a*visibleSize.width*5));
	bullet->runAction(action);

	//increasing total bullets amount
	Bullet::bcount+=1;
}
