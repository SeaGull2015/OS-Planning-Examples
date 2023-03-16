// OSLab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <queue>
#include <cstdlib>
#include <string>
#include "Process.h"

std::vector<Process> input() {
    srand(0);
    std::cout << "Process input" << '\n';
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
        int exectime = q.front().ShowTime();
        q.front().Execute(exectime, globalTime);

        std::cout << "Executed process (id/time/waiting time):"
            << q.front().getID() << ";" << exectime << ";" << q.front().getWaitingTime() << '\n';

        r.push_back(q.front());
        q.pop();
        globalTime += exectime;
    }

    float meantime = 0;
    float waittime = 0;
    for (auto& e : r) {
        meantime += e.GetFullTime();
        waittime += e.getWaitingTime();
    }
    meantime /= r.size();
    waittime /= r.size();
    std::cout << "Mean full execution time " << meantime << '\n';
    std::cout << "Mean waiting time " << waittime << '\n';
}

bool execTimeComp(Process& a, Process& b) {
    return a.GetCPUBurst() < b.GetCPUBurst();
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
        int exectime = q.front().ShowTime();
        q.front().Execute(exectime, globalTime);

        std::cout << "Executed process (id/time/waiting time):"
            << q.front().getID() << ";" << exectime << ";" << q.front().getWaitingTime() << '\n';

        r.push_back(q.front());
        q.pop();
        globalTime += exectime;
    }

    float meantime = 0;
    float waittime = 0;
    for (auto& e : r) {
        meantime += e.GetFullTime();
        waittime += e.getWaitingTime();
    }
    meantime /= r.size();
    waittime /= r.size();
    std::cout << "Mean full execution time " << meantime << '\n';
    std::cout << "Mean waiting time " << waittime << '\n';
}

int main()
{
    std::vector<Process> v = input();//
    FCFS(v);
    SJF(v);
    std::cout << "Hello World!\n";
}

