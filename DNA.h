#ifndef DNA_H
#define DNA_H
#include <iostream>
#include"Sequence.h"
#include"Global.h"

using namespace std;

class RNA ;

class DNA : public Sequence
{
    public:
        DNA();
        DNA(char * seq, DNA_Type atype , int x);
        DNA(const DNA& rhs);
        DNA operator= (const DNA& rhs) ;
        void setStartIndex ( int s ) ;
        void setEndIndex ( int e ) ;
        void setDNAStrand ( char* dnas ) ;
        void setDNAsize ( int s1 ) ;
        char* getDNAStrand () ;
        int getDNAsize () ;
        void setType (DNA_Type t) ;
        DNA_Type getType () ;
        char* toChar ( ) ; // conver from complmentary strand to char array
        void Print();
        RNA& ConvertToRNA();
        void BuildComplementaryStrand();
        DNA& operator+ (const DNA& se) ;
        bool operator== (const DNA& se) ;
        bool operator!= (const DNA& se) ;
        ~DNA();
        friend ostream& operator<< (ostream& out, const DNA& d);
        friend istream& operator>> (istream& in,  DNA& d);
     private:
        DNA_Type type;
        DNA* complementary_strand;
        int startIndex;
        int endIndex;
        char* To_Char ;
};


#endif // DNA_H

