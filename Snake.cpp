#include"Snake.h"
/*目前已经实现基本功能，后续需要处理：
1：增加四周的墙，撞墙则死
2：增加积分规则，按照存活时间和长度算积分
*/



/*Sprite method*/
void Sprite::draw()
{
	//设置填充颜色
	setfillcolor(m_color);
	//绘制矩形
	fillrectangle(m_x, m_y, m_x + 10, m_y + 10);//四个参数，分别表示矩形的左上角到右下角的坐标
};

void Sprite::moveBy(int x, int y)
{
	m_x += x;
	m_y += y;
}
bool Sprite::collision(const Sprite& other)
{
	return m_x == other.m_x && m_y == other.m_y;
}
void Sprite::changeFoodPos()
{
	m_x = rand() % 64 * 10;//保证坐标是10的倍数，这样才能吃到
	m_y = rand() % 48 * 10;
}


/*Snake method*/
void Snake::draw()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].draw();
	}
}

void Snake::bodyMove()
{
	for (size_t i = nodes.size() - 1; i > 0; i--)
	{
		nodes[i] = nodes[i - 1];
	}

	switch (dir)
	{
	case VK_UP://vkcode的上键的返回值的宏定义
		nodes[0].moveBy(0, -10);
		break;
	case VK_DOWN:
		nodes[0].moveBy(0, 10);
		break;
	case VK_LEFT:
		nodes[0].moveBy(-10, 0);
		break;
	case VK_RIGHT:
		nodes[0].moveBy(10, 0);
		break;

	}
}
bool Snake::collision(const Sprite& other)
{
	return nodes[0].collision(other);
}
void Snake::increment()
{
	nodes.push_back(Sprite());
}

/*GameSence method*/
void GameSence::onMsg(const ExMessage& msg)
{
	//如果有键盘消息
	if (msg.message == WM_KEYDOWN)//msg.message为消息类型，WM_KEYDOWN反应按键
	{
		//判断具体按键virtual code 虚拟键码
		switch (msg.vkcode)
		{
		case VK_UP:
			if (snake.dir != VK_DOWN)
				snake.dir = msg.vkcode;
			break;
		case VK_DOWN:
			if (snake.dir != VK_UP)
				snake.dir = msg.vkcode;
			break;
		case VK_RIGHT:
			if (snake.dir != VK_LEFT)
				snake.dir = msg.vkcode;
			break;
		case VK_LEFT:
			if (snake.dir != VK_RIGHT)
				snake.dir = msg.vkcode;
			break;
		}

	}
}
void GameSence::run()
{
	//双缓冲绘图
	BeginBatchDraw(); //双缓冲绘图是一种减少图形闪烁和提高绘制性能的技术。它的基本思想是使用一个或多个内存缓冲
	cleardevice();
	snake.draw();
	food.draw();
	EndBatchDraw();//一次性更新到屏幕上
	//移动蛇就是改变蛇的坐标
	snake.bodyMove();
	//改变蛇的移动方向，获取键盘按键_getch()
	snakeEatFood();
	//获取消息
	ExMessage msg = { 0 };
	while (peekmessage(&msg, EX_KEY))//如果有消息
	{
		onMsg(msg);
	} 

}
void GameSence::snakeEatFood()
{
	if (snake.collision(food))
	{
		//吃到食物，节数增加
		snake.increment();
		//蛇得吃后，食物改变位置
		food.changeFoodPos();
	}
}
/*Food methods*/
void Food::draw()
{
	setfillcolor(m_color);
	solidellipse(m_x, m_y, m_x + 10, m_y + 10);
}



int main()
{
	initgraph(640, 480,EX_SHOWCONSOLE);
	srand(time(nullptr));//初始化随机数种子
	GameSence scene;

	while (1)
	{
		scene.run();
		Sleep(100);
	}

	return 0;
}