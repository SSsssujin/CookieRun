#pragma once
#include "gameNode.h"
#include "Lobby.h"
#include "result.h"
#include "stage1.h"
#include "stage2.h"
#include "jelly.h"
//#include "player.h"

class mainGame : public gameNode
{
private:
	int totalScore;

	Lobby*	_lobby;
	result* _result;
	stage1*	_stage1;
	stage2*	_stage2;

	bool lobby_active;
	bool stage1_active;
	bool stage2_active;
	bool result_active;
	
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// player* GetPlayer() { return _player; }
	// stage1* GetStage() { return _stage1; }
	// jelly* GetJelly() { return _jelly; }
};

