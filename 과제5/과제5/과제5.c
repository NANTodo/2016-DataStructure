#include <stdio.h>
#include <stdlib.h>

typedef struct Node {	//����Ʈ�� ��� ����ü
	struct Node* left;	//���� �ڽ� ���
	struct Node* right;	//������ �ڽ� ���
}Node;

typedef struct roman { //isEmperor()���� ����ϱ� ���� �θ��Լ����ο� �ڽ��� ũ������ ���� ����ü
	int isroman, issize;
}roman;

Node* initTree();	//����Ʈ�� ����� �Լ�
roman* isEmperor(Node *root);	//Ȳ����� ã�� �Լ�
Node** makequeue(int*, int*);	//���ο� ť ����
void enqueue(struct node **, int *, struct node*);	//ť �߰��Է�
Node *dequeue(struct node **, int *);	//ť ����


Node ** makequeue(int *front, int *rear) {
	Node **queue = (Node **)malloc(sizeof(struct node*) * 500);	//queue�� �޸��Ҵ�
	*front = *rear = 0;	//queue�� ó���� ���� 0
	return queue;
}

void enqueue(struct node **queue, int *rear, Node *new) {	//ť �߰��Է�
	queue[*rear] = new;	//queue[��(ũ��)] ���� �ۼ�
	(*rear)++;	//����
}

Node *dequeue(Node **queue, int *front) {	//ť ����
	(*front)++;
	return queue[*front - 1];
}

Node* initTree() {	//����Ʈ������

	int i;
	Node* node[29];	//���� ���� 29��.

	for (i = 0; i < 29; i++) {
		node[i] = (Node*)malloc(sizeof(Node));//for�� ����Ͽ� node�� ���� �޸��Ҵ��Ű��.
		node[i]->left = NULL;
		node[i]->right = NULL;
	}

	node[0]->left = node[1];
	node[1]->left = node[3];
	node[3]->left = node[7];
	node[7]->left = node[13];
	node[7]->right = node[14];
	node[14]->left = node[23];
	node[14]->right = node[24];
	node[24]->right = node[25];
	node[24]->left = node[26];
	node[25]->left = node[27];
	node[25]->right = node[28];
	node[3]->right = node[8];
	node[1]->right = node[4];
	node[4]->left = node[9];
	node[4]->right = node[10];
	node[9]->left = node[15];
	node[9]->right = node[16];
	node[10]->left = node[17];
	node[10]->right = node[18];
	node[0]->right = node[2];
	node[2]->left = node[5];
	node[2]->right = node[6];
	node[6]->right = node[12];
	node[12]->right = node[22];
	node[11]->right = node[20];
	node[6]->left = node[11];
	node[11]->left = node[19];
	node[12]->left = node[21];
	//Ʈ�� ����

	return node[0]; //root��� ��ȯ
}

roman* isEmperor(Node* root) {	//Ȳ����� ���ϱ�

	roman *A = (roman *)malloc(sizeof(roman));
	roman *B = (roman *)malloc(sizeof(roman));
	roman *C = (roman *)malloc(sizeof(roman));

	if ((root->left == NULL) && (root->right == NULL)) {	//��忡�� �ڽ��� ���°��(root)
		C->isroman = 1;	//roman C�� isroman�� 1����
		C->issize = 1;	//roman C�� issize�� 1 ���� (��Ʈ���� ũ�Ⱑ 1)
		return C;
	}
	else {	//���γ���ΰ��
		if (root->left != NULL)	//����� ������ 0�� �ƴѰ��
			A = isEmperor(root->left);	//A�� ����Ű�� �ٴ� ����� ������ isEmperor�� ������ ��
		else {	//0�ΰ��
			A->isroman = 1;
			A->issize = 0;
		}
		if (root->right != NULL)	//����� �������� 0�� �ƴ� ���
			B = isEmperor(root->right);	//B�� ����Ű�� �ٴ� ����� �������� isEmperor�� ������ ��
		else {	//0�ΰ��
			B->isroman = 1;
			B->issize = 0;
		}
		if (((-5 <= ((A->issize) - (B->issize))) && ((A->issize) - (B->issize)) <= 5) && ((A->isroman == 1) || (B->isroman == 1)))
			//A�� B�� ũ�����̰� 5�̳��� ����� �����ʵ� ���ʵ� Ȳ����尡 �ƴѰ��
			C->isroman = 1;
		else
			C->isroman = 0;
		C->issize = (A->issize) + (B->issize) + 1;

		return C;
	}
}

int main() {
	int cnt = 0, e_cnt = 0;	//����, Ȳ����� Ƚ��
	int rear, front, i;
	int cnt1 = 1, cnt2;

	Node* root;
	root = initTree();	//rootƮ�� ����

	Node **queue = makequeue(&front, &rear);
	Node *temp = root;	//temp �ӽ÷� ����. ������ root�� ����

	while (temp) {

		while ((temp->left != NULL) && (temp->right != NULL)) {
			cnt2 = 0;

			for (i = 0; i < cnt1; i++) {
				cnt++;
				if (temp->left) {
					enqueue(queue, &rear, temp->left);	//ť �Է�
					cnt2++;
				}

				if (temp->right) {
					cnt2++;
					enqueue(queue, &rear, temp->right);	//ť �Է�
				}

				temp = dequeue(queue, &front); //temp ť ����

			}
			cnt1 = cnt2;
			isEmperor(temp);	//temp���� Ȳ����� ã��
			if ((isEmperor(temp)->isroman) == 0) {	//roman C�� isroman�� 0�̶��
				printf("%d			Ȳ�����\n", cnt);
				e_cnt++;	//Ȳ����� ���� �߰�
			}
		}
		break;
	}
	printf("�湮�� ���γ�� �� %d��, Ȳ����� �� %d��\n", cnt+1, e_cnt);//cnt�� root���� �ٸ� ���γ����� ���� Ƚ���� root�� ���� ���Ͽ��⿡ +1 �Ѵ�.
	return 0;
}

