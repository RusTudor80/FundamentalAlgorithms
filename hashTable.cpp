#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define EMPTY -1
#include"Profiler.h"
Profiler p("Hash");

void writeHash(int hash[], int size) {
	printf("Table:\n");
	for (int i = 0; i < size; i++)
	{
		printf("%d: %d\n", i, hash[i]);
	}
}
int hashing(int key, int i, int m)
{
	return(key + 3 * i + 5 * i*i) % m;
}
void insert(int key, int hash[], int size) {
	for (int i = 0; i < size; i++) {
		int h = hashing(key, i, size);
		if (hash[h] == EMPTY) {
			hash[h] = key;
			break;
		}
	}
}
int search_key(int key, int hash[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		int h = hashing(key, i, size);
		if (hash[h] == key)
			return (i + 1);
		else
			if (hash[h] == EMPTY)
				return i + 1;
	}
	return (i + 1);

}
int search(int key, int hash[], int size) {
	for (int i = 0; i < size; i++) {
		int h = hashing(key, i, size);
		if (hash[h] == key)
			return 1;
		else
			if (hash[h] == EMPTY)
				return 0;
	}
	return 0;

}
int main()
{
	/*

	int  hash[10];
	for(int i=0;i<10;i++)
	hash[i]=EMPTY;
	int a[10] = { 3,12,7,9,8,22,23,34,6 };
	for (int i = 0; i<int(0.95*10); i++)
	insert(a[i], hash, 10);
	writeHash(hash,10);
	printf("%d\n", search(25, hash, 10));

	*/
	double factor[] = { 0.8,0.85,0.9,0.95,0.99 };
	const int size = 10007;
	int suma_gasite = 0;
	int suma_negasite = 0;
	int max_gasit = 0;
	int max_negasit = 0;
	int a[size];
	printf("|Factor de umplere      |Efort maxim gasit|Efort mediu gasit      |Ef  maxim negasit|Efort mediu negasit   ");
	for (int m = 0; m < 5; m++) {
		for (int j = 0; j < 5; j++) {
			int hash[size];
			for (int i = 0; i < size; i++)
				hash[i] = EMPTY;
			FillRandomArray(a, int(factor[m] * size), 10, 30000, true);
			for (int i = 0; i<int(factor[m] * size); i++)
				insert(a[i], hash, size);
			//writeHash(hash, size);
			int negasit[1500], gasit[1500];
			int p = 0;

			while (p < 1500)
			{
				int poz = rand() % 30000;
				if (search(poz, hash, size) != 0)
				{
					gasit[p] = poz;
					p++;
				}
			}

			for (int k = 0; k < 1500; k++)
			{
				int poz = 30001 + rand() % (40000 - 30001 + 1);
				negasit[k] = poz;
			}
			for (int i = 0; i < p; i++)
			{
				suma_gasite = suma_gasite + search_key(gasit[i], hash, size);

				suma_negasite = suma_negasite + search_key(negasit[i], hash, size);

				if (search_key(gasit[i], hash, size) > max_gasit)
					max_gasit = search_key(gasit[i], hash, size);

				if (search_key(negasit[i], hash, size) > max_negasit)
					max_negasit = search_key(negasit[i], hash, size);
			}
		}
		suma_gasite = suma_gasite / 5;;
		suma_negasite = suma_negasite / 5;


		printf("\n");
		printf("|      %f         ", factor[m]);
		printf("|      %d         ", max_gasit);
		printf("|      %f         ", suma_gasite / 1500.0);
		printf("|      %d         ", max_negasit);
		printf("|      %f         ", suma_negasite / 1500.0);

	}
	system("pause");
	return 0;
}


