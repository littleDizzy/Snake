#pragma once
#include<iostream>
#include<easyx.h>
#include<ctime>
#include<vector>//顺序表 容器  ！此处需要学习！



/*精灵类*/
class Sprite
{
protected:
	int m_x;
	int m_y;
	COLORREF m_color;//COLORREF 是一个用于表示颜色的 32 位整数类型。你可以通过 RGB 宏来定义颜色，并将其用于图形绘制
public:
	//Sprite() {};
	Sprite() :Sprite(0, 0) {};//委托构造函数
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(RED) {};//实际构造函数,使用列表初始化
	virtual void draw();//虚函数允许使用基类的指针或引用来调用派生类的函数，而无需知道实际对象的类型
	void moveBy(int x, int y);//每次移动量
	bool collision(const Sprite& other);//判断碰撞
	void changeFoodPos();//改变食物坐标（蛇得吃后）
};

/*蛇类，从精灵类继承*/
class Snake :public Sprite
{
private:
	//蛇有很多节，应该用数组存储它口口口口 
	std::vector<Sprite> nodes;//蛇的所有节点

public:
	int dir;//表示蛇的方向
	Snake() :Snake(0, 0) {}
	Snake(int x, int y) :Sprite(x, y), dir(VK_RIGHT)
	{
		//初始化三节蛇
		nodes.push_back(Sprite(20, 0));
		nodes.push_back(Sprite(10, 0));
		nodes.push_back(Sprite(0, 0));
	}
	void draw() override;//override 关键字用于显式告知编译器一个虚函数在派生类中重写了基类中的虚函数。
	void bodyMove();//蛇的身体移动
	bool collision(const Sprite& other);//判断碰撞
	void increment();//蛇增加一节


};
/*食物类*/
class Food :public Sprite
{
public:
	Food() :Sprite(0, 0) 
	{
		changeFoodPos();
	}
	void draw()override;
};

/*游戏场景类*/
class GameSence
{
private:
	Snake snake;
	Food food;
public:
	GameSence() {};
	void run();
	void onMsg(const ExMessage& msg);//响应消息：鼠标消息，键盘消息
	void snakeEatFood();
};

