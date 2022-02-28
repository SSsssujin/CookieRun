#pragma once
#include "gameNode.h"

//┌─────────────────────────────┐
//			상수 정보
//	오브젝트 숫자
#define FLOOR 100
#define LOWER_OBS1 5
#define LOWER_OBS2 4
#define UPPER_OBS 5
//#define OBJECTSPEED 5
//└─────────────────────────────┘

struct tagRect
{
	RECT rc1;
	RECT rc2;
	image* img;
};

class obstacle : public gameNode
{
private:

	int fixY;

	//stage1.
	tagRect _obstacle1[LOWER_OBS1];
	tagRect _obstacle2[LOWER_OBS2];
	tagRect _obstacle3[UPPER_OBS];

	//stage2.
	//tagRect _flyingObs[2];
	//tagRect _obstacle4[2];			//밑-큰거

	bool isDebug;


public:
	obstacle();
	~obstacle();

	HRESULT init();
	HRESULT init(const int x, const int y);
	void release();
	void update();
	void render();

	tagRect* getObstacle1RC() { return _obstacle1; }
	tagRect* getObstacle2RC() { return _obstacle2; }
	tagRect* getObstacle3RC() { return _obstacle3; }

	//void setIsstage1(bool active) { isStage1 = active; }
	//void setIsstage2(bool active) { isStage2 = active; }
};
