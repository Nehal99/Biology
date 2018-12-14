#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>
#include"Global.h"

using namespace std ;

class Sequence
{
    public:
        Sequence();
        Sequence(int length) ;
        Sequence(Sequence& rhs) ;
        void StringToChar (string s) ;
        virtual void Print()= 0 ;
        int getSize () ;
        void setSequence(char* se) ;
        void setSize(int s) ;
        char* getSequence () ;
        virtual ~Sequence();
        friend char* Align(Sequence& s1, Sequence& s2);
    protected:
        char* seq;
        int sizee;
};

#endif // SEQUENCE_H
