// ClrWrapper.h

#pragma once

#define FORTHDLL 1
#include "..\\codeelement.h"

using namespace System;
using namespace System::Runtime::InteropServices;

#pragma managed

namespace ClrWrapper {

	public ref class ManagedLanguage
	{
	public:
		ManagedLanguage(void);

		virtual ~ManagedLanguage(void);
		void Input(String ^ input, String ^ command);
		void Input(String ^ input);
		
		bool DoneOut(void);
	    String ^ GetOut(void);
		bool DoneTrace();
		String ^ GetTrace();

	protected:

		!ManagedLanguage(void);


	private:
		Language * m_Impl;

	};




}
