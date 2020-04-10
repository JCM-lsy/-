//2.7 ��Ŀ7 �ƶ�С��90�֣�
//����һЩС�򣬴��������α��Ϊ1, 2, 3, 4����n��
//������ָ�
//A X Y ��ʾ��С��X�ƶ���С��Y��ߣ�B X Y ��ʾ��С��X �ƶ���С�� Y �ұߡ�
//ָ�֤�Ϸ�����X������Y��(��ʱ��Ļ����Լ�һ���쳣����)
//
//����������
//��һ����С�����n
//�ڶ�����ָ��ĸ���m
//������m��ÿ��һ��ָ��
//
//���������
//���������С�����������
//
//�������룺
//6 2
//A 1 4
//B 3 5
//
//���������
//2 1 4 5 3 6
#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node *next;
	Node *prior;
};
class ball                               //����һ��˫������
{
private:
	Node *front;                         //ͷָ����βָ��
	Node *rear;
	int length;
public:
	ball(int n);
	void moveA(int x, int y);
	void moveB(int x, int y);
	void print();
	~ball();
};
ball::ball(int n)                        //���ι��캯��������1~n��˳���ʼ��ÿ��С���ֵ
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
void ball::moveB(int x, int y)//��С��X�ƶ���С���ұ�
{
	//���Ȱ�ֵ����С��x��y���˴������԰�λ�ò��ң���Ϊֻ�г�ʼ״̬��С���ǰ�˳��ڷŵ�
	Node *p = front->next;
	Node *q = front->next;
	while (p->data != x) { p = p->next; }
	while (q->data != y) { q = q->next; }           //��ʱp��qָ��˳��ָ���˽�Ҫ�ƶ���С��x����Ŀ��y
	//���Ȱ�С��xȡ��
	p->next->prior = p->prior;//x��һ������priorָ��xǰһ�����
	p->prior->next = p->next; //xǰһ������nextָ��x��һ����㣬��ʱxС��ȡ��
	//������y����߲���x
	p->next = q->next;//x��nextָ��ָ��y����һ�����
	p->prior = q;//x��priorָ��ָ��y
	p->next->prior = p;//y����һ���ڵ��priorָ��x
	p->prior->next = p;//y��nextָ��ָ��x��xС�򱻳ɹ��嵽y�����
}
void ball::moveA(int x, int y)//��С��X�ƶ���С��Y��ߣ�ԭ��ͬ��
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
	cout << s->data << endl;//Ϊ�����һ�����ֺ�����ո���ı�ѧУ��OJ������
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