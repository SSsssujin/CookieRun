#include "framework.h"
#include "player.h"
#define barFront 500
#define barBack 25


player::player()
{
}

player::~player()
{
}

//HRESULT player::init(mainGame mg)
HRESULT player::init()
{
	//_mainGame3 = mg;
	//_jelly = _mainGame3.GetJelly();
	//_stage1 = _mainGame3.GetStage();

	_jelly = new jelly;				 ////////////
	_jelly->init();					 ////////////

	tagJelly = _jelly->getJellyRC();

	IMAGE->addFrameImage("brave", "images/brave.bmp", 817, 205, 4, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("brave_slide", "images/brave_slide.bmp", 408, 205, 2, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("brave_jump", "images/brave_jump.bmp", 408, 205, 2, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("brave_doubleJump", "images/brave_doubleJump.bmp", 1429, 205, 7, 1, true, RGB(255, 0, 255)); //1906*274
	IMAGE->addFrameImage("brave_damage", "images/brave_damage.bmp", 1021, 205, 5, 1, true, RGB(255, 0, 255)); //1906*274

	IMAGE->addImage("체력바_아이콘", "images/hp_icon.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGE->addImage("체력바_앞", "images/hp_front.bmp", barFront, barBack, true, RGB(0, 0, 0));
	IMAGE->addImage("체력바_뒤", "images/hp_back.bmp", barFront, barBack, true, RGB(0, 0, 0));
	
	_x = WINSIZEX / 2 - 320;
	_y = WINSIZEY / 2 - 100;
	score = 0;
	coin = 100;

	isDebug = false;
	_currentState = PLAYER_STATE::RUN;
	_prevState = PLAYER_STATE::RUN;
	_brave = IMAGE->findImage("brave");

	isDamage = false;
	isStage1 = false;

	isDie = false;
	isSound = false;

	//점프 변수
	isJump = false;			
	isGround = true;		
	_jumpPower = 0;		
	_gravity = 0;		
	_jumpCount = 1;		


	//체력바
	HP = 10000;
	_hpBar = new progressBar;
	_hpBar->init(IMAGE->findImage("체력바_앞"), IMAGE->findImage("체력바_뒤"), 10, 10, 400, 15);
	_hpBar->setGauge(HP, 10000);


	activeTime = 0;




	playerRC = RectMake(_x + 50, _y + 70, _brave->getFrameWidth() / 3, _brave->getFrameHeight() / 2 - 10);

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_brave);
}

void player::update()
{
	_jelly->update();
	HP -= 3;

	if (InputManager->isOnceKeyUp(VK_F1)) isDebug = !isDebug;

	//슬라이드
	if (isGround && !isDamage && !isDie)
	{
		if (InputManager->isOnceKeyDown(VK_DOWN))
		{
			SOUND->play("슬라이드");		///조심
		}
		if (InputManager->isStayKeyDown(VK_DOWN))
		{
			_brave = IMAGE->findImage("brave_slide");
			_prevState = _currentState;
			_currentState = PLAYER_STATE::SLIDE;
		}
		if (InputManager->isOnceKeyUp(VK_DOWN))
		{
			_brave = IMAGE->findImage("brave");
			_prevState = _currentState;
			_currentState = PLAYER_STATE::RUN;
		}
	}

	if (!isDie)
	{
		jump();
		jellyGet();
		collision();
	}

	_hpBar->setGauge(HP, 10000);
	_hpBar->update();

	//프레임 돌리기
	if (!isDie)
	{
		if (_currentState == PLAYER_STATE::RUN)
		{
			m_count++;
			_brave->setFrameY(0);

			if (m_count % 5 == 0)
			{
				m_count = 0;
				m_index++;
				if (m_index >= 4)
				{
					m_index = 0;
				}
				_brave->setFrameX(m_index);

			}
			playerRC = RectMake(_x + 80, _y + 110, _brave->getFrameWidth() / 4, _brave->getFrameHeight() / 2 - 10);
		}
		else if (_currentState == PLAYER_STATE::JUMP1)
		{
			m_count++;
			_brave->setFrameY(0);

			if (m_count % 3 == 0)
			{
				m_count = 0;
				m_index++;
				if (m_index >= 1)
				{
					m_index = 0;
				}
				if (isGround)
				{
					_brave = IMAGE->findImage("brave");
					_prevState = _currentState;
					_currentState = PLAYER_STATE::RUN;
				}
			}
			playerRC = RectMake(_x + 80, _y + 110, _brave->getFrameWidth() / 4, _brave->getFrameHeight() / 2 - 10);
		}
		else if (_currentState == PLAYER_STATE::JUMP2)
		{
			m_count++;
			_brave->setFrameY(0);

			if (m_count % 5 == 0)
			{
				m_count = 0;
				m_index++;
				if (m_index >= 7)
				{
					m_index = 2;
					m_index++;
				}
				if (isGround)
				{
					_brave = IMAGE->findImage("brave");
					_prevState = _currentState;
					_currentState = PLAYER_STATE::RUN;
				}
				_brave->setFrameX(m_index);
			}
			playerRC = RectMake(_x + 80, _y + 110, _brave->getFrameWidth() / 4, _brave->getFrameHeight() / 2 - 10);
		}
		else if (_currentState == PLAYER_STATE::SLIDE)
		{
			m_count++;
			_brave->setFrameY(0);

			if (m_count % 10 == 0)
			{
				m_count = 0;
				m_index++;
				if (m_index >= 2)
				{
					m_index = 0;
				}
				_brave->setFrameX(m_index);
			}
			playerRC = RectMake(_x + 60, _y + 160, _brave->getFrameWidth() / 3 + 30, _brave->getFrameHeight() / 2 - 60);
		}
		else if (_currentState == PLAYER_STATE::DAMAGE)
		{
			_brave = IMAGE->findImage("brave_damage");
			m_count++;
			_brave->setFrameY(0);

			//[수정] 점프 프레임 조절하기
			if (m_count % 10 == 0)
			{
				m_count = 0;
				m_index++;
				if (m_index >= 5)
				{
					m_index = 0;
					_brave = IMAGE->findImage("brave");
					_currentState = PLAYER_STATE::RUN;
				}
				_brave->setFrameX(m_index);
			}
			isDamage = false;

			playerRC = RectMake(_x + 60, _y + 160, _brave->getFrameWidth() / 3 + 30, _brave->getFrameHeight() / 2 - 60);
			//_y = WINSIZEY / 2 - 100;
		}
	}
	if (_currentState == PLAYER_STATE::DIE)
	{
		_brave = IMAGE->findImage("brave_damage");
		m_count++;
		_brave->setFrameY(0);

		if (m_count % 10 == 0)
		{
			m_count = 0;
			m_index++;
			if (m_index >= 3)
			{
				m_index = 3;
			}
			_brave->setFrameX(m_index);
		}
		isDamage = false;
		
		playerRC = RectMake(_x + 60, _y + 160, _brave->getFrameWidth() / 3 + 30, _brave->getFrameHeight() / 2 - 60);
	}
	
	if (isDie)
	{
		_x -= OBJECTSPEED;
	}
}

void player::render()
{


	switch (_currentState)
	{
	case PLAYER_STATE::RUN:
		_brave->frameRender(getMemDC(), _x, _y);
		break;
	case PLAYER_STATE::JUMP1:
		_brave->frameRender(getMemDC(), _x, _y);
		break;
	case PLAYER_STATE::JUMP2:
		_brave->frameRender(getMemDC(), _x, _y);
		break;
	case PLAYER_STATE::SLIDE:
		_brave->frameRender(getMemDC(), _x, _y);
		break;
	case PLAYER_STATE::DAMAGE:
		_brave->frameRender(getMemDC(), _x, _y);
	case PLAYER_STATE::DIE:
		_brave->frameRender(getMemDC(), _x, _y);
	default:
		break;
	}

	if (isDebug)
	{
		Rectangle(getMemDC(), playerRC.left, playerRC.top, playerRC.right, playerRC.bottom);
	}

	//sprintf_s(strBlock, "x좌표 : %d, y좌표 : %d", m_ptMouse.x, m_ptMouse.y);
	//SetTextColor(getMemDC(), RGB(255, 255, 255));
	//TextOut(getMemDC(), 0, 60, strBlock, strlen(strBlock));
	//
	//sprintf_s(strBlock, "isJump : %d, isGround : %d", isJump, isGround);
	//SetTextColor(getMemDC(), RGB(255, 255, 255));
	//TextOut(getMemDC(), 0, 80, strBlock, strlen(strBlock));
	//
	//sprintf_s(strBlock, "jumpCount : %d", _jumpCount);
	//SetTextColor(getMemDC(), RGB(255, 255, 255));
	//TextOut(getMemDC(), 0, 100, strBlock, strlen(strBlock));



	//sprintf_s(strBlock, "score : %d", score);
	//SetTextColor(getMemDC(), RGB(255, 255, 255));
	//TextOut(getMemDC(), WINSIZEX - 200, 30, strBlock, strlen(strBlock));
	
	HFONT font, oldfont;
	//AddFontResource("images/font/CookieRun Regular.ttf");
	//AddFontResource("images/font/CookieRun Black.ttf");
	
	font = CreateFont(36, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Bold"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255)); 
	

	//코인 렌더
	IMAGE->render("코인", getMemDC(), WINSIZEX - 170, 30);
	IMAGE->render("젤리1", getMemDC(), WINSIZEX / 2 - 80, 70);

	char strBlock[128];

	sprintf_s(strBlock, "%d", score);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 40, 65, strBlock, strlen(strBlock));

	sprintf_s(strBlock, "%d", coin);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX - 120, 30, strBlock, strlen(strBlock));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	//RECT temp;
	//TCHAR strr[20];
	//wsprintf(strr, "activeTime : %d", activeTime);
	//TextOut(getMemDC(), 100, 100, strr, strlen(strr));
	//
	//wsprintf(strr, "isSound : %d", isSound);
	//TextOut(getMemDC(), 100, 120, strr, strlen(strr));
	//
	//wsprintf(strr, "_jumpPower : %d", _jumpPower);
	//TextOut(getMemDC(), 100, 140, strr, strlen(strr));
	//
	//wsprintf(strr, "POWER : %d", POWER);
	//TextOut(getMemDC(), 100, 160, strr, strlen(strr));

	_jelly->render();
	_hpBar->render(250, 30);
	IMAGE->render("체력바_아이콘", getMemDC(), 210, 20);
}
 
void player::jump()
{
	//1.점프
	if (InputManager->isOnceKeyDown(VK_SPACE) && _jumpCount < JUMPMAX)
	{
		isJump = true;
		isGround = false;
		_jumpCount++;
		_jumpPower = POWER;

		if (_jumpCount == 1)
		{
			SOUND->play("점프");		///조심
			_brave = IMAGE->findImage("brave_jump");
			_prevState = _currentState;
			_currentState = PLAYER_STATE::JUMP1;
		}
		else if (_jumpCount == 2)
		{
			SOUND->play("점프");
			_brave = IMAGE->findImage("brave_doubleJump");
			_prevState = _currentState;
			_currentState = PLAYER_STATE::JUMP2;
		}
	}
	
	if (isJump)
	{
		_gravity = GRAVITY;
		_y -= _jumpPower;
		_jumpPower -= _gravity;

		if (_jumpPower < 0)
		{
			_gravity = GRAVITY;
			isJump = false;
		}
	}
	else
	{
		_y += _gravity;
		_gravity += GRAVITY;
		//if (_gravity > 5) { _gravity = 5; }
		if (isStage1 && _y > WINSIZEY / 2 - 70)
		{
			_y = WINSIZEY / 2 - 70;
			isGround = true;
			_jumpCount = 0;
		}
	}
}

void player::jellyGet()
{
	//tagJellyInfo* jelly = _jelly->getJellyRC();

	RECT temp;
	for (int i = 0; i < JELLYMAX; i++)
	{
		if (IntersectRect(&temp, &tagJelly[i].jellyRC, &playerRC))
		{
			score += tagJelly[i].score;
			coin += tagJelly[i].coin;

			if (!tagJelly[i].isGain)
			{
				if (i % 10 == _jelly->getRand()) SOUND->play("코인");
				else SOUND->play("젤리");
			}
			tagJelly[i].isGain = true;
		}
		if (tagJelly[i].isGain)
		{
			tagJelly[i].jellyImg = IMAGE->findImage("젤리먹음");
		}
	}
}

void player::collision()
{
	//int activeTime = 0;
	RECT temp;
	for (int i = 0; i < LOWER_OBS1; i++)
	{
		if (IntersectRect(&temp, &_jelly->getObstacle()->getObstacle1RC()[i].rc1, &playerRC))
		{
			//================================
			//if(!isDamage) SOUND->play("충돌");
			if(!isSound) SOUND->play("충돌");
			isSound = true;
			//================================
			
			isDamage = true;
			HP -= 10;
			_currentState = PLAYER_STATE::DAMAGE;
		}
		else if (IntersectRect(&temp, &_jelly->getObstacle()->getObstacle1RC()[i].rc2, &playerRC))
		{
			//================================
			if (!isSound) SOUND->play("충돌");
			isSound = true;
			//================================

			isDamage = true;
			HP -= 10;
			_currentState = PLAYER_STATE::DAMAGE;
		}
		//if (isSound) activeTime++;
		//if (activeTime >= 50) isSound = false; activeTime = 0;
	}
	for (int i = 0; i < LOWER_OBS2; i++)
	{
		if (IntersectRect(&temp, &_jelly->getObstacle()->getObstacle2RC()[i].rc1, &playerRC))
		{
			//================================
			if (!isSound) SOUND->play("충돌");
			isSound = true;
			//================================

			isDamage = true;
			HP -= 10;
			_currentState = PLAYER_STATE::DAMAGE;
		}
		else if (IntersectRect(&temp, &_jelly->getObstacle()->getObstacle2RC()[i].rc2, &playerRC))
		{
			//================================
			if (!isSound) SOUND->play("충돌");
			isSound = true;
			//================================

			isDamage = true;
			HP -= 10;
			_currentState = PLAYER_STATE::DAMAGE;
		}
	}
	for (int i = 0; i < UPPER_OBS; i++)
	{
		if (IntersectRect(&temp, &_jelly->getObstacle()->getObstacle3RC()[i].rc1, &playerRC))
		{
			//================================
			if (!isSound) SOUND->play("충돌");
			isSound = true;
			//================================

			isDamage = true;
			HP -= 10;
			_currentState = PLAYER_STATE::DAMAGE;
		}
	}
	
	
	if (isSound) activeTime++;
	if (activeTime >= 40) { isSound = false; activeTime = 0; }
}
