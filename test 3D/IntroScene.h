#pragma once
#include "MainClass.h"
//#include "JButtonCtrl.h"
//#include "JCheckCtrl.h"
//#include "JImageCtrl.h"
//#include "JParticleSystem.h"
//#include "JSliderCtrl.h"
//#include "JSpriteCtrl.h"
class IntroScene : public MainClass
{
public:
	void LoadSound() noexcept;
public:
	virtual bool Init()		noexcept override;
	virtual bool Frame()	noexcept override;
	virtual bool Render()	noexcept override;
	virtual bool Release()	noexcept override;

	IntroScene() = default;
	virtual ~IntroScene() = default;
};