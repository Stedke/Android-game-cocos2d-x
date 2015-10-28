#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

//Class acts as a game's main menu with buttons: Play, Settings, Exit

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

private:
    void GoToPlay(Ref *Sender);	//functions for menu buttons' callbacks
    void GoToSettings(Ref *Sender);
    void GoToClose(Ref *Sender);
};

#endif // __MAINMENU_H__
