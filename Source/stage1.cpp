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

    IMAGE->addImage("���_����", "images/background_oven.bmp", WINSIZEX, WINSIZEY - 30, false, RGB(0, 0, 0));
    IMAGE->addImage("�ٴ�_����", "images/ground_oven.bmp", 150, 150, true, RGB(255, 0, 255));
    IMAGE->addImage("���", "images/flag.bmp", 321, 338, true, RGB(255, 0, 255));
    IMAGE->addImage("������ư", "images/townbutton.bmp", 100, 50, true, RGB(255, 67, 255));

    //�ٴ� �ʱ�ȭ
    for (int i = 0; i < FLOOR; i++)
    {
        _floor[i].rc1 = RectMake(i * 150, 435, 150, 150);
    }

    //���� �ڽ�
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
    //�÷��̾�-��ֹ� �浹ó��
    //collision();

    //���������� �̵�
    if (IntersectRect(&temp, &_player->getPlayerRC(), &endingBox))
    {
        activeTime++;
        if (activeTime >= 150)
        {
           SOUND->stop("��������1");
            result_active = true;
            activeTime = 0;

            SOUND->play("���");
        }
    }

    //�κ� ��ư
    if (InputManager->isOnceKeyUp(VK_LBUTTON))
    {
        if (PtInRect(&townButton, m_ptMouse))
        {
            SOUND->stop("��������1");
            result_active = true;
            SOUND->play("���");
        }
    }

}

void stage1::render()
{
    IMAGE->loopRender("���_����", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), m_loopX * 4, 0);
    IMAGE->render("���", getMemDC(), endingBox.left, endingBox.top);
    
   for (int i = 0; i < FLOOR; i++)
   {
       IMAGE->render("�ٴ�_����", getMemDC(), _floor[i].rc1.left, _floor[i].rc1.top);
   }

    _player->render();

    IMAGE->render("������ư", getMemDC(), townButton.left, townButton.top);
}
