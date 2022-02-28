#pragma once
#include "gameNode.h"
#include "player.h"

class animationTest :public gameNode
{
private:
	player* _brave;

public:
	animationTest();
	~animationTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

