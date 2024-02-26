// Домашнее задание к занятию «Конкуренция, состояние гонки»
// Задание 2. Прогресс-бар

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include "Timer.h"


std::mutex m1; // for printing a number and a id of threads
std::mutex m2;
std::mutex m3;
std::mutex m4;


void tableHeader()
{
    std::cout << "#\t";
    std::cout << "id\t";
    std::cout << "Progress Bar\t";
    std::cout << "Time";
}

void moveKaretka1(const int progress, const int numberThreadsNow)
{
    std::unique_lock ulc(m1);
    consol_parameter::SetPosition(0, numberThreadsNow + 1);
    //ulc.unlock();
}

void moveKaretka2(const int progress, const int numberThreadsNow)
{
    std::unique_lock ulc(m4);
    std::cout << '\r';
    std::cout << numberThreadsNow << '\t';
    std::cout << std::this_thread::get_id() << '\t';
    std::cout << std::string(progress, char(219));
    ulc.unlock();
}

void progressBar(const int numberThreadsNow)
{
    int progress = 0;
    int total = 12;
    int y = 1;
    moveKaretka1(progress, numberThreadsNow);
    std::unique_lock ulc(m3);
    
    Timer(Timer1);
    Timer1.start();

    while (progress < total)
    {
        
        moveKaretka2(progress, numberThreadsNow);
        std::unique_lock ulc(m2);
        std::cout << char(178);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << '\b';
        std::cout << char(219);
        std::cout << std::string(total - progress, '\t');
        std::cout.flush();
        ++progress;
        
    }
    
    Timer1.print();
    ulc.unlock();
}




int main()
{
    tableHeader();
    int countThreads = 3;
    std::vector<std::thread> vectorThreads(countThreads);
    
    for (size_t i = 0; i < countThreads; i++)
    {
        vectorThreads[i] = std::thread(progressBar, i);
    }
    for (auto& i : vectorThreads)
    {
        i.join();
    }
    std::cout << "\n\n...main end...\n";
}