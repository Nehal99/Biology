#include "RNA.h"
#include"Global.h"
#include"Sequence.h"
#include"CodonsTable.h"
#include"Protein.h"
#include<iostream>
#include"DNA.h"
#include<cstring>

using namespace std ;

Protein::Protein()  //Default Constructor
{
    type = Cellular_Function;
    seq = new char ;
}
Protein::Protein(char* p, Protein_Type atype , int s) : Sequence(s)  //Parameterized Constructor
{
    seq = p ;
    type = atype ;
}
Protein :: Protein(Protein& pr) //copy constructor to copy all attributes
{
    type = pr.type ;
    sizee = pr.sizee ;
    seq = pr.seq ;
}
Protein Protein:: operator= (Protein& pr) //Assignment Operator to copy all attributes
{
    strcpy (seq , pr.seq) ;
    sizee = pr.sizee ;
    type = pr.type ;
    return *this ;
}
void Protein:: setPStrand ( char* p )
{
    seq[sizee] = '\0' ;
    for (int i = 0; i < sizee; i++)
    {
        seq[i] = p[i] ;
    }
}
void Protein:: setPsize ( int s1 )
{
    sizee = s1 ;
}
char* Protein:: getPStrand ( )
{
  return seq ;
}
int Protein:: getPsize ( )
{
    return sizee ;
}
void Protein::  setType(Protein_Type t)
{
    type = t ;
}
Protein_Type Protein:: getType()
{
    return type ;
}
DNA* Protein:: GetDNAStrandsEncodingMe(DNA & bigDNA) // Get DNA strand that possibly produce protein strand
{
    string filename ;
    PDstrand= new DNA ;
    CodonsTable c ;
    int z=0, c1 = 0 , SZ=0 ;

    char* seq1 = new char [bigDNA.getSize()+1] ;  //To Do Operations on Protected DNA Sequence
    char* seq2 = new char [bigDNA.getSize()+1] ;  //Final DNA Sequence

    char found[4] ;

    found[4] = '\0' ;
    seq1[bigDNA.getSize()] = '\0' ;
    seq2[bigDNA.getSize()] = '\0' ;

    strcpy(seq1, bigDNA.getSequence()) ;

    cout << " Enter file name " ;
    cin >> filename ;
    c.LoadCodonsFromFile(filename) ;

    for (int i = 0 ; i < bigDNA.getSize() ; i++)  // convert DNA TO RNA
    {
        if (seq1[i]=='T')
        {
            seq1[i] = 'U' ;
        }
    }

    for ( int i = 0 ; i < bigDNA.getSize() ; i++)
    {
        found[0] = seq1[i] ;
        found[1] = seq1[i+1] ;
        found[2] = seq1[i+2] ;

        c.getAminoAcid(found).AminoAcid  ;

        if ( seq[c1] == ( c.getAminoAcid(found).AminoAcid ))
        {
            for (int j=0 ; j < 3 ; j++)
            {
                seq2[z]=found[j];
                z++ ;
                SZ++ ;
            }
            c1++;
            i+=2;
            if(c1==sizee)
            {
                c1=0;
            }
        }
        else
        {
            c1=0;
            i -= z ;
        }
    }
    for (int i = 0 ; i < SZ ; i++) //Get Again DNA
    {
        if (seq2[i]=='U')
        {
            seq2[i] = 'T' ;
        }
    }
    PDstrand->setDNAsize(SZ) ;
    PDstrand->setDNAStrand(seq2);
    return PDstrand ;
}
void Protein :: Print() //print type and protein strand
{
    cout << "type is " << type << endl ;
    cout << "Sequence is " << seq << endl ;
}
Protein& Protein:: operator+ (const Protein& pr) //concatenate two Protein strands
{
    Protein* p= new Protein ;
    int j = sizee ;

    p->sizee = sizee + pr.sizee ;
    p->seq =new char [p->sizee] ;
    p->seq[p->sizee]= '\0';

    for (int i = 0 ; i < sizee ; i++)
    {
        p->seq[i] = seq[i] ;
    }
    for (int i = 0 ; i < pr.sizee ; i++)
    {
        p->seq[j] = pr.seq[i] ;
        j++ ;
    }
    return *p ;
}
bool Protein :: operator== (const Protein& pr)  //it check if the length of two strands are equal
{
    if (sizee == pr.sizee)
    {
        for (int i = 0 ; i < sizee ; i++)
        {
            if(seq[i] != pr.seq[i])
            {
                return false ;
            }
        }
        return true ;
    }
    return false ;
}
bool Protein :: operator!= (const Protein& pr)  //it check if the length of two strands aren't equal
{
    if (sizee== pr.sizee)
    {
        for (int i = 0 ; i < sizee ; i++)
        {
            if(seq[i] != pr.seq[i])
            {
                return true ;
            }
        }
        return false ;
    }
    return true ;
}
ostream& operator<< (ostream& out, const Protein& pr)
{

    for (int i = 0 ; i < pr.sizee ; i++)
    {
        out << pr.seq[i] ;
    }
    cout << endl << " type is " ;
    if (pr.type == 0 )
    {
        cout << " Hormon " << endl ;
    }
    if (pr.type == 1 )
    {
        cout << " Enzyme " << endl ;
    }
    if (pr.type == 2 )
    {
        cout << " TF " << endl ;
    }
    if (pr.type == 3 )
    {
        cout << " Cellular Function " << endl ;
    }
    return out ;
}
istream& operator>> (istream& in, Protein& pr)
{
    string strand ;
    int num ;
    bool exit = true ;

    cout << " Enter type number " << endl << " 0- Hormon 1- Enzyme 2- TF 3- Cellular_Function" << endl ;
    cin >> num ;

    if (num == 0)
    {
        pr.type = Hormon ;
    }
    if (num == 1)
    {
        pr.type = Enzyme ;
    }
    if (num == 2)
    {
        pr.type = TF ;
    }
    if (num == 3)
    {
        pr.type = Cellular_Function ;
    }

   do
    {
        try
        {
            exit = true ;
            cout << " Enter Protein sequence " ;
            cin >> strand ;

            for (int i = 0 ; i < strand.length() ; i++)
            {
                if (strand[i]== 'B' || strand[i]== 'J' || strand[i]== 'O' ||strand[i]== 'U' ||strand[i]== 'X' ||strand[i]== 'Z' ) //not available character in protein
                    throw "Invalid Letter! Try again" ;
            }

        }
        catch (const char* msg)
        {
            exit = false ;
            cout << msg << endl ;
        }
    }
    while (exit!= true) ;

    pr.sizee = strand.length() ;
    pr.seq = new char [strand.length()] ;
    for (int i = 0 ; i < strand.length() ; i++)
    {
        pr.seq[i] = strand[i] ;
    }
}
Protein:: ~Protein()
{
    delete PDstrand ;
}
