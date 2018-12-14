#ifndef CODONSTABLE_H
#define CODONSTABLE_H
#include <iostream>
#include"Global.h"

using namespace std;


class CodonsTable
{
  	private:
        Codon codons[64];
   	public:
 	 	// constructors and destructor
        CodonsTable();
        ~CodonsTable();
 	 	// function to load all codons from the given text file
        void LoadCodonsFromFile(string codonsFileName);
        Codon getAminoAcid(char* value);
        void setCodon(char * v, char Amino, int index);
        friend class Protein ;
};

#endif // CODONSTABLE_H
