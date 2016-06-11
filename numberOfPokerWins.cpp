#include <fstream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

ifstream fin("carti.txt");
ofstream fout("poker.out");


int primul, n;

string carti1[100005][10], carti2[100005][10];
string tura1[10], tura2[10];

string rankuri[] = {"highCard", "onePair", "twoPairs", "threeOfAKind",
			"straight", "flush", "fullHouse", "fourOfAKind", "straightFlush",
			"royalFlush"};

struct structuraMana
{
	string ranku;
	int valoare, valoare2, aparitii[20], highCard; 
};
structuraMana mana1, mana2;


void citire()
{
	fin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= 5; j++)
			fin >> carti1[i][j];

		for (int j = 1; j <= 5; j++)
			fin >> carti2[i][j];
	}
}

void stergere(int v[], int n)
{
	for (int i = 1; i <= n; i++)
		v[i] = 0;
}

int transformaLiteraInNumar(string litera)
{
	int nr1;
	nr1 = atoi(litera.c_str());

	if (nr1 == 0)
	{
		if (litera == "T")
			nr1 = 10;
		else if (litera == "J")
			nr1 = 11;
		else if (litera == "Q")
			nr1 = 12;
		else if (litera == "K")
			nr1 = 13;
		else if (litera == "A")
			nr1 = 14;
	}

	return nr1;
}

void ordonare(string tura[], int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int nr1, nr2;
			string litera;
			litera = tura[i][0];
			nr1 = transformaLiteraInNumar(litera);

			litera = tura[j][0];
			nr2 = transformaLiteraInNumar(litera);

			if (nr1 > nr2)
				swap(tura[i], tura[j]);
		}
	}
}

string rankul(string tura[], int &valoare, int &valoare2, int aparitii[])
{
	string rankReturn = "";

	stergere(aparitii, 14);
	ordonare(tura, 5);

	for (int i = 1; i <= 5; i++)
	{
		string litera;
		litera = tura[i][0];
		int nr = transformaLiteraInNumar(litera);

		aparitii[nr]++;
	}

	int nrPerechi = 0;
	bool treiCuie = false, careu = false, chinta = false, culoare = false;

	for (int i = 1; i <= 14; i++)
	{
		if (aparitii[i] == 2)
			nrPerechi++, valoare = i;

		if (aparitii[i] == 4)
			careu = true, valoare = i;
	}

	for (int i = 1; i <= 14; i++)
	{
		if (aparitii[i] == 3)
		{
			treiCuie = true;
			valoare = i;
		}
	}

	if (tura[1][1] == tura[2][1] && tura[1][1] == tura[3][1] &&
	 tura[1][1] == tura[4][1] && tura[1][1] == tura[5][1])
	{
		culoare = true;
		for (int i = 1; i <= 14; i++)
		{
			if (aparitii[i] == 1)
				valoare = i;
		}
	}

	for (int i = 1; i <= 10; i++)
	{
		if (aparitii[i] == 1 && aparitii[i+1] == 1 && aparitii[i+2] == 1 &&
			aparitii[i+3] && aparitii[i+4] == 1)
			chinta = true, valoare = i;
	}
		
	if (chinta == true && culoare == true && valoare == 10)
		return "royalFlush";

	else if (chinta == true && culoare == true)
		return "straightFlush";

	else if (careu == true)
		rankReturn = "fourOfAKind";

	else if (nrPerechi == 1 && treiCuie == true)
	{
		for (int i = 1; i <= 14; i++)
			if (aparitii[i] == 2)
				valoare2 = i;

		rankReturn = "fullHouse";
	}

	else if (culoare == true)
		rankReturn = "flush";

	else if (chinta == true)
		rankReturn = "straight";

	else if (treiCuie == true)
		rankReturn = "threeOfAKind";

	else if (nrPerechi == 2)
	{
		for (int i = 1; i <= 14; i++)
			if (aparitii[i] == 2 && i != valoare)
				valoare2 = i;

		rankReturn = "twoPairs";
	}

	else if (nrPerechi == 1)
		rankReturn = "onePair";

	else
	{
		for (int i = 1; i <= 14; i++)
		{
			if (aparitii[i] == 1)
				valoare = i;
		}
		rankReturn = "highCard";
	}

	return rankReturn;
}

string colori(string litera)
{
	string cul;
	if (litera == "S")
		cul = "♠";
	else if (litera == "D")
		cul = "♦";
	else if (litera == "C")
		cul = "♣";
	else if (litera == "H")
		cul = "♥";

	return cul;
}

void afisareCarte(string tura[])
{
	string lit1, lit2, lit3, lit4, lit5;
	lit1 = tura[1][1];
	lit2 = tura[2][1];
	lit3 = tura[3][1];
	lit4 = tura[4][1];
	lit5 = tura[5][1];

	fout << " -------  -------  -------  -------  ------- \n";
	for (int i = 1; i <= 5; i++)
	{
		int a;
		string lit;
		lit = tura[i][0];
		a = transformaLiteraInNumar(lit);
		if (a != 10)
			fout << "|" << tura[i][0] << "      |";
		else
			fout << "|" << "10     |";
	}
	fout << endl;
	fout << "|" << colori(lit1) << "      ||" << colori(lit2) << "      ||" << colori(lit3) << "      ||" << colori(lit4) << "      ||" << colori(lit5) << "      |\n";
	fout << "|       ||       ||       ||       ||       |\n";
	fout << "|       ||       ||       ||       ||       |\n";
	fout << "|       ||       ||       ||       ||       |\n";
	fout << "|      " << colori(lit1) << "||      " << colori(lit2) << "||      " << colori(lit3) << "||      " << colori(lit4) << "||      " << colori(lit5) << "|\n";
	for (int i = 1; i <= 5; i++)
	{
		int a;
		string lit;
		lit = tura[i][0];
		a = transformaLiteraInNumar(lit);
		if (a != 10)
			fout << "|      " << tura[i][0] << "|";
		else
			fout << "|     " << "10|";
	}
	fout << endl;
	fout << " -------  -------  -------  -------  ------- \n";
}

string numarInLitera(int nr)
{
	string liter;
	if (nr <= 10)
		liter = to_string(nr);
	else if (nr == 11)
		liter = "J";
	else if (nr == 12)
		liter = "Q";
	else if (nr == 13)
		liter = "K";
	else if (nr == 14)
		liter = "A";

	return liter;
}

int castigaPrimulHighCard(structuraMana &mana1, structuraMana &mana2)
{
	int i1 = 14, i2 = 14;
	while (i1 >= 0 && i2 >= 0)
	{
		while (mana1.aparitii[i1] == 0 || i1 == mana1.valoare || i1 == mana1.valoare2)
			i1--;
		while (mana2.aparitii[i2] == 0 || i2 == mana2.valoare || i2 == mana2.valoare2)
			i2--;

		if (i1 > i2)
		{
			mana1.highCard = i1;
			mana2.highCard = i2;
			return 1;
		}
		if (i2 > i1)
		{
			mana1.highCard = i1;
			mana2.highCard = i2;
			return 0;
		}
		else
			i1--, i2--;
	}
	return -1;
} 

bool primulCastigator(string tura1[], string tura2[])
{

	mana1.ranku = rankul(tura1, mana1.valoare, mana1.valoare2, mana1.aparitii);
	mana2.ranku = rankul(tura2, mana2.valoare, mana2.valoare2, mana2.aparitii);


	int poz1, poz2;

	for (int i = 0; i < 10; i++)
	{
		if (mana1.ranku == rankuri[i])
			poz1 = i;

		if (mana2.ranku == rankuri[i])
			poz2 = i;
	}
	fout << "\n";
	afisareCarte(tura1);
	fout << "\n";

	afisareCarte(tura2);
	fout << "\n";
	if (poz1 > poz2)
	{
		fout << "The first player wins with " << mana1.ranku 
			<< " of " << numarInLitera(mana1.valoare) << "\n";

		fout << "The second player had " << mana2.ranku 
			<< " of " << numarInLitera(mana2.valoare) << "\n";
		return true;
	}
	else if (poz1 < poz2)
	{
		fout << "The second player wins with " << mana2.ranku 
			<< " of " << numarInLitera(mana2.valoare) << "\n";
		fout << "The first player had " << mana1.ranku 
			<< " of " << numarInLitera(mana1.valoare) << "\n";
		return false;
	}
	else
	{
		if (mana1.valoare > mana2.valoare)
		{
			fout << "The first player wins with " << mana1.ranku 
				<< " of " << numarInLitera(mana1.valoare) << "\n";

			fout << "The second player had " << mana2.ranku 
				<< " of " << numarInLitera(mana2.valoare) << "\n";
			return true;
		}
		else if (mana1.valoare < mana2.valoare)
		{
			fout << "The second player wins with " << mana2.ranku 
				<< " of " << numarInLitera(mana2.valoare) << "\n";

			fout << "The first player had " << mana1.ranku 
				<< " of " << numarInLitera(mana1.valoare) << "\n";
			return false;
		}
		else if (mana1.ranku == "twoPairs" || mana1.ranku == "fullHouse")
		{
			if (mana1.valoare2 > mana2.valoare2)
			{
				fout << "The first player wins with " << mana1.ranku 
					<< " of " << numarInLitera(mana1.valoare) << " and " 
					<< numarInLitera(mana1.valoare2) << "\n";

				fout << "The second player had " << mana2.ranku 
					<< " of " << numarInLitera(mana2.valoare) << " and " 
					<< numarInLitera(mana2.valoare2) << "\n";
				return true;
			}
			else if (mana1.valoare2 < mana2.valoare2)
			{
				fout << "The second player wins with " << mana2.ranku 
					<< " of " << numarInLitera(mana2.valoare) << " and " 
					<< numarInLitera(mana2.valoare2) << "\n";

				fout << "The first player had " << mana1.ranku 
					<< " of " << numarInLitera(mana1.valoare) << " and " 
					<< numarInLitera(mana1.valoare2) << "\n";
				return false;
			}
		}
		else
		{
			if (castigaPrimulHighCard(mana1, mana2) == 1)
			{
				fout << "The first player wins with " << mana1.ranku << " of " 
					<< numarInLitera(mana1.valoare) << " and highCard of " 
					<< numarInLitera(mana1.highCard) << "\n";

				fout << "The second player had " << mana2.ranku << " of " 
					<< numarInLitera(mana2.valoare) << " and highCard of "
					<< numarInLitera(mana2.highCard) << "\n";
				return true;
			}
			else if (castigaPrimulHighCard(mana1, mana2) == 0)
			{
				fout << "The second player wins with " << mana2.ranku << " of " 
					<< numarInLitera(mana2.valoare) << " and highCard of " 
					<< numarInLitera(mana2.highCard) << "\n";

				fout << "The first player had " << mana1.ranku << " of " 
					<< numarInLitera(mana1.valoare) << " and highCard of " 
					<< numarInLitera(mana1.highCard) << "\n";
				return false;
			}
			else
			{
				fout << "Truly equal, both have " << mana1.ranku << " of "
					<< numarInLitera(mana1.valoare) << "\n";
			}	
		}
	}
}

int main()
{
	clock_t start = clock();

	citire();

	for (int i = 1; i <= n; i++)
	{
		if (primulCastigator(carti1[i], carti2[i]))
			primul++;
	}
	
	fout << "\nThe number of times the first player wins is " << primul << "\n";

	clock_t end = clock();
	double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
	fout << "The program ran in " << time << " ms";
}
