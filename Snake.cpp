#include"Snake.h"
/*Ŀǰ�Ѿ�ʵ�ֻ������ܣ�������Ҫ����
1���������ܵ�ǽ��ײǽ����
2�����ӻ��ֹ��򣬰��մ��ʱ��ͳ��������
*/



/*Sprite method*/
void Sprite::draw()
{
	//���������ɫ
	setfillcolor(m_color);
	//���ƾ���
	fillrectangle(m_x, m_y, m_x + 10, m_y + 10);//�ĸ��������ֱ��ʾ���ε����Ͻǵ����½ǵ�����
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
	m_x = rand() % 64 * 10;//��֤������10�ı������������ܳԵ�
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
	case VK_UP://vkcode���ϼ��ķ���ֵ�ĺ궨��
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
	//����м�����Ϣ
	if (msg.message == WM_KEYDOWN)//msg.messageΪ��Ϣ���ͣ�WM_KEYDOWN��Ӧ����
	{
		//�жϾ��尴��virtual code �������
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
	//˫�����ͼ
	BeginBatchDraw(); //˫�����ͼ��һ�ּ���ͼ����˸����߻������ܵļ��������Ļ���˼����ʹ��һ�������ڴ滺��
	cleardevice();
	snake.draw();
	food.draw();
	EndBatchDraw();//һ���Ը��µ���Ļ��
	//�ƶ��߾��Ǹı��ߵ�����
	snake.bodyMove();
	//�ı��ߵ��ƶ����򣬻�ȡ���̰���_getch()
	snakeEatFood();
	//��ȡ��Ϣ
	ExMessage msg = { 0 };
	while (peekmessage(&msg, EX_KEY))//�������Ϣ
	{
		onMsg(msg);
	} 

}
void GameSence::snakeEatFood()
{
	if (snake.collision(food))
	{
		//�Ե�ʳ���������
		snake.increment();
		//�ߵóԺ�ʳ��ı�λ��
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
	srand(time(nullptr));//��ʼ�����������
	GameSence scene;

	while (1)
	{
		scene.run();
		Sleep(100);
	}

	return 0;
}