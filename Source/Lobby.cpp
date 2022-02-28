#include "framework.h"
#include "Lobby.h"

Lobby::Lobby()
{
}

Lobby::~Lobby()
{
}

HRESULT Lobby::init()
{
	SOUND->play("로비", VOLUME);

	IMAGE->addImage("배경_로비", "images/background2_lobby.bmp", WINSIZEX, WINSIZEY - 30, false, RGB(0, 0, 0));
	IMAGE->addImage("튜토리얼", "images/튜토리얼.bmp", 250, 220, true, RGB(255, 0, 255));
	IMAGE->addImage("게임시작", "images/게임시작.bmp", 250, 220, true, RGB(255, 0, 255));
	_brave = IMAGE->addFrameImage("brave_idle", "images/brave_idle.bmp", 1248, 350, 4, 1, true, RGB(255,0,255));

	tutorialButton	=	RectMake(500, 50, 250, 220);
	playButton		=	RectMake(500, 300, 250, 220);

	//임시 사각형
	//temp = RectMake(400, 300, 100, 100);


	lobby_active = true;
	stage1_active = false;
	stage2_active = false;

	return S_OK;
}

void Lobby::release()
{
}

void Lobby::update()
{

	//쿠키 프레임
	m_count++;
	_brave->setFrameY(0);

	if (m_count % 30 == 0)
	{
		m_count = 0;
		m_index++;
		if (m_index >= 5)
		{
			m_index = 0;
		}
		_brave->setFrameX(m_index);

	}

	if (InputManager->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&tutorialButton, m_ptMouse)) 
		{
			stage1_active = true;
			SOUND->play("스테이지1", VOLUME);
			SOUND->stop("로비");
		}
		if (PtInRect(&playButton, m_ptMouse))
		{
			stage2_active = true;
			SOUND->play("스테이지2", VOLUME);
			SOUND->stop("로비");
		}
	}
}

void Lobby::render()
{
	IMAGE->render("배경_로비", getMemDC());
	IMAGE->render("튜토리얼", getMemDC(), tutorialButton.left, tutorialButton.top);
	IMAGE->render("게임시작", getMemDC(), playButton.left, playButton.top);
	_brave->frameRender(getMemDC(), 100, 100);



	//Rectangle(getMemDC(), temp.left, temp.top, temp.right, temp.bottom);

	//char strBlock[128];
	//sprintf_s(strBlock, "x좌표 : %d, y좌표 : %d", m_ptMouse.x, m_ptMouse.y);
	//SetTextColor(getMemDC(), RGB(0,0,0));
	//TextOut(getMemDC(), 0, 60, strBlock, strlen(strBlock));
	//
	//sprintf_s(strBlock, "stage_active : %d", stage1_active);
	//SetTextColor(getMemDC(), RGB(0,0,0));
	//TextOut(getMemDC(), 0, 80, strBlock, strlen(strBlock));
}
