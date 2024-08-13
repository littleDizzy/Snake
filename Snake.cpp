#include"Snake.h"
/*目前已经实现基本功能，后续需要处理：
1：增加四周的墙（已解决），撞墙则死(已解决）,更换墙的颜色（已解决）
2: 头撞身子也死(已解决)
3：增加积分规则，按照存活时间和长度算积分(已解决)
4：小bug:食物有可能长在墙上(已修复)
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
	int tem_x;
	int tem_y;
	int wallData[64][48] = { 0 };
	tem_x = rand() % 64 * 10;//保证坐标是10的倍数，这样才能吃到
	tem_y = rand() % 48 * 10;
	//用一个数组把墙的位置装上
	// 设置上边墙
	for (int i = 0; i < 64; ++i) {
		wallData[i][0] = 1;
	}

	// 设置下边墙
	for (int i = 0; i < 64; ++i) {
		wallData[i][48 - 1] = 1;
	}

	// 设置左边墙
	for (int i = 0; i < 48; ++i) {
		wallData[0][i] = 1;
	}

	// 设置右边墙
	for (int i = 0; i < 48; ++i) {
		wallData[64 - 1][i] = 1;
	}
	//如果食物长在墙上，重新生成食物
	while(wallData[tem_x / 10][tem_y / 10] == 1)
	{
		tem_x = rand() % 64 * 10;
		tem_y = rand() % 48 * 10;
	}
	m_x = tem_x;
	m_y = tem_y;
}


/*Snake method*/
void Snake::draw()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].draw();//调用了sprite的draw
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

bool Snake::collisionWall()
{
	int x;
	int y;
	int flag = 0;
	const Sprite& head = nodes[0];


	y = 0;
	for (int i = 0; i < 64; i++)
	{
		x = i * 10;
		if (head.getX() == x && head.getY() == y)
		{
			flag = 1;
		}
;
	}
	y = 470;
	for (int i = 0; i < 64; i++)
	{
		x = i * 10;
		if (head.getX() == x && head.getY() == y)
		{
			flag = 1;
		}
	}
	x = 0;
	for (int i = 0; i < 48; i++)
	{
		y = i * 10;
		if (head.getX() == x && head.getY() == y)
		{
			flag = 1;
		}
	}
	x = 630;
	for (int i = 0; i < 48; i++)
	{
		y = i * 10;
		if (head.getX() == x && head.getY() == y)
		{
			flag = 1;
		}
	}
	return flag == 1;
}

void Snake::increment()
{
	nodes.push_back(Sprite());
}
bool Snake::collisionSelf()
{
	int flag = 0;
	for (int i = 1; i < nodes.size(); i++)
	{
		if (nodes[0].collision(nodes[i]))
		{
			flag =1;
		}
	}
	return flag == 1;
}
/*wall method*/

void Wall::setWall()
{
	setfillcolor(m_color);

	m_y = 0;
	for (int i = 0; i < 64; i++)
	{
		m_x = i * 10;
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);
	}
	m_y = 470;
	for (int i = 0; i < 64; i++)
	{
		m_x = i * 10;
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);
	}
	m_x = 0;
	for (int i = 0; i < 48; i++)
	{
		m_y = i * 10;
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);
	}
	m_x = 630;
	for (int i = 0; i < 48; i++)
	{
		m_y = i * 10;
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);
	}



}
int Snake::getLength()
{
	return nodes.size();
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
	wall.setWall();
	snake.draw();
	food.draw();
	displaySurviveTime();
	displayPoints();
	EndBatchDraw();//一次性更新到屏幕上
	//移动蛇就是改变蛇的坐标,改变蛇的移动方向，获取键盘按键_getch()
	snake.bodyMove();
	//各种检测
	snakeEatFood();
	snakeStrikeWall();
	snakeHeadStrikeBody();

	
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
void GameSence::snakeStrikeWall()
{
	if (snake.collisionWall())
	{
		std::cout << "撞墙辣！";
		exit(0);
	}

}
void GameSence::snakeHeadStrikeBody()
{
	if (snake.collisionSelf())
	{
		std::cout << "撞到自己辣！";
		exit(1);
	}
}

void GameSence::displaySurviveTime()
{
	time_t currentTime = time(nullptr); // 获取当前时间
	double elapsed = difftime(currentTime, startTime); // 计算存活时间（秒）
	// 转换存活时间为字符串
	TCHAR timeStr[50];
	swprintf_s(timeStr, _T("你存活了:%.0f 秒"), elapsed); // 使用 _stprintf 将 double 类型转换为字符串
	// 设置文本颜色
	settextcolor(WHITE);
	// 设置文本大小
	settextstyle(20, 20, L"微软雅黑");
	// 在屏幕上绘制文本
	outtextxy(100, 100, timeStr);
}

void GameSence::displayPoints()
{
	//读取当前的蛇的节数，算出积分
	int length=snake.getLength()-3;
	// 转换为字符串
	TCHAR lengthstr[50];
	swprintf_s(lengthstr, _T("当前得分:%.0d "), length); // 使用 _stprintf 将 double 类型转换为字符串
	// 设置文本颜色
	settextcolor(LIGHTMAGENTA);
	// 设置文本大小
	settextstyle(20, 20, L"微软雅黑");
	// 在屏幕上绘制文本
	outtextxy(200, 200, lengthstr);
}

void GameSence::showStartScreen() {
	cleardevice(); // 清空屏幕
	setfillcolor(LIGHTCYAN);
	fillrectangle(0, 0, 640, 480); // 填充整个窗口背景
	settextcolor(BROWN); // 设置文字颜色

	settextstyle(40, 30, L"微软"); // 设置文字样式
	wchar_t s0[] = L"欢迎使用贪吃蛇定制版";
	outtextxy(20, 0, s0);

	settextstyle(40, 30, L"微软"); // 设置文字样式
	TCHAR s1[] = _T("请按回车键开始游戏");
	outtextxy(20, 50, s1);

	settextstyle(40, 30, L"微软"); // 设置文字样式
	TCHAR s2[] = _T("按ESC退出游戏");
	outtextxy(20, 90, s2);
}

/*Food methods*/
void Food::draw()
{
	setfillcolor(m_color);
	solidellipse(m_x, m_y, m_x + 10, m_y + 10);//// Draw a filled ellipse without a border
}



int main()
{
	initgraph(640, 480,EX_SHOWCONSOLE);
	srand(time(nullptr));//初始化随机数种子
	GameSence scene;
	scene.showStartScreen();
	ExMessage msg1;
	while (true) {
		if (peekmessage(&msg1, EX_KEY)) {
			if (msg1.message == WM_KEYDOWN) {
				if (msg1.vkcode == VK_RETURN) {
					// 按下 Enter 键，开始游戏
					break;
				}
				else if (msg1.vkcode == VK_ESCAPE) {
					// 按下 Esc 键，退出程序
					std::cout << "你真退啊？.jpg";
					exit(0);
				}
			}
		}
	}

	while (1)
	{
		scene.run();
		Sleep(100);
	}

	return 0;
}