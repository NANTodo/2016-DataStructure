#include <stdio.h>
#include <stdlib.h>
#include <windows.h>	 //QueryPerformanceFrequency()
float* SlowprefixAverages(int n, int *X, float *A);		//���������� �Լ�
float* FastprefixAverages(int n, int *X, float *A);		//���������� �Լ�

int main() {
	int n[3] = { 100000, 200000, 300000 };	//�����ؾ��ϴ� n�� �� ���� �迭�� ����
	int i;	//for()
	int *X;		//
	float *A;	//
	LARGE_INTEGER Frequency;	//QueryPerformanceFrequency()�� ����ϱ����� �� ����
	LARGE_INTEGER startTime, endTime;	//QueryPerformanceFrequency()�� ����ϱ����� ���۽ð��� ����ð� ����

	for (i = 0; i < 3; i++) {	//n = �ʸ�, �̽ʸ�, ��ʸ����� ����������
		A = (float *)malloc(sizeof(float) * n[i]);	//������ A�� �����Ҵ�
		X = (int *)malloc(sizeof(int) * n[i]);	 //������ X�� �����Ҵ�

		srand((unsigned int)time(NULL)); //�����߻�	
		QueryPerformanceFrequency(&Frequency); //ms�������� �˷��ִ� �ð������Լ�

		QueryPerformanceCounter(&startTime);	//�������� �Լ� �������� �ð�����
		SlowprefixAverages(n[i], X, A);		//�������� �Լ� ����
		QueryPerformanceCounter(&endTime);	//�Լ� ���� ���� �ð� ����
		printf("n�� ���� %d�� ��� slow ����ð� : %f��\n", n[i], (double)(endTime.QuadPart - startTime.QuadPart) / Frequency.QuadPart);

		QueryPerformanceCounter(&startTime);	//�������� �Լ� �������� �ð�����
		FastprefixAverages(n[i], X, A);		//�������� �Լ� ����
		QueryPerformanceCounter(&endTime);	//�Լ� ���� ���� �ð� ����
		printf("n�� ���� %d�� ��� fast ����ð� : %lf��\n", n[i], (double)(endTime.QuadPart - startTime.QuadPart) / Frequency.QuadPart);

		printf("\n\n");
	}
	return 0;
}
float* SlowprefixAverages(int n, int *X, float *A) {	//���� ����

	int i, j;
	float sum = 0.0;

	for (i = 0; i < n; i++) {
		sum++;
		for (j = 0; j < i; j++)
			sum += X[j];
		A[i] = sum / (float)(i + 1);
	}
	return A;
}	//slow

float* FastprefixAverages(int n, int *X, float *A) {	//���� ����

	int i;
	float sum = 0.0;

	for (i = 0; i < n; i++) {
		sum += X[i];
		A[i] = sum / (float)(i + 1);
	}

	return A;
}	//fast