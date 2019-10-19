#include "TightBindingFrame.h"

#include "OptionsFrame.h"

#include "wx/aboutdlg.h"
#include "wx/statline.h"
#include "wx/generic/aboutdlgg.h"

#include <vtkAutoInit.h>


VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#define MY_VTK_WINDOW 102

#define ID_CALCULATE 105

wxBEGIN_EVENT_TABLE(TightBindingFrame, wxFrame)
EVT_MENU(ID_CALCULATE, TightBindingFrame::OnCalculate)
EVT_UPDATE_UI(ID_CALCULATE, TightBindingFrame::OnUpdateCalculate)
EVT_MENU(wxID_EXIT, TightBindingFrame::OnExit)
EVT_MENU(wxID_PREFERENCES, TightBindingFrame::OnOptions)
EVT_MENU(wxID_ABOUT, TightBindingFrame::OnAbout)
EVT_TIMER(101, TightBindingFrame::OnTimer)
EVT_ERASE_BACKGROUND(TightBindingFrame::OnEraseBackground)
wxEND_EVENT_TABLE()


TightBindingFrame::TightBindingFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size),
	timer(this, 101), runningThreads(0)
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_CALCULATE, "C&alculate\tCtrl+a", "Starts computing");
	menuFile->Append(wxID_SEPARATOR);
	menuFile->Append(wxID_EXIT);

	wxMenu *menuView = new wxMenu;
	menuView->Append(wxID_PREFERENCES);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuView, "&View");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Welcome to Tight Binding!");

	m_pVTKWindow = new wxVTKRenderWindowInteractor(this, MY_VTK_WINDOW);
	m_pVTKWindow->UseCaptureMouseOn();
	//m_pVTKWindow->DebugOn();
	m_pVTKWindow->DebugOff();

	ConstructVTK();

	std::vector<std::vector<double>> empty_results;
	std::vector<unsigned int> empty_pos;
	std::vector<std::string> empty_strings;
	ConfigureVTK("", empty_results, empty_pos, empty_strings);
	
	currentOptions.Open();
	currentOptions.Load();
}


TightBindingFrame::~TightBindingFrame()
{
	DestroyVTK();
	if (m_pVTKWindow) m_pVTKWindow->Delete();
}

void TightBindingFrame::ConstructVTK()
{
	pRenderer = vtkRenderer::New();
	pContextView = vtkContextView::New();

	vtkRenderWindow *pRenderWindow = m_pVTKWindow->GetRenderWindow();
	pRenderWindow->AddRenderer(pRenderer);
	pContextView->SetInteractor(pRenderWindow->GetInteractor());
	//pContextView->GetInteractor()->Initialize();

	pChart = vtkChartXY::New();
	pChart->SetRenderEmpty(true);		
	pContextView->GetScene()->AddItem(pChart);
}

void TightBindingFrame::DestroyVTK()
{
	if (pChart) pChart->Delete();
	if (pRenderer) pRenderer->Delete();
	if (pContextView) pContextView->Delete();

	currentOptions.Close();
}


void TightBindingFrame::OnCalculate(wxCommandEvent& /*event*/)
{
	Compute();
}

void TightBindingFrame::OnUpdateCalculate(wxUpdateUIEvent& event)
{
	event.Enable(isFinished());
}


void TightBindingFrame::ConfigureVTK(const std::string& name, const std::vector<std::vector<double>>& results, std::vector<unsigned int>& symmetryPointsPositions, const std::vector<std::string>& symmetryPointsLabels)
{
	pChart->ClearPlots();

	if (name.empty()) pChart->SetTitle("Band");
	else
	{
		std::string Name = name;
		Name += " Band";
		pChart->SetTitle(Name.c_str());
	}


	pChart->SetAutoAxes(false);

	pChart->GetAxis(vtkAxis::BOTTOM)->SetTitle("k - Symmetry Points");
	pChart->GetAxis(vtkAxis::LEFT)->SetTitle("Energy (eV)");

	if (results.empty()) return;

	int numPoints = results.size();


	// set up the data table

	vtkNew<vtkTable> table;

	vtkNew<vtkFloatArray> arrX;
	arrX->SetName("X");
	table->AddColumn(arrX.GetPointer());

	for (int i = 0; i < results[0].size(); ++i)
	{
		vtkNew<vtkFloatArray> arrC;
		arrC->SetName((std::string("Y") + std::to_string(i)).c_str());
		table->AddColumn(arrC.GetPointer());
	}

	table->SetNumberOfRows(numPoints);


	// set values for X axis column
	for (int j = 0; j < numPoints; ++j)
		table->SetValue(j, 0, j);


	// now the lines in the chart, each has its own column in the table
	for (int j = 0; j < numPoints; ++j)
		for (int i = 0; i < results[j].size(); ++i)
		  table->SetValue(j, i + 1ULL, results[j][i]);

	// add the lines to the chart
	for (int i = 0; i < results[0].size(); ++i)
	{
	  vtkPlot *line = pChart->AddPlot(vtkChart::LINE);
	  // Use columns 0 and 1 for x and y
	  line->SetInputData(table.GetPointer(), 0, i + 1ULL);
	  
	  // Make the plot green, with a width of 2.0 pixels
	  line->SetColor(0, 128, 0, 255);
	  line->SetWidth(2.0);	
	}

	vtkAxis *xAxis = pChart->GetAxis(vtkAxis::BOTTOM);

	vtkNew<vtkDoubleArray> posArray;
	vtkNew<vtkStringArray> labelsArray;

	

	posArray->SetName("X");
	labelsArray->SetName("X");

	posArray->SetNumberOfValues(symmetryPointsPositions.size() + 1);
	labelsArray->SetNumberOfValues(symmetryPointsPositions.size() + 1);

	unsigned int index = 0;
	for (unsigned int pos : symmetryPointsPositions)
	{
		posArray->SetValue(index, pos);
		labelsArray->SetValue(index, symmetryPointsLabels[index]);
		++index;
	}
	// add the last

	posArray->SetValue(index, numPoints - 1ULL);
	labelsArray->SetValue(index, symmetryPointsLabels[index]);

	xAxis->SetCustomTickPositions(posArray.GetPointer(), labelsArray.GetPointer());	
}

bool TightBindingFrame::isFinished() const
{
	return 0 == runningThreads;
}


void TightBindingFrame::OnOptions(wxCommandEvent& /*event*/)
{

	OptionsFrame *optionsFrame = new OptionsFrame("Options", this);
	optionsFrame->options = currentOptions;
	if (wxID_OK == optionsFrame->ShowModal())
	{
		currentOptions = optionsFrame->options;
		currentOptions.Save();
	}

	delete optionsFrame;
}


void TightBindingFrame::Compute()
{
	if (!isFinished()) return;

	wxBeginBusyCursor();

	computeOptions = currentOptions;

	SetTitle("Computing - TightBinding");

	bandStructure.Initialize(computeOptions.paths[computeOptions.pathNo], computeOptions.nrPoints);

	unsigned int nrThreads = computeOptions.nrThreads;
	if (0 == nrThreads) computeOptions.nrThreads = nrThreads = 1;

	runningThreads = nrThreads;

	const unsigned int nrPoints = bandStructure.GetPointsNumber();
	const unsigned int interval =  nrPoints / nrThreads;

	unsigned int startPoint = 0;
	for (unsigned int i = 0; i < nrThreads; ++i)
	{
		threadsList.push_back(std::make_unique<TBThread>(computeOptions, this, startPoint, std::min(startPoint + interval, nrPoints)));
		startPoint += interval;

		threadsList.back()->Start();
	}

	timer.Start(100);
}


void TightBindingFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{	
	if (isFinished())
	{
		timer.Stop();
		StopThreads();

		SetTitle("Finished - Tight Binding");

		Refresh();
	}
}

void TightBindingFrame::OnEraseBackground(wxEraseEvent &event)
{
  event.Skip(false);
}



void TightBindingFrame::OnExit(wxCommandEvent& /*event*/)
{
	Close(true);
}

void TightBindingFrame::OnAbout(wxCommandEvent& /*event*/)
{
	wxAboutDialogInfo info;

	info.SetName("Tight Binding");

	static const int majorVer = 1;
	static const int minorVer = 0;
	wxString verStr = wxString::Format("%d.%d", majorVer, minorVer);
	info.SetVersion(verStr,	wxString::Format("Version %s", verStr));

	info.SetDescription("   Tight Binding Application   ");
	info.SetLicense("GNU GPL v3.0, see LICENSE file for details");

	info.AddDeveloper("Adrian Roman");

	info.SetWebSite("https://github.com/aromanro/TightBinding", "GitHub repository");


	wxAboutBox(info, this);	
}


void TightBindingFrame::StopThreads(bool cancel)
{
	if (cancel)
		for (auto &thrd : threadsList) thrd->Terminate();

	for (auto &thrd : threadsList)
	{
		thrd->join();

		if (!cancel) bandStructure.results.insert(bandStructure.results.end(), thrd->results.begin(), thrd->results.end());
	}
	threadsList.clear();

	SetTitle("Finished - TightBinding");

	if (!cancel)
		ConfigureVTK(std::string(computeOptions.materialName.c_str()), bandStructure.results, bandStructure.symmetryPointsPositions, bandStructure.GetPath());

	if (wxIsBusy()) wxEndBusyCursor();
}