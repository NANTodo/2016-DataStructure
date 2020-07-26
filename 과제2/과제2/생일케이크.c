#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int *A;
int candleArrayVer1(int n, int k); //ù��° ��� : �迭�� ���ϴ� �Լ�
int candleArrayVer2(int n, int k);	//�ι�° ��� : �迭�� ���ϴ� �Լ�
void buildListArray(int A[], int n);	//�迭 ����
int runSimulationVer1(int A[], int n, int k);	//ù��° ������� ����
int runSimulationVer2(int A[], int n, int k);	//�ι�° ������� ����
int removeAtRank(int rank, int n, int A[]);	//�����Լ�

LARGE_INTEGER startTimeLinked, endTimeLinked;	//���Ḯ��Ʈ �Լ� �ð����ϱ� ���� ��ŸƮ�� ����Ÿ��, simulation�Լ��� ���
LARGE_INTEGER startTimeArray1, endTimeArray1;	//�迭�Լ� ù��° ��� �ð����ϱ� ���� ��ŸƮ�Լ��� ����Ÿ��, simulation �Լ��� ���
LARGE_INTEGER startTimeArray2, endTimeArray2; //�迭�Լ� �ι�° ��� �ð����ϱ� ���� ��ŸƮ�� ����Ÿ��, simulation�Լ��� ���.
LARGE_INTEGER Frequency;	//ms�ʷ� �ð��� ���ϱ� ����

typedef struct node	//���Ḯ��Ʈ 
{
	int elem;	
	struct node* next;
}NODE;

NODE *L;	//���Ḯ��Ʈ L
NODE* getnode();	//����Լ�
int candleLinked(int n, int k);	//���Ḯ��Ʈ�� ���ϴ� �Լ�
NODE* buildListLinked(int n);	//���Ḯ��Ʈ ����
int runSimulationLinked(NODE* L, int n, int k);	// ���Ḯ��Ʈ�� ����
int removeLinked(NODE* L);


int candleArrayVer1(int n, int k) {
	int *A;

	A = (int*)malloc(sizeof(int)*n);	//������ A �����Ҵ�

	buildListArray(A, n);	//build�Լ� ����
	
	return runSimulationVer1(A, n, k);
}

int candleArrayVer2(int n, int k) {
	int *A;

	A = (int*)malloc(sizeof(int)*n);	//������ A �����Ҵ�

	buildListArray(A, n);
	
	return runSimulationVer2(A, n, k);
}

void buildListArray(int A[], int n) {
		//build�Լ��� ���۽ð��� ���.
	int r;

	for (r = 0; r < n; r++) {
		A[r] = r + 1;
	}
	//build�Լ��� ������ �ð��� ���.
}

int removeAtRank(int r, int n, int A[]) {

	int i;
	int data = 0;

	data = A[r];	//data���� A[r]
	for (int i = r + 1; i < n; i++)	//r+!���� n-1���� �ݺ�
		A[i - 1] = A[i];
	n -= 1;	//n�� 1�� ����
	return n;
}


int runSimulationVer1(int A[], int n, int k) {
	QueryPerformanceFrequency(&Frequency);	//frequency ����
	QueryPerformanceCounter(&startTimeArray1);	//ù��° �迭 ��� ��ŸƮŸ�� ���
	int rank = 0, i, N;

	N = n;
	rank = 0;
	while (n >= 1) {	//while�� n�� 1���� ũ�Ŵ� ���� ��
		i = 0;
		while (i < k) {	//i�� k���� ��������
			rank = (rank + 1) % N;	//rank�� rank+1�� �迭�� ũ��� ���� ��������
			if (A[rank] != 0) {	//A[rank]�� 0�� �ƴ϶��
				i += 1;	//i�� 1�� ����
			}
		}
		if (n > 1) {	//n�� 1���� Ŭ���
			A[rank] = 0;	//A[rank]�� 0
			do
				rank = (rank + 1) % N;	//rank�� rank+1�� �迭�� ũ��� ���� ��������
			while (A[rank] == 0);	//A[rank]�� 0�ϵ���
		}
		n -= 1;
	}
	QueryPerformanceCounter(&endTimeArray1);	//ù��° �迭��� ���� Ÿ�� ���
	return A[rank];
}

int runSimulationVer2(int A[], int n, int k) {
	
	QueryPerformanceCounter(&startTimeArray2);	//�ι�° �迭��� ��ŸƮŸ�� ���
	int r = 0;

	r = 0;
	while (n > 1) {	//n�� 1���� Ŭ����
		r = (r + k) % n;	//r�� r+k�� �迭�� ũ��� ���� ��������
		n = removeAtRank(r, n, A);
	}
	QueryPerformanceCounter(&endTimeArray2);	//�ι�° �迭��� ����Ÿ�� ���
	return A[0];
	
}

NODE *getnode() {	//node �����
	NODE* node;
	node = (NODE*)malloc(sizeof(NODE));
	node->elem = NULL;
	node->next = NULL;
	return node;
}

int removeLinked(NODE* L) {	//Node ����
	NODE* temp;
	int nTemp;
	
	temp = L;	//���Ḯ��Ʈ temp�� L����.
	nTemp = L->elem;	//ntemp���� L��elem�� ����.
		
	while (temp->next != L) {
		temp = temp->next;	//temp ������ �̵�
	}
	temp->next = L->next;	//�̵��� ���� L�� �̵��� ����
	free(L);	//L�� ������

	return nTemp;
}

int candleLinked(int n, int k) {

	NODE* L = buildListLinked(n);
	return runSimulationLinked(L, n, k);
}
NODE* buildListLinked(int n) {	//build�Լ�

	int i;
	NODE* p;
	NODE* L;

	p = getnode();
	L = p;
	p->elem = 1;

	for (i = 2; i <= n; i++) {
		p->next = getnode();	//p->next�� getnode()��
		p = p->next;	//p�� �̵�
		p->elem = i;	//p�� ������ҿ� i
	}
	p->next = L;
	return L;
}

int runSimulationLinked(NODE* L, int n, int k) {
	
	QueryPerformanceCounter(&startTimeLinked);	//���Ḯ��Ʈ �Լ� ��ŸƮŸ�� ���
	int i;
	NODE* p;

	p = L;

	while (p != p->next) {	//p�� p�� ������尡 �ƴҶ�
		for (i = 1; i < k; i++) {
			p = p->next;	//p�� �̵�
		}
		removeLinked(p->next);
		p = p->next;	//p�� �̵�
	}
	QueryPerformanceCounter(&endTimeLinked);	//���Ḯ��Ʈ �Լ� ����Ÿ�� ���
	return p->elem;
	
}

void main() {
	int n[] = { 31, 33, 10000 };
	int k[] = { 5, 59, 100 };
	int i;
	QueryPerformanceFrequency(&Frequency);	//frequency ����

	for (i = 0; i < 2; i++) {
		printf("�迭����1: (n = %d, k = %d) ���� ��ġ = %d\n", n[i], k[i], candleArrayVer1(n[i], k[i]));

		printf("�迭����2: (n = %d, k = %d) ���� ��ġ = %d\n", n[i], k[i], candleArrayVer2(n[i], k[i]));

		printf("�������:  (n = %d, k = %d) ���� ��ġ = %d\n", n[i], k[i], candleLinked(n[i], k[i]));
		printf("\n");
	}
	if (i = 2) {

		printf("�迭����1: (n = %d, k = %d) ���� ��ġ = %d ����ð� = %lf\n", n[2], k[2], candleArrayVer1(n[2], k[2]), (double)(endTimeArray1.QuadPart - startTimeArray1.QuadPart) / Frequency.QuadPart);

		printf("�迭����2: (n = %d, k = %d) ���� ��ġ = %d ����ð� = %lf\n", n[2], k[2], candleArrayVer2(n[2], k[2]), (double)(endTimeArray2.QuadPart - startTimeArray2.QuadPart) / Frequency.QuadPart);

		printf("�������:  (n = %d, k = %d) ���� ��ġ = %d ����ð� = %lf\n", n[2], k[2], candleLinked(n[2], k[2]), (double)(endTimeLinked.QuadPart - startTimeLinked.QuadPart) / Frequency.QuadPart);
	}
	return 0;
}


