#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"

//class for spawning new targets

class Target
{
public:
	void SpawnTarget(cocos2d::Layer *layer);

	Target();

	static int getcount(){
		return count;
	}

	static void setcount(int a){
		count=a;
	}

	static void reducecount(){
		count-=1;
	}

	static void morecount(){
		count+=1;
	}

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	static int count;
};

#endif // __TARGET_H__
