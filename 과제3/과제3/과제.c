#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct Node //��� ����
{
	int data;
	struct Node *next;
}Node;

typedef struct Stack //Stack ����ü ����
{
	Node *top;    //�� �� ���(���� �ֱٿ� ������ ���)
}Stack;

struct stack *all;//��ü ����Ʈ
struct stack *minlist;//�ּҰ� ����Ʈ
struct stack *getNode(); //��� ���� �Լ�
struct stack *p(int k);
struct stack pop(Stack *);
int f();
int count = 0;
int c = 0;
int *min;
int mini = 0;

LARGE_INTEGER startpush, endpush;
LARGE_INTEGER Frequency;

int main(void)
{
	
	
	return 0;
}
struct stack *p(int k)
{
	QueryPerformanceCounter(&startpush);
	struct stack *b;
	struct stack *a;
	struct stack *r;
	c = 0;
	count++;
	if (all == NULL)
	{
		b = getNode();
		b->data = k;
		b->next = all;
		all = b;
		a = getNode();
		a->data = k;
		a->next = minlist;
		minlist = a;
		minlist = (int *)malloc(sizeof(int));
		min[mini] = k;
		mini++;
	}
	else
	{
		r = all;
		if (r->data > k)
		{
			a = getNode();
			a->data = k;
			a->next = minlist;
			minlist = a;
			if (min[mini - 1] > min[mini])
			{
				min = (int *)malloc(sizeof(int));
				min[mini] = k;
				mini++;
			}
		}
		b = getNode();
		b->data = k;
		b->next = all;
		all = b;
	}
	QueryPerformanceCounter(&endpush);
	return  all;
}
struct stack *getNode() {

}

int o(Stack *stack, int k)
{
	Node *now;
	int re;
	if (IsEmpty(stack))
	{
		return 0;
	}
	now = stack->top;//now�� top���� ����
	re = now->data;//���� ���� now�� data�� ����

	stack->top = now->next;//top�� now�� next�� ����
	free(now);//�ʿ������ �޸� ����
	return re;
}