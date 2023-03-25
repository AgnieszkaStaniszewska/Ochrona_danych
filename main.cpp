#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

const int nall = 26;
char tab[nall];

int los(int length)
{
    return ( rand()%length);
}



void gen()
{
    for(int i=0; i<nall; i++)
    {
        bool losuj=1;

        while(losuj)
        {
            tab[i]='a'+los(nall);
            losuj=0;

            for(int j=0; j<i; j++)
            {
                if( tab[i] == tab[j] )
                {
                    losuj=1;
                    break;
                }

            }

        }

    }

}


void zapiszklucz(const char *nameout)
{

    ofstream file(nameout);
    for (int i = 0; i < nall; i++ )
    {
        file << tab[i];
    }

    file.close();
}


void wczytajklucz(const char *namein) {

    ifstream file(namein);

    for (int i = 0; i < nall; i++ )
    {
        file >> tab[i];
    }
    file.close();
}


void koduj(const char *filein, const char *fileout){

    ifstream inputfile(filein);
    ofstream resultfile(fileout);

    char ch;

    while(inputfile >> noskipws >> ch)
        {
            ch = tolower(ch);
            if(isalpha(ch))
            {
                ch=tab[ch - 'a'];
            }
            cout << ch;
            resultfile << ch;
        }
    inputfile.close();
    resultfile.close();

}


void dekoduj(const char *namein)
{
    ifstream inputfile(namein);
    char ch;
    char *dtab = new char[nall];
    for (int i=0; i<nall;i++)
        {
            dtab[i] = '#';
        }

    for (int i=0; i<nall; i++)
        {
            if(isalpha(tab[i]))
            {
                dtab[tab[i]-'a'] = 'a'+i;
            }
        }

    while(inputfile >> noskipws >> ch)
    {
        ch=tolower(ch);
        if(isalpha(ch))
            {
            ch = dtab[ch - 'a'];
            }
        ch = toupper(ch);
        cout<<ch;
    }
inputfile.close();
}


int main () {

    srand(time(NULL));
    gen();
    zapiszklucz("klucz.txt");
    koduj("jawny.txt", "zakodowany.txt");
    wczytajklucz("klucz.txt");
    dekoduj("zakodowany.txt");

return 0;
}
