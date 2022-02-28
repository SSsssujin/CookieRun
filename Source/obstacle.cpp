#include "framework.h"
#include "obstacle.h"

obstacle::obstacle()
{
}

obstacle::~obstacle()
{
}

HRESULT obstacle::init()
{
    int randRange = RND->getFromIntTo(50, 200);

    //_stage2 = new stage2;
    //_stage2->init();

    //stage1
    IMAGE->addImage("장애물_아래", "images/obstacle1_oven.bmp", 65, 70, true, RGB(255, 0, 255));
    IMAGE->addImage("큰장애물1_아래", "images/obstacle2_oven.bmp", 70, 130, true, RGB(255, 0, 255));
    IMAGE->addImage("큰장애물2_아래", "images/obstacle3_oven.bmp", 70, 130, true, RGB(255, 0, 255));
    IMAGE->addImage("장애물_위", "images/obstacle4_oven.bmp", 250, 370, true, RGB(255, 0, 255));


   
    fixY = 435;
    //장애물_아래 초기화
    for (int i = 0; i < LOWER_OBS1; i++)
    {
       _obstacle1[i].rc1 = RectMake(WINSIZEX + 3000 + (i * 317), fixY - 10, 63, 10);
       _obstacle1[i].rc2 = RectMake(WINSIZEX + 3000 + (i * 317) + 20, fixY - 68, 20, 68);
       
       // _obstacle1[i].rc1 = RectMake(WINSIZEX + 300 + (i * 317), fixY - 10, 63, 10);
       // _obstacle1[i].rc2 = RectMake(WINSIZEX + 300 + (i * 317) + 20, fixY - 68, 20, 68);
    }
    //큰장애물_아래
    for (int i = 0; i < LOWER_OBS2; i++)
    {
        _obstacle2[i].rc1 = RectMake(WINSIZEX + 5000 + (i * 360), fixY - 15, 63, 15);
        _obstacle2[i].rc2 = RectMake(WINSIZEX + 5000 + (i * 360) + 23, fixY - 125, 18, 125);
    }
    //장애물_위
    for (int i = 0; i < UPPER_OBS; i++)
    {
        _obstacle3[i].rc1 = RectMake(WINSIZEX + 7000 + (i * 250) + 20, 0, 210, 370);
    }


    isDebug = false;

    return S_OK;
}

HRESULT obstacle::init(const int x, const int y)
{




    return S_OK;
}

void obstacle::release()
{
}

void obstacle::update()
{
    if (InputManager->isOnceKeyUp(VK_F2)) isDebug = !isDebug;

        for (int i = 0; i < LOWER_OBS1; i++)
        {
            OffsetRect(&_obstacle1[i].rc1, -OBJECTSPEED, 0);
            OffsetRect(&_obstacle1[i].rc2, -OBJECTSPEED, 0);
        }
        for (int i = 0; i < LOWER_OBS2; i++)
        {
            OffsetRect(&_obstacle2[i].rc1, -OBJECTSPEED, 0);
            OffsetRect(&_obstacle2[i].rc2, -OBJECTSPEED, 0);
        }
        for (int i = 0; i < UPPER_OBS; i++)
        {
            OffsetRect(&_obstacle3[i].rc1, -OBJECTSPEED, 0);
        }
}

void obstacle::render()
{
    //장애물_아래 렌더
    for (int i = 0; i < LOWER_OBS1; i++)
    {
        IMAGE->render("장애물_아래", getMemDC(), _obstacle1[i].rc1.left + 2, _obstacle1[i].rc2.top - 2);

        if (isDebug)
        {
            Rectangle(getMemDC(), _obstacle1[i].rc1.left, _obstacle1[i].rc1.top, _obstacle1[i].rc1.right, _obstacle1[i].rc1.bottom);
            Rectangle(getMemDC(), _obstacle1[i].rc2.left, _obstacle1[i].rc2.top, _obstacle1[i].rc2.right, _obstacle1[i].rc2.bottom);
        }
    }

    //큰장애물_아래 렌더
    IMAGE->render("큰장애물1_아래", getMemDC(), _obstacle2[0].rc1.left, _obstacle2[0].rc2.top - 5);
    IMAGE->render("큰장애물2_아래", getMemDC(), _obstacle2[1].rc1.left, _obstacle2[1].rc2.top - 5);
    IMAGE->render("큰장애물1_아래", getMemDC(), _obstacle2[2].rc1.left, _obstacle2[2].rc2.top - 5);
    IMAGE->render("큰장애물2_아래", getMemDC(), _obstacle2[3].rc1.left, _obstacle2[3].rc2.top - 5);

    for (int i = 0; i < LOWER_OBS2; i++)
    {
        if (isDebug)
        {
            Rectangle(getMemDC(), _obstacle2[i].rc1.left, _obstacle2[i].rc1.top, _obstacle2[i].rc1.right, _obstacle2[i].rc1.bottom);
            Rectangle(getMemDC(), _obstacle2[i].rc2.left, _obstacle2[i].rc2.top, _obstacle2[i].rc2.right, _obstacle2[i].rc2.bottom);
        }
    }

    //장애물_위 렌더
    for (int i = 0; i < UPPER_OBS; i++)
    {
        IMAGE->render("장애물_위", getMemDC(), _obstacle3[i].rc1.left - 20, _obstacle3[i].rc1.top);

        if (isDebug)
        {
            Rectangle(getMemDC(), _obstacle3[i].rc1.left, _obstacle3[i].rc1.top, _obstacle3[i].rc1.right, _obstacle3[i].rc1.bottom);
        }
    }
}
