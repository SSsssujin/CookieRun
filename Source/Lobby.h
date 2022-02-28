#pragma once
#include "gameNode.h"
//#include "player.h"
//#include "stage1.h"

class Lobby : public gameNode
{
private:

	image* _brave;
	int m_count;
	int m_index;

	RECT tutorialButton;
	RECT playButton;

	bool stage1_active;
	bool stage2_active;
	bool lobby_active;


	//RECT temp;

public:

	Lobby();
	~Lobby();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getStage1_active() { return stage1_active; }
	bool getStage2_active() { return stage2_active; }
	void setStage1_active(bool active) { stage1_active = active; }
	void setStage2_active(bool active) { stage2_active = active; }

	bool getLobby_active() { return lobby_active; }					 ///////////////////
	void setLobby_active(bool active) { lobby_active = active; }	 ///////////////////
};

