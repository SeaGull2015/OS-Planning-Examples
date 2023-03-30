#pragma once
class Process
{
public:
	Process(int time, int id);
	Process(int time, int id, int starterTime);
	Process(const Process &P);
	~Process();
	void setStartTime(const int gtime);
	int execute(int time, const int gtime);
	int showTime();
	int getFullTime();
	int getID();
	int getWaitingTime();
	int getStartTime();
	const int getCPUBurst();

private:
	int ID;
	int startTime;
	int CPUburst;
	int leftOverTime;
	int waitingTime;
	int lastExec;
	int finishTime;
};