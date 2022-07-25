// console_forth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <io.h>
#include <fcntl.h>

#include <cmath>
#include <cfloat>
#include <ctime>
#include <cstdlib>
#include <cstdio>

// #pragma warning(disable: 4786)

#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>

#include "..\codeelement.h"

using namespace std;

//Language lang;

int main(int argc, char* argv[])
{
    Language lang;
    char text[50000];
    int filein;
    string ofilename;

	ofilename = "console_put.txt";
    COORD ab;
    ab.X = 100;
    ab.Y = 5000;

  SetConsoleScreenBufferSize( GetStdHandle(STD_OUTPUT_HANDLE), ab);

  lang.SetStdOut();

    if(argc > 1)
    {
      if((filein = _open(argv[1], _O_RDONLY)) != -1)
      {
         read(filein, text, 50000l);
         close(filein);
         lang.SetOut(ofilename.c_str());
         if(filein != 0)
         {
            lang.Parse(text, NULL);
         }
      }
    }

    DWORD nr;
    text[0] = 0;
    text[1] = 0;
    char *np = &text[0];
    
    while(true)
    {
       ReadConsole(GetStdHandle(STD_INPUT_HANDLE),  np, 1, &nr, NULL);
       if(nr == 1 && *np == '\n') 
       {
         np++;
         (*np) = 0;
         if((np - &text[0]) > 2)
         {
           if(lang.Parse(text, "STDIN") == false)
           {
              ;
           }
         }
         text[0] = 0;
         text[1] = 0;
         np = &text[0];
         lang.Prompt();
       }
       else
       {
         if(nr == 1)
         {
           np++;
           (*np) = 0;
         }
       }
    }

	return 0;
}

