#include"Snake.h"
/*Ŀǰ�Ѿ�ʵ�ֻ������ܣ�������Ҫ����
1���������ܵ�ǽ���ѽ������ײǽ����(�ѽ����,����ǽ����ɫ���ѽ����
2: ͷײ����Ҳ��(�ѽ��)
3�����ӻ��ֹ��򣬰��մ��ʱ��ͳ��������
4��Сbug:ʳ���п��ܳ���ǽ��(���޸�)
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
	int tem_x;
	int tem_y;
	int wallData[64][48] = { 0 };
	tem_x = rand() % 64 * 10;//��֤������10�ı������������ܳԵ�
	tem_y = rand() % 48 * 10;
	//��һ�������ǽ��λ��װ��
	// �����ϱ�ǽ
	for (int i = 0; i < 64; ++i) {
		wallData[i][0] = 1;
	}

	// �����±�ǽ
	for (int i = 0; i < 64; ++i) {
		wallData[i][48 - 1] = 1;
	}

	// �������ǽ
	for (int i = 0; i < 48; ++i) {
		wallData[0][i] = 1;
	}

	// �����ұ�ǽ
	for (int i = 0; i < 48; ++i) {
		wallData[64 - 1][i] = 1;
	}
	//���ʳ�ﳤ��ǽ�ϣ���������ʳ��
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
		nodes[i].draw();//������sprite��draw
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
	wall.setWall();
	snake.draw();
	food.draw();
	EndBatchDraw();//һ���Ը��µ���Ļ��
	//�ƶ��߾��Ǹı��ߵ�����
	snake.bodyMove();
	//�ı��ߵ��ƶ����򣬻�ȡ���̰���_getch()

	//���ּ��
	snakeEatFood();
	snakeStrikeWall();
	snakeHeadStrikeBody();

	
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
void GameSence::snakeStrikeWall()
{
	if (snake.collisionWall())
	{
		std::cout << "ײǽ����";
		exit(0);
	}

}
void GameSence::snakeHeadStrikeBody()
{
	if (snake.collisionSelf())
	{
		std::cout << "ײ���Լ�����";
		exit(1);
	}
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
	srand(time(nullptr));//��ʼ�����������
	GameSence scene;

	while (1)
	{
		scene.run();
		Sleep(100);
	}

	return 0;
}