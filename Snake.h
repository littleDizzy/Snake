#pragma once
#include<iostream>
#include<easyx.h>//��ͼ��
#include<ctime>
#include<vector>//˳����˴���Ҫѧϰ������py��list



/*������*/
class Sprite
{
protected:
	int m_x;
	int m_y;
	COLORREF m_color;//COLORREF ��һ�����ڱ�ʾ��ɫ�� 32 λ�������͡������ͨ�� RGB ����������ɫ������������ͼ�λ���
public:
	//Sprite() {};
	Sprite() :Sprite(0, 0,RED) {};//ί�й��캯��
	Sprite(int x, int y, COLORREF mycolor=RED) :m_x(x), m_y(y), m_color(mycolor) {};//ʵ�ʹ��캯��,ʹ���б��ʼ��
	virtual void draw();//�麯������ʹ�û����ָ�������������������ĺ�����������֪��ʵ�ʶ��������
	void moveBy(int x, int y);//ÿ���ƶ���
	bool collision(const Sprite& other);//�ж���ײ
	void changeFoodPos();//�ı�ʳ�����꣨�ߵóԺ�
	int getX() const { return m_x; }
	int getY() const { return m_y; }
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
		nodes.push_back(Sprite(30, 10));
		nodes.push_back(Sprite(20, 10));
		nodes.push_back(Sprite(10, 10));
	}
	void draw() override;//override �ؼ���������ʽ��֪������һ���麯��������������д�˻����е��麯����
	void bodyMove();//�ߵ������ƶ�
	bool collision(const Sprite& other);//�ж���ײ
	bool collisionWall();//�ж���ײǽ,���ڿ��Ǹĳ�collision������
	bool collisionSelf();//�ж���ײ�Լ�,���ڿ��Ǹĳ�collision������
	void increment();//������һ��
	int getLength();



};
/*ʳ����*/
class Food :public Sprite
{
public:
	Food() :Sprite(0, 0,YELLOW) 
	{
		changeFoodPos();
	}
	void draw()override;

};

/*ǽ��*/
class Wall :public Sprite
{
public:
	Wall() :Sprite(0, 0, LIGHTGRAY) {}
	//void draw() override;
	void setWall();//����ǽ�Ĵ�С���
};

/*��Ϸ������*/
class GameSence
{
private:
	Snake snake;
	Food food;
	Wall wall;
	time_t startTime; // ��Ϸ��ʼʱ��
public:
	GameSence() 
	{
		startTime = time(nullptr);
	};
	void run();
	void onMsg(const ExMessage& msg);//��Ӧ��Ϣ�������Ϣ��������Ϣ 
	void snakeEatFood();
	void snakeStrikeWall();
	void snakeHeadStrikeBody();
	void displaySurviveTime();
	void displayPoints();
	void showStartScreen();
};

