#include<stdlib.h>
#include<stdio.h>
#include"Profiler.h"

Profiler p("quick");
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
void move(int a[], int b[],int n)
{
	for (int i = 0; i < n; i++)
		a[i] = b[i];

}

void show(int a[], int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}


void heapify(int* a, int n, int i,int size)
{
	Operation o_c = p.createOperation("Heap sort heapify", size);

	int maxim = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left<n && a[left]>a[maxim]) {
		maxim = left; 
		o_c.count(1);
	}
	if (right<n && a[right]>a[maxim]) {
		maxim = right;
		o_c.count(1);
		
	}
	if (maxim != i) {
		
		o_c.count(3);
		swap(a + i, a + maxim);
		heapify(a, n, maxim,size);
	}
	
}


void heapsort(int* a, int n)
{
	Operation o_c = p.createOperation("Heap sort main", n);

	for (int i = n / 2 - 1; i >= 0; i--) 
		heapify(a, n, i,n);
	for (int i = n - 1; i >= 0; i--)
	{
		o_c.count(3);
		swap(a + 0, a + i);
		heapify(a, i, 0,n);
	}
}
int partition(int a[], int stanga, int dreapta,int n)
{	
	Operation o_c = p.createOperation("Quick sort",n);
	o_c.count(1);
	int pivot = a[dreapta];  
	int i = (stanga - 1);   

	for (int j = stanga; j <= dreapta - 1; j++)
	{
		o_c.count(1);
		if (a[j] < pivot)
		{
			i++;
			o_c.count(3);
			swap(&a[i], &a[j]);
		}
	}
	o_c.count(3);
	swap(&a[i + 1], &a[dreapta]);
	return (i + 1);
}
void quick(int a[], int stanga, int dreapta,int n)
{
	if (stanga < dreapta)
	{

		int pi = partition(a, stanga, dreapta,n);
		quick(a, stanga, pi - 1,n);
		quick(a, pi + 1, dreapta,n);

	}
}
int random_partition(int a[], int stanga, int dreapta,int n)
{
	int i = stanga+ rand() % (dreapta - stanga);
	swap(a+i, a+dreapta);
	return partition(a, stanga, dreapta,n);
}
void quick_random(int a[], int stanga, int dreapta, int n)
{
	if (stanga < dreapta)
	{

		int pi = random_partition(a, stanga, dreapta, n);
		quick(a, stanga, pi - 1, n);
		quick(a, pi + 1, dreapta, n);

	}
}

void HeapSort_vs_QuickSort(){

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
			FillRandomArray(a1, n, 10, 50000,false, 0);
			
			move(a2, a1,n);
			heapsort(a1, n);
			quick(a2,0,n-1,n);

			free(a1);
			free(a2);
		}
	}

	p.addSeries("Heap sort", "Heap sort heapify", "Heap sort main");
	
	p.divideValues("Heap sort", 5);
	p.divideValues("Quick sort", 5);

	p.createGroup("Caz Mediu HEAP vs QUICK", "Heap sort", "Quick sort");
}
void Quick_Favorabil()
{
	int* a1 = NULL;
	for (int m = 0; m < 5; m++) {
		for (int n = 50; n <= 1000; n = n + 50) {
			a1 = (int*)malloc(n * sizeof(int));
			if (NULL == a1) {
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, ASCENDING);
			quick(a1, 0, n - 1, n);

			free(a1);
		}
	}

}
void Quick_Mediu()
{
	int* a1 = NULL;
	for (int m = 0; m < 5; m++) {
		for (int n = 500; n <= 10000; n = n + 500) {
			a1 = (int*)malloc(n * sizeof(int));
			if (NULL == a1) {
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, 0);
			quick(a1, 0, n - 1, n);

			free(a1);
		}
	}
	p.divideValues("Quick sort", 5);

}
void Quick_Defavorabil()
{
		int* a1 = NULL;
		for (int m = 0; m < 5; m++) {
			for (int n = 50; n <= 1000; n = n + 50) {
				a1 = (int*)malloc(n * sizeof(int));
				if (NULL == a1) {
					printf("Nu este memorie");
					exit(1);
				}
				FillRandomArray(a1, n, 10, 50000, false, 2);
				quick(a1, 0, n - 1, n);

				free(a1);
			}
		}
}
int main()
{
	//int n = 11;
	//int a[] = { 0, 13, 40, 24, 18, 27, 9, 36, 69, 21, 15 };
	//int b[] = { 0, 13, 40, 24, 18, 27, 9, 36, 69, 21, 15 };
	//int c[] = { 0, 13, 40, 24, 18, 27, 9, 36, 69, 21, 15 };

	//heapsort(a, n);
	//show(a, n);

	//quick_random(b,0,n-1,n);
	//show(b, n);

	//quick(c,0,n-1,n);
	//show(c,n);


	p.reset("Average heap quick");
	HeapSort_vs_QuickSort();

	p.reset("Mediu Quick sort");
	Quick_Mediu();

	p.reset("Defavorabil Quick sort");
	Quick_Defavorabil();

	p.reset("Favorabil Quick sort");
	Quick_Favorabil();

	//p.createGroup("Cazuri quick", "Mediu Quick sort", "Defavorabil Quick sort", "Favorabil Quick Sort");

	p.showReport();
	return 0;
}
