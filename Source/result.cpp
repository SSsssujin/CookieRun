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
	//SOUND->play("���");

	_player = new player;
	_player->init();

	//_stage1 = new stage1;
	//_stage1->init();

	IMAGE->addImage("���", "images/result.bmp", WINSIZEX, WINSIZEY - 30, false, RGB(0, 0, 0));
	IMAGE->addImage("Ȯ��", "images/okbutton.bmp", 141, 65, true, RGB(255, 67, 255));
	
	IMAGE->addImage("�����", "images/Bronze.bmp", 72, 67, true, RGB(255, 0, 255));
	IMAGE->addImage("�ǹ�", "images/Silver.bmp", 72, 67, true, RGB(255, 0, 255));
	IMAGE->addImage("���", "images/Gold.bmp", 72, 67, true, RGB(255, 0, 255));
	IMAGE->addImage("ũ����Ż", "images/Diamond.bmp", 116, 81, true, RGB(255, 0, 255));

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
			SOUND->stop("���");
			SOUND->play("�κ�", VOLUME);
		}
	}
}

void result::render()
{
	_player->render();


	IMAGE->render("���", getMemDC());
	IMAGE->render("Ȯ��", getMemDC(), okButton.left, okButton.top);
	IMAGE->render("����1", getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2 - 10);
	IMAGE->render("����", getMemDC(), WINSIZEX / 2 - 160, WINSIZEY / 2 + 60);

	HFONT font, oldfont;
	AddFontResource("images/font/CookieRun Regular.ttf");
	AddFontResource("images/font/CookieRun Black.ttf");
	AddFontResource("images/font/CookieRun Bold.ttf");

	font = CreateFont(68, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Bold"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TCHAR str[100];
	wsprintf(str, " Score���� %d", score);
	TextOut(getMemDC(), WINSIZEX / 2 - 150, WINSIZEY / 2 - 30, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	font = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Bold"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	wsprintf(str, "Coin������ %d", coin);
	TextOut(getMemDC(), WINSIZEX / 2 - 80, WINSIZEY / 2 + 50, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	font = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("CookieRun Regular"));
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));



	if (score < 100000)
	{
		IMAGE->render("�����", getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 - 100);
		
		wsprintf(str, "����� �޼�!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}
	else if (score >= 100000 && score < 300000)
	{
		IMAGE->render("�ǹ�", getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 - 100);

		wsprintf(str, "�ǹ� �޼�!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}
	else if (score >= 300000 && score < 500000)
	{
		IMAGE->render("���", getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 - 110);

		wsprintf(str, "��� �޼�!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}
	else if (score >= 500000)
	{
		IMAGE->render("ũ����Ż", getMemDC(), WINSIZEX / 2 - 150, WINSIZEY / 2 - 120);

		wsprintf(str, "�ְ��� �޼�!");
		TextOut(getMemDC(), WINSIZEX / 2 - 10, WINSIZEY / 2 - 100, str, lstrlen(str));
	}

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);




}
