#include "Target.h"
#include "Definitions.h"
#include "Level.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

//targets tags' are counted from 11 to 100
int Target::count=10;

Target::Target()
{
	visibleSize=Director::getInstance()->getVisibleSize();
	origin=Director::getInstance()->getVisibleOrigin();
	count=10;
}

void Target::SpawnTarget(cocos2d::Layer* layer)
{
	//settong up physics body for a target
	auto targetBody = PhysicsBody::createBox(Size(60,60));
    targetBody->setCollisionBitmask(TARGET_COLLISION_BITMASK);
    targetBody->setContactTestBitmask(true);
	targetBody->setDynamic(true);

	auto random = CCRANDOM_0_1( );

	auto target = Sprite::create("TARGET.png");

	target->setPhysicsBody(targetBody);

	//target will be placed randomly on the right side of the screen
	if(random>0.5)
	{
		auto targetPosition = random * visibleSize.height-60;
		target->setPosition(Point(visibleSize.width-60, targetPosition));
	}
	else
	{
		auto targetPosition = random * visibleSize.height+60;
		target->setPosition(Point(visibleSize.width-60, targetPosition));
	}

	layer->addChild(target,0,Target::count);

	int random2;

	//target's move action will be determined randomly: 3 options are available
	if(rand_0_1()<0.333){
		random2=1;}
	else if(rand_0_1()<0.666) {
		random2=2;}
	else{
		random2=3;}

	switch(random2)
	{
	case 1:
	{
		auto speed=(0.1-0.02*(static_cast<double>(Level::GetLevel())-1.0)>0) ? (0.1-0.02*(static_cast<double>(Level::GetLevel())-1.0)) : 0.01;
		auto targetAction=MoveBy::create(speed*visibleSize.width,Point(-visibleSize.width*1.5,0));
		target->runAction(targetAction);
		break;
	}
	case 2:
	{
		auto speed=(0.1-0.02*(static_cast<double>(Level::GetLevel())-1.0)>0) ? (0.1-0.02*(static_cast<double>(Level::GetLevel())-1.0)) : 0.01;
		auto targetAction=MoveBy::create(speed*visibleSize.width,Point(-visibleSize.width*3,0));
		target->runAction(targetAction);
		break;
	}
	case 3:
	{
		ccBezierConfig bezier;
		bezier.controlPoint_1=Point(0,300);
		bezier.controlPoint_2=Point(0,-300);
		bezier.endPosition=Point(-visibleSize.width*3,0);

		auto speed=(0.05-0.01*(static_cast<double>(Level::GetLevel())-1.0)>0) ? (0.05-0.01*(static_cast<double>(Level::GetLevel())-1.0)) : 0.01;
		auto targetAction=BezierBy::create(speed*visibleSize.width,bezier);
		target->runAction(targetAction);
		break;
	}
	default:
		break;
	}

	Target::count+=1;
}
