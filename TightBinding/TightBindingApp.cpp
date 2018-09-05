#include "TightBindingApp.h"
#include "TightBindingFrame.h"


wxIMPLEMENT_APP(TightBindingApp);


bool TightBindingApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	frame = new TightBindingFrame("TightBinding", wxPoint(50, 50), wxSize(1024, 800));
	frame->Show(true);

	return true;
}