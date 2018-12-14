#ifndef PROTEIN_H
#define PROTEIN_H
#include<iostream>
#include"Sequence.h"
#include"DNA.h"
#include"RNA.h"
#include"CodonsTable.h"
#include"Global.h"

using namespace std;

class DNA ;
class RNA ;

class Protein : public Sequence
{
private:
    Protein_Type type;
    DNA* PDstrand ;
    char* CONCarr ;
public:
    // constructors and destructor
    Protein();
    Protein(char * p,Protein_Type atype, int s);
    void Print() ;
    Protein (Protein & pr);
    Protein  operator= (Protein & pr) ;
    void setPsize ( int s1 ) ;
    void setPStrand ( char* p ) ;
    int getPsize () ;
    void setType (Protein_Type t) ;
    Protein_Type getType () ;
    char* getPStrand () ;
    bool operator!= (const Protein & pr) ;
    bool operator== (const Protein & pr) ;
    Protein& operator+ (const Protein & pr) ;
    friend istream& operator>> (istream& in, Protein& pr) ;
    friend ostream& operator<< (ostream& out, const Protein & pr) ;
    // return an array of DNA sequences that can possibly
    // generate that protein sequence
    DNA* GetDNAStrandsEncodingMe( DNA & bigDNA);
    ~Protein() ;
};

#endif // PROTEIN_H
