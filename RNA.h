#ifndef RNA_H
#define RNA_H
#include<iostream>
#include "Sequence.h"
#include"DNA.h"
#include"CodonsTable.h"
#include"Global.h"

using namespace std;

class DNA ;
class CodonsTable ;
class Protein ;

class RNA : public Sequence
{
public:
    RNA();
    RNA(char * seq, RNA_Type atype, int s);
    RNA(RNA& rhs);
    RNA operator= (RNA& se) ;
    void setRNAsize ( int s1 ) ;
    void setRNAStrand ( char* r ) ;
    int getRNAsize () ;
    char* getRNAStrand () ;
    void setType (RNA_Type t) ;
    RNA_Type getType () ;
    char* ToRNAChar () ;
    bool operator!= (const RNA& se) ;
    bool operator== (const RNA& se) ;
    RNA& operator+ (const RNA& se) ;
    void Print();
    Protein& ConvertToProtein(CodonsTable & table);
    DNA& ConvertToDNA();
    friend istream& operator>> (istream& in, RNA& r) ;
    friend ostream& operator<< (ostream& out, const RNA& r) ;
    ~RNA();
private:
    RNA_Type type;
    char* RNAChar ;
};

#endif
