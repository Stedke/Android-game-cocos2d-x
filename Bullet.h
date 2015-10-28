#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

//bullet class implementing bullet objects

class Bullet
{
public:
	void SpawnBullet(cocos2d::Layer *layer,cocos2d::Vec2 &aim);

	Bullet();

	static int getbulletcount(){
		return bcount;
	}

	static void setbulletcount(int a){
		bcount=a;
	}

	static void reducebulletcount(){
		bcount-=1;
	}

	static void morebulletcount(){
		bcount+=1;
	}

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	static int bcount;
};

#endif // __BULLET_H__
