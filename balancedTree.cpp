

#include <stdlib.h>
#include <stdio.h>

#include "Profiler.h"

Profiler p("balanced_tree");

struct Node {
	int data;
	int size;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};


Node* buildTree( int inceput, int final,int a[]) {
	if (inceput > final)
		return NULL;

	Node* x= (Node*)calloc(1, sizeof(Node));
	x->data = a[(inceput + final) / 2];// ma duc pe jumatate din sir
	x->left = buildTree( inceput, (inceput + final) / 2 - 1,a);//construiesc stanga 
	x->right = buildTree((inceput + final) / 2 + 1, final,a);//construiesc dreapta
	if (NULL != x->left) {
		x->left->parent = x;
		x->size =x->size+ x->left->size + 1;//atata timp cat ma duc pe stanga cresc rangu // la fel pe dreapta
	}
	if (NULL != x->right) {
		x->right->parent = x;
		x->size = x->size+x->right->size + 1;
	}
	return x;
}

Node* OS_SELECT(Node* x, int i, int n, char s[]) {
	p.countOperation(s,n,1);
	int r;
	if (x == NULL)
		return NULL;
	p.countOperation(s,n,2);
	if (x->left != NULL)//daca nu am null ma duc in adancime si cresc rangul fiecarui nod din arborele meu
		 r = x->left->size + 2;
	else
		 r = 1;
	if (r == i)
		return x;//daca rangul corespunde returnez nodul cu indicele i
	else 
		if (i < r)
			return OS_SELECT(x->left, i, n, s);//daca nu ma duc pe sub arborele stang sau dreapta
		else 
			return OS_SELECT(x->right, i - r, n, s);
}
void OS_DELETE( Node* &x, int rang,int n,char s[]) {
	p.countOperation(s, n, 1);
	Node* q = OS_SELECT(x,rang,n,s);
	p.countOperation(s, n, 1);
	if (NULL == q) //verific radacina sa nu fie null 
		return;
	p.countOperation(s, n, 1);//intram pe arbore in nodul din os select
	if (q == x) {
		p.countOperation(s, n, 2);
		if (q->left == NULL && q->right == NULL) {//verificam fii 
			p.countOperation(s, n, 1);
			free(q);
			 x= NULL;
			return;
		}
		else 
			if (q->left == NULL) {//nu avem copil pe stanga
				//mergem pe dreapta
				p.countOperation(s,n,2);
				x = x->right;
				x->parent = NULL;
				//printf("%d ", q->data);
				free(q);
				return;
			}
			else 
				if (q->right == NULL) {//nu avem copil pe dreapta
					//mergem pe stanga
					p.countOperation(s, n, 2);
					x= x->left;
					x->parent = NULL;
					//printf("%d ", q->data);
					free(q);
					return;
				}

				else
					goto cazRau;
	}

	
	p.countOperation(s, n, 2);
	if (q->left == NULL && q->right == NULL) {//stergere propriu zisa a unui copil
		p.countOperation(s, n, 1);
		if (q->parent->right == q) {
			p.countOperation(s, n, 1);
			q->parent->right = NULL;
		}
		else {
			p.countOperation(s,n,1);
			q->parent->left = NULL;
		}

		//de jos in sus repar pentru fiecare nod pe care am venit ca sa sterg copilul
		Node* repar = q;
		while (repar != x ){
			repar = repar->parent;
			repar->size--;
		}

		//printf("%d ", q->data);
		free(q);
		return;
	}

	//stergere copil drept 
	p.countOperation(s, n, 1);
	if (q->left == NULL) { //daca am copil doar pe dreapta
		p.countOperation(s, n, 1);
		if (q->parent->right == q) {
			p.countOperation(s, n, 1);
			q->parent->right = q->right;
		}
		else {
			p.countOperation(s, n, 1);
			q->parent->left = q->right;
		}
		q->right->parent = q->parent;
		p.countOperation(s, n, 1);
		//acuma repar din nou de jos in sus si repar 
		Node* repar = q;
		while (repar != x) {
			repar = repar->parent;
			repar->size--;
		}
		free(q);
		return;
	}

	//stergere copil stang
	p.countOperation(s, n, 1);
	//daca am copil doar pe stanga
	if (q->right == NULL) {
		p.countOperation(s, n, 1);
		if (q->parent->left == q) {
			p.countOperation(s, n, 1);
			q->parent->left = q->left;
		}
		else {
			p.countOperation(s, n, 1);
			q->parent->right = q->left;
		}
		q->left->parent = q->parent;
		p.countOperation(s, n, 1);
		//iar repar de jos in sus pe traseul pe care am venit
		Node* repar = q;
		while (repar != x) {
			repar = repar->parent;
			repar->size--;
		}
		free(q);
		return;
	}
	cazRau:
	//am si copil pe dreapta si copil pe stanga respectiv sub arbore drept si sub arbore stang
	Node* aux = OS_SELECT(q->right, 1, n, s);
	p.countOperation(s,n,1);
	//imi iau un nod auxiliar sa zicem cel din dreapta nodului pe care vreau sa il sterg
	//parcurg arborele de jos in sus pe fiecare ramura
	Node* repar = aux;
	while (repar!= x) {
		repar = repar->parent;
		repar->size--;
	}
	//pt aux
	p.countOperation(s,n,1);
	if (NULL != aux->right) {//cat timp ma duc pe dreapta caut minimul
		p.countOperation(s,n,1);
		if (aux->parent->left == aux) {
			p.countOperation(s,n,2);
			aux->parent->left = aux->right;
			aux->right->parent = aux->parent;
		}
		else {
			p.countOperation(s,n,2);
			aux->parent->right = aux->right;
			aux->right->parent = aux->parent;
		}
	}
	else {//cat timp ma duc pe stanga ma duc si caut maximul
		p.countOperation(s,n,1);
		if (aux->parent->left == aux) {
			p.countOperation(s,n,1);
			aux->parent->left = NULL;
		}
		else {
			p.countOperation(s,n,1);
			aux->parent->right = NULL;
		}
	}
	//interschimb  nodul sters cu nodul parinte
	p.countOperation(s,n,1);
	aux->parent = q->parent;
	p.countOperation(s,n,1);
	if (q->parent != NULL) {//verific sa nu ies din arbore cand parcurg invers
		p.countOperation(s,n,1);
		if (q->parent->left == q) {//daca sunt pe nodul bun interschimb nodul cu cel de dinainte
			p.countOperation(s,n,1);
			q->parent->left = aux;
		}
		else {
			p.countOperation(s,n,1);
			q->parent->right = aux;
		}
	}
	aux->size = q->size;//actualizez rangul nodului auxiliar cu cel modificat

	p.countOperation(s,n,2);
	if (q->left != NULL && q->left != aux) {
		p.countOperation(s,n,2);
		q->left->parent = aux;
		aux->left = q->left;
	}
	else {
		aux->left = NULL;
		p.countOperation(s,n,1);
	}

	p.countOperation(s,n,2);
	if (q->right != NULL && q->right != aux) {
		p.countOperation(s,n,2);
		q->right->parent = aux;
		aux->right = q->right;
	}
	else {
		p.countOperation(s,n,1);
		aux->right = NULL;
	}

	p.countOperation(s,n,1);
	if (x == q)
		x = aux;
	free(q);
	
	
}


void print(Node* root, int space)
{//prety print
	if (root == NULL)
		return;
	space =space+10;
	print(root->right, space);
	printf("\n");
	for (int i = 10; i < space; i++)
		printf(" ");
	if (root->data != -1)
		printf("%d", root->data);
	printf("\n");
	print(root->left, space);
}

void mediu() {
	char s[2][7] = { "select","delete" };
	for (int n = 500; n <= 10000; n = n + 500) {
		int* a = (int*)calloc(n, sizeof(int));
		FillRandomArray(a, n, 0, 10000, true, ASCENDING);
		Node* x = buildTree(0, n - 1, a);
		for (int i=n; i>=1; i--) {
			int r = rand()%i + 1;
			printf("Se sterge %d \n", OS_SELECT(x, r, n, s[0])->data);
			OS_DELETE(x,r, n, s[1]);
		}
		if (x != NULL)
			free(x);
		free(a);
		
	}
	p.createGroup("Opera", s[0], s[1]);
	p.showReport();


}


int main()
{
	/*
	Node* root;
	int x = 11;
	int* v = (int*)malloc(x * sizeof(int));
	char s[7];
	for (int i = 0; i < x; i++)
		v[i] = i + 1;
	root = buildTree(0, x - 1, v);

		
	Node* q = OS_SELECT(root, 3, x, s);
	OS_DELETE(root, 3, x, s);
	print(root, 0);
	*/
	mediu();
	return 0;










}