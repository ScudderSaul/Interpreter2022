//+---------------------------------------------------------------------------------------+
//This file parseinnnnput.h is copyright 2004 by Saul Scudder
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

#ifndef PARSERFEED
#define PARSERFEED

#include "stdafx.h"
#include <queue>
#include "..\codeelement.h"
#include <afxmt.h>

extern Language lang;
extern UINT IIterate(void * pv);
extern UINT OIterate(void * pv);

class ParseInput
{
   string parse_what;
   string parse_name;

public:

    ParseInput()
    {
       parse_what.clear();
       parse_name.clear();
    }

    ParseInput(string &in, string & nm)
    {
      parse_what = in;
      parse_name = nm;
    }

    ParseInput(const ParseInput & pi)
    {
       parse_what = pi.parse_what;
       parse_name = pi.parse_name;
    }

    ParseInput & operator = (const ParseInput & pi)
    {
       parse_what = pi.parse_what;
       parse_name = pi.parse_name;
       return(*this);
    }

    ~ParseInput()
    {
      parse_what.clear();
      parse_name.clear();
    }


    void Fill(string &in, string & nm)
    {
      parse_what = in;
      parse_name = nm;
    }

    string & What()
    {
      return(parse_what);
    }

    string & Name()
    {
      return(parse_name);
    }

    void What(string & in)
    {
       parse_what = in;
    }

    void Name(string & nm)
    {
       parse_name = nm;
    }
};

class ParseFeeder
{
   queue<ParseInput, deque<ParseInput> > input_queue;

   bool enditerate;
   int skipiterate;
   bool suspendstate;
   CWinThread* itthread;

   bool outenditerate;
   int outskipiterate;
   bool outsuspendstate;
   CWinThread* outthread;

   string outbuf;
   string traceoutbuf;
   static CCriticalSection _critSect;
   ParseInput spare;
   ParseInput sparetwo;
   string prompt;

public:

   ParseFeeder()
   {
     enditerate = false;
     itthread = NULL;
     skipiterate = 0;
     suspendstate = false;   // false to start even thought the thread is created suspended

     outenditerate = false;
     outthread = NULL;
     outskipiterate = 0;
     outsuspendstate = false;   // false to start even thought the thread is created suspended
     prompt = "\nForth: ";
     outbuf.clear();
     traceoutbuf.clear();
   }

   ~ParseFeeder()
   {
        if(itthread != NULL)
        {
            itthread->SuspendThread( );
            delete itthread;
        }
       if(outthread != NULL)
        {
            outthread->SuspendThread( );
            delete outthread;
        }
   }

   void StartFeed()
   {
      itthread =    AfxBeginThread(IIterate,  this,   0,   0,   CREATE_SUSPENDED   ,  NULL );
      ResumeIterate();
      SuspendIterate();

      outthread =    AfxBeginThread(OIterate,  this,   0,   0,   CREATE_SUSPENDED   ,  NULL );
      OutResumeIterate();
      OutSuspendIterate();
   }

   void DirectSuspend(void)
   {
      if(itthread != NULL)
      {
         itthread->SuspendThread( );
      }
   }

     void OutDirectSuspend(void)
   {
      if(outthread != NULL)
      {
         outthread->SuspendThread( );
      }
   }

   bool Parse(void)
   {
      bool isempty;
      EmptyFeed(isempty);
      if(isempty == false)
      {
          _critSect.Lock();
          sparetwo = input_queue.front();
          input_queue.pop();      
          _critSect.Unlock();
          AppendOutBufPrompt(sparetwo.What());
          try
          {
            lang.Parse(sparetwo.What(), sparetwo.Name());
          }
          catch(...)
          {
             string err = "\nError at ---> \"";
             err += sparetwo.What();
             err += "\"\n";
             AppendOutBuf(err);
          }

          return(true);
      }
      else
      {
         SleepEx(10, FALSE);
      }
      return(false);
   }


     bool Parse(ParseInput & pi)
   {
       _critSect.Lock();
       input_queue.push(pi);
       _critSect.Unlock();
        return(true);
   }

   bool Parse(string & in, string &nm)
   {
       _critSect.Lock();
       spare.Fill(in, nm);
       input_queue.push(spare);
       _critSect.Unlock();
       return(true);
   }

   // access output buffer

   void AppendOutBuf(string & st)
   {
      _critSect.Lock();
      outbuf += st;
      _critSect.Unlock();
   }

   void AppendOutBufPrompt(string & st)
   {
      _critSect.Lock();
      outbuf += prompt;
      outbuf += st;
      _critSect.Unlock();
   }

   void ClearOutBuf()
   {
       _critSect.Lock();
      outbuf.clear();
      _critSect.Unlock();
   }

   void GetOutBuf(string & ob)
   {
      _critSect.Lock();
      ob = outbuf;
      outbuf.clear();
      _critSect.Unlock();
   }


   // access trace output buffer 

   void AppendTraceOutBuf(string & st)
   {
      _critSect.Lock();
      traceoutbuf += st;
      _critSect.Unlock();
   }

   void ClearTraceOutBuf()
   {
       _critSect.Lock();
      traceoutbuf.clear();
      _critSect.Unlock();
   }

   void GetTraceOutBuf(string & ob)
   {
      _critSect.Lock();
      ob = traceoutbuf;
      traceoutbuf.clear();
      _critSect.Unlock();
   }

   void Skip(int & test)
   {
      _critSect.Lock();
      test = skipiterate;
      _critSect.Unlock();
   }

   void SkipMinus()
   {
      _critSect.Lock();
      skipiterate--;
      _critSect.Unlock();
   }

   void SkipPlus()
   {
      _critSect.Lock();
      skipiterate++;
      _critSect.Unlock();
   }

   void End(bool & test)
   {
      _critSect.Lock();
      test = enditerate;
      _critSect.Unlock();
   }

   void SetEnd(bool & ee)
   {
      _critSect.Lock();
      enditerate = ee;
      _critSect.Unlock();
   }

   void EmptyFeed(bool & ef)
   {
      _critSect.Lock();
      ef = input_queue.empty();
      _critSect.Unlock();
   }

   void StateSuspend(bool vv)
   {
      _critSect.Lock();
       suspendstate = vv;
      _critSect.Unlock();
   }

  void SuspendQuery(bool &vv)
   {
      _critSect.Lock();
       vv = suspendstate;
      _critSect.Unlock();
   }

  void Busy(bool & onoff)
  {
      _critSect.Lock();
     onoff = lang.Busy();
     _critSect.Unlock();
  }

void ResumeIterate(void)
{
    if(itthread != NULL)
    {
        CWinThread* tstthread = AfxGetThread( );

        if(tstthread != NULL && tstthread->m_nThreadID != itthread->m_nThreadID)
        {
            int test;
            Skip(test);
            if(test > 0)
            {
               SkipMinus();
            }
            Skip(test);
            if(test == 0)
            {
              itthread->ResumeThread( );
            }
        }
    }
}

void SuspendIterate()
{
    if(itthread != NULL)
    {
        CWinThread* tstthread = AfxGetThread( );

        if(tstthread != NULL && tstthread->m_nThreadID != itthread->m_nThreadID)
        {
            SkipPlus();
        }
    }
}

// outthread methods;

  void OutSkip(int & test)
   {
      _critSect.Lock();
      test = outskipiterate;
      _critSect.Unlock();
   }

   void OutSkipMinus()
   {
      _critSect.Lock();
      outskipiterate--;
      _critSect.Unlock();
   }

   void OutSkipPlus()
   {
      _critSect.Lock();
      outskipiterate++;
      _critSect.Unlock();
   }

   void OutEnd(bool & test)
   {
      _critSect.Lock();
      test = outenditerate;
      _critSect.Unlock();
   }

   void OutSetEnd(bool & ee)
   {
      _critSect.Lock();
      outenditerate = ee;
      _critSect.Unlock();
   }

      void OutStateSuspend(bool vv)
   {
      _critSect.Lock();
       outsuspendstate = vv;
      _critSect.Unlock();
   }

  void OutSuspendQuery(bool &vv)
   {
      _critSect.Lock();
       vv = outsuspendstate;
      _critSect.Unlock();
   }

  void OutResumeIterate(void)
{
    if(outthread != NULL)
    {
        CWinThread* tstthread = AfxGetThread( );

        if(tstthread != NULL && tstthread->m_nThreadID != outthread->m_nThreadID)
        {
            int test;
            OutSkip(test);
            if(test > 0)
            {
               OutSkipMinus();
            }
            OutSkip(test);
            if(test == 0)
            {
              outthread->ResumeThread( );
            }
        }
    }
}

void OutSuspendIterate()
{
    if(outthread != NULL)
    {
        CWinThread* tstthread = AfxGetThread( );

        if(tstthread != NULL && tstthread->m_nThreadID != outthread->m_nThreadID)
        {
            OutSkipPlus();
        }
    }
}

bool WaitSuspend(int milisec)
{
   bool test;
   int waitsofar;
   int rv = false;

   waitsofar = 0;
   SuspendIterate();

   while(waitsofar < milisec)
   {
      SuspendQuery(test);
      if(test)
      {
         rv = true;
         break;
      }
      SleepEx(10, FALSE);
      waitsofar += 2;
   }
   return(rv);
}

void ClearOutput(void)
{
  OutSuspendIterate();
    if(WaitSuspend(100))
    {
        lang.GetStringOut().str() = "\n";
        if(lang.GetStringOut().fail())
        {
            lang.GetStringOut().clear();  
        }
    }
    ResumeIterate();
    OutResumeIterate();
}

void ClearTraceOutput(void)
{
  OutSuspendIterate();
    if(WaitSuspend(100))
    {
        lang.GettraceStream().str() = "\n";
        if(lang.GettraceStream().fail())
        {
            lang.GettraceStream().clear();  
        }
    }
    ResumeIterate();
    OutResumeIterate();
}

void StopStringTrace(void)  // not perfect but
{
  _critSect.Lock();
  lang.TraceToStringOff();
  _critSect.Unlock();
}

void StartStringTrace(void)  // not perfect but
{
  _critSect.Lock();
  lang.TraceToStringOn();
  _critSect.Unlock();
}

void GetOutputStillFeeding()   // use if input is still being queued
{
    string gstr;
    string tracetmp;
    tracetmp.clear();
    gstr.clear();
    if(WaitSuspend(100))
    {
        getline(lang.GetStringOut(), gstr);
        if(lang.GetStringOut().fail())
        {
            lang.GetStringOut().clear();  
            AppendOutBuf(gstr);
            gstr.clear();
        }
        getline(lang.GettraceStream(), tracetmp); 
        if(lang.GettraceStream().fail())
        {
            lang.GettraceStream().clear();
            AppendTraceOutBuf(tracetmp);
            tracetmp.clear();
        }

    }
    ResumeIterate();
    if(gstr.empty() == false)
    {
        AppendOutBuf(gstr);
    }

    if(tracetmp.empty() == false)
    {
      tracetmp += "\n\r";
      AppendTraceOutBuf(tracetmp);
    }
}




};



#endif