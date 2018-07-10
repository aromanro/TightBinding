#include "TBThread.h"


#include "TightBindingFrame.h"

TBThread::TBThread(const Options& options, TightBindingFrame* frame, unsigned int startPoint, unsigned int endPoint)
	: m_options(options), m_frame(frame), m_startPoint(startPoint), m_endPoint(endPoint), terminate(false)
{
}


TBThread::~TBThread()
{
	join();
}

void TBThread::Start()
{
	mThread = std::thread([this]() {
		Calculate();		
	});
}

void TBThread::join()
{
	if (mThread.joinable()) mThread.join();
}


void TBThread::Calculate()
{
	TightBinding::Material &mat = m_frame->bandStructure.materials.materials[std::string(m_options.materialName.c_str())];

	results = m_frame->bandStructure.Compute(mat, m_startPoint, m_endPoint, terminate);

	--m_frame->runningThreads;
}

void TBThread::Terminate()
{
	terminate = true;
}