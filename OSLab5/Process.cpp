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

int Process::Execute(int time, const int gtime)
{
	waitingTime += gtime - lastExec;
	lastExec = gtime + time;
	if (time > leftOverTime)
	{
		leftOverTime -= time;
		return 0;
	}
	else
	{
		finishTime = gtime + time;
		leftOverTime -= time;
		return -leftOverTime; // we passed too much time for some reason
	}
}

int Process::ShowTime()
{
	return leftOverTime;
}

int Process::GetFullTime()
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

const int Process::GetCPUBurst()
{
	return CPUburst;
}
