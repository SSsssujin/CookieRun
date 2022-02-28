#include "framework.h"
#include "result.h"

result::result()
{
}

result::~result()
{      
}

HRESULT result::init()
{
	//SOUND->play("결과");

	_player = new player;
	_player->init();

	//_stage1 = new stage1;
	//_stage1->init();

	IMAGE->addImage("결과", "images/result.bmp", WINSIZEX, WINSIZEY - 30, false, RGB(0, 0, 0));
	IMAGE->addImage("확인", "images/okbutton.bmp", 141, 65, true, RGB(255, 67, 255));
	
	IMAGE->addImage("브론즈", "images/Bronze.bmp", 72, 67, true, RGB(255, 0, 255));
	IMAGE->addImage("실버", "images/Silver.bmp", 72, 67, true, RGB(255, 0, 255));
	IMAGE->addImage("골드", "images/Gold.bmp", 72, 67, true, RGB(255, 0, 255));
	IMAGE->addImage("크리스탈", "images/Diamond.bmp", 116, 81, true, RGB(255, 0, 255));

	okButton = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY - 150, 141, 65);

	lobby_active = false;

	score = 0;

	return S_OK;
}

void result::release()
{
	//_player->release();
}

void result::update()
{
	_player->update();

	if (InputManager->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&okButton, m_ptMouse))
		{
			lobby_active = true;
			SOUND->stop("결과");
			SOUND->play("로비", VOLUME);
		}
	}
}

void result::render()
{
	_player->render();


	IMAGE->render("결과", getMemDC());
	IMAGE->render("확인", getMemDC(), okButton.left, okButton.top);
	IMAGE->render("젤리1", getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2 - 10);
	IMAGE->render("코인", getMemDC(), WINSIZEX / 2 - 160, WINSIZEY / 2 + 60);

	HFONT font, oldfont;
	AddFontResource("images/font/CookieRun Regular.ttf");
	AddFontResource("images/font/CookieRun Black.ttf");
	AddFontResource("images/font/CookieRun Bold.ttf");

	font = CreateFont(68, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Bold"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TCHAR str[100];
	wsprintf(str, " Score　　 %d", score);
	TextOut(getMemDC(), WINSIZEX / 2 - 150, WINSIZEY / 2 - 30, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	font = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Bold"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	wsprintf(str, "Coin　　　 %d", coin);
	TextOut(getMemDC(), WINSIZEX / 2 - 80, WINSIZEY / 2 + 50, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	font = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Regular"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));



	if (score < 100000)
	{
		IMAGE->render("브론즈", getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 - 100);
		
		wsprintf(str, "브론즈 달성!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}
	else if (score >= 100000 && score < 300000)
	{
		IMAGE->render("실버", getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 - 100);

		wsprintf(str, "실버 달성!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}
	else if (score >= 300000 && score < 500000)
	{
		IMAGE->render("골드", getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 - 110);

		wsprintf(str, "골드 달성!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}
	else if (score >= 500000)
	{
		IMAGE->render("크리스탈", getMemDC(), WINSIZEX / 2 - 150, WINSIZEY / 2 - 120);

		wsprintf(str, "최고등급 달성!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);




}
