#pragma once
#include "gameNode.h"
#include "obstacle.h"

//┌─────────────────────────────┐
//			상수 정보
//	오브젝트 숫자
	//#define OBJECTSPEED 5
	#define JELLYMAX 160
//└─────────────────────────────┘


struct tagJellyInfo
{
	int coin;	
	int score;
	RECT jellyRC;
	image* jellyImg;
	bool isGain;
};

//class stage2;
class jelly : public gameNode
{

private:

	//mainGame _mainGame1;
	//player* _player;
	//stage2* _stage2;

	tagJellyInfo	_jellys[JELLYMAX];
	obstacle*		_obstacle;


	/// 장애물2 배치용 난수
	int randX;
	int obsX, obsY;

	bool	isStage1;
	bool	isStage2;

	//장애물이랑 충돌 체크
	RECT boundingBox1;
	RECT boundingBox2;
	RECT boundingBox3;

	int	posX, posY;
	int rand;


	bool isDebug;

	//젤리 좌표 변경 (유사점프)
	int		index;
	bool	isBumped1;			
	bool	isBumped2;			
	bool	isBumped3;			
	

	//스테이지1 장애물
	tagRect* obstacle1_copy;
	tagRect* obstacle2_copy;
	tagRect* obstacle3_copy;

	//스테이지2 장애물
	//tagObsInfo* obstacle1_copy2;
	//tagObsInfo* obstacle2_copy2;
	//tagObsInfo* obstacle3_copy2;

public:

	jelly();
	~jelly();

	//HRESULT init(mainGame mg);
	HRESULT init();
	void release();
	void update();
	void render();
	
	void setIsStage1(bool active) { isStage1 = active; }
	void setIsStage2(bool active) { isStage2 = active; }

	//장애물 호출용
	tagJellyInfo* getJellyRC() { return _jellys; }
	obstacle* getObstacle() { return _obstacle; }

	int getRand() { return rand; }
};

