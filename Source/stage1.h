#pragma once
#include "gameNode.h"
#include "player.h"

//��������������������������������������������������������������
//			��� ����
//	������Ʈ ����
	#define FLOOR 100
	#define LOWER_OBS1 5
	#define LOWER_OBS2 4
	#define UPPER_OBS 5
	//#define OBJECTSPEED 5
//��������������������������������������������������������������

//============================
// Ʃ�丮��
//============================

class stage1 : public gameNode
{
private:
	player*	_player;

	tagRect	_floor[FLOOR];
	RECT	endingBox;
	RECT	townButton;

	int		activeTime;
	int		m_loopX;			//������ ����
	bool	isDebug;

	bool result_active;
	bool stage1_active;			//////////////////


public:
	
	stage1();
	~stage1();

	//HRESULT init(mainGame mg);
	HRESULT init();
	void release();
	void update();
	void render();

	player* getPlayer() { return _player; }
	RECT getEndingBox() const { return endingBox; }

	bool getResult_active() { return result_active; }
	void setResult_active(bool active) { result_active = active; }

	bool getStage1_active() { return stage1_active; }
	void setStage1_active(bool active) { stage1_active = active; }

	int getScore() { return _player->getScore(); }
	int getCoin() { return _player->getCoin(); }
};	

