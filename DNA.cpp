#include "RNA.h"
#include"Global.h"
#include"Sequence.h"
#include"CodonsTable.h"
#include"Protein.h"
#include<iostream>
#include"DNA.h"
#include<cstring>

using namespace std;

DNA::DNA()  //Default Constructor
{
    type = promoter ;
    startIndex = 0;
    endIndex = 0;
    seq = new char ;
}
DNA::DNA(char* seq, DNA_Type atype,int x) : Sequence (x)  //Parameterized Constructor
{
    this->seq = seq ;
    type = atype ;
}
DNA:: DNA(const DNA& rhs)  //copy constructor to copy all attributes
{
    type = rhs.type ;
    sizee = rhs.sizee ;
    seq = rhs.seq ;
}
DNA DNA :: operator= (const DNA& rhs)  //Assignment Operator to copy all attributes
{
    strcpy (seq , rhs.seq) ;
    sizee = rhs.sizee ;
    type = rhs.type ;
    return *this ;
}
void DNA:: setStartIndex ( int s )
{
    startIndex = s ;
}
void DNA:: setEndIndex ( int e )
{
    endIndex = e  ;
}
void DNA:: setDNAStrand ( char* dnas )
{
    seq[sizee] = '\0' ;
    for (int i = 0; i < sizee; i++)
    {
        seq[i] = dnas[i] ;
    }
}
void DNA:: setDNAsize ( int s1 )
{
    sizee = s1;
}
char* DNA:: getDNAStrand ()
{
    return seq ;
}
int DNA:: getDNAsize ()
{
    return sizee;
}
void DNA:: setType(DNA_Type t)
{
    type = t ;
}
DNA_Type DNA:: getType()
{
    return type ;
}
char* DNA ::  toChar ()  //To put the complementary_strand in char array to save it in the file
{
    To_Char = new char [sizee] ;
    To_Char[sizee] = '\0' ;
    for (int i = 0 ; i < sizee ; i++)
    {
        To_Char[i] = complementary_strand->seq[i] ;
    }
    return To_Char ;
}
void DNA:: Print() //print type and complementary_strand
{
    cout << " DNA type: " << type << endl ;
    cout << " complementary strand is: " ;
    for (int i = 0 ; i < sizee ; i++)
    {
        cout << complementary_strand->seq[i] ;
    }
    cout << endl ;
}
void DNA:: BuildComplementaryStrand() //Get the complement of the origin Sequence
{
    complementary_strand = new DNA ;
    for (int i = 0 ; i < sizee ; i++)
    {
        if (seq[i] == 'A')
        {
            complementary_strand->seq[i] = 'T';
        }
        if (seq[i] == 'T')
        {
            complementary_strand->seq[i] = 'A';
        }
        if (seq[i] == 'C')
        {
            complementary_strand->seq[i] = 'G';
        }
        if (seq[i] == 'G')
        {
            complementary_strand->seq[i] = 'C';
        }
    }
}
RNA& DNA:: ConvertToRNA() //Convert DNA Sequence To RNA
{
    int value, counter =0  ;
    value = (endIndex+1)-startIndex ; // GET NUMBER OF LETTERS CHANGED
    char* RNAstrand = new char [value] ;
    RNAstrand[value] = '\0' ;

    for (int i = (startIndex-1); i < endIndex ; i++)
    {
        if (seq[i] == 'T')
        {
            RNAstrand[counter] = 'U';
        }
        else
        {
            RNAstrand[counter] = seq[i] ;
        }
        counter++ ;
    }

    RNA* r = new RNA (RNAstrand , mRNA , value) ;
    delete RNAstrand ;
    return *r ;
}
DNA& DNA :: operator+ (const DNA& se) //concatenate two DNA strands
{
    DNA* d = new DNA ;
    int j = sizee ;
    d->sizee = sizee + se.sizee ;
    d->seq =new char [d->sizee] ;
    d->seq[d->sizee] = '\0';

    for (int i = 0 ; i < sizee ; i++)
    {
        d->seq[i] = seq[i] ;
    }
    for (int i = 0 ; i < se.sizee ; i++)
    {
        d->seq[j] = se.seq[i] ;
        j++ ;
    }

    return *d ;
}
bool DNA :: operator== (const DNA& se)  //it check if the length of two strands are equal
{
    if (sizee == se.sizee)
    {
        for (int i = 0 ; i < sizee ; i++)
        {
            if(seq[i] != se.seq[i])
            {
                return false ;
            }
        }
        return true ;
    }
    return false ;
}
bool DNA :: operator!= (const DNA& se) //it check if the length of two strands aren't equal
{
    if (sizee== se.sizee)
    {
        for (int i = 0 ; i < sizee ; i++)
        {
            if(seq[i] != se.seq[i])
            {
                return true ;
            }
        }
        return false ;
    }
    return true ;
}
DNA :: ~DNA() // Destructor
{
    delete complementary_strand;
    delete To_Char ;
}
ostream& operator<< (ostream& out, const DNA& d)
{
    for (int i = 0; i < d.sizee; i++)
    {
        out << d.seq[i] ;
    }

    cout << endl << " DNA type: " ;
    if (d.type == 0 )
    {
        cout << " Promoter " << endl ;
    }
    if (d.type == 1 )
    {
        cout << " motif " << endl ;
    }
    if (d.type == 2 )
    {
        cout << " tail " << endl ;
    }
    if (d.type == 3 )
    {
        cout << " non coding " << endl ;
    }
    return out ;
}

istream& operator>> (istream& in , DNA& d)
{
    string strand ;
    int num ;
    bool exit = true ;

    cout << " Enter type number " << endl << " 0- promoter 1- motif 2- tail 3- non coding " << endl ;
    cin >> num ;

    if (num == 0)
    {
        d.type = promoter ;
    }
    if (num == 1)
    {
        d.type =  motif ;
    }
    if (num == 2)
    {
        d.type = tail ;
    }
    if (num == 3)
    {
        d.type = noncoding ;
    }

    do
    {
        try
        {
            exit = true ;
            cout << " Enter DNA sequence " ;
            cin >> strand ;

            for (int i = 0 ; i < strand.length() ; i++)
            {
                if (strand[i]== 'A' || strand[i]== 'C' || strand[i]== 'G' ||strand[i]== 'T' )
                {
                    continue ;
                }
                else
                {
                    throw "Invalid Letter! Try again" ;
                }
            }

        }
        catch (const char* msg)
        {
            exit = false ;
            cout << msg << endl ;
        }
    }
    while (exit!= true) ;

    d.sizee = strand.length() ;
    d.seq = new char [strand.length()] ;
    for (int i = 0 ; i < strand.length() ; i++)
    {
        d.seq[i] = strand[i] ;
    }
}
