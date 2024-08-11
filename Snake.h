#pragma once
#include<iostream>
#include<easyx.h>
#include<ctime>
#include<vector>//˳��� ����  ���˴���Ҫѧϰ��



/*������*/
class Sprite
{
protected:
	int m_x;
	int m_y;
	COLORREF m_color;//COLORREF ��һ�����ڱ�ʾ��ɫ�� 32 λ�������͡������ͨ�� RGB ����������ɫ������������ͼ�λ���
public:
	//Sprite() {};
	Sprite() :Sprite(0, 0) {};//ί�й��캯��
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(RED) {};//ʵ�ʹ��캯��,ʹ���б��ʼ��
	virtual void draw();//�麯������ʹ�û����ָ�������������������ĺ�����������֪��ʵ�ʶ��������
	void moveBy(int x, int y);//ÿ���ƶ���
	bool collision(const Sprite& other);//�ж���ײ
	void changeFoodPos();//�ı�ʳ�����꣨�ߵóԺ�
};

/*���࣬�Ӿ�����̳�*/
class Snake :public Sprite
{
private:
	//���кܶ�ڣ�Ӧ��������洢���ڿڿڿ� 
	std::vector<Sprite> nodes;//�ߵ����нڵ�

public:
	int dir;//��ʾ�ߵķ���
	Snake() :Snake(0, 0) {}
	Snake(int x, int y) :Sprite(x, y), dir(VK_RIGHT)
	{
		//��ʼ��������
		nodes.push_back(Sprite(20, 0));
		nodes.push_back(Sprite(10, 0));
		nodes.push_back(Sprite(0, 0));
	}
	void draw() override;//override �ؼ���������ʽ��֪������һ���麯��������������д�˻����е��麯����
	void bodyMove();//�ߵ������ƶ�
	bool collision(const Sprite& other);//�ж���ײ
	void increment();//������һ��


};
/*ʳ����*/
class Food :public Sprite
{
public:
	Food() :Sprite(0, 0) 
	{
		changeFoodPos();
	}
	void draw()override;
};

/*��Ϸ������*/
class GameSence
{
private:
	Snake snake;
	Food food;
public:
	GameSence() {};
	void run();
	void onMsg(const ExMessage& msg);//��Ӧ��Ϣ�������Ϣ��������Ϣ
	void snakeEatFood();
};

