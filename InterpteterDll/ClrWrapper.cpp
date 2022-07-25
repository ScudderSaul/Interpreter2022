// This is the main DLL file.

#pragma region Includes

#include "Stdafx.h"

#include "msclr\marshal_cppstd.h"
using namespace msclr::interop;

#include "ClrWrapper.h"
using namespace ClrWrapper;

#pragma endregion

#pragma managed

ManagedLanguage::ManagedLanguage(void)
{
	m_Impl = new Language();
	m_Impl->SetStringOut();
}

ManagedLanguage::~ManagedLanguage(void)
{
	if(m_Impl)
	{
		delete m_Impl;
		m_Impl = NULL;
	}
}

ManagedLanguage::!ManagedLanguage(void)
{
	if(m_Impl)
	{
		delete m_Impl;
		m_Impl = NULL;
	}
}

void ManagedLanguage::Input(String ^ input, String ^ command)
{
	IntPtr ip = Marshal::StringToHGlobalAnsi(input);
    char* inputstr = static_cast<char*>(ip.ToPointer());

	IntPtr ip2 = Marshal::StringToHGlobalAnsi(command);
    char* cmdstr = static_cast<char*>(ip2.ToPointer());

	int ret = m_Impl->Parse(inputstr, cmdstr);

	//std::string ins = marshal_as<std::string>(input);
	//std:string nm = marshal_as<std::string>(command);
	//int ret = m_Impl->Parse(ins, nm);
}


void ManagedLanguage::Input(String ^ input)
{
//IntPtr ip = Marshal::StringToHGlobalAnsi(input);
 // char* inputstr = static_cast<char*>(ip.ToPointer());

	String ^ cmd = "input";
	std::string cmdstr = marshal_as<std::string>(cmd);

	std::string instr = marshal_as<std::string>(input);


	int ret = m_Impl->Parse(instr, cmdstr);

	//std::string ins = marshal_as<std::string>(input);
	//std:string nm = marshal_as<std::string>(command);
	//int ret = m_Impl->Parse(ins, nm);
}



String ^ ManagedLanguage::GetOut(void)
{
	std::string gstr;
    gstr.clear();

	std::getline(m_Impl->GetStringOut(), gstr);
				
	return(marshal_as<System::String^>(gstr));

}

bool ManagedLanguage::DoneOut()
{
	if(m_Impl->GetStringOut().fail())
	{
		m_Impl->GetStringOut().clear();  
		return(true);
	}
	return(false);
}

String ^ManagedLanguage::GetTrace(void)
{
	std::string gstr;
    gstr.clear();

	std::getline(m_Impl->GettraceStream(), gstr);
				
	return(marshal_as<System::String^>(gstr));

}

bool ManagedLanguage::DoneTrace()
{
	if(m_Impl->GettraceStream().fail())
	{
		m_Impl->GettraceStream().clear();  
		return(true);
	}
	return(false);
}
			
		

