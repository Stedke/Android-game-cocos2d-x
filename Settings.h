#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"

//Class is a place to change all settings: music, audio

class Settings : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Settings);

private:
    void SwitchMusic(Ref *Sender);	//functions for buttons' callbacks
    void SwitchAudio(Ref *Sender);
    void Back(Ref* Sender);
};

#endif // __SETTINGS_H__
