#include "Options.h"

#include <wx/stdpaths.h> 


Options::Options()
	: nrThreads(2), materialName("GaP"), nrPoints(600), pathNo(0),
	paths{ { {"K", "W", "X", "G", "L", "W"}, 
			 {"L", "G", "X", "K", "G" }, 
			 {"W", "G", "X", "W", "L", "G"}, 
			 {"L", "G", "X", "W", "K", "G"}, 
			 {"L", "G", "X", "U", "K", "G"}, 
			 {"G", "X", "K", "G", "L", "K", "W", "X"}, 
			 {"G", "X", "W", "L", "G", "K", "W", "U"}, 
			 {"G", "X", "W", "L", "G", "K"},
			 {"G", "X", "W", "G", "U", "X"},
			 {"L", "G", "X", "U", "G"}
		} },
	m_fileconfig(nullptr)
{
}


void Options::Open()
{
	if (m_fileconfig) return;

	wxString dir = wxStandardPaths::Get().GetConfigDir() + wxFileName::GetPathSeparator();

	if(!wxFileName::DirExists(dir))
		wxFileName::Mkdir(dir, 0777, wxPATH_MKDIR_FULL);

	wxString iniFilePath = dir + "TightBinding.ini";

	m_fileconfig = new wxFileConfig("TightBinding", wxEmptyString, iniFilePath);

	wxConfigBase::Set(m_fileconfig);
}

void Options::Close()
{
	delete m_fileconfig;
	m_fileconfig = NULL;
	wxConfigBase::Set(NULL);
}

void Options::Load()
{
	wxConfigBase *conf=wxConfigBase::Get(false);
	if (conf)
	{
		nrThreads = conf->ReadLong("/nrThreads", 2);
		materialName = conf->Read("/materialName", "Si");
		nrPoints = conf->ReadLong("/nrPoints", 600);
		pathNo = conf->ReadLong("/pathNo", 0);
	}
}

void Options::Save()
{
	wxConfigBase *conf=wxConfigBase::Get(false);
	if (conf)
	{
		conf->Write("/nrThreads", static_cast<long int>(nrThreads));
		conf->Write("/materialName", materialName);
		conf->Write("/nrPoints", static_cast<long int>(nrPoints));
		conf->Write("/pathNo", static_cast<long int>(pathNo));
	}

	if (m_fileconfig)
		m_fileconfig->Flush();
}
