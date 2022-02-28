#pragma once
#include "gameNode.h"
#include "player.h"

class result : public gameNode
{
private:
	player* _player;

	RECT okButton;
	
	int score;
	int coin;

	bool lobby_active;


public:
	
	result();
	~result();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getLobby_active() { return lobby_active; }
	void setLobby_active(bool active) { lobby_active = active; }

	void setScore(int score) { this->score = score; }
	void setCoin(int coin) { this->coin = coin; }
	
};

