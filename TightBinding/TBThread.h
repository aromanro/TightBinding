#pragma once

#include <thread>
#include <vector>
#include <atomic>

#include "Options.h"

class TightBindingFrame;

class TBThread
{
public:
	TBThread(const Options& options, TightBindingFrame* frame, unsigned int startPoint, unsigned int endPoint);
	~TBThread();


	void Start();
	void join();

	void Terminate();


	const Options& m_options;

	TightBindingFrame* m_frame;

	unsigned int m_startPoint;
	unsigned int m_endPoint;


	std::vector<std::vector<double>> results;

protected:
	void Calculate();

	std::thread mThread;
	std::atomic_bool terminate;
};

