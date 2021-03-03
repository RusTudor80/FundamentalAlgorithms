#include <iostream>
#include"Profiler.h"

using namespace std;

typedef struct Set{
	int rank;
	int value;
	struct Set* parent;
	
} Set;
typedef struct Node {
	int key;
	struct Node** vecini;
	int nrVecini;
} Node;

typedef struct Muchie {
	Node* u, * v;
	int cost;
} Muchie, * MMuchie;

typedef struct Graf {

	int nrNoduri;
	int nrMuchii;
	Node** noduri;
	Muchie** muchii;
	
} Graf;


void makeSet(Set* set, int value) {
	set->parent = set;
	set->rank = 0;
	set->value = value;
}

Set* findSet(Set* set) {

	if (set != set->parent) {
		set->parent = findSet(set->parent);
	}
	return set->parent;
}

void Link(Set* x, Set* y) {
	if (x->rank < y->rank) {
		x->parent = y;
	}
	else {
		if (x->rank > y->rank) {
			y->parent = x;
		}
		else {
			x->parent = y;
			y->rank++;
		}
	}
}

void Union(Set* x, Set* y) {
	return Link(x,y);
}

Set** makeSets(int* valori) {

	Set** sets = (Set**)malloc(10 * sizeof(Set*));
	for (int i = 0; i < 10; i++) {
		sets[i] = (Set*)malloc(sizeof(Set));
		makeSet(sets[i], valori[i]);
	}

	return sets;
}

void UnionDemo(Set** sets) {
	//0->9, 1->8, 2->7, 3->6, 4->5 => 0, 1, 2, 3, 4
	for (int i = 0; i < 5; i++)
		Union(sets[9 - i], sets[i]); 

	//0->4, 1->3, 2->2 => 0, 1, 2
	Union(sets[4], sets[0]); 
	Union(sets[3], sets[1]); 

	//0->1, 0->2 => 0
	Union(sets[1], sets[0]);   
	Union(sets[2], sets[0]);   

}

void demo() {
	int* a = (int*)malloc(10 * sizeof(int));
	FillRandomArray(a, 10, 0, 20, true, 1);
	for (int i = 0; i < 10; i++) {
		cout << a[i] << " ";
	}
	cout << endl;


	Set** sets = makeSets(a);

	Set** b = (Set**)malloc(10 * sizeof(Set*));
	memmove(b, sets, 10* sizeof(Set*));
	UnionDemo(sets);

	for (int i = 0; i <10; i++) {
		cout << "Radacina nodului " <<sets[i]->value<< " este "<< findSet(b[i])->value << endl;
	}
	free(sets);
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void insertion(Graf* a, int n)
{
	int i, j, aux;
	for (i = 1; i < n; i++) {
		aux = a->muchii[i]->cost;
		j = i - 1;
		while (j >= 0 && a->muchii[j]->cost > aux) {
			a->muchii[j + 1]->cost = a->muchii[j]->cost;
			j = j - 1;
		}
		a->muchii[j + 1]->cost = aux;
	}

}
int compare_muchii(const void* a, const void* b) {
	MMuchie p1 = (MMuchie)a;
	MMuchie p2 = (MMuchie)b;
	if (p1->cost > p2->cost)
		return 1;
	else
		if (p1->cost < p2->cost)
			return -1;
	return 0;
}
void sort_muchii(MMuchie muchii, int n) {
	qsort(muchii, n, sizeof(Muchie), compare_muchii);
}

MMuchie* kruskal(Graf* g) {
	int nrMuchii = 0;
	MMuchie* muchii = (MMuchie*)malloc(sizeof(MMuchie));
	Set** sets = (Set**)malloc(g->nrNoduri * sizeof(Set*));

	for (int i = 0; i < g->nrNoduri; i++) {
		sets[i] = (Set*)malloc(sizeof(Set));
		makeSet(sets[i], g->noduri[i]->key);   
	}
	insertion(g, g->nrMuchii - 1);

	for (int i = 0; i < g->nrMuchii; i++) {
		if (findSet(sets[g->muchii[i]->u->key]) != findSet(sets[g->muchii[i]->v->key])) {
			muchii[nrMuchii++] = g->muchii[i];
			Union(sets[g->muchii[i]->u->key], sets[g->muchii[i]->v->key]);
			muchii = (MMuchie*)realloc(muchii, (nrMuchii + 1) * sizeof(MMuchie));
		}
	}
	for (int i = 0; i < g->nrNoduri; i++)
		free(sets[i]);
	free(sets);
	muchii[nrMuchii++] = NULL;

	return muchii;
}

Graf* createGraf(int nrNoduri,int nrMuchii) {
	if (nrNoduri - 1 > nrMuchii) {
		cout << "Eroare";
	}
	Graf* g = (Graf*)malloc(sizeof(Graf));
	g->nrNoduri = nrNoduri;
	g->noduri = (Node**)malloc(nrNoduri * sizeof(Node*));
	g->nrMuchii = nrMuchii;
	g->muchii = (Muchie**)malloc(nrMuchii * sizeof(Muchie*));

	for (int i = 0; i < nrNoduri; i++) {
		g->noduri[i] = (Node*)malloc(sizeof(Node));
		g->noduri[i]->key = i;
		g->noduri[i]->vecini = NULL;
		g->noduri[i]->nrVecini = 0;
	}

	for (int i = 0; i < nrNoduri - 1; i++) {
		g->muchii[i] = (Muchie*)malloc(sizeof(Muchie));
		g->muchii[i]->u = g->noduri[i];
		g->muchii[i]->v = g->noduri[i + 1];
		g->muchii[i]->cost = rand() % 50;

		g->muchii[i]->u->vecini = (Node**)realloc(g->muchii[i]->u->vecini, (++g->muchii[i]->u->nrVecini) * sizeof(Node*));
		g->muchii[i]->v->vecini = (Node**)realloc(g->muchii[i]->v->vecini, (++g->muchii[i]->v->nrVecini) * sizeof(Node*));
		g->muchii[i]->u->vecini[g->muchii[i]->u->nrVecini - 1] = g->muchii[i]->v;
		g->muchii[i]->v->vecini[g->muchii[i]->v->nrVecini - 1] = g->muchii[i]->u;
	}

	for (int i = nrNoduri - 1; i < nrMuchii; i++) {
		g->muchii[i] = (Muchie*)malloc(sizeof(Muchie));
		int aux1 = rand() % g->nrNoduri;
		int aux2= rand() % g->nrNoduri;

		while (aux1 == aux2){
			aux2 = rand() % g->nrNoduri; 
		}
		g->muchii[i]->u = g->noduri[aux1];
		g->muchii[i]->v = g->noduri[aux2];
		g->muchii[i]->cost = rand() % 50;

		g->muchii[i]->u->vecini = (Node**)realloc(g->muchii[i]->u->vecini, (++g->muchii[i]->u->nrVecini) * sizeof(Node*));
		g->muchii[i]->v->vecini = (Node**)realloc(g->muchii[i]->v->vecini, (++g->muchii[i]->v->nrVecini) * sizeof(Node*));
		g->muchii[i]->u->vecini[g->muchii[i]->u->nrVecini - 1] = g->muchii[i]->v;
		g->muchii[i]->v->vecini[g->muchii[i]->v->nrVecini - 1] = g->muchii[i]->u;
	}

	return g;
}

void demoKruskal() {
	Graf* graf = createGraf(10, 20);
	cout<<"Nodurile sunt:";
	for (int i = 0; i < graf->nrNoduri; i++)
		cout<< graf->noduri[i]->key<<" ";
	cout<<endl;

	cout<<"Muchiile sunt:";
	cout << endl;
	for (int i = 0; i < graf->nrMuchii; i++)
		cout<<"Muchia de cost "<<graf->muchii[i]->cost<<" intre nodurile "<<graf->muchii[i]->u->key<<" "<< graf->muchii[i]->v->key<<endl;

	Muchie** muchii = kruskal(graf);

	int total = 0;
	cout << endl;
	cout<<"Kruskal e:";
	cout << endl;
	for (int i = 0; muchii[i] != NULL; i++) {
		cout << "Muchia de cost " << muchii[i]->cost << " intre nodurile " << muchii[i]->u->key << " " << muchii[i]->v->key << endl;
		total =total+ muchii[i]->cost;
	}
	cout<<endl;
	cout<<"Costul minim este:"<< total; 
}


int main() {
	demo();
	demoKruskal();
	return 0;
}
