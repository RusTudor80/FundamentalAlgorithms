
#include<stdlib.h>
#include<stdio.h>
#include"Profiler.h"

Profiler p("heap");

inline int parent(int index) {
		return (index - 1)/ 2;
}

void swap(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
void heapify(int* a, int n,int i)
{
	Operation o_c = p.createOperation("Bottom operatii", n);

	int maxim = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	o_c.count(1);
	if (left<n && a[left]>a[maxim])
		maxim = left;
	o_c.count(1);
	if (right<n && a[right]>a[maxim])
		maxim = right;
	if (maxim != i) {
		o_c.count(3);
		swap(a+i, a+maxim);
		heapify(a, n, maxim);
	}
}
void heapsort(int *a, int n)
{

	for (int i = n / 2 - 1; i  >= 0; i--)
		heapify(a, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(a+0, a+i);
		heapify(a, i, 0);
	}
}
void bottom_up(int* a, int n)
{
	int start;
	if (n % 2 == 0)
		 start = n / 2;
	else
		 start = (n-1)/2;
	for (int i = start; i >= 0; i--)
		heapify(a, n, i);
}
void insert(int a[], int i, int n) {

	Operation o_c = p.createOperation("Top operatii", n);
	while (i >= 1 && a[parent(i)] < a[i])
	{
		o_c.count(4);
		swap(a+parent(i), a+i);
		i =parent(i);
	}
}
 

void top_down(int* a, int n)
{
	int heap_size=1;
	for (int i = 2; i <=n; i++) {
		++heap_size;
		insert(a, heap_size, n);
	}
}
void move(int a[], int b[], int n)
{
	for (int i = 0; i < n; i++)
		a[i] = b[i];

}

void show(int a[], int n)
{
	for (int i = 0; i <n; ++i)
		printf("%d ",a[i]);
	printf( "\n");
}

void mediu() {
	int* a1 = NULL;
	int* a2 = NULL;
	for (int m = 0; m < 5; m++) {
		for (int n = 500; n <= 10000; n = n + 500) {

			a1 = (int*)malloc(n * sizeof(int));
			a2 = (int*)malloc(n * sizeof(int));
			if (NULL == a1 || NULL == a2) {
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, 0);
			move(a2, a1, n);
			bottom_up(a1, n);
			top_down(a2, n);

			free(a1);
			free(a2);
		}
	}

	p.divideValues("Bottom operatii", 5);
	p.divideValues("Top operatii", 5);
	p.createGroup("Caz Mediu", "Bottom operatii", "Top operatii");
}
void defavorabil() {
	int* a1 = NULL;
	int* a2 = NULL;
	for (int m = 0; m < 5; m++) {
		for (int n = 500; n <= 10000; n = n + 500) {

			a1 = (int*)malloc(n * sizeof(int));
			a2 = (int*)malloc(n * sizeof(int));
			if (NULL == a1 || NULL == a2) {
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, 2);
			move(a2, a1, n);
			bottom_up(a1, n);
			top_down(a2, n);

			free(a1);
			free(a2);
		}
	}

	p.createGroup("Caz Defavorabil", "Bottom operatii", "Top operatii");
}


int main()
{
	
	p.reset("Mediu");
	mediu();

	//p.reset("Defavorabil");
	//defavorabil();

	p.showReport();

	return 0;
	

}