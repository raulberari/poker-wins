#include <fstream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

ifstream fin("carti.txt");
ofstream fout("poker.out");

//n should be less than or equal to 10000
int firstPlayer, secondPlayer, ties, n;

string carti1[100005][10], carti2[100005][10];
string game1[10], game2[10];

string rankri[] = {"highCard", "onePair", "twoPairs", "threeOfAKind",
			"straight", "flush", "fullHouse", "fourOfAKind", "straightFlush",
			"royalFlush"};

struct handStructure
{
	string rank; 
	int value, value2, highCard, frequency[20]; 
	//value determines the primary value of the rank
	//value2 is the secondary value, used in the case of the lower pair from twoPairs and the pair from fullHouse
	//highCard is used if all the other values are equal
	//frequency[] registers the frequency of each card in one hand
};
handStructure hand1, hand2; 


void read()
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

void frequencyReset(int v[], int n)
{
	for (int i = 1; i <= n; i++)
		v[i] = 0;
}

int letterToNumber(string letter)
{
	int nr1;
	nr1 = atoi(letter.c_str());

	if (nr1 == 0)
	{
		if (letter == "T")
			nr1 = 10;
		else if (letter == "J")
			nr1 = 11;
		else if (letter == "Q")
			nr1 = 12;
		else if (letter == "K")
			nr1 = 13;
		else if (letter == "A")
			nr1 = 14;
	}

	return nr1;
}

void sort(string game[], int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int nr1, nr2;
			string letter;
			letter = game[i][0];
			nr1 = letterToNumber(letter);

			letter = game[j][0];
			nr2 = letterToNumber(letter);

			if (nr1 > nr2)
				swap(game[i], game[j]);
		}
	}
}

string rankCalculation(string game[], int &value, int &value2, int frequency[])
{
	string rankReturn = "";

	frequencyReset(frequency, 14);
	sort(game, 5);

	//the letters are transformed into a number and then registered in the frequency array
	for (int i = 1; i <= 5; i++)
	{
		string letter;
		letter = game[i][0];
		int nr = letterToNumber(letter);

		frequency[nr]++;
	}

	//the number of pairs is counted, while the others can be either true or false
	int pairNumber = 0;
	bool threeOfAKind = false, fourOfAKind = false, straight = false, flush = false;

	for (int i = 1; i <= 14; i++)
	{
		if (frequency[i] == 2)
			pairNumber++, value = i; //the value of the highest pair

		if (frequency[i] == 4)
			fourOfAKind = true, value = i;
	}

	for (int i = 1; i <= 14; i++)
	{
		if (frequency[i] == 3)
		{
			threeOfAKind = true;
			value = i; //in the case of another pair coexisting, meaning a fullHouse is created, the primary value shifts to the one of the threeOfAKind
		}
	}

	//comparing the suits
	if (game[1][1] == game[2][1] && game[1][1] == game[3][1] &&
	 game[1][1] == game[4][1] && game[1][1] == game[5][1])
	{
		flush = true;
		for (int i = 1; i <= 14; i++)
		{
			if (frequency[i] == 1)
				value = i;
		}
	}

	//comparing consecutive cards
	for (int i = 1; i <= 10; i++)
	{
		if (frequency[i] == 1 && frequency[i+1] == 1 && frequency[i+2] == 1 &&
			frequency[i+3] && frequency[i+4] == 1)
			straight = true, value = i;
	}
		
	if (straight == true && flush == true && value == 10)
		rankReturn = "royalFlush";

	else if (straight == true && flush == true)
		rankReturn = "straightFlush";

	else if (fourOfAKind == true)
		rankReturn = "fourOfAKind";

	else if (pairNumber == 1 && threeOfAKind == true)
	{
		for (int i = 1; i <= 14; i++)
			if (frequency[i] == 2)
				value2 = i;
		//the secondary value, the one of the pair, is found

		rankReturn = "fullHouse";
	}

	else if (flush == true)
		rankReturn = "flush";

	else if (straight == true)
		rankReturn = "straight";

	else if (threeOfAKind == true)
		rankReturn = "threeOfAKind";

	else if (pairNumber == 2)
	{
		for (int i = 1; i <= 14; i++)
			if (frequency[i] == 2 && i != value)
				value2 = i;
		//the secondary value, the one of the lower pair, is found

		rankReturn = "twoPairs";
	}

	else if (pairNumber == 1)
		rankReturn = "onePair";

	else
	{
		for (int i = 1; i <= 14; i++)
		{
			if (frequency[i] == 1)
				value = i;
		}
		//the primary value is found and returned in the case of other higher ranks not existing
		rankReturn = "highCard";
	}

	return rankReturn;
}

string suits(string letter)
{
	//a function to aid in the ASCII representation of the cards
	string suit;
	if (letter == "S")
		suit= "♠";
	else if (letter == "D")
		suit= "♦";
	else if (letter == "C")
		suit= "♣";
	else if (letter == "H")
		suit= "♥";

	return suit;
}

void printCards(string game[])
{
	//it prints 5 cards with their values and suits

	string letter;

	//the upper margin
	fout << " -------  -------  -------  -------  ------- \n";

	//the values in the upper left corners
	for (int i = 1; i <= 5; i++)
	{
		int a;
		letter = game[i][0];
		a = letterToNumber(letter);
		if (a != 10)
			fout << "|" << game[i][0] << "      |";
		else
			fout << "|" << "10     |";
	}
	fout << "\n";

	//the suits in the upper left corners
	for (int i = 1; i <= 5; i++)
	{
		letter = game[i][1];
		fout << "|" << suits(letter) << "      |";
	}
	fout << "\n";

	//the lateral margins of the cards
	for (int i = 1; i <= 3; i++)
		fout << "|       ||       ||       ||       ||       |\n";

	//the suits in the lower right corners
	for (int i = 1; i <= 5; i++)
	{
		letter = game[i][1];
		fout << "|      " << suits(letter) << "|";
	}
	fout << "\n";

	//the values in the lower right corners
	for (int i = 1; i <= 5; i++)
	{
		int a;
		letter = game[i][0];
		a = letterToNumber(letter);
		if (a != 10)
			fout << "|      " << game[i][0] << "|";
		else
			fout << "|     " << "10|";
	}
	fout << "\n";

	//the lower margin
	fout << " -------  -------  -------  -------  ------- \n";
}

string numberToLetter(int nr)
{
	string letter;
	if (nr <= 10)
		letter = to_string(nr);
	else if (nr == 11)
		letter = "J";
	else if (nr == 12)
		letter = "Q";
	else if (nr == 13)
		letter = "K";
	else if (nr == 14)
		letter = "A";

	return letter;
}

int theFirstOnesWinsHighCard(handStructure &hand1, handStructure &hand2)
{
	//returns 1 if the first player wins, 0 if the second one wins, -1 in the special case of a tie
	int i1 = 14, i2 = 14;
	while (i1 >= 0 && i2 >= 0)
	{
		while (hand1.frequency[i1] == 0 || i1 == hand1.value )
			i1--;
		while (hand2.frequency[i2] == 0 || i2 == hand2.value)
			i2--;

		if (i1 > i2)
		{
			hand1.highCard = i1;
			hand2.highCard = i2;
			return 1;
		}
		if (i2 > i1)
		{
			hand1.highCard = i1;
			hand2.highCard = i2;
			return 0;
		}
		else
			i1--, i2--;
	}
	return -1;
} 

int theFirstWins(string game1[], string game2[])
{

	hand1.rank = rankCalculation(game1, hand1.value, hand1.value2, hand1.frequency);
	hand2.rank = rankCalculation(game2, hand2.value, hand2.value2, hand2.frequency);


	int poz1, poz2;

	for (int i = 0; i < 10; i++)
	{
		if (hand1.rank == rankri[i])
			poz1 = i;

		if (hand2.rank == rankri[i])
			poz2 = i;
	}
	fout << "\n";
	printCards(game1);
	fout << "\n";

	printCards(game2);
	fout << "\n";
	if (poz1 > poz2)
	{
		fout << "The first player wins with " << hand1.rank 
			<< " of " << numberToLetter(hand1.value) << "\n";

		fout << "The second player had " << hand2.rank 
			<< " of " << numberToLetter(hand2.value) << "\n";
		return 1;
	}
	else if (poz1 < poz2)
	{
		fout << "The second player wins with " << hand2.rank 
			<< " of " << numberToLetter(hand2.value) << "\n";
		fout << "The first player had " << hand1.rank 
			<< " of " << numberToLetter(hand1.value) << "\n";
		return 0;
	}
	else
	{
		if (hand1.value > hand2.value)
		{
			fout << "The first player wins with " << hand1.rank 
				<< " of " << numberToLetter(hand1.value);

			if (hand1.rank == "twoPairs" || hand1.rank == "fullHouse")
				fout << " and " << numberToLetter(hand1.value2);

			fout << "\n";

			fout << "The second player had " << hand2.rank 
				<< " of " << numberToLetter(hand2.value);

			if (hand2.rank == "twoPairs" || hand2.rank == "fullHouse")
				fout << " and " << numberToLetter(hand2.value2);

			fout << "\n";

			return 1;
		}
		else if (hand1.value < hand2.value)
		{
			fout << "The second player wins with " << hand2.rank 
				<< " of " << numberToLetter(hand2.value);

			if (hand2.rank == "twoPairs" || hand2.rank == "fullHouse")
				fout << " and " << numberToLetter(hand2.value2);

			fout << "\n";

			fout << "The first player had " << hand1.rank 
				<< " of " << numberToLetter(hand1.value);

			if (hand1.rank == "twoPairs" || hand1.rank == "fullHouse")
				fout << " and " << numberToLetter(hand1.value2);

			fout << "\n";
			return 0;
		}
		else if (hand1.rank == "twoPairs" || hand1.rank == "fullHouse")
		{
			if (hand1.value2 > hand2.value2)
			{
				fout << "The first player wins with " << hand1.rank 
					<< " of " << numberToLetter(hand1.value) << " and " 
					<< numberToLetter(hand1.value2) << "\n";

				fout << "The second player had " << hand2.rank 
					<< " of " << numberToLetter(hand2.value) << " and " 
					<< numberToLetter(hand2.value2) << "\n";
				return 1;
			}
			else if (hand1.value2 < hand2.value2)
			{
				fout << "The second player wins with " << hand2.rank 
					<< " of " << numberToLetter(hand2.value) << " and " 
					<< numberToLetter(hand2.value2) << "\n";

				fout << "The first player had " << hand1.rank 
					<< " of " << numberToLetter(hand1.value) << " and " 
					<< numberToLetter(hand1.value2) << "\n";
				return 0;
			}
			else
			{
				if (theFirstOnesWinsHighCard(hand1, hand2) == 1)
				{
					fout << "The first player wins with " << hand1.rank << " of " 
						<< numberToLetter(hand1.value) << " and " 
						<< numberToLetter(hand1.value2) << " and highCard of " 
						<< numberToLetter(hand1.highCard) << "\n";

					fout << "The second player had " << hand2.rank << " of " 
						<< numberToLetter(hand2.value) << " and " 
						<< numberToLetter(hand2.value2) << " and highCard of "
						<< numberToLetter(hand2.highCard) << "\n";
					return 1;
				}
				else if (theFirstOnesWinsHighCard(hand1, hand2) == 0)
				{
					fout << "The second player wins with " << hand2.rank << " of " 
						<< numberToLetter(hand2.value) << " and " 
						<< numberToLetter(hand2.value2) << " and highCard of " 
						<< numberToLetter(hand2.highCard) << "\n";

					fout << "The first player had " << hand1.rank << " of " 
						<< numberToLetter(hand1.value) << " and " 
						<< numberToLetter(hand1.value2) << " and highCard of " 
						<< numberToLetter(hand1.highCard) << "\n";
					return 0;
				}
				else
				{
					fout << "Truly equal, both have " << hand1.rank << " of "
						<< numberToLetter(hand1.value) << " and " << numberToLetter(hand1.value2) << "\n";
					return -1;
				}
			}
		}
		else
		{
			if (theFirstOnesWinsHighCard(hand1, hand2) == 1)
			{
				fout << "The first player wins with " << hand1.rank << " of " 
					<< numberToLetter(hand1.value) << " and highCard of " 
					<< numberToLetter(hand1.highCard) << "\n";

				fout << "The second player had " << hand2.rank << " of " 
					<< numberToLetter(hand2.value) << " and highCard of "
					<< numberToLetter(hand2.highCard) << "\n";
				return 1;
			}
			else if (theFirstOnesWinsHighCard(hand1, hand2) == 0)
			{
				fout << "The second player wins with " << hand2.rank << " of " 
					<< numberToLetter(hand2.value) << " and highCard of " 
					<< numberToLetter(hand2.highCard) << "\n";

				fout << "The first player had " << hand1.rank << " of " 
					<< numberToLetter(hand1.value) << " and highCard of " 
					<< numberToLetter(hand1.highCard) << "\n";
				return 0;
			}
			else
			{
				fout << "Truly equal, both have " << hand1.rank << " of "
					<< numberToLetter(hand1.value) << "\n";
				return -1;
			}	
		}
	}
}

int main()
{
	clock_t start = clock();

	read();

	for (int i = 1; i <= n; i++)
	{
		int win = theFirstWins(carti1[i], carti2[i]);
		if (win == 1)
			firstPlayer++;
		else if (win == 0)
			secondPlayer++;
		else
			ties++;
	}
	
	fout << "\nThe first player won " << firstPlayer << " times\n";
	fout << "The second player won " << secondPlayer << " times\n";
	fout << "There were " << ties << " ties\n";

	clock_t end = clock();
	double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
	fout << "The program ran in " << time << " ms";
}
