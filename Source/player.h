#pragma once
#include "gameNode.h"
#include "jelly.h"
#include "progressBar.h"

//┌─────────────────────────────┐
//			상수 정보
//	점프 상수
	#define POWER 10.0f
	#define GRAVITY 0.5f
	#define JUMPMAX 2
//└─────────────────────────────┘

enum class PLAYER_STATE
{
	//일반
	RUN,
	JUMP1,
	JUMP2,
	SLIDE,
	DAMAGE,
	DIE
};


class player : public gameNode
{
private:
	progressBar* _hpBar;
	jelly*		_jelly;	
	tagJellyInfo* tagJelly;

	//쿠키 프레임
	image*		_brave;
	PLAYER_STATE _currentState;
	PLAYER_STATE _prevState;
	int			m_count;
	int			m_index;

	//재화
	float		HP;
	int			score;
	int			coin;


	int activeTime;


	

	//위치 정보
	int			_x, _y;
	RECT		playerRC;

	//점프(중력)
	float		_gravity;	
	float		_jumpPower;	
	int			_jumpCount;	

	//bool 변수
	bool		isDebug;
	bool		isJump; 		
	bool		isGround; 		
	bool		isDamage;

	bool		isDie;
	bool		isSound;

	//스테이지
	bool		isStage1;
	bool		isStage2;



public:
	player();
	~player();

	//HRESULT init(mainGame mg);
	HRESULT init();
	void release();
	void update();
	void render();

	void jump();
	void jellyGet();
	void collision();

	//HP
	void	setHP(int hp)		{ HP = hp; }
	float	getHP()				{ return HP; }
	//Score
	void	setScore(int score) { this->score = score; }
	int		getScore()			{ return score; }
	//Coin
	void	setCoin(int coin)	{ this->coin = coin; }
	int		getCoin()			{ return coin; }
	
	//스테이지 관련
	void setIsStage1(bool active) { isStage1 = active; _jelly->setIsStage1(active); }
	void setIsStage2(bool active) { isStage2 = active; _jelly->setIsStage2(active); }
	bool getIsStage1() const { return isStage1; }

	//플레이어 상태
	RECT getPlayerRC() { return playerRC; }
	void setPlayerState(PLAYER_STATE state) { _currentState = state; }
	void setIsDie(bool active) { isDie = active; }
	
	void setIsDamage(bool active) { isDamage = active; }
	bool getIsDamage() { return isDamage; }

	//플레이어 좌표
	int getPlayerX() const { return _x; }
	void setPlayerX(int x) { _x = x; }
	int getPlayerY() const { return _y; }
	void setPlayerY(int y) { _y = y; }

	//점프 정보
	bool getIsGround() { return isGround; }
	bool getIsJump() { return isJump; }

	void setGravity(float gravity) { _gravity = gravity; }
	void setIsGround(bool isGround) { this->isGround = isGround; }
	void setJumpCount(int jumpCount) { _jumpCount = jumpCount; }
};
