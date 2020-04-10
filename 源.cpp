//2.7 题目7 移动小球（90分）
//你有一些小球，从左到右依次编号为1, 2, 3, 4……n。
//有两种指令。
//A X Y 表示把小球X移动到小球Y左边，B X Y 表示把小球X 移动到小球 Y 右边。
//指令保证合法，即X不等于Y。(有时间的话可以加一个异常处理)
//
//输入描述：
//第一行是小球个数n
//第二行是指令的个数m
//接下来m行每行一条指令
//
//输出描述：
//从左到右输出小球的最终序列
//
//样例输入：
//6 2
//A 1 4
//B 3 5
//
//样例输出：
//2 1 4 5 3 6
#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node *next;
	Node *prior;
};
class ball                               //定义一个双向链表
{
private:
	Node *front;                         //头指针与尾指针
	Node *rear;
	int length;
public:
	ball(int n);
	void moveA(int x, int y);
	void moveB(int x, int y);
	void print();
	~ball();
};
ball::ball(int n)                        //含参构造函数，按照1~n的顺序初始化每个小球的值
{
	front = new Node;
	front->next = front;
	front->prior = NULL;
	front->data = 0;
	rear = front;
	length = 0;
	for (int i = 1; i < n+1; i++)
	{
		Node *s = new Node;
		s->data = i;
		s->prior = rear;
		s->next =rear->next;
		rear->next = s;
		rear = s;
		length++;
	}
}
void ball::moveB(int x, int y)//把小球X移动到小球右边
{
	//首先按值查找小球x，y，此处不可以按位置查找，因为只有初始状态下小球是按顺序摆放的
	Node *p = front->next;
	Node *q = front->next;
	while (p->data != x) { p = p->next; }
	while (q->data != y) { q = q->next; }           //此时p、q指针顺利指向了将要移动的小球x，与目标y
	//首先把小球x取出
	p->next->prior = p->prior;//x后一个结点的prior指向x前一个结点
	p->prior->next = p->next; //x前一个结点的next指向x后一个结点，此时x小球被取出
	//下面在y的左边插入x
	p->next = q->next;//x的next指针指向y的下一个结点
	p->prior = q;//x的prior指针指向y
	p->next->prior = p;//y的下一个节点的prior指向x
	p->prior->next = p;//y的next指针指向x，x小球被成功插到y的左侧
}
void ball::moveA(int x, int y)//把小球X移动到小球Y左边，原理同上
{
	Node *p = front->next;
	Node *q = front->next;
	while (p->data != x) { p = p->next; }
	while (q->data != y) { q = q->next; }
	p->next->prior = p->prior;
	p->prior->next = p->next;
	p->next = q;
	p->prior = q->prior;
	q->prior = p;
	p->prior->next = p;
}
void ball::print()
{
	Node *s = front->next;
	while (s!=rear)
	{
		cout << s->data << " ";
		s = s->next;
	}
	cout << s->data << endl;//为了最后一个数字后不输出空格，真的被学校的OJ整怕了
}
ball::~ball()
{
	Node *p = front;
	for (int i = 0; i < length-1; i++)
	{
		p = front->next;
		cout << "xigou" << endl;
		delete front;
		front = p;
	}
	rear = NULL;
}
int main()
{
	int m, n;
	cin >> m >> n;
	ball b(m);
	for (int i = 0; i < n; i++)
	{
		char c;
		int x, y;
		cin >> c>> x >> y;
		switch (c)
		{
		case'A':
			b.moveA(x, y);
			break;
		case'B':
			b.moveB(x, y);
		default:
			break;
		}
	}
	b.print();
	b.~ball();
}