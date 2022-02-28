#include "framework.h"
#include "jelly.h"
#include "stage2.h"

jelly::jelly()
{
}

jelly::~jelly()
{
}

HRESULT jelly::init()
{
	rand = RND->getFromIntTo(1, 9);

	_obstacle = new obstacle;
	_obstacle->init();

	obstacle1_copy = _obstacle->getObstacle1RC();
	obstacle2_copy = _obstacle->getObstacle2RC();
	obstacle3_copy = _obstacle->getObstacle3RC();

	//�̹���
	IMAGE->addImage("����1", "images/jelly1.bmp", 25, 31, true, RGB(255, 0, 255));
	IMAGE->addImage("��������", "images/jelly_eat.bmp", 40, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("����", "images/coin1.bmp", 35, 35, true, RGB(255, 0, 255));

	posX = WINSIZEX - 150;
	posY = 370;

	//���� ����
	for (int i = 0; i < JELLYMAX; i++)
	{
		_jellys[i].jellyRC = RectMake(posX + (60 * i), posY, 25, 31);
		if (i % 10 == rand)
		{
			_jellys[i].score = 0;
			_jellys[i].coin = 2;	
			_jellys[i].jellyImg = IMAGE->findImage("����");
		}
		else
		{
			_jellys[i].score = 100;
			_jellys[i].coin = 0;
			_jellys[i].jellyImg = IMAGE->findImage("����1");
		}
		_jellys[i].isGain = false;
	}

	//[����] ���߿� x��ǥ ����
	boundingBox1 = RectMake(WINSIZEX / 2 - 320 + 1010, 385, 10, 50);																		//����ֹ�-�������
	boundingBox2 = RectMake(WINSIZEX / 2 - 320 + 1000, 340, 10, 50);																		//����ֹ�-ū���
	boundingBox3 = RectMake(WINSIZEX / 2 - 320 + 1000, 0, 150, 400);		//����ֹ���

	isDebug = false;
	isBumped1 = false;
	isBumped2 = false;
	isBumped3 = false;

	return S_OK;
}

void jelly::release()
{
	//SAFE_DELETE(_player);
	//SAFE_DELETE(_stage1);
	SAFE_DELETE(_obstacle);
	//SAFE_DELETE(_obstacle2);
}

void jelly::update()
{
	if (InputManager->isOnceKeyUp(VK_F3)) isDebug = !isDebug;

	if (isStage1)
	{

		for (int i = 0; i < JELLYMAX; i++)
		{
			OffsetRect(&_jellys[i].jellyRC, -OBJECTSPEED, 0);
			_jellys[i].jellyRC = RectMake(_jellys[i].jellyRC.left, _jellys[i].jellyRC.top, 25, 31);
		}

		RECT temp;
		//1.������ֹ� �浹
		for (int i = 0; i < LOWER_OBS1; i++)
		{
			//if (IntersectRect(&temp, &_stage1->getObstacle1RC()[i].rc1, &boundingBox1))
			if (IntersectRect(&temp, &obstacle1_copy[i].rc1, &boundingBox1))
			{
				isBumped1 = true;
			}
			if (isBumped1)
			{
				for (int j = 0; j < JELLYMAX; j++)
				{
					if (IntersectRect(&temp, &_jellys[j].jellyRC, &boundingBox1))
					{
						index = j;
						_jellys[index].jellyRC.top = posY - 55;
						_jellys[index].jellyRC.bottom = posY - 55;
					}
				}
				isBumped1 = false;
			}
		}
		//2.ū��ֹ� �浹
		for (int i = 0; i < LOWER_OBS2; i++)
		{
			//if (IntersectRect(&temp, &_stage1->getObstacle2RC()[i].rc2, &boundingBox2))
			if (IntersectRect(&temp, &obstacle2_copy[i].rc2, &boundingBox2))
			{
				isBumped2 = true;
			}
			if (isBumped2)
			{
				for (int j = 0; j < JELLYMAX; j++)
				{
					if (IntersectRect(&temp, &_jellys[j].jellyRC, &boundingBox2))
					{
						index = j;
						_jellys[index - 1].jellyRC.top = posY - 100;
						_jellys[index - 1].jellyRC.bottom = posY - 100;
						_jellys[index].jellyRC.top = posY - 150;
						_jellys[index].jellyRC.bottom = posY - 150;
						_jellys[index + 1].jellyRC.top = posY - 100;
						_jellys[index + 1].jellyRC.bottom = posY - 100;
					}
				}
				isBumped2 = false;
			}
		}
		//3. ����ֹ� �浹
		for (int i = 0; i < UPPER_OBS; i++)
		{
			//if (IntersectRect(&temp, &_stage1->getObstacle2RC()[i].rc2, &boundingBox2))
			if (IntersectRect(&temp, &obstacle3_copy[i].rc1, &boundingBox3))
			{
				isBumped3 = true;
			}
			if (isBumped3)
			{
				for (int j = 0; j < JELLYMAX; j++)
				{
					if (IntersectRect(&temp, &_jellys[j].jellyRC, &boundingBox3))
					{
						index = j;
						_jellys[index].jellyRC.top = posY + 30;
						_jellys[index].jellyRC.bottom = posY + 30;
					}
				}
				isBumped3 = false;
			}
		}
		_obstacle->update();
	}
	
	//stage2�϶� �ڵ�.
	//else if (isStage2)
	//{
	//	//ū��ֹ�_��
	//	/*�غ�*/ _obstacle2->getObstacle1()->width = _obstacle2->getObstacle1()->rc1.right - _obstacle2->getObstacle1()->rc1.left;
	//	/*����*/ _obstacle2->getObstacle1()->height = _obstacle2->getObstacle1()->rc1.bottom - _obstacle2->getObstacle1()->rc1.top;
	//
	//	if (_stage2->getFoothold()->landKind == LANDKIND::GROUND)
	//	{
	//		obsX = RND->getFromIntTo(_obstacle2->getObstacle1()->width / 2, _obstacle2->getObstacle1()->width);
	//		obsY = _obstacle2->getObstacle1()->height - 130;
	//	}
	//
	//	_obstacle2->update();
	//}
	
	//_player->update();
	//_stage1->update();
	//_obstacle->update();
}

void jelly::render()
{
	if (isStage1)
	{
		for (int i = 0; i < JELLYMAX; i++)
		{
			//if (isGain[i])
			if (!_jellys[i].isGain)
			{
				_jellys[i].jellyImg->render(getMemDC(), _jellys[i].jellyRC.left, _jellys[i].jellyRC.top);
			}
			//else if (isGain[i])
			else if (_jellys[i].isGain)
			{
				_jellys[i].jellyImg->alphaRender(getMemDC(), _jellys[i].jellyRC.left - 10, _jellys[i].jellyRC.top, 70);
			}
		}


		if (isDebug)
		{
			Rectangle(getMemDC(), boundingBox3.left, boundingBox3.top, boundingBox3.right, boundingBox3.bottom);
			Rectangle(getMemDC(), boundingBox1.left, boundingBox1.top, boundingBox1.right, boundingBox1.bottom);
			Rectangle(getMemDC(), boundingBox2.left, boundingBox2.top, boundingBox2.right, boundingBox2.bottom);

			for (int i = 0; i < JELLYMAX; i++)
			{
				Rectangle(getMemDC(), _jellys[i].jellyRC.left, _jellys[i].jellyRC.top, _jellys[i].jellyRC.right, _jellys[i].jellyRC.bottom);
			}
			for (int i = 0; i < LOWER_OBS1; i++)
			{
				Rectangle(getMemDC(), obstacle1_copy[i].rc1.left, obstacle1_copy[i].rc1.top, obstacle1_copy[i].rc1.right, obstacle1_copy[i].rc1.bottom);
				//Rectangle(getMemDC(), _stage1->getObstacle1RC()[i].rc1.left, _stage1->getObstacle1RC()[i].rc1.top, _stage1->getObstacle1RC()[i].rc1.right, _stage1->getObstacle1RC()[i].rc1.bottom);
			}
			for (int i = 0; i < LOWER_OBS2; i++)
			{
				Rectangle(getMemDC(), obstacle2_copy[i].rc2.left, obstacle2_copy[i].rc2.top, obstacle2_copy[i].rc2.right, obstacle2_copy[i].rc2.bottom);
				//Rectangle(getMemDC(), _stage1->getObstacle2RC()[i].rc2.left, _stage1->getObstacle2RC()[i].rc2.top, _stage1->getObstacle2RC()[i].rc2.right, _stage1->getObstacle2RC()[i].rc2.bottom);
			}
			for (int i = 0; i < UPPER_OBS; i++)
			{
				Rectangle(getMemDC(), obstacle3_copy[i].rc1.left, obstacle3_copy[i].rc1.top, obstacle3_copy[i].rc1.right, obstacle3_copy[i].rc1.bottom);
				//Rectangle(getMemDC(), _stage1->getObstacle2RC()[i].rc2.left, _stage1->getObstacle2RC()[i].rc2.top, _stage1->getObstacle2RC()[i].rc2.right, _stage1->getObstacle2RC()[i].rc2.bottom);
			}
		}
		_obstacle->render();
	}


	//if (isStage2)
	//{
	//	_obstacle2->render();
	//}




	//char strBlock[128];
	//SetTextColor(getMemDC(), RGB(255, 255, 255));
	//
	//sprintf_s(strBlock, "isStage1 : %d", isStage1);
	//TextOut(getMemDC(), 0, 0, strBlock, strlen(strBlock));
	//
	//sprintf_s(strBlock, "isStage2 : %d", isStage2);
	//TextOut(getMemDC(), 0, 20, strBlock, strlen(strBlock));
}

