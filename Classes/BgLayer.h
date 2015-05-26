#ifndef __BG_LAYER_H__
#define __BG_LAYER_H__

#include "cocos2d.h"

class BgLayer : public cocos2d::Layer
{
public:
	enum tags
	{
		ProgressTag = 10,
		ProgressBgtag = 11,
		FinishTag = 20,
		GoingTag = 30,
		TimeTag = 50
	};
	BgLayer();
	~BgLayer();
	virtual bool init();
	void update(float delta); 
	void updateProgress(int);
	void resetProgress();
	CREATE_FUNC(BgLayer);

private:
	const int speed = 2;
	const float ProgressTimerScale = 0.3f;
	const int progressGZOrder = 100;
	cocos2d::Sprite* sprite1;
	cocos2d::Sprite* sprite2;
	cocos2d::ParticleSystemQuad *finishParticle;
};

#endif // __BG_LAYER_H__
