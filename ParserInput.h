

#ifndef PARSERFEED
#define PARSERFEED

#include <queue>
#include "..\codeelement.h"

extern Language lang;

class ParseINput
{
   string parse_what;
   string parse_name;

public:

    ParseInput()
    {
       parse_what.clear();
       parse_name.clear();
    }

    ParseInput(string *in, string & nm)
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

    string & What()
    {
      return(parse_what());
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
   CWinThread* itthread;

   // limit to line length
   char inbuf[6000];
   chae namebuf[100];

public:

   ParseFeeder()
   {
     enditerate = false;
     itthread = NULL;
     skipiterate = 0;
   }

   void StartFeed()
   {
    itthread =    AfxBeginThread(IIterate,  this,   0,   0,   CREATE_SUSPENDED   ,  NULL );
   }

   bool Parse(void)
   {
      if(!input_queue.empty())
      {
          strncpy(inbuf, input_queue.front().What().c_str(), 5999);
          strncpy(namebuf, input_queue.front().Name().c_str(), 5999);
          input_queue.pop();
          lang.Parse(inbuf, namebuf);
          return(true);
      }
      return(false);
   }

   int &Skip(void)
   {
     return(skipiterate);
   }

   bool & End(void)
   {
      return(enditerate);
   }

void ResumeIterate(void)
{
    if(itthread != NULL)
    {
        CWinThread* tstthread = AfxGetThread( );

        if(tstthread != NULL && tstthread->m_nThreadID != itthread->m_nThreadID)
        {
            if(skipiterate > 0)
            {
               skipiterate--;
            }
            if(skipiterate == 0)
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
            skipiterate++;
            SleepEx(020, FALSE);
        }
    }
}

};



#endif