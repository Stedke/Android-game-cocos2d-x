#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "cocos2d.h"

//Class implementing a game pause screen with a menu: music, audio

class Pause : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::LayerColor* createLayer();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Pause);

private:
    //menu buttons' callbacks
    void Exit(Ref *Sender);
    void Resume(Ref *Sender);
    void SwitchAudio(Ref *Sender);
    void SwitchMusic(Ref *Sender);

    //touch swallowing event
    bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event);
};

#endif // __PAUSE_H__
