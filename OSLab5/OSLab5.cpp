// OSLab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <queue>
#include <cstdlib>
#include <string>
#include "Process.h"
#define nonStartProcesses // means that we want processes appear after the start

int timeQuant = 10;
int contextSwitchTime = 1;

std::vector<Process> input() {
    srand(0);
    std::cout << "Process input" << '\n';
    std::cout << "Time quant?" << '\n';
    std::cin >> timeQuant;
    std::cout << "contextSwitchTime?" << '\n';//l-z
    std::cin >> contextSwitchTime;
    std::string s;
    int id;
    unsigned int cpuburst;
    std::vector<Process> v;
    while (1) {
        std::cout << "Process id" << '\n';
        std::cin >> id;
        std::cout << "Process cpu burst" << '\n';
        std::cin >> cpuburst;
        if (cpuburst < 1) cpuburst = 1;
        v.push_back(Process(cpuburst, id));

        std::cout << "Continue? (y/n)" << '\n';
        std::cin >> s;
        if (std::tolower(s[0]) == 'n') return v;
    }
}

std::vector<Process> makeRandInp(int n) {
    std::vector<Process> v;
    for (int i = 0; i < n; i++) {
        v.push_back(Process(rand() % 100 + 25, i));
    }
    return v;
}

void FCFS(std::vector<Process> v = std::vector<Process>()) {
    int globalTime = 0;

    std::cout << "FCFS\n";
    if (v.empty()) v = input();        
    std::vector<Process> r;
    std::queue<Process> q;
    for (auto& e : v) q.push(e);

    while (!q.empty()) {
        int exectime = q.front().showTime();
        q.front().execute(exectime, globalTime);

        std::cout << "Executed process (id/time/waiting time):"
            << q.front().getID() << ";" << exectime << ";" << q.front().getWaitingTime() << '\n';

        r.push_back(q.front());
        q.pop();
        globalTime += exectime;
    }

    float meantime = 0;
    float waittime = 0;
    for (auto& e : r) {
        meantime += e.getFullTime();
        waittime += e.getWaitingTime();
    }
    meantime /= r.size();
    waittime /= r.size();
    std::cout << "Mean full execution time " << meantime << '\n';
    std::cout << "Mean waiting time " << waittime << '\n';
}

bool execTimeComp(Process& a, Process& b) {
    return a.getCPUBurst() < b.getCPUBurst();
}

void SJF(std::vector<Process> v = std::vector<Process>()) {
    int globalTime = 0;

    std::cout << "SJF\n";
    if (v.empty()) std::vector<Process> v = input();  
    std::sort(v.begin(), v.end(), execTimeComp);
    std::vector<Process> r;
    std::queue<Process> q;
    for (auto& e : v) q.push(e);

    while (!q.empty()) {
        int exectime = q.front().showTime();
        q.front().execute(exectime, globalTime);

        std::cout << "Executed process (id/time/waiting time):"
            << q.front().getID() << ";" << exectime << ";" << q.front().getWaitingTime() << '\n';

        r.push_back(q.front());
        q.pop();
        globalTime += exectime;
    }

    float meantime = 0;
    float waittime = 0;
    for (auto& e : r) {
        meantime += e.getFullTime();
        waittime += e.getWaitingTime();
    }
    meantime /= r.size();
    waittime /= r.size();
    std::cout << "Mean full execution time " << meantime << '\n';
    std::cout << "Mean waiting time " << waittime << '\n';
}


// Вытесняющее планирование

bool startTimeComp(Process& a, Process& b) {
    return a.getStartTime() < b.getStartTime();
}

void RR(std::vector<Process> v = std::vector<Process>()) {
    int globalTime = 0;

    std::cout << "RR\n";
    if (v.empty()) v = input();
    std::vector<Process> r;
#ifndef nonStartProcesses
    std::vector<Process> operationalVector(v); // we're going to work with this Vector
    std::vector<Process> processesToAdd;
#else
    std::vector<Process> operationalVector;
    std::vector<Process> processesToAdd;
    for (auto& e : v) {
        if (e.getStartTime() == 0) {
            operationalVector.push_back(e);
        }
        else processesToAdd.push_back(e);
    }
    std::sort(processesToAdd.begin(), processesToAdd.end(), startTimeComp);
#endif

    int curr = 0;
    while (!operationalVector.empty() || !processesToAdd.empty()) {
        int exectime = operationalVector[curr].showTime();
        globalTime -= operationalVector[curr].execute(timeQuant, globalTime);
        std::cout << "Executed process (id/time/waiting time):"
            << operationalVector[curr].getID() << ";" << exectime << ";" << operationalVector[curr].getWaitingTime() << '\n';
        if (operationalVector[curr].showTime() <= 0) {
            r.push_back(operationalVector[curr]);
            operationalVector.erase(std::next(operationalVector.begin(), curr));
            curr--; //we don't wanna adjust pointer if our vector shrinked down, pretty cringe solution tbh fr fr
        }

#ifdef nonStartProcesses
        if (!processesToAdd.empty() && processesToAdd[0].getStartTime() >= globalTime) { // this is actually kinda wrong bc there is no system call that stops current process
            operationalVector.push_back(processesToAdd[0]);
            processesToAdd.erase(processesToAdd.begin());
        }
#endif

        curr++;
        globalTime += timeQuant;
        if (operationalVector.size() > 1) globalTime += contextSwitchTime;
        if (curr >= operationalVector.size()) {
            curr = 0;
        }
    }
    
    float meantime = 0;
    float waittime = 0;
    for (auto& e : r) {
        meantime += e.getFullTime();
        waittime += e.getWaitingTime();
    }
    meantime /= r.size();
    waittime /= r.size();
    std::cout << "Mean full execution time " << meantime << '\n';
    std::cout << "Mean waiting time " << waittime << '\n';
}

void SJFP(std::vector<Process> v = std::vector<Process>()) {
    int globalTime = 0;

    std::cout << "SJFP\n";
    if (v.empty()) v = input();
    std::vector<Process> r;
    std::vector<Process> operationalVector;
    std::vector<Process> processesToAdd;
    for (auto& e : v) {
        if (e.getStartTime() == 0) {
            operationalVector.push_back(e);
        }
        else processesToAdd.push_back(e);
    }
    std::sort(operationalVector.begin(), operationalVector.end(), execTimeComp);
    std::sort(processesToAdd.begin(), processesToAdd.end(), startTimeComp);


    while (!operationalVector.empty() || !processesToAdd.empty()) {
        int exectime = operationalVector.front().showTime();
        operationalVector.front().execute(1, globalTime);

        std::cout << "Executed process (id/time/waiting time):"
            << operationalVector.front().getID() << ";" << exectime << ";" << operationalVector.front().getWaitingTime() << '\n';

        if (operationalVector.front().showTime() <= 0) {
            r.push_back(operationalVector.front());
            operationalVector.erase(operationalVector.begin());
        }
        globalTime += 1;
        if (!processesToAdd.empty() && processesToAdd[0].getStartTime() >= globalTime) { // this is actually kinda wrong bc there is no system call that stops current process
            operationalVector.push_back(processesToAdd[0]);
            std::sort(operationalVector.begin(), operationalVector.end(), execTimeComp); // very nasty, though qsort should be pretty fast in better case scenario
            processesToAdd.erase(processesToAdd.begin());
        }
    }

    float meantime = 0;
    float waittime = 0;
    for (auto& e : r) {
        meantime += e.getFullTime();
        waittime += e.getWaitingTime();
    }
    meantime /= r.size();
    waittime /= r.size();
    std::cout << "Mean full execution time " << meantime << '\n';
    std::cout << "Mean waiting time " << waittime << '\n';
}



int main()
{
    //std::vector<Process> v = input();//
    /*std::vector<Process> v = {
        Process(13, 0), Process(4, 1), Process(1, 2)
    };*/
    std::vector<Process> v = {
        Process(3, 0, 0), Process(1, 1, 1)
    };
    timeQuant = 4;
    contextSwitchTime = 0;
    /*FCFS(v);
    SJF(v);
    RR(v);*/
    SJFP(v);
    std::cout << "Hello World!\n";
}

