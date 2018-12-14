#include <iostream>
#include <cstring>
#include <fstream>
#include "Sequence.h"
#include "DNA.h"
#include "RNA.h"
#include "CodonsTable.h"
#include "Protein.h"
#include "Global.h"

using namespace std;

string data;
char* data1;
ifstream file, newfile;
int i = 0;
int j = 0;


int menu(int num)
{
	bool exit = true;
	do
	{
		try
		{
			exit = true;

			cout << " 1- Enter DNA Sequence " << endl << " 2- Get DNA Complementary strand " << endl << " 3- Convert DNA to RNA " << endl
				<< " 4- ADD 2 DNA Sequences " << endl << " 5- IS DNA sequence1 == DNA sequence2 " << endl << " 6- IS DNA sequence1 != DNA sequence2"
				<< endl << " 7- Longest Common Subsequence Of 2 DNA Sequences  " << endl << " 8- Enter RNA Sequence " << endl
				<< " 9- Is RNA sequence1 != RNA sequence2" << endl << " 10- Is RNA sequence1 == RNA sequence2" << endl
				<< " 11- Add 2 RNA sequences " << endl << " 12- Convert RNA To Protein " << endl << " 13- Convert RNA To DNA " << endl
				<< " 14- Longest Common Subsequence Of 2 RNA Sequences " << endl << "15- Enter Protein Sequence "
				<< "16- Is Protein sequence1 != Protein sequence2 " << endl << "17- Is Protein sequence1 == Protein sequence2" << endl
				<< "18- Add 2 Protein sequences " << endl << "19- Get DNA strand that match this Protein " << endl
				<< "20- Longest Common Subsequence Of 2 Protein Sequences " << endl << "21- Exit " << endl;
			cin >> num;

			if (num < 0 || num > 21)
				throw " Invalid Number! Try again ";
		}
		catch (const char* msg)
		{
			exit = false;
			cout << msg << endl;
		}
	} while (exit != true);
	return num;
}
void SaveSequenceToFile(string file_name, char* strand)
{
	strand[strlen(strand)] = '\0';
	ofstream file;

	file.open(file_name.c_str());

	if (file.is_open())
	{
		for (int r = 0; r < strlen(strand); r++)
		{
			file << strand[r];
		}
	}
	else
	{
		cout << "Error while opening the file";
	}
	file.close();
}
void LoadSequenceFromFile(string file_name)
{
	i = 0;
	j = 0;
	file.open(file_name.c_str());

	if (file.is_open())
	{
		char data2;
		while (file >> data2)
		{
			i++;
		}
		data1 = new char[i];
		file.close();

		newfile.open(file_name.c_str());
		while (newfile >> data1[j])
		{
			j++;
		}
	}
	else
	{
		cout << "Error while opening the file";
	}
}
int main()
{
	int choice = 0, load = 0, save = 0;
	string filename;
	char* s = new char;
	char* LCS = new char ;
	DNA d;
	RNA r;
	Protein p;

	while (choice != 21)
	{
		choice = menu(choice);
		if (choice == 1)
		{
			cout << " would you like to load from text file? " << endl << " 1- YES " << " 2- NO " << endl;
			cin >> load;
			if (load == 1)
			{
				cout << " Enter file name ";
				cin >> filename;
				LoadSequenceFromFile(filename);
				d.setDNAsize(i);
				d.setDNAStrand(data1);
			}
			else
			{
				cin >> d;
			}
		}
		else if (choice == 2)
		{
			d.BuildComplementaryStrand();
			d.Print();
			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				s = new char[d.getDNAsize()];
				s[d.getDNAsize()] = '\0 ';
				s = d.toChar();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else if (choice == 3)
		{
			int start, endd;
			cout << " Enter Start ";
			cin >> start;
			d.setStartIndex(start);

			cout << " Enter End: ";
			cin >> endd;
			d.setEndIndex(endd);

			cout << "RNA Strand: ";

			RNA& r1 = (d.ConvertToRNA());
			cout << r1 << endl;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				int value = (endd + 1) - start;
				s = new char[value];
				s[value] = '\0 ';
				s = r1.ToRNAChar();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}

		}
		else if (choice == 4)
		{
			DNA d1;

			cin >> d1;
			cout << " Strand1 + Strand2 = ";

			DNA& d2 = d + d1;
			d2.setType(d.getType());
			cout << d2 << endl;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				int value = d.getDNAsize() + d1.getDNAsize();
				s = new char[value];
				s[value] = '\0 ';
				s = d2.getDNAStrand();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else if (choice == 5)
		{
			DNA d1;
			cin >> d1;

			if (d.getType() == d1.getType())
			{
				cout << " Two types are equal " << endl;
			}
			else
			{
				cout << " Two types aren't equal " << endl;
			}

			if (d == d1)
			{
				cout << " two sequences are equal " << endl;
			}
			else
			{
				cout << " Two sequences aren't equal " << endl;
			}
		}
		else if (choice == 6)
		{
			DNA d1;
			cin >> d1;

			if (d.getType() != d1.getType())
			{
				cout << " Two types aren't equal " << endl;
			}
			else
			{
				cout << " Two types are equal " << endl;
			}

			if (d != d1)
			{
				cout << " Two Sequences aren't equal " << endl;
			}
			else
			{
				cout << " Two Sequences are equal " << endl;
			}
		}
		else if (choice == 7)
		{
			DNA d1;
			cin >> d1;

			char* LCS = Align(d, d1);

			cout << "LCS = " << LCS << endl;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				s = new char[strlen(LCS)];
				s[strlen(LCS)] = '\0 ';
				s = LCS;
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else if (choice == 8)
		{
			cout << " would you like to load from text file? " << endl << " 1- YES " << " 2- NO " << endl;
			cin >> load;
			if (load == 1)
			{
				cout << " Enter file name ";
				cin >> filename;
				LoadSequenceFromFile(filename);
				r.setRNAsize(i);
				r.setRNAStrand(data1);
			}
			else
			{
				cin >> r;

			}
		}
		else if (choice == 9)
		{
			RNA r1;
			cin >> r1;

			if (r.getType() == r1.getType())
			{
				cout << " Two types are equal " << endl;
			}
			else
			{
				cout << " Two types aren't equal " << endl;
			}

			if (r != r1)
			{
				cout << " Two Sequences aren't equal " << endl;
			}
			else
			{
				cout << " Two Sequences are equal " << endl;
			}
		}
		else if (choice == 10)
		{
			RNA r1;
			cin >> r1;

			if (r.getType() == r1.getType())
			{
				cout << " Two types are equal " << endl;
			}
			else
			{
				cout << " Two types aren't equal " << endl;
			}

			if (r == r1)
			{
				cout << " Two Sequences are equal " << endl;
			}
			else
			{
				cout << " Two Sequences are not equal " << endl;
			}
		}
		else if (choice == 11)
		{
			RNA r1;
			cin >> r1;

			RNA& r2 = r + r1;
			r2.setType(r.getType());

			cout << " Strand1 + Strand2 = " << r2;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				int value = r.getRNAsize() + r1.getRNAsize();
				s = new char[value];
				s[value] = '\0 ';
				s = r2.getRNAStrand();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}

		}
		else if (choice == 12)
		{
			CodonsTable c;
			Protein& p1 = (r.ConvertToProtein(c));

			cout << " RNA To Protein is " << p1 << endl;
			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;

			if (save == 1)
			{
				s = new char[p1.getPsize()];
				s[p1.getPsize()] = '\0';
				s = p1.getPStrand();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else if (choice == 13)
		{
			DNA& d3 = (r.ConvertToDNA());

			cout << " RNA To DNA is " << d3;
			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				s = new char[d3.getDNAsize()];
				s[d3.getDNAsize()] = '\0';
				s = d3.getDNAStrand();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);

			}
		}
		else if (choice == 14)
		{
			RNA r1;
			cin >> r1;

			char* LCS = Align(r, r1);
			cout << " LCS = " << LCS << endl;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				s = new char[strlen(LCS)];
				s[strlen(LCS)] = '\0 ';
				s = LCS;
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
			delete LCS;
		}
		else if (choice == 15)
		{
			cout << " would you like to load from text file? " << endl << " 1- YES " << " 2- NO " << endl;
			cin >> load;
			if (load == 1)
			{
				cout << " Enter file name ";
				cin >> filename;
				LoadSequenceFromFile(filename);
				p.setPsize(i);
				p.setPStrand(data1);
			}
			else
			{
				cin >> p;
			}
		}
		else if (choice == 16)
		{
			Protein p1;
			cin >> p1;

			if (p.getType() == p1.getType())
			{
				cout << " Two types are equal " << endl;
			}
			else
			{
				cout << " Two types aren't equal " << endl;
			}

			if (p != p1)
			{
				cout << " Two Sequences aren't equal " << endl;
			}
			else
			{
				cout << " Two Sequences are equal " << endl;
			}
		}
		else if (choice == 17)
		{
			Protein p1;
			cin >> p1;

			if (p.getType() == p1.getType())
			{
				cout << " Two types are equal " << endl;
			}
			else
			{
				cout << " Two types aren't equal " << endl;
			}

			if (p == p1)
			{
				cout << " Two Sequences are equal " << endl;
			}
			else
			{
				cout << " Two Sequences are not equal " << endl;
			}
		}
		else if (choice == 18)
		{
			Protein p1;
			cin >> p1;

			Protein& p2 = p + p1;
			p2.setType(p.getType());
			cout << " Strand1 + Strand2 = " << p2 << endl;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				int value = p.getPsize() + p1.getPsize();
				s = new char[value];
				s[value] = '\0 ';
				s = p2.getPStrand();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else if (choice == 19)
		{
			DNA d2;
			cin >> d2;

			DNA& d3 = *(p.GetDNAStrandsEncodingMe(d2));

			cout << " Protein To DNA is " << d3.getDNAStrand() << endl;
			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				s = new char[d3.getDNAsize()];
				s[d3.getDNAsize()] = '\0 ';
				s = d3.getDNAStrand();
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else if (choice == 20)
		{
			Protein p1;
			cin >> p1;

			LCS = Align(p, p1);
			cout << " LCS = " << LCS << endl;

			cout << " would you like to save in text file? " << endl << " 1- yes 2- NO " << endl;
			cin >> save;
			if (save == 1)
			{
				s = new char[strlen(LCS)];
				s[strlen(LCS)] = '\0 ';
				s = LCS;
				cout << " Enter file name ";
				cin >> filename;
				SaveSequenceToFile(filename, s);
			}
		}
		else
		{
			break;
		}
	}
	delete s;
	delete LCS;
}

