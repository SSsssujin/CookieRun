#include "framework.h"
#include "stage2.h"
#include "math.h"

stage2::stage2()
{
}

stage2::~stage2()
{
	
}

HRESULT stage2::init()
{
	_player = new player;
	_player->init();

	_player->setPlayerY(100);
	_player->setIsStage2(true);

	//���&����
	IMAGE->addImage("���_����", "images/background_witch.bmp", WINSIZEX, WINSIZEY - 30, false, RGB(0, 0, 0));
	IMAGE->addImage("�ٴ�_����", "images/ground_witch.bmp", 145, 150, true, RGB(255, 0, 255));
	IMAGE->addImage("����_����", "images/foothold_witch.bmp", 150, 30, true, RGB(255, 0, 255));
	//��ֹ�
	IMAGE->addFrameImage("2��ֹ�_�Ʒ�1", "images/obstacle3_witch.bmp", 420, 150, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("2��ֹ�_�Ʒ�2", "images/obstacle2_witch.bmp", 420, 150, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("2��ֹ�_���", "images/obstacle1_witch.bmp", 606, 117, 3, 1, true, RGB(255, 0, 255));
	//����
	//IMAGE->addImage("����", "images/hp_posion.bmp", 58, 72, true, RGB(255, 0, 255));
	posion = IMAGE->addImage("����", "images/hp_posion.bmp", 45, 55, true, RGB(255, 0, 255));
	IMAGE->addImage("ȸ��", "images/recover.bmp", 78, 27, true, RGB(255, 0, 255));

	
	posionX = 1000;
	posionY = 200;

	//����
	posionRC = RectMake(posionX, posionY, 45, 55);
	isUp = true;



	//��ֹ�1-1.
	for (int i = 0; i < 2; i++)
	{
		_obstacle1[i].img = IMAGE->findImage("2��ֹ�_�Ʒ�2");
		_obstacle1[i].rc1 = RectMake(_player->getPlayerX() + 1000 + (i * 500), 435 - 130, 70, 130);
	}
	//��ֹ�1-2.
	for (int i = 0; i < 2; i++)
	{
		_obstacle1_1[i].img = IMAGE->findImage("2��ֹ�_�Ʒ�1");
		_obstacle1_1[i].rc1 = RectMake(_player->getPlayerX() - 1000 + (i * 500), 435 - 130, 70, 130);
	}

	//��ֹ�2.
	_obstacle2.img = IMAGE->findImage("2��ֹ�_���");
	_obstacle2.rc1 = RectMake(WINSIZEX + 1000, 300, 110, 70);
	 
	//���� ����
	//���� ������ ����
	rand_Ground = RND->getFromIntTo(20, 30);
	rand_foothold = RND->getFromIntTo(10, 10);
	randCreate = RND->getFromIntTo(1, 2);
	//���� ����
	for (int i = 0; i < rand_foothold; i++)
	{
		randHeight[i] = RND->getFromIntTo(-10, 90);
	}
	
	//����2
	posX = WINSIZEX - 150;
	posY = 370;
	

	//��������
	for (int i = 0; i < JELLYMAX; i++)
	{
		_jelly2[i].jellyRC = RectMake(posX + (60 * i), posY, 25, 31);
		//int randNum = RND->getFromIntTo(1, 9);		//Ȯ�������� ����
		//if (i % 10 == rand)
		if (i % 10 == 9)					
		{
			_jelly2[i].score = 0;
			_jelly2[i].coin = 2;		
			_jelly2[i].jellyImg = IMAGE->findImage("����");
		}
		else
		{
			_jelly2[i].score = 100;
			_jelly2[i].coin = 0;
			_jelly2[i].jellyImg = IMAGE->findImage("����1");
		}
		_jelly2[i].isGain = false;
	}
	for (int i = 0; i < JELLYMAX; i++)
	{
		_jelly2_1[i].jellyRC = RectMake(_jelly2[JELLYMAX - 1].jellyRC.right + (60 * i), posY, 25, 31);
		//int randNum = RND->getFromIntTo(1, 9);		//Ȯ�������� ����
		//if (i % 10 == rand)
		if (i % 10 == 9)
		{
			_jelly2_1[i].score = 0;
			_jelly2_1[i].coin = 2;		
			_jelly2_1[i].jellyImg = IMAGE->findImage("����");
		}
		else
		{
			_jelly2_1[i].score = 100;
			_jelly2_1[i].coin = 0;
			_jelly2_1[i].jellyImg = IMAGE->findImage("����1");
		}
		_jelly2_1[i].isGain = false;
	}

	
	//���� ����ǥ ����
	for (int i = 0; i < rand_Ground; i++)
	{
		_ground[i].landRC = RectMake(100 + (i * 146), 434, 145, 150);
		_ground[i].landImg = IMAGE->findImage("�ٴ�_����");
		_ground[i].landKind = LANDKIND::GROUND;
	}

	//���� ���� ����
	switch (randCreate)
	{
	case 1:			//����1.
		for (int i = 0; i < rand_foothold; i++)
		{
			_foothold[i].landRC = RectMake(_ground[rand_Ground - 1].landRC.right + 150 + (i * 270), _ground[rand_Ground - 1].landRC.top - 70, 80, 30);
			_foothold[i].landImg = IMAGE->findImage("����_����");
			_foothold[i].landKind = LANDKIND::FOOTHOLD;
		}
		break;
	case 2:
		for (int i = 0; i < rand_foothold; i++)
		{
			_foothold[i].landRC = RectMake(_ground[rand_Ground - 1].landRC.right + 150 + (i * 270), _ground[rand_Ground - 1].landRC.top - randHeight[i], 80, 30);
			_foothold[i].landImg = IMAGE->findImage("����_����");
			_foothold[i].landKind = LANDKIND::FOOTHOLD;
		}
		break;
	//case 3:
	//	for (int i = 0; i < 3; i++)
	//	{
	//		_foothold[i].landRC = RectMake(_ground[rand_Ground - 1].landRC.right + 200 + (i * 270), _ground[rand_Ground - 1].landRC.top - (i * 30), 80, 30);
	//		_foothold[i].landImg = IMAGE->findImage("����_����");
	//		_foothold[i].landKind = LANDKIND::FOOTHOLD;
	//	}
	//	break;
	}

	switch (randCreate)
	{
	case 1:
		for (int i = 0; i < rand_foothold; i++)
		{
			//_foothold2[i].landRC = RectMake(_ground[rand_Ground - 1].landRC.right + 100 + (i * 270), _ground[rand_Ground - 1].landRC.top - 70, 150, 30);
			//_foothold2[i].landRC = RectMake(_foothold[rand_foothold - 1].landRC.right + 100 + (i * 270), _foothold[rand_foothold - 1].landRC.top - 70, 150, 30);
			_foothold2[i].landRC = RectMake(_foothold[rand_foothold - 1].landRC.right + 150 + (i * 270), _ground[rand_Ground - 1].landRC.top - 70, 80, 30);
			_foothold2[i].landImg = IMAGE->findImage("����_����");
			_foothold2[i].landKind = LANDKIND::FOOTHOLD;
		}
		break;
	case 2:
		for (int i = 0; i < rand_foothold; i++)
		{
			//_foothold2[i].landRC = RectMake(_foothold[rand_foothold - 1].landRC.right + 100 + (i * 270), _ground[rand_Ground - 1].landRC.top + randHeight[i], 150, 30);
			_foothold2[i].landRC = RectMake(_foothold[rand_foothold - 1].landRC.right + 150 + (i * 270), _ground[rand_Ground - 1].landRC.top - randHeight[i], 80, 30);
			_foothold2[i].landImg = IMAGE->findImage("����_����");
			_foothold2[i].landKind = LANDKIND::FOOTHOLD;
		}
		break;
	//case 3:
		//	for (int i = 0; i < rand_foothold; i++)
		//	{
		//		//_foothold2[i].landRC = RectMake(_foothold[rand_foothold - 1].landRC.right + 150 + (i * 270), _ground[rand_Ground - 1].landRC.top - (i * 30), 150, 30);
		//		_foothold2[i].landRC = RectMake(_foothold[rand_foothold - 1].landRC.right + 200 + (i * 270), _ground[rand_Ground - 1].landRC.top - (i * 30), 80, 30);
		//		_foothold2[i].landImg = IMAGE->findImage("����_����");
		//		_foothold2[i].landKind = LANDKIND::FOOTHOLD;
		//	}
		//	break;
	}

	//boundingBox1 = RectMake(500, 434 - 70, 100, 30);
	//for (int i = 0; i < 6; i++)
	//{
	//	//boundingBox2[i] = RectMake(500, 434 - 140, 100, 30);
	//	boundingBox2[i] = RectMake(500, 320 - (i * 30), 100, 10);
	//}

	//���� ���� �ʱ�ȭ
	isGetPos = false;
	isDebug = false;
	result_active = false;
	m_loopX = 0;
	
	m_count0 = 0;
	m_count1 = 0;
	m_index0 = 0;
	m_index1 = 0;


	activeCol;
	isSound = false;
	townButton = RectMake(WINSIZEX - 180, WINSIZEY - 120, 100, 50);

	return S_OK;
}

void stage2::release()
{
	SAFE_DELETE(_player);
}

void stage2::update()
{
	if (InputManager->isOnceKeyUp(VK_F4)) isDebug = !isDebug;

	m_loopX++;

	//������Ʈ ������

	//����
	for (int i = 0; i < rand_Ground; i++)
	{
		OffsetRect(&_ground[i].landRC, -OBJECTSPEED, 0);
	}
	for (int i = 0; i < rand_foothold; i++)
	{
		OffsetRect(&_foothold[i].landRC, -OBJECTSPEED, 0);
		OffsetRect(&_foothold2[i].landRC, -OBJECTSPEED, 0);
	}
	//��ֹ�
	for (int i = 0; i < 2; i++)
	{
		OffsetRect(&_obstacle1[i].rc1, -OBJECTSPEED, 0);
		OffsetRect(&_obstacle1_1[i].rc1, -OBJECTSPEED, 0);
	}
	//��ֹ�(�����¾�)
	OffsetRect(&_obstacle2.rc1, -(OBJECTSPEED * 1.7), 0);
	//����
	for (int i = 0; i < JELLYMAX; i++)
	{
		OffsetRect(&_jelly2[i].jellyRC, -OBJECTSPEED, 0);
		OffsetRect(&_jelly2_1[i].jellyRC, -OBJECTSPEED, 0);

		_jelly2[i].jellyRC = RectMake(_jelly2[i].jellyRC.left, _jelly2[i].jellyRC.top, 25, 31);
		_jelly2_1[i].jellyRC = RectMake(_jelly2_1[i].jellyRC.left, _jelly2_1[i].jellyRC.top, 25, 31);
	}



	//���� ������ ����
	if (isUp)
	{
		if (posionRC.top >= 150)
		{
			//OffsetRect(&posionRC, -OBJECTSPEED / 2, -1);
			//posionX -= OBJECTSPEED * cosf(PI / 3);
			//posionX -= OBJECTSPEED * m_iXDist;
			posionX -= OBJECTSPEED / 2; 
			posionY -= 1;
		}
		else
		{
			//OffsetRect(&posionRC, -OBJECTSPEED * 1.3, +1);
			isUp = false;
		}
	}
	else if (!isUp)
	{
		if (posionRC.bottom < 500)
		{
			//OffsetRect(&posionRC, -OBJECTSPEED / 2, +1);
			posionX -= OBJECTSPEED / 2;
			posionY += 1;
		}
		else if (posionRC.bottom >= 500)
		{
			isUp = true;
		}
	}

	//���� ȹ���
	RECT stop;
	if (IntersectRect(&stop, &_player->getPlayerRC(), &posionRC))
	{
		if (!isGetPos)
		{
			SOUND->play("����");
		}
		_player->setHP(_player->getHP() + 10);
		isGetPos = true;
		if (_player->getHP() >= 10000) _player->setHP(9999);
		posion = IMAGE->findImage("ȸ��");
	}
	if (isGetPos)
	{
		activeTime++;
		posionX = _player->getPlayerRC().left;
		posionY = _player->getPlayerRC().top - 25;
	}
	if (activeTime >= 100)
	{
		//SOUND->stop("����");
		posionX = WINSIZEX + 1000;
		posion = IMAGE->findImage("����");
		activeTime = 0;
		isGetPos = false;
	}
	posionRC = RectMake(posionX, posionY, 45, 55);		//���Ƿ�Ʈ ������Ʈ



	//������¾� ��ġ����
	if (_obstacle2.rc1.right < -100)
	{
		int randY = RND->getFromIntTo(50, 450);
		_obstacle2.rc1 = RectMake(WINSIZEX + 1000, randY, 110, 70);
	}
	//������¾� ����������
	if (_obstacle2.rc1.left > 0 && _obstacle2.rc1.right < WINSIZEX)
	{
		m_count0++;
		_obstacle2.img->setFrameY(0);
		if (m_count0 % 5 == 0)
		{
			m_count0 = 0;
			m_index0++;
			if (m_index0 >= 3)
			{
				m_index0 = 0;
			}
			_obstacle2.img->setFrameX(m_index0);
		}
	}

	//��ֹ� ������ ����
	if (_obstacle1[0].rc1.left - 200 <= _player->getPlayerRC().right + 100)
	{
		m_count0++;
		_obstacle1[0].img->setFrameY(0);

		if (m_count0 % 10 == 0)
		{
			m_count0 = 0;
			m_index0++;
			if (m_index0 >= 4)
			{
				m_index0 = 4;
			}
			_obstacle1[0].img->setFrameX(m_index0);

		}
	}
	//if (_obstacle1[0].rc1.left < 0)
	//{
	//	m_index0 = 0;
	//}

	//if (_obstacle1[1].rc1.left - 200 <= _player->getPlayerRC().right + 100)
	//{
	//	m_count1++;
	//	_obstacle1[1].img->setFrameY(0);
	//
	//	if (m_count1 % 10 == 0)
	//	{
	//		m_count1 = 0;
	//		m_index1++;
	//		if (m_index1 >= 4)
	//		{
	//			m_index1 = 4;
	//		}
	//		_obstacle1[1].img->setFrameX(m_index1);
	//	}
	//}
	//if (_obstacle1[1].rc1.left < 0)
	//{
	//	m_index1 = 0;
	//}





	//����1.
	if (_jelly2[JELLYMAX - 1].jellyRC.right < -100)
	{
		RECT rect1 = RectMake(_jelly2_1[JELLYMAX - 1].jellyRC.right - 150, 434, 145, 150);

		for (int i = 0; i < JELLYMAX; i++)
		{
			_jelly2[i].jellyRC = RectMake(rect1.right + 50 + (60 * i), _jelly2[i].jellyRC.top, 25, 31);
			//int randNum = RND->getFromIntTo(1, 9);		//Ȯ�������� ����
			//if (i % 10 == rand)
			if (i % 10 == 9)
			{
				_jelly2[i].score = 0;
				_jelly2[i].coin = 2;
				_jelly2[i].jellyImg = IMAGE->findImage("����");
			}
			else
			{
				_jelly2[i].score = 100;
				_jelly2[i].coin = 0;
				_jelly2[i].jellyImg = IMAGE->findImage("����1");
			}
			_jelly2[i].isGain = false;
		}
	}
	//����2.
	if (_jelly2_1[JELLYMAX - 1].jellyRC.right < -100)
	{
		RECT rect1 = RectMake(_jelly2[JELLYMAX - 1].jellyRC.right - 150, 434, 145, 150);

		for (int i = 0; i < JELLYMAX; i++)
		{
			_jelly2_1[i].jellyRC = RectMake(rect1.right + 50 + (60 * i), _jelly2[i].jellyRC.top, 25, 31);
			//int randNum = RND->getFromIntTo(1, 9);		//Ȯ�������� ����
			//if (i % 10 == rand)
			if (i % 10 == 9)
			{
				_jelly2_1[i].score = 0;
				_jelly2_1[i].coin = 2;
				_jelly2_1[i].jellyImg = IMAGE->findImage("����");
			}
			else
			{
				_jelly2_1[i].score = 100;
				_jelly2_1[i].coin = 0;
				_jelly2_1[i].jellyImg = IMAGE->findImage("����1");
			}
			_jelly2_1[i].isGain = false;
		}
	}

	



	//������ ������ ������ �� 1.
	if (_foothold2[rand_foothold - 1].landRC.right < -100)
	{
		randCreate = RND->getFromIntTo(4, 5);

		RECT rect1 = RectMake(_foothold[rand_foothold - 1].landRC.right - 150, 434, 145, 150);

		if (randCreate == 1)			//����1.
		{
			for (int i = 0; i < rand_foothold; i++)
			{
				//_foothold2[i].landRC = RectMake(rect1.right + 100 + (i * 270), rect1.top - 70, 150, 30);
				_foothold2[i].landRC = RectMake(rect1.right + 150 + (i * 270), rect1.top - 70, 80, 30);
				_foothold2[i].landImg = IMAGE->findImage("����_����");
				_foothold2[i].landKind = LANDKIND::FOOTHOLD;
			}
		}
		else if (randCreate == 2)		//����2.
		{
			for (int i = 0; i < rand_foothold; i++)
			{
				//_foothold2[i].landRC = RectMake(rect1.right + 100 + (i * 270), rect1.top + randHeight[i], 150, 30);
				_foothold2[i].landRC = RectMake(rect1.right + 150 + (i * 270), rect1.top - randHeight[i], 80, 30);
				_foothold2[i].landImg = IMAGE->findImage("����_����");
				_foothold2[i].landKind = LANDKIND::FOOTHOLD;
			}
		}
		//else if (randCreate == 3)		//����3.
		//{
		//	for (int i = 0; i < rand_foothold; i++)
		//	{
		//		//_foothold2[i].landRC = RectMake(rect1.right + 150 + (i * 270), rect1.top - (i * 30), 150, 30);
		//		_foothold2[i].landRC = RectMake(rect1.right + 200 + (i * 270), rect1.top - (i * 30), 80, 30);
		//		_foothold2[i].landImg = IMAGE->findImage("����_����");
		//		_foothold2[i].landKind = LANDKIND::FOOTHOLD;
		//	}
		//}
		else
		{
			for (int i = 0; i < rand_foothold; i++)
			{
				_foothold2[i].landRC = RectMake(rect1.right + 150 + (i * 146), 434, 145, 30);
				_foothold2[i].landImg = IMAGE->findImage("�ٴ�_����");
				_foothold2[i].landKind = LANDKIND::GROUND;

				createObs(rect1.right + 150);	//��ֹ�����
			}
		}
	}

	//������ ������ ������ �� 2.
	if (_foothold[rand_foothold - 1].landRC.right < - 100)
	{
		randCreate = RND->getFromIntTo(1, 5);

		RECT rect2 = RectMake(_foothold2[rand_foothold - 1].landRC.right - 150, 434, 145, 150);

		if (randCreate == 1)
		{
			for (int i = 0; i < rand_foothold; i++)
			{
				//_foothold[i].landRC = RectMake(rect2.right + 100 + (i * 270), rect2.top - 70, 150, 30);
				_foothold[i].landRC = RectMake(rect2.right + 150 + (i * 270), rect2.top - 70, 80, 30);
				_foothold[i].landImg = IMAGE->findImage("����_����");
				_foothold[i].landKind = LANDKIND::FOOTHOLD;
			}
		}
		else if (randCreate == 2)
		{
			for (int i = 0; i < rand_foothold; i++)
			{
				//_foothold[i].landRC = RectMake(rect2.right + 100 + (i * 270), rect2.top + randHeight[i], 150, 30);
				_foothold[i].landRC = RectMake(rect2.right + 150 + (i * 270), rect2.top - randHeight[i], 80, 30);
				_foothold[i].landImg = IMAGE->findImage("����_����");
				_foothold[i].landKind = LANDKIND::FOOTHOLD;
			}
		}
		//else if (randCreate == 3)
		//{
		//	for (int i = 0; i < rand_foothold; i++)
		//	{
		//		_foothold[i].landRC = RectMake(rect2.right + 200 + (i * 270), rect2.top - (i * 30), 80, 30);
		//		_foothold[i].landImg = IMAGE->findImage("����_����");
		//		_foothold[i].landKind = LANDKIND::FOOTHOLD;
		//	}
		//}
		else
		{
			for (int i = 0; i < rand_foothold; i++)
			{

				_foothold[i].landRC = RectMake(rect2.right + 150 + (i * 146), 434, 145, 30);
				_foothold[i].landImg = IMAGE->findImage("�ٴ�_����");
				_foothold[i].landKind = LANDKIND::GROUND;
				
				createObs2(rect2.right + 150);
			}
		}
	}


	RECT temp;

	//===================================
	//				������ġ
	//===================================

	for (int i = 0; i < rand_foothold; i++)
	{
		for (int j = 0; j < JELLYMAX; j++)
		{
			if (IntersectRect(&temp, &_foothold2[i].landRC, &_jelly2[j].jellyRC))
			//if (_jelly2[j].jellyRC.bottom >= _foothold2[i].landRC.top)
			{
				colIndex = j;
				colIndex2 = i;
	
				_jelly2[colIndex - 2].jellyRC.top = _foothold2[colIndex2].landRC.top - 100;
				_jelly2[colIndex - 2].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 100;
				_jelly2[colIndex].jellyRC.top = _foothold2[colIndex2].landRC.top - 55;
				_jelly2[colIndex].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 55;
				_jelly2[colIndex - 1].jellyRC.top = _foothold2[colIndex2].landRC.top - 55;
				_jelly2[colIndex - 1].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 55;
				_jelly2[colIndex + 1].jellyRC.top = _foothold2[colIndex2].landRC.top - 55;
				_jelly2[colIndex + 1].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 55;
				_jelly2[colIndex + 2].jellyRC.top = _foothold2[colIndex2].landRC.top - 100;
				_jelly2[colIndex + 2].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 100;
			}

			if (IntersectRect(&temp, &_foothold2[i].landRC, &_jelly2_1[j].jellyRC))
				//if (_jelly2[j].jellyRC.bottom >= _foothold2[i].landRC.top)
			{
				colIndex = j;
				colIndex2 = i;

				_jelly2_1[colIndex - 2].jellyRC.top = _foothold2[colIndex2].landRC.top - 100;
				_jelly2_1[colIndex - 2].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 100;
				_jelly2_1[colIndex].jellyRC.top = _foothold2[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex - 1].jellyRC.top = _foothold2[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex - 1].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex + 1].jellyRC.top = _foothold2[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex + 1].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex + 2].jellyRC.top = _foothold2[colIndex2].landRC.top - 100;
				_jelly2_1[colIndex + 2].jellyRC.bottom = _foothold2[colIndex2].landRC.top - 100;
			}
		}
	}
	for (int i = 0; i < rand_foothold; i++)
	{
		for (int j = 0; j < JELLYMAX; j++)
		{
			if (IntersectRect(&temp, &_foothold[i].landRC, &_jelly2[j].jellyRC))
			//if (_jelly2[j].jellyRC.bottom >= _foothold[i].landRC.top)
			{
				colIndex = j;
				colIndex2 = i;
	
				_jelly2[colIndex - 2].jellyRC.top = _foothold[colIndex2].landRC.top - 100;
				_jelly2[colIndex - 2].jellyRC.bottom = _foothold[colIndex2].landRC.top - 100;
				_jelly2[colIndex].jellyRC.top = _foothold[colIndex2].landRC.top - 55;
				_jelly2[colIndex].jellyRC.bottom = _foothold[colIndex2].landRC.top - 55;
				_jelly2[colIndex + 1].jellyRC.top = _foothold[colIndex2].landRC.top - 55;
				_jelly2[colIndex + 1].jellyRC.bottom = _foothold[colIndex2].landRC.top - 55;
				_jelly2[colIndex - 1].jellyRC.top = _foothold[colIndex2].landRC.top - 55;
				_jelly2[colIndex - 1].jellyRC.bottom = _foothold[colIndex2].landRC.top - 55;
				_jelly2[colIndex + 2].jellyRC.top = _foothold[colIndex2].landRC.top - 100;
				_jelly2[colIndex + 2].jellyRC.bottom = _foothold[colIndex2].landRC.top - 100;
			}
			if (IntersectRect(&temp, &_foothold[i].landRC, &_jelly2_1[j].jellyRC))
				//if (_jelly2[j].jellyRC.bottom >= _foothold[i].landRC.top)
			{
				colIndex = j;
				colIndex2 = i;

				_jelly2_1[colIndex - 2].jellyRC.top = _foothold[colIndex2].landRC.top - 100;
				_jelly2_1[colIndex - 2].jellyRC.bottom = _foothold[colIndex2].landRC.top - 100;
				_jelly2_1[colIndex].jellyRC.top = _foothold[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex].jellyRC.bottom = _foothold[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex + 1].jellyRC.top = _foothold[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex + 1].jellyRC.bottom = _foothold[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex - 1].jellyRC.top = _foothold[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex - 1].jellyRC.bottom = _foothold[colIndex2].landRC.top - 55;
				_jelly2_1[colIndex + 2].jellyRC.top = _foothold[colIndex2].landRC.top - 100;
				_jelly2_1[colIndex + 2].jellyRC.bottom = _foothold[colIndex2].landRC.top - 100;
			}
		}
	}


	//��ֹ�-������ġ
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < JELLYMAX; j++)
		{
			//����1.
			if (IntersectRect(&temp, &_obstacle1[i].rc1, &_jelly2[j].jellyRC))
				//if (_jelly2[j].jellyRC.bottom >= _foothold[i].landRC.top)
			{
				colIndex = j;
				colIndex2 = i;
	
				_jelly2[colIndex].jellyRC.top = _obstacle1[i].rc1.top - 55;
				_jelly2[colIndex].jellyRC.bottom = _obstacle1[i].rc1.top - 55;
			}
			if (IntersectRect(&temp, &_obstacle1_1[i].rc1, &_jelly2[j].jellyRC))
				//if (_jelly2[j].jellyRC.bottom >= _foothold[i].landRC.top)
			{
				colIndex = j;
				colIndex2 = i;
	
				_jelly2[colIndex].jellyRC.top = _obstacle1_1[i].rc1.top - 55;
				_jelly2[colIndex].jellyRC.bottom = _obstacle1_1[i].rc1.top - 55;
			}
			//����2.
			if (IntersectRect(&temp, &_obstacle1[i].rc1, &_jelly2_1[j].jellyRC))
			{
				colIndex = j;
				colIndex2 = i;

				_jelly2_1[colIndex].jellyRC.top = _obstacle1[i].rc1.top - 55;
				_jelly2_1[colIndex].jellyRC.bottom = _obstacle1[i].rc1.top - 55;
			}
			if (IntersectRect(&temp, &_obstacle1_1[i].rc1, &_jelly2_1[j].jellyRC))
			{
				colIndex = j;
				colIndex2 = i;

				_jelly2_1[colIndex].jellyRC.top = _obstacle1_1[i].rc1.top - 55;
				_jelly2_1[colIndex].jellyRC.bottom = _obstacle1_1[i].rc1.top - 55;
			}
		}
	}


	//�÷��̾� ���� 1.�ƻ�
	if (_player->getHP() <= 0)
	{
		if (_player->getIsGround())
		{
			_player->setPlayerState(PLAYER_STATE::DIE);
			_player->setIsDie(true);

			activeTime++;
			if (activeTime >= 100)
			{
				result_active = true;
				SOUND->stop("��������2");
				SOUND->play("���");
			}
		}
	}
	//�÷��̾� ���� 2.�߶���
	if (_player->getPlayerY() > 2000)
	{
		result_active = true;
		SOUND->stop("��������2");
		SOUND->play("���");
	}


	//�κ� ��ư
	if (InputManager->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&townButton, m_ptMouse))
		{
			SOUND->stop("��������2");
			result_active = true;
			SOUND->play("���");
		}
	}

	//�ٴ�-�÷��̾� �浹
	collision();
	//����-�÷��̾�
	getJelly();
	//��ֹ�-�÷��̾�   
	damage();

	_player->update();
}

void stage2::render()
{
	IMAGE->loopRender("���_����", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), m_loopX * 4, 0);

	 
	for (int i = 0; i < rand_Ground; i++)
	{
		_ground[i].landImg->render(getMemDC(), _ground[i].landRC.left, _ground[i].landRC.top);
	}
	for (int i = 0; i < rand_foothold; i++)
	{
		_foothold[i].landImg->render(getMemDC(), _foothold[i].landRC.left - 30, _foothold[i].landRC.top);
		_foothold2[i].landImg->render(getMemDC(), _foothold2[i].landRC.left - 30, _foothold2[i].landRC.top);
	}


	//��ֹ� ����
	_obstacle1[0].img->frameRender(getMemDC(), _obstacle1[0].rc1.left - 5, _obstacle1[0].rc1.top - 20);
	_obstacle1[1].img->frameRender(getMemDC(), _obstacle1[1].rc1.left - 5, _obstacle1[1].rc1.top - 20);

	_obstacle1_1[0].img->frameRender(getMemDC(), _obstacle1_1[0].rc1.left - 5, _obstacle1_1[0].rc1.top - 20);
	_obstacle1_1[1].img->frameRender(getMemDC(), _obstacle1_1[1].rc1.left - 5, _obstacle1_1[1].rc1.top - 20);
	/// ������ϴ٤�����������

	_obstacle2.img->frameRender(getMemDC(), _obstacle2.rc1.left - 30, _obstacle2.rc1.top - 20);
	

	//���� ����
	//[����] ->�̰Ż���ǳ�? ->�����ȿ���
	for (int i = 0; i < JELLYMAX; i++)
	{
		if (!_jelly2[i].isGain)
		{
			_jelly2[i].jellyImg->render(getMemDC(), _jelly2[i].jellyRC.left, _jelly2[i].jellyRC.top);
		}
		if (_jelly2[i].isGain)
		{
			_jelly2[i].jellyImg->alphaRender(getMemDC(), _jelly2[i].jellyRC.left - 10, _jelly2[i].jellyRC.top, 70);
		}
		if (!_jelly2_1[i].isGain)
		{
			_jelly2_1[i].jellyImg->render(getMemDC(), _jelly2_1[i].jellyRC.left, _jelly2_1[i].jellyRC.top);
		}
		if (_jelly2_1[i].isGain)
		{
			_jelly2_1[i].jellyImg->alphaRender(getMemDC(), _jelly2_1[i].jellyRC.left - 10, _jelly2_1[i].jellyRC.top, 70);
		}
	}


	if (isDebug)
	{
		//�ٴ� ��Ʈ
		for (int i = 0; i < rand_Ground; i++)
		{
			Rectangle(getMemDC(), _ground[i].landRC.left, _ground[i].landRC.top, _ground[i].landRC.right, _ground[i].landRC.bottom);
		}
		//���� ��Ʈ
		for (int i = 0; i < rand_foothold; i++)
		{
			Rectangle(getMemDC(), _foothold[i].landRC.left, _foothold[i].landRC.top, _foothold[i].landRC.right, _foothold[i].landRC.bottom);
		}
		for (int i = 0; i < rand_foothold; i++)
		{
			Rectangle(getMemDC(), _foothold2[i].landRC.left, _foothold2[i].landRC.top, _foothold2[i].landRC.right, _foothold2[i].landRC.bottom);
		}
		for (int i = 0; i < 2; i++)
		{
			Rectangle(getMemDC(), _obstacle1[i].rc1.left, _obstacle1[i].rc1.top, _obstacle1[i].rc1.right, _obstacle1[i].rc1.bottom);
			Rectangle(getMemDC(), _obstacle1_1[i].rc1.left, _obstacle1_1[i].rc1.top, _obstacle1_1[i].rc1.right, _obstacle1_1[i].rc1.bottom);
		}

		Rectangle(getMemDC(), _obstacle2.rc1.left, _obstacle2.rc1.top, _obstacle2.rc1.right, _obstacle2.rc1.bottom);

		Rectangle(getMemDC(), posionRC.left, posionRC.top, posionRC.right, posionRC.bottom);

	}


	posion->render(getMemDC(), posionRC.left, posionRC.top);
	_player->render();
	IMAGE->render("������ư", getMemDC(), townButton.left, townButton.top);

	//TCHAR strr[20];
	//wsprintf(strr, "%d", activeTime);
	//TextOut(getMemDC(), 100, 100, strr, strlen(strr));
}

void stage2::collision()
{
	//�浹ó��
	for (int i = 0; i < rand_Ground; i++)
	{
		RECT temp;
		//if (_player->getPlayerRC().bottom == _ground[i].landRC.top)
		if (IntersectRect(&temp, &_ground[i].landRC, &_player->getPlayerRC()))
		{
			if (_player->getPlayerRC().bottom < _ground[i].landRC.bottom)
			{
				_player->setPlayerY(_ground[i].landRC.top - 200);
				_player->setGravity(0);
				_player->setIsGround(true);
				_player->setJumpCount(0);
			}
			//else continue;
		}
	}
	for (int i = 0; i < rand_foothold; i++)
	{
		RECT temp;
		//if (_player->getPlayerRC().bottom > _foothold[i].landRC.bottom - 10 || _player->getPlayerRC().bottom > _foothold2[i].landRC.bottom - 10) continue;
		//if (_player->getPlayerRC().bottom <= _foothold[i].landRC.top)
		if (IntersectRect(&temp, &_foothold[i].landRC, &_player->getPlayerRC()))
		{
			//index = i;
			_player->setPlayerY(_foothold[i].landRC.top - 200);
			_player->setGravity(0);
			_player->setIsGround(true);
			_player->setJumpCount(0);
			if (_player->getPlayerRC().bottom > _foothold[i].landRC.top) _player->setGravity(0.5);
		}
		if (IntersectRect(&temp, &_foothold2[i].landRC, &_player->getPlayerRC()))
		{
			//index = i;
			_player->setPlayerY(_foothold2[i].landRC.top - 200);
			_player->setGravity(0);
			_player->setIsGround(true);
			_player->setJumpCount(0);

			//if (_player->getPlayerRC().bottom > _foothold[i].landRC.top) continue;
			//if (_player->getPlayerRC().bottom > _foothold2[i].landRC.top) _player->setGravity(0.5);
		}
	}
}

void stage2::getJelly()
{
	RECT col;
	for (int i = 0; i < JELLYMAX; i++)
	{
		if (_player->getHP() <= 0) continue;

		if (IntersectRect(&col, &_player->getPlayerRC(), &_jelly2[i].jellyRC))
		{
			_player->setScore(_player->getScore() + _jelly2[i].score);
			_player->setCoin(_player->getCoin() + _jelly2[i].coin);

			if (!_jelly2[i].isGain)
			{
				if (i % 10 == 9) SOUND->play("����");
				else SOUND->play("����");
			}

			_jelly2[i].isGain = true;
		}
		if (_jelly2[i].isGain)
		{
			_jelly2[i].jellyImg = IMAGE->findImage("��������");
			//SOUND->stop("����");
		}

		if (IntersectRect(&col, &_player->getPlayerRC(), &_jelly2_1[i].jellyRC))
		{
			_player->setScore(_player->getScore() + _jelly2_1[i].score);
			_player->setCoin(_player->getCoin() + _jelly2_1[i].coin);

			if (!_jelly2_1[i].isGain)
			{
				if (i % 10 == 9) SOUND->play("����");
				else SOUND->play("����");
			}

			_jelly2_1[i].isGain = true;
		}
		if (_jelly2_1[i].isGain)
		{
			_jelly2_1[i].jellyImg = IMAGE->findImage("��������");
			//SOUND->stop("����");
		}
	
	}
}

void stage2::damage()
{
	RECT damRC;
	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&damRC, &_player->getPlayerRC(), &_obstacle1[i].rc1))
		{
			//========================================
			//if (!_player->getIsDamage()) SOUND->play("�浹");
			if (!isSound) SOUND->play("�浹");
			isSound = true;
			//========================================
			_player->setPlayerState(PLAYER_STATE::DAMAGE);
			_player->setHP(_player->getHP() - 20);
			_player->setIsDamage(true);
		}
		if (IntersectRect(&damRC, &_player->getPlayerRC(), &_obstacle1_1[i].rc1))
		{
			//========================================
			if (!isSound) SOUND->play("�浹");
			isSound = true;
			//========================================
			_player->setPlayerState(PLAYER_STATE::DAMAGE);
			_player->setHP(_player->getHP() - 20);
			_player->setIsDamage(true);
		}
	}
	if (IntersectRect(&damRC, &_player->getPlayerRC(), &_obstacle2.rc1))
	{
		//========================================
		if (!isSound) SOUND->play("�浹");
		isSound = true;
		//========================================
		_player->setPlayerState(PLAYER_STATE::DAMAGE);
		_player->setHP(_player->getHP() - 20);
		_player->setIsDamage(true);
	}

	if (isSound) activeCol++;
	if (activeCol >= 40) { isSound = false; activeCol = 0; }
}

void stage2::createObs(int x)
{
	for (int i = 0; i < 2; i++)
	{
		int randSpace = RND->getFromIntTo(300, 600);
		_obstacle1[i].img = IMAGE->findImage("2��ֹ�_�Ʒ�2");
		_obstacle1[i].rc1 = RectMake(x + 500  + (i * randSpace), 435 - 130, 70, 130);
		//_obstacle1[i].rc1 = RectMake(x + 500  + (i * 500), 435 - 150, 70, 145);
	}
}

void stage2::createObs2(int x)
{
	for (int i = 0; i < 2; i++)
	{
		int randSpace = RND->getFromIntTo(300, 600);
		_obstacle1_1[i].img = IMAGE->findImage("2��ֹ�_�Ʒ�2");
		_obstacle1_1[i].rc1 = RectMake(x + 500 + (i * randSpace), 435 - 130, 70, 130);
		//_obstacle1_1[i].rc1 = RectMake(x + 500 + (i * 500), 435 - 150, 70, 145);
	}
}



