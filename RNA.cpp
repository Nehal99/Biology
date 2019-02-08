#include "RNA.h"
#include"Global.h"
#include"Sequence.h"
#include"CodonsTable.h"
#include"Protein.h"
#include<iostream>
#include"DNA.h"
#include<cstring>

using namespace std;

RNA::RNA() //Default Constructor
{
    type = mRNA ;
    seq = new char ;
}
RNA:: RNA(char* seq, RNA_Type atype, int s) : Sequence (s)  //Parameterized Constructor
{
    this->seq = seq ;
    type = atype ;
}
RNA :: RNA(RNA& rhs) //copy constructor to copy all attributes
{
    type = rhs.type ;
    sizee = rhs.sizee ;
    seq = rhs.seq ;
}
RNA RNA :: operator= (RNA& se) //Assignment Operator to copy all attributes
{
    strcpy (seq , se.seq) ;
    sizee = se.sizee ;
    type = se.type ;
    return *this ;
}
void RNA:: Print()  //print type and RNA sequence
{
    for (int i = 0 ; i < sizee ; i++)
    {
        cout << seq[i] ;
    }
    cout << " RNA type is " << type ;
}
void RNA:: setRNAStrand ( char* r )
{
    seq[sizee] = '\0' ;
    for (int i = 0; i < sizee; i++)
    {
        seq[i] = r[i] ;
    }
}
void RNA:: setRNAsize ( int s1 )
{
    sizee = s1 ;
}
char* RNA:: getRNAStrand ( )
{
  return seq ;
}
int RNA:: getRNAsize ( )
{
    return sizee ;
}
void RNA:: setType(RNA_Type t)
{
    type = t ;
}
RNA_Type RNA:: getType()
{
    return type ;
}
char* RNA ::  ToRNAChar ()  //Put RNA Sequence in char array
{
    RNAChar = new char [sizee] ;
    RNAChar[sizee] = '\0' ;
    for (int i = 0 ; i < sizee ; i++)
    {
        RNAChar [i] = seq[i] ;
    }
    return RNAChar ;
}
DNA& RNA :: ConvertToDNA() //Convert RNA Sequence To DNA
{
    char* DNAstrand = new char [sizee] ;
    DNAstrand[sizee] = '\0';

    for (int i = 0 ; i < sizee ; i++)
    {
        if (seq[i] == 'U')
        {
            DNAstrand[i] = 'T';
        }
        else
        {
            DNAstrand[i] = seq[i] ;
        }
    }

    DNA* d2 = new DNA(DNAstrand ,tail, sizee) ;
    delete DNAstrand ;
    return *d2 ;
}
Protein& RNA :: ConvertToProtein(CodonsTable& table) // Convert RNA Sequence To Protein
{
    Codon c2 ;
    Protein* p = new Protein ;
    string filename ;
    int c = -1  , k=0 , index =0 , counter = 0 ;
    char* codonn = new char [sizee/3] ; // size/3 bec each 3 characters convert to 1 amino acid
    codonn[sizee/3] = '\0' ;
    char stringg[4] ;

    cout << "enter file name " ;
    cin >> filename ;
    table.LoadCodonsFromFile(filename) ;

    for (int i =0 ; i < sizee ; i++)
    {
        stringg[k] = seq[i] ;
        c++ ; // COUNTER TO STOP TO START CHECKING AFTER TAKING 3RD LETTER
        k++ ;
        if (c == 2)
        {
            c2 = table.getAminoAcid(stringg) ; // after filling stringg with 3 characters it sends to the function to get its amino acid
            table.getAminoAcid(stringg).AminoAcid  ;
            if ( c2.AminoAcid == 0 ) // stop codon
            {
                break ; // when it fins a stop codon
            }
            codonn[index] = c2.AminoAcid ;
            index++;
            c = -1 ;
            k = 0 ;
            counter++ ;
        }
    }
    p->setPsize(counter) ;
    p->setPStrand(codonn) ;
    delete codonn ;
    return *p ;
}
RNA& RNA :: operator+ (const RNA& se) //concatenate two RNA strands
{
    RNA* r = new RNA ;
    int j = sizee ;
    r->sizee = sizee + se.sizee ;
    r->seq =new char [r->sizee] ;
    r->seq[r->sizee] = '\0';

    for (int i = 0 ; i < sizee ; i++)
    {
        r->seq[i] = seq[i] ;
    }
    for (int i = 0 ; i < se.sizee ; i++)
    {
        r->seq[j] = se.seq[i] ;
        j++ ;
    }

    return *r ;
}
bool RNA :: operator== (const RNA& se) //it check if the length of two strands are equal
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
bool RNA :: operator!= (const RNA& se) //it check if the length of two strands aren't equal
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
RNA :: ~RNA()
{
    delete RNAChar  ;

}
ostream& operator<< (ostream& out , const RNA& r)
{
    for (int i = 0 ; i < r.sizee ; i++)
    {
        out << r.seq[i] ;
    }
    cout << endl << " RNA type is " ;
    if (r.type == 0 )
    {
        cout << " mRNA " << endl ;
    }
    if (r.type == 1 )
    {
        cout << " pre_mRNA " << endl ;
    }
    if (r.type == 2 )
    {
        cout << " mRNA_exon " << endl ;
    }
    if (r.type == 3 )
    {
        cout << " mRNA_intron " << endl ;
    }
    return out ;
}

istream& operator>> (istream& in , RNA& r)
{
    string strand ;
    int num ;
    bool exit = true ;

    cout << " Enter type number " << endl << " 0- mRNA 1- pre_mRNA 2- mRNA_exon 3- mRNA_intron" << endl ;
    cin >> num ;

    if (num == 0)
    {
        r.type = mRNA ;
    }
    if (num == 1)
    {
        r.type = pre_mRNA ;
    }
    if (num == 2)
    {
        r.type = mRNA_exon ;
    }
    if (num == 3)
    {
        r.type = mRNA_intron ;
    }

    do
    {
        try
        {
            exit = true ;
            cout << " Enter RNA sequence " ;
            cin >> strand ;

            for (int i = 0 ; i < strand.length() ; i++)
            {
                if (strand[i]== 'A' || strand[i]== 'C' || strand[i]== 'G' ||strand[i]== 'U' )
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

    r.sizee = strand.length() ;
    r.seq = new char [strand.length()] ;
    for (int i = 0 ; i < strand.length() ; i++)
    {
        r.seq[i] = strand[i] ;
    }
}
