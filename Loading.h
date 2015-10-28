#ifndef __LOADING_H__
#define __LOADING_H__

#include "cocos2d.h"

//Class performing basic 'loading' tasks.

class Loading : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Loading);

private:
    void GoToMainMenu( float dt );	//after some time go to Main Menu
};

#endif // __LOADING_H__
