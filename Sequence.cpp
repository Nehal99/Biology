#include "Sequence.h"
#include"DNA.h"
#include <iostream>
#include"Global.h"
#include<cstring>
#include<algorithm>

using namespace std ;

Sequence::Sequence() //Default Constructor
{
    seq = new char ;
}
Sequence:: Sequence(int length) //Parameterized Constructor
{
    sizee = length ;
    seq = new char[sizee+1];
    seq[sizee] = '\0' ;
}
Sequence:: Sequence(Sequence& rhs) //copy constructor to copy all attributes
{
    sizee = rhs.sizee ;
    seq = new char [sizee] ;
    strcpy(seq, rhs.seq ) ;
}
void  Sequence:: Print() // pure virtual function
{

}
void Sequence :: setSequence ( char* se )
{
    strcpy ( seq , se ) ;
}
void Sequence:: setSize ( int s )
{
    sizee = s ;
}
int Sequence:: getSize ()
{
    return sizee ;
}
char* Sequence:: getSequence ()
{
    return seq ;
}
void Sequence:: StringToChar (string s )
{
    for (int i = 0; i < s.length() ; i++)
    {
        seq[i] = s[i] ;
    }
}

Sequence :: ~Sequence()
{
    delete seq;
}
char* Align(Sequence& s1, Sequence& s2) //Get the longest common subsequence of any type of the strands
{
    int row, col ;

    row = s1.sizee ;
    col = s2.sizee ;

    int** arr = new int*[row+1] ;
    for ( int i = 0 ; i <= row ; i++)
    {
        arr[i] = new int [col+1] ;
    }

    for ( int i = 0 ; i <= row ; i++)
    {
        arr[i][0] = 0 ;
    }
    for ( int i = 0 ; i <= col ; i++)
    {
        arr[0][i] = 0 ;
    }

    for (int i=1 ; i <= row ; i++)
    {
        for (int j=1; j <= col; j++)
        {
            if (s1.seq[i-1] == s2.seq[j-1])
            {
                arr[i][j] = arr[i-1][j-1] + 1 ;
            }
            else
            {
                if ( arr[i-1][j] > arr[i][j-1] )
                {
                    arr[i][j] = arr[i-1][j];
                }
                else
                {
                    arr[i][j] = arr[i][j-1];
                }
            }
        }
    }
    int index = arr[row][col];
    char* lcs = new char [index] ;
    lcs[index]='\0' ;
    int i , j ;
    i = row ;
    j = col ;

    while (i > 0 && j > 0)
    {
        if (s1.seq[i-1] == s2.seq[j-1])
        {
            lcs[index-1] = s1.seq[i-1];
            i--;
            j--;
            index--;
        }
        else if (arr[i-1][j] > arr[i][j-1])
        {
            i--;
        }
        else
        {
            j--;
        }
   }
   return lcs ;
}
char* localAlign(Sequence& s1, Sequence& s2)
{
    int row, col , match = 1 , gap = 2 , misMatch = 1 , maxi , maxIndex=0 , cPos = 0 , rPos = 0 ;

    row = s1.sizee ;
    col = s2.sizee ;

    int** arr = new int*[row+1] ;
    for ( int i = 0 ; i <= row ; i++)
    {
        arr[i] = new int [col+1] ;
    }

    for ( int i = 0 ; i <= row ; i++)
    {
        arr[i][0] = 0 ;
    }
    for ( int i = 0 ; i <= col ; i++)
    {
        arr[0][i] = 0 ;
    }

    for (int i=1 ; i <= row ; i++)
    {
        for (int j=1; j <= col; j++)
        {
            if (s1.seq[i-1] == s2.seq[j-1])
            {
                maxi = max((arr[i-1][j]-gap) , (arr[i][j-1]-gap)) ;
                maxi = max (maxi , (arr[i-1][j-1]+match)) ;
                if (maxi < 0 )
                {
                    arr[i][j] = 0 ;
                }
                else
                {
                    arr[i][j] = maxi ;
                }
            }
            else
            {
                maxi = max((arr[i-1][j]-gap) , (arr[i][j-1]-gap)) ;
                maxi = max (maxi , (arr[i-1][j-1]-misMatch)) ;
                if (maxi < 0 )
                {
                    arr[i][j] = 0 ;
                }
                else
                {
                    arr[i][j] = maxi ;
                }
            }
        }
    }

    for (int i = 0 ; i <= row ; i++)
    {
        for (int j = 0 ; j <=col ; j++)
        {
            if (arr[i][j] > maxIndex)
            {
                maxIndex = arr[i][j] ;
                rPos = i ;
                cPos = j ;
            }
        }
    }

    int s = 0 ;
    int i , j ;
    i = rPos ;
    j = cPos ;
    char* temp = new char [i + j] ;
    temp[i+j]='\0' ;

    while (i > 0 && j > 0)
    {
        if (s1.seq[i] == s2.seq[j])
        {
            temp[s] = s1.seq[i];
            i--;
            j--;
            s++ ;
        }
        else if (arr[i-1][j] > arr[i][j-1])
        {
            i--;
        }
        else
        {
            j--;
        }
   }
}

