#pragma once
#include "gameNode.h"
#include "obstacle.h"

//��������������������������������������������������������������
//			��� ����
//	������Ʈ ����
	//#define OBJECTSPEED 5
	#define JELLYMAX 160
//��������������������������������������������������������������


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


	/// ��ֹ�2 ��ġ�� ����
	int randX;
	int obsX, obsY;

	bool	isStage1;
	bool	isStage2;

	//��ֹ��̶� �浹 üũ
	RECT boundingBox1;
	RECT boundingBox2;
	RECT boundingBox3;

	int	posX, posY;
	int rand;


	bool isDebug;

	//���� ��ǥ ���� (��������)
	int		index;
	bool	isBumped1;			
	bool	isBumped2;			
	bool	isBumped3;			
	

	//��������1 ��ֹ�
	tagRect* obstacle1_copy;
	tagRect* obstacle2_copy;
	tagRect* obstacle3_copy;

	//��������2 ��ֹ�
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

	//��ֹ� ȣ���
	tagJellyInfo* getJellyRC() { return _jellys; }
	obstacle* getObstacle() { return _obstacle; }

	int getRand() { return rand; }
};

