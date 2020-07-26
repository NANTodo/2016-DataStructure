#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct Node //노드 정의
{
	int data;
	struct Node *next;
}Node;

typedef struct Stack //Stack 구조체 정의
{
	Node *top;    //맨 앞 노드(가장 최근에 생성한 노드)
}Stack;

struct stack *all;//전체 리스트
struct stack *minlist;//최소값 리스트
struct stack *getNode(); //노드 생성 함수
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
	now = stack->top;//now를 top으로 설정
	re = now->data;//꺼낼 값은 now의 data로 설정

	stack->top = now->next;//top을 now의 next로 설정
	free(now);//필요없으니 메모리 해제
	return re;
}