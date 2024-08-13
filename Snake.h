#pragma once
#include<iostream>
#include<easyx.h>//画图库
#include<ctime>
#include<vector>//顺序表，此处需要学习！类似py的list



/*精灵类*/
class Sprite
{
protected:
	int m_x;
	int m_y;
	COLORREF m_color;//COLORREF 是一个用于表示颜色的 32 位整数类型。你可以通过 RGB 宏来定义颜色，并将其用于图形绘制
public:
	//Sprite() {};
	Sprite() :Sprite(0, 0,RED) {};//委托构造函数
	Sprite(int x, int y, COLORREF mycolor=RED) :m_x(x), m_y(y), m_color(mycolor) {};//实际构造函数,使用列表初始化
	virtual void draw();//虚函数允许使用基类的指针或引用来调用派生类的函数，而无需知道实际对象的类型
	void moveBy(int x, int y);//每次移动量
	bool collision(const Sprite& other);//判断碰撞
	void changeFoodPos();//改变食物坐标（蛇得吃后）
	int getX() const { return m_x; }
	int getY() const { return m_y; }
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
		nodes.push_back(Sprite(30, 10));
		nodes.push_back(Sprite(20, 10));
		nodes.push_back(Sprite(10, 10));
	}
	void draw() override;//override 关键字用于显式告知编译器一个虚函数在派生类中重写了基类中的虚函数。
	void bodyMove();//蛇的身体移动
	bool collision(const Sprite& other);//判断碰撞
	bool collisionWall();//判断碰撞墙,后期考虑改成collision的重载
	bool collisionSelf();//判断碰撞自己,后期考虑改成collision的重载
	void increment();//蛇增加一节
	int getLength();



};
/*食物类*/
class Food :public Sprite
{
public:
	Food() :Sprite(0, 0,YELLOW) 
	{
		changeFoodPos();
	}
	void draw()override;

};

/*墙类*/
class Wall :public Sprite
{
public:
	Wall() :Sprite(0, 0, LIGHTGRAY) {}
	//void draw() override;
	void setWall();//设置墙的大小宽度
};

/*游戏场景类*/
class GameSence
{
private:
	Snake snake;
	Food food;
	Wall wall;
	time_t startTime; // 游戏开始时间
public:
	GameSence() 
	{
		startTime = time(nullptr);
	};
	void run();
	void onMsg(const ExMessage& msg);//响应消息：鼠标消息，键盘消息 
	void snakeEatFood();
	void snakeStrikeWall();
	void snakeHeadStrikeBody();
	void displaySurviveTime();
	void displayPoints();
	void showStartScreen();
};

