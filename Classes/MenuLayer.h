#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer
{
public:
	MenuLayer();
	~MenuLayer();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(MenuLayer);

private:

};

#endif // __MENU_LAYER_H__
