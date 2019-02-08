#include "CodonsTable.h"
#include"Global.h"
#include <fstream>
#include <cstring>

CodonsTable::CodonsTable()
{
    //ctor
}

void CodonsTable:: LoadCodonsFromFile(string codonsFileName)
{
    ifstream file, newfile ;
    string found  = "NON" ;
    file.open(codonsFileName.c_str());
    if ( file.is_open())
    {
        char data ;
        int i = 0, j = 0, n =0 ;
        while ( file >> data )
        {
            i++;
        }
        char* arr = new char [i] ;
        newfile.open(codonsFileName.c_str());
        while ( newfile >> arr[j] )
        {
            j++;
        }
        for (int l = 0 ; l < 64 ; l++ )
        {
            for (int m = 0 ; m <= 3 ; m++)
            {
                if (m < 3)
                {
                    found[m] = arr[n]  ;
                     n++ ;
                }
                if ( m == 3 )
                {
                    if (found == "UAA" || found == "UAG" || found == "UGA")
                    {
                        codons[l].AminoAcid = 0 ;
                    }
                    else
                    {
                        codons[l].AminoAcid = arr[n] ;
                        n++ ;
                    }
                }
                strcpy(codons[l].value,found.c_str());
            }
        }
    }
    else
    {
        cout << " Error while opening the file " ;
    }
}
Codon CodonsTable:: getAminoAcid(char* value)
{
    Codon c4 ;
    for (int i = 0 ; i < 64 ;i++)
    {
        string v = value ;
        if ( (codons[i].value) == v )
        {
            c4.AminoAcid = codons[i].AminoAcid ;
            return c4 ;
        }

    }

}
void CodonsTable:: setCodon(char * v, char Amino, int index)
{
    codons[index].AminoAcid = Amino ;
    strcpy(codons[index].value, v) ;
}
CodonsTable:: ~CodonsTable()
{

}
