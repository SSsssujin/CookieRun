#pragma once
#include "gameNode.h"
#include "player.h"
//#include "stage1.h"

//┌─────────────────────────────┐
//			상수 정보
//	오브젝트 숫자
	#define TEMP 30
	//#define OBJECTSPEED 5
//└─────────────────────────────┘


enum class LANDKIND
{
	GROUND = 1,
	FOOTHOLD,
	//UPSTAIR,
	//DOWNSTAIR
};

struct tagLandInfo
{
	image*		landImg;
	LANDKIND	landKind;
	RECT		landRC;
};

struct tagJellyInfo2
{
	int coin;
	int score;
	RECT jellyRC;
	image* jellyImg;
	bool isGain;
};

struct tagObsInfo
{
	RECT rc1;
	image* img;
};

class stage2 : public gameNode
{
private:

	player* _player;
	RECT	posionRC;

	tagObsInfo _obstacle1[2];
	tagObsInfo _obstacle1_1[2];
	tagObsInfo _obstacle2;

	tagJellyInfo _jelly2[JELLYMAX];
	tagJellyInfo _jelly2_1[JELLYMAX];

	int posX, posY;
	int colIndex;
	int colIndex2;

	int posionX, posionY;
	image* posion;
	RECT townButton;

	//삼각함수실험
	//============================
	//float m_iXDist, m_iYDist;
	//float m_fDegree;
	//============================


	//난수 설정
	int rand_Ground;
	int rand_foothold;
	int randHeight[TEMP];
	int randCreate;

	int m_count0, m_count1;
	int m_index0, m_index1;

	tagLandInfo _ground[TEMP];
	tagLandInfo _foothold[TEMP];
	tagLandInfo _foothold2[TEMP];	
	
	int m_loopX;
	int activeTime;

	bool isDebug;
	bool result_active;
	bool isUp;
	bool isGetPos;

	//================================
	//소리실험
	bool isSound;
	int activeCol;
	//================================

public:

	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();

	void collision();
	void getJelly();
	void damage();
	void createObs(int x);
	void createObs2(int x);

	bool getResult_active() { return result_active; }

	//tagLandInfo* getFoothold() { return _foothold; }
	//tagLandInfo* getFoothold2() { return _foothold2; }

	int getScore() { return _player->getScore(); }
	int getCoin() { return _player->getCoin(); }
};

