#pragma once

#include <string>
#include <vector>

#define wxNEEDS_DECL_BEFORE_TEMPLATE

#include <wx/fileconf.h>

class Options
{
public:
	Options();

	// avoid double deletion of m_fileconfig at destruction if copied
	Options(const Options& other)
		:
		nrThreads(other.nrThreads),
		materialName(other.materialName),
		nrPoints(other.nrPoints),
		pathNo(other.pathNo),
		paths(other.paths),
		m_fileconfig(nullptr)
	{
	}

	Options& operator=(const Options& other)
	{
		nrThreads = other.nrThreads;
		materialName = other.materialName;
		nrPoints = other.nrPoints;
		pathNo = other.pathNo;
		paths = other.paths;
		m_fileconfig = nullptr;

		return *this;
	}

	void Load();
	void Save();

	void Open();
	void Close();

	int nrThreads;

	wxString materialName;
	int nrPoints;

	int pathNo;

	std::vector<std::vector<std::string>> paths;

protected:
	wxFileConfig *m_fileconfig;
};

