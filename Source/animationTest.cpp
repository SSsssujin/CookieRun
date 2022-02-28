#include "framework.h"
#include "animationTest.h"

animationTest::animationTest()
{
}

animationTest::~animationTest()
{
}

HRESULT animationTest::init()
{

	_brave = new player;
	_brave->init();
	return S_OK;
}

void animationTest::release()
{
	SAFE_DELETE(_brave);

}

void animationTest::update()
{
	_brave->update();
}

void animationTest::render()
{
	_brave->render();
}
