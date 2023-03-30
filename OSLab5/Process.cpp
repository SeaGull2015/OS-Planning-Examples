#include "Process.h"

Process::Process(int time, int id)
{
	ID = id;
	startTime = 0;
	CPUburst = time;
	leftOverTime = time;
	waitingTime = 0;
	lastExec = 0;
	finishTime = -1;
}

Process::Process(int time, int id, int starterTime)
{
	ID = id;
	startTime = starterTime;
	CPUburst = time;
	leftOverTime = time;
	waitingTime = 0;
	lastExec = 0;
	finishTime = -1;
}

Process::Process(const Process& P)
{
	ID = P.ID;
	startTime = P.startTime;
	CPUburst = P.CPUburst;
	leftOverTime = P.leftOverTime;
	waitingTime = P.waitingTime;
	lastExec = P.lastExec;
	finishTime = P.finishTime;
}

Process::~Process()
{
}

void Process::setStartTime(const int gtime)
{
	startTime = gtime;
}

int Process::execute(int time, const int gtime)
{
	waitingTime += gtime - lastExec;
	lastExec = gtime + time;
	if (time < leftOverTime)
	{
		leftOverTime -= time;
		return 0;
	}
	else
	{
		leftOverTime -= time;
		finishTime = gtime + time + leftOverTime;
		return -leftOverTime; // we passed too much time for some reason
	}
}

int Process::showTime()
{
	return leftOverTime;
}

int Process::getFullTime()
{
	if (finishTime == -1) return -1;
	return finishTime - startTime;
}

int Process::getID()
{
	return ID;
}

int Process::getWaitingTime()
{
	return waitingTime;
}

int Process::getStartTime()
{
	return startTime;
}

const int Process::getCPUBurst()
{
	return CPUburst;
}
