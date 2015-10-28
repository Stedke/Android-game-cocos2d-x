#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"

//Game Over screen with ok button and score

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int points);
	virtual bool init();
	CREATE_FUNC(GameOver);
private:
	//ok button action and score
	void Ok();
	static int points;
};

#endif // __GAMEOVER_H__
