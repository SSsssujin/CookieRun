#include "framework.h"
#include "stage1.h"

stage1::stage1()
{
}

stage1::~stage1()
{
}

//HRESULT stage1::init(mainGame mg)
HRESULT stage1::init()
{

    _player = new player;
    _player->init();

    IMAGE->addImage("배경_오븐", "images/background_oven.bmp", WINSIZEX, WINSIZEY - 30, false, RGB(0, 0, 0));
    IMAGE->addImage("바닥_오븐", "images/ground_oven.bmp", 150, 150, true, RGB(255, 0, 255));
    IMAGE->addImage("깃발", "images/flag.bmp", 321, 338, true, RGB(255, 0, 255));
    IMAGE->addImage("마을버튼", "images/townbutton.bmp", 100, 50, true, RGB(255, 67, 255));

    //바닥 초기화
    for (int i = 0; i < FLOOR; i++)
    {
        _floor[i].rc1 = RectMake(i * 150, 435, 150, 150);
    }

    //골인 박스
    endingBox = RectMake(WINSIZEX + 10000, _floor[0].rc1.top - 338, 800, 338);
    //endingBox = RectMake(1000, _floor[0].rc1.top - 338, 800, 338);
    townButton = RectMake(WINSIZEX - 180, WINSIZEY - 120, 100, 50);
    
    m_loopX = 0;
    isDebug = false;
    result_active = false;
    activeTime = 0;

    stage1_active = false;
    _player->setIsStage1(true);

    return S_OK;
}

void stage1::release()
{
    //SAFE_DELETE(_player);
    //SAFE_DELETE(_obstacle);
    //SAFE_DELETE(_jelly);
}

void stage1::update()
{
    if (InputManager->isOnceKeyUp(VK_F2)) isDebug = !isDebug;

    _player->update();
    m_loopX++;

    OffsetRect(&endingBox, -OBJECTSPEED, 0);
    for (int i = 0; i < FLOOR; i++)
    {
        OffsetRect(&_floor[i].rc1, -OBJECTSPEED, 0);
    }

    RECT temp;
    //플레이어-장애물 충돌처리
    //collision();

    //엔딩씬으로 이동
    if (IntersectRect(&temp, &_player->getPlayerRC(), &endingBox))
    {
        activeTime++;
        if (activeTime >= 150)
        {
           SOUND->stop("스테이지1");
            result_active = true;
            activeTime = 0;

            SOUND->play("결과");
        }
    }

    //로비 버튼
    if (InputManager->isOnceKeyUp(VK_LBUTTON))
    {
        if (PtInRect(&townButton, m_ptMouse))
        {
            SOUND->stop("스테이지1");
            result_active = true;
            SOUND->play("결과");
        }
    }

}

void stage1::render()
{
    IMAGE->loopRender("배경_오븐", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), m_loopX * 4, 0);
    IMAGE->render("깃발", getMemDC(), endingBox.left, endingBox.top);
    
   for (int i = 0; i < FLOOR; i++)
   {
       IMAGE->render("바닥_오븐", getMemDC(), _floor[i].rc1.left, _floor[i].rc1.top);
   }

    _player->render();

    IMAGE->render("마을버튼", getMemDC(), townButton.left, townButton.top);
}
