#pragma once
#include "gameNode.h"
#include "jelly.h"
#include "progressBar.h"

//��������������������������������������������������������������
//			��� ����
//	���� ���
	#define POWER 10.0f
	#define GRAVITY 0.5f
	#define JUMPMAX 2
//��������������������������������������������������������������

enum class PLAYER_STATE
{
	//�Ϲ�
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

	//��Ű ������
	image*		_brave;
	PLAYER_STATE _currentState;
	PLAYER_STATE _prevState;
	int			m_count;
	int			m_index;

	//��ȭ
	float		HP;
	int			score;
	int			coin;


	int activeTime;


	

	//��ġ ����
	int			_x, _y;
	RECT		playerRC;

	//����(�߷�)
	float		_gravity;	
	float		_jumpPower;	
	int			_jumpCount;	

	//bool ����
	bool		isDebug;
	bool		isJump; 		
	bool		isGround; 		
	bool		isDamage;

	bool		isDie;
	bool		isSound;

	//��������
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
	
	//�������� ����
	void setIsStage1(bool active) { isStage1 = active; _jelly->setIsStage1(active); }
	void setIsStage2(bool active) { isStage2 = active; _jelly->setIsStage2(active); }
	bool getIsStage1() const { return isStage1; }

	//�÷��̾� ����
	RECT getPlayerRC() { return playerRC; }
	void setPlayerState(PLAYER_STATE state) { _currentState = state; }
	void setIsDie(bool active) { isDie = active; }
	
	void setIsDamage(bool active) { isDamage = active; }
	bool getIsDamage() { return isDamage; }

	//�÷��̾� ��ǥ
	int getPlayerX() const { return _x; }
	void setPlayerX(int x) { _x = x; }
	int getPlayerY() const { return _y; }
	void setPlayerY(int y) { _y = y; }

	//���� ����
	bool getIsGround() { return isGround; }
	bool getIsJump() { return isJump; }

	void setGravity(float gravity) { _gravity = gravity; }
	void setIsGround(bool isGround) { this->isGround = isGround; }
	void setJumpCount(int jumpCount) { _jumpCount = jumpCount; }
};
