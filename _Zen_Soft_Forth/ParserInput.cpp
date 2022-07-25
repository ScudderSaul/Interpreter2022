//+---------------------------------------------------------------------------------------+
//This file parseinnnnput.cpp is copyright 2004 by Saul Scudder
//It is distributed for non-profit use as freeware and no warranty is given with the use of
//this source for any purpose whatsoever.
//This copyright notice is to remain unmodified in the file
//A license for commercial use of the _Zen_Soft programmers tools may be obtained by sending
//a check for $10.00 to 
//_Zen_Soft c/o 
//Saul Scudder
//358 E Whitton Ave.
//Phoenix AZ 85012
//+---------------------------------------------------------------------------------------+
#include "stdafx.h"
#include "ParserInput.h"

CCriticalSection ParseFeeder::_critSect;

UINT IIterate(void * pv)
 {   
    ParseFeeder * feed = (ParseFeeder *)pv;

    bool myend;
    int test;
    feed->End(myend);
    while(myend == false)
    { 
         feed->Skip(test);
         if(test == 0)
         {    
             feed->Parse();
         }
         else
         {
            feed->StateSuspend(true);
            feed->DirectSuspend();
            feed->StateSuspend(false);
         }

      feed->End(myend); 
    }
    return(0);
}



UINT OIterate(void * pv)
 {   
    ParseFeeder * feed = (ParseFeeder *)pv;

    bool myend;
    int test;
    feed->OutEnd(myend);
    while(myend == false)
    { 
         feed->OutSkip(test);
         if(test == 0)
         {    
             feed->GetOutputStillFeeding();
         }
         else
         {
            feed->OutStateSuspend(true);
            feed->OutDirectSuspend();
            feed->OutStateSuspend(false);
         }

      feed->End(myend); 
    }
    return(0);
}
