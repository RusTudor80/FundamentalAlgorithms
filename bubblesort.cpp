/*
Ca si complexitate insertion sort este cel mai bun,
ca si numar de atribuiri cel mai bine sta selection sort,
ca si numar de comparatii cel mai bine sta insertion sort,
si ca si numar de operatii cel mai bine sta insertion sort,
Per total insertion sort si selection sort sunt cele mai eficiente ca timp si memorie alocata
erori nu am avut 
bubble sort nu se foloseste niciodata in nici un caz

*/




#include"Profiler.h"
#include <stdio.h>
#include <stdlib.h>

Profiler p("sort");



void swap(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;

}

void bubble(int *a,int n)
{
	int ok = 0, k = n - 2;
	Operation o_c = p.createOperation("Bubble_comparatii", n);
	Operation o_a = p.createOperation("Bubble_atribuiri", n);

	while (ok == 0)
	{
		ok = 1;
		for (int i = 0; i <= k; i++) {
			o_c.count(1);
			if (a[i] > a[i + 1]) {
				swap(a+i, a+i + 1);
				o_a.count(3);
				ok = 0;
			}
		}
		k--;
	}
}
void insertion(int* a, int n)
{
	int i, j, aux;
	Operation o_c = p.createOperation("Insertion_comparatii", n);
	Operation o_a = p.createOperation("Insertion_atribuiri", n);
	for (i = 1; i < n; i++) {
		o_a.count(1);
		aux = a[i];
		j = i - 1;
		while (j >= 0 && a[j] >aux) {
			o_c.count(1);
			o_a.count(1);
			a[j + 1] = a[j];
			j = j - 1;
		}
		o_a.count(1);
		a[j + 1] = aux;

	}
	
}
void selection(int* a, int n)
{
	
	Operation o_c = p.createOperation("Selection_comparatii", n);
	Operation o_a = p.createOperation("Selection_atribuiri", n);
	int i, j, minim;
	for (i =0; i < n-1 ; i++)
	{
		minim= i;
		for (j = i + 1; j < n; j++) {
			o_c.count(1);
			if (a[j] < a[minim])
				minim = j;
		}
		if (minim != i) {
			o_a.count(3);
			swap(a + minim, a + i);
		}
	}
}
void move(int a[],int b[],int n)
{
	for (int i = 0; i < n; i++)
		a[i] = b[i];

}
void favorabil()
{
	int* a1 = NULL;
	int* a2 = NULL;
	int* a3 = NULL;
	for (int m = 0; m < 5; m++) {

		for (int n = 100; n <= 1000; n = n + 100) {


			a1 = (int*)malloc(n * sizeof(int));
			a2 = (int*)malloc(n * sizeof(int));
			a3 = (int*)malloc(n * sizeof(int));

			if (NULL == a1 || NULL == a2 || NULL == a3) {
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, 1);
			move(a2, a1, n);
			move(a3, a1, n);


			bubble(a1, n);
			insertion(a2, n);
			selection(a3, n);

			if (false == IsSorted(a1, n))
				printf("Nu e sortat");
			if (false == IsSorted(a2, n))
				printf("Nu e sortat");
			if (false == IsSorted(a3, n))
				printf("Nu e sortat");


			free(a1);
			free(a2);
			free(a3);

		}

	}
	p.addSeries("Bubble_operatii", "Bubble_comparatii", "Bubble_atribuiri");
	p.addSeries("Insertion_operatii", "Insertion_comparatii", "Insertion_atribuiri");
	p.addSeries("Selection_operatii", "Selection_comparatii", "Selection_atribuiri");

	p.createGroup("Favorabil_operatii", "Bubble_operatii", "Insertion_operatii", "Selection_operatii");
	p.createGroup("Favorabil_comparatii", "Bubble_comparatii", "Insertion_comparatii", "Selection_comparatii");
	p.createGroup("Favorabil_atribuiri", "Bubble_atribuiri", "Insertion_atribuiri", "Selection_atribuiri");

}

void mediu(){
	int* a1 = NULL;
	int* a2 = NULL;
	int* a3 = NULL;
	for (int m = 0; m < 5; m++) {

		for (int n = 100; n <=1000; n = n + 100) {

		
			a1= (int*)malloc(n * sizeof(int));
			a2= (int*)malloc(n * sizeof(int));
			a3= (int*)malloc(n * sizeof(int));

			if (NULL == a1||NULL==a2||NULL==a3){
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, 0);
			move(a2, a1, n);
			move(a3, a1, n);


			bubble(a1, n);
			insertion(a2, n);
			selection(a3, n);

			if (false == IsSorted(a1, n))
				printf("Nu e sortat");
			if (false == IsSorted(a2, n))
				printf("Nu e sortat");
			if (false == IsSorted(a3, n))
				printf("Nu e sortat");


			free(a1);
			free(a2);
			free(a3);

		}

	}
	p.addSeries("Bubble_operatii", "Bubble_comparatii", "Bubble_atribuiri");
	p.addSeries("Insertion_operatii", "Insertion_comparatii", "Insertion_atribuiri");
	p.addSeries("Selection_operatii", "Selection_comparatii", "Selection_atribuiri");


	p.divideValues("Bubble_operatii", 5);
	p.divideValues("Bubble_comparatii", 5);
	p.divideValues("Bubble_atribuiri", 5);

	p.divideValues("Insertion_operatii", 5);
	p.divideValues("Insertion_comparatii", 5);
	p.divideValues("Insertion_atribuiri", 5);

	p.divideValues("Selection_operatii", 5);
	p.divideValues("Selection_comparatii", 5);
	p.divideValues("Selection_atribuiri", 5);

	p.createGroup("Mediu_operatii", "Bubble_operatii", "Insertion_operatii", "Selection_operatii");
	p.createGroup("Mediu_comparatii", "Bubble_comparatii", "Insertion_comparatii", "Selection_comparatii");
	p.createGroup("Mediu_atribuiri", "Bubble_atribuiri", "Insertion_atribuiri", "Selection_atribuiri");

}
void defavorabil()
{
	int* a1 = NULL;
	int* a2 = NULL;
	int* a3 = NULL;
	for (int m = 0; m < 5; m++) {

		for (int n = 100; n <= 1000; n = n + 100) {


			a1 = (int*)malloc(n * sizeof(int));
			a2 = (int*)malloc(n * sizeof(int));
			a3 = (int*)malloc(n * sizeof(int));

			if (NULL == a1 || NULL == a2 || NULL == a3) {
				printf("Nu este memorie");
				exit(1);
			}
			FillRandomArray(a1, n, 10, 50000, false, 2);
			move(a2, a1, n);
			move(a3, a1, n);


			bubble(a1, n);
			insertion(a2, n);
			selection(a3, n);

			if (false == IsSorted(a1, n))
				printf("Nu e sortat");
			if (false == IsSorted(a2, n))
				printf("Nu e sortat");
			if (false == IsSorted(a3, n))
				printf("Nu e sortat");


			free(a1);
			free(a2);
			free(a3);

		}

	}
	p.addSeries("Bubble_operatii", "Bubble_comparatii", "Bubble_atribuiri");
	p.addSeries("Insertion_operatii", "Insertion_comparatii", "Insertion_atribuiri");
	p.addSeries("Selection_operatii", "Selection_comparatii", "Selection_atribuiri");

	p.createGroup("Defavorabil_operatii", "Bubble_operatii", "Insertion_operatii", "Selection_operatii");
	p.createGroup("Defavorabil_comparatii", "Bubble_comparatii", "Insertion_comparatii", "Selection_comparatii");
	p.createGroup("Defavorabil_atribuiri", "Bubble_atribuiri", "Insertion_atribuiri", "Selection_atribuiri");
}


void show(int *a ,int n){
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	p.reset("Favorabil");
	favorabil();

	p.reset("Mediu");
	mediu();

	p.reset("Defavorabil");
	defavorabil();

	p.showReport();

	return 0;


}

