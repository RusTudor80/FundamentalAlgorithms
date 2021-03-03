
#include<iostream>

using namespace std;
int parinte[10] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 };
int copii[10];
int n = 9;


void Reprezentare1(int parinte[], int level, int n, int tata)
{
	for (int i = 0; i < n; i++) {
		if (parinte[i] == tata) {
			for (int space = 0; space < level; space++)
				cout << "   ";
			cout << i + 1 << endl;
			Reprezentare1(parinte, level + 2, n, i + 1);
		}
	}
}

struct arbore_multicai
{
	int cheie;
	int nr_copii;
	arbore_multicai** copii;
} *multiCai[100],*radacina;

struct arbore_binar
{
	int cheie;
	arbore_binar* fiu;
	arbore_binar* frate;
} *binar[100];




void Transformare1()
{
	int aux;
	for (int i = 1; i <= n; i++)
	{
		if (parinte[i] == -1)
			radacina = multiCai[i];
		else
		{
			multiCai[parinte[i]]->nr_copii = multiCai[parinte[i]]->nr_copii+ 1;
			aux = multiCai[parinte[i]]->nr_copii;
			multiCai[parinte[i]]->copii[aux] = multiCai[i];
		}
	}
}

void Reprezentare2(arbore_multicai* p)
{
	
	if (p != NULL)
	{
		if (p->nr_copii == 0)
			cout<< "Nodul " << p->cheie << " nu are copii " << endl;
		else
		{
			if (p->nr_copii == 1)
				cout << "Nodul " << p->cheie << " are un copil ";
			else
				cout << "Nodul " << p->cheie << " are urmatorii copii ";
			for (int i = 1; i <= p->nr_copii; i++)
				cout<< p->copii[i]->cheie<<" ";
			cout << endl;

			for (int i = 1; i <= p->nr_copii; i++)
				Reprezentare2(p->copii[i]);
		}
	}
}

void Transformare2(arbore_multicai* p)
{
	if (p != NULL)
	{
		for (int i = 1; i <= p->nr_copii; i++)
		{
			if (i == 1)
				binar[p->cheie]->fiu = binar[p->copii[1]->cheie];
			else
				binar[p->copii[i - 1]->cheie]->frate = binar[p -> copii[i]->cheie];

			Transformare2(p->copii[i]);
		}
	}
}

void Reprezentare3(int nod, int nivel)
{
	cout <<endl;
	for (int j = 1; j <= nivel; j++)
		cout<<"      ";
	cout << nod;

	if (binar[nod]->fiu != NULL)
		Reprezentare3(binar[nod]->fiu->cheie, nivel + 1);

	if (binar[nod]->frate != NULL)
		Reprezentare3(binar[nod]->frate->cheie, nivel);

}

int main()
{
	for (int i = 1; i <= n; i++)
	{
		multiCai[i] = (arbore_multicai*)malloc(sizeof(arbore_multicai));
		multiCai[i]->cheie = i;
		multiCai[i]->nr_copii = 0;                                
		multiCai[i]->copii = (arbore_multicai**)malloc(copii[i] *sizeof(arbore_multicai*));

		binar[i] = (arbore_binar*)malloc(sizeof(arbore_binar));
		binar[i]->cheie = i;
		binar[i]->fiu = NULL;
		binar[i]->frate = NULL;
	
	}
	cout<<"Primul caz"<<endl;
	cout << endl;
	cout<<"Vector parinti : "<<endl;
	cout << endl;
	for (int i = 1; i <= n; i++)
		cout << parinte[i] << " ";
	cout << endl << endl;
	cout << "Prima reprezentare :"<<endl;
	Reprezentare1(parinte+1,0,n,-1);

	cout << endl;
	Transformare1();
	cout << endl;

	cout<<"Al doilea caz"<<endl;
	cout << endl;
	cout << "A doua reprezentare :" << endl ;
	Reprezentare2(radacina);

	Transformare2(radacina);
	cout << endl;

	cout<<"Al treilea caz"<<endl;
	cout << endl;
	cout << "A treia reprezentare :" << endl;
	Reprezentare3(radacina->cheie, 0);

	

	return 0;

}
