#ifndef __PLAY_H__
#define __PLAY_H__

#include "cocos2d.h"
#include "Target.h"
#include "Bullet.h"

//Class  that controls play screen functions - all 'play' actions, sprites, etc.
//Can be 'paused' by a proper button.
//Several Level layers will appear during playthrough, acting as game speed and difficulty boosters' announcements.

class Play : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Play);

    //methods to get & set Play points field
    int getpoints()
    {
    	return points;
    }

    void setpoints(int a)
    {
    	points=a;
    }

private:
    //pause button callback function
    void Pause();

    //level layer interruption (more speed and enemies)
    void Level(float dt);

    //handling screen touch
    bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch,cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *event);

    //functions for handling custom events - these ensure that game will continue after a pause, or a level layer
    virtual void ContinueL(cocos2d::EventCustom *event);
    virtual void ContinueP(cocos2d::EventCustom *event);

    //score counter
    int points;

    //built-in menu
    cocos2d::Menu *menu;

    //built in label (score display)
    cocos2d::Label *label;

    //built in physics world
    cocos2d::PhysicsWorld *World;

    //built in target & bullet (new targets,bullets spawn)
    Target target;
    Bullet bullet;

    //method to set physics world
    void SetPhysicsWorld (cocos2d::PhysicsWorld *world){World=world;}

    //method that will spawn new targets
    void SpawnTargetP(float dt);

    //method that will help to stop all actions on the layer, when pause or level are enabled
    void Stop();

    //physics contact handling method
    bool onContactBegin( cocos2d::PhysicsContact &contact );

    //method that will pop-up the game over scene
    void GameOver();
};

#endif // __PLAY_H__

//unused code
//virtual void onEnterTransitionDidFinish();
