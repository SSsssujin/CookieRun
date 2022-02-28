#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);

	//게임BGM
	SOUND->addSound("로비", "sound/Bgm_epN02-Lobby.mp3", true, true);
	SOUND->addSound("스테이지1", "sound/Bgm_epN01-1.mp3", true, true);
	SOUND->addSound("스테이지2", "sound/Bgm_epN01-2.mp3", true, true);
	SOUND->addSound("결과", "sound/r_medal.ogg", true, false);
	//효과음
	SOUND->addSound("점프", "sound/ch01jump.ogg", true, false);
	SOUND->addSound("슬라이드", "sound/ch01slide.ogg", true, false);
	SOUND->addSound("포션", "sound/g_ijelly.ogg", true, false);
	SOUND->addSound("젤리", "sound/g_alphabet.ogg", true, false);
	SOUND->addSound("충돌", "sound/g_obs1.ogg", true, false);
	SOUND->addSound("코인", "sound/g_coin.ogg", true, false);


	
	_stage1 = new stage1;
	_stage1->init();

	_stage2 = new stage2;
	_stage2->init();

	_lobby = new Lobby;
	_lobby->init();

	_result = new result;
	_result->init();

	lobby_active = true;
	stage1_active = false;
	stage2_active = false;
	result_active = false;

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	//SCENE->release();

	_lobby->release();
	_result->release();
	//_stage1->release();
	//_stage2->release();
	//_jelly->release();
}

void mainGame::update()
{
	gameNode::update();
	//SCENE->update();
	//ANIMATION->update();

	if (lobby_active)
	{
		stage1_active = false;
		stage2_active = false;
		result_active = false;
	
		_lobby->update();

		stage1_active = _lobby->getStage1_active();
		stage2_active = _lobby->getStage2_active();
	
		if (stage1_active)
		{ 
			_stage1 = new stage1;
			_stage1->init();

			_lobby->setStage1_active(false);
			lobby_active = false;
		}
		if (stage2_active)
		{
			_stage2 = new stage2;
			_stage2->init();

			_lobby->setStage2_active(false);
			lobby_active = false;
		}
	}

	if (stage1_active)
	{
		result_active = false;
		lobby_active = false;
	
		_stage1->update();
		result_active = _stage1->getResult_active();
		
		if (result_active)
		{
			//SOUND->stop("스테이지1");

			_result->setScore(_stage1->getScore());
			_result->setCoin(_stage1->getCoin());
			SAFE_DELETE(_stage1);
			stage1_active = false;
		}
	}
	if (stage2_active)
	{
		//SOUND->play("스테이지2");

		result_active = false;
		lobby_active = false;
	
		_stage2->update();
		result_active = _stage2->getResult_active();

		if (result_active)
		{
			//SOUND->stop("스테이지2");

			_result->setScore(_stage2->getScore());
			_result->setCoin(_stage2->getCoin());
			SAFE_DELETE(_stage2);
			stage2_active = false;
		}
	}
	if (result_active)
	{
		lobby_active = false;
		stage1_active = false;
		stage2_active = false;
	
		_result->update();
		lobby_active = _result->getLobby_active();

		if (lobby_active)
		{
			_result->setLobby_active(false);
			result_active = false;
		}
	}

	//_player->update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	SetBkMode(getMemDC(), TRANSPARENT);

	if (lobby_active) { _lobby->render(); }
	if (stage1_active) { _stage1->render(); } //_jelly->render(); }
	if (stage2_active) { _stage2->render(); }// _jelly->render(); }
	if (result_active) { _result->render(); }
	//_player->render();

	
	//char strBlock[128];
	//sprintf_s(strBlock, "lobby_active : %d", lobby_active);
	//SetTextColor(getMemDC(), RGB(0,0,0));
	//TextOut(getMemDC(), 0, 60, strBlock, strlen(strBlock));
	//
	//sprintf_s(strBlock, "stage1_active : %d", stage1_active);
	//SetTextColor(getMemDC(), RGB(0, 0, 0));
	//TextOut(getMemDC(), 0, 80, strBlock, strlen(strBlock));
	//
	//sprintf_s(strBlock, "result_active : %d", result_active);
	//SetTextColor(getMemDC(), RGB(0, 0, 0));
	//TextOut(getMemDC(), 0, 100, strBlock, strlen(strBlock));

	//==============================================

	//TIME->render(getMemDC());

	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

