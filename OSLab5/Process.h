#pragma once
class Process
{
public:
	Process(int time, int id);
	Process(const Process &P);
	~Process();
	void setStartTime(const int gtime);
	int Execute(int time, const int gtime);
	int ShowTime();
	int GetFullTime();
	int getID();
	int getWaitingTime();
	const int GetCPUBurst();

private:
	int ID;
	int startTime;
	int CPUburst;
	int leftOverTime;
	int waitingTime;
	int lastExec;
	int finishTime;
};