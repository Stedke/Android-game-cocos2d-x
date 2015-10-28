#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"

//Class that displays a notification when game starts and later,
//when a new difficulty level is reached

class Level : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::LayerColor* createLayer();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level);

    //methods to get and set actual difficulty level
    static void SetLevel(int level)
    {
    	Level::ALevel=level;
    }

    static int GetLevel()
    {
    	return Level::ALevel;
    }

private:
    //actual difficulty level
    static int ALevel;

    //menu button's callback to exit the notification
    void Ok(Ref* Sender);

    //touch swallowing event
    bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event);
};

#endif // __LEVEL_H__
