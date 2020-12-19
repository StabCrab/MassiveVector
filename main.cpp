#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>

#define LENGTH_OF_NUMBER 100000000
using namespace std;
mutex addMutex;
void countBitsWithMutex(const bool *number, long long int begin, long long int end, unsigned long long int& count)
{
    for (long long i = begin; i < end; ++i)
    {
        if (number[i])
        {
            addMutex.lock();
            count++;
            addMutex.unlock();
        }
    }
}

void countBitsWithoutMutex(const bool *number, long long int begin, long long int end, unsigned long long int& count)
{
    for (long long i = begin; i < end; ++i)
    {
        if (number[i])
        {
            count++;
        }
    }
}

void threadCountWithMutex(bool* number, unsigned long long int& count, int numberOfThreads)
{

    vector<thread> th;

    for (int i = 0; i < numberOfThreads; ++i)
    {
        th.push_back(thread(countBitsWithMutex, number, LENGTH_OF_NUMBER * i / numberOfThreads, LENGTH_OF_NUMBER * (i + 1) / numberOfThreads, ref(count)));
    }

    for (auto& t : th)
    {
        t.join();
    }

}

void threadCountWithoutMutex(bool* number, unsigned long long int& count, const int numberOfThreads)
{
    unsigned long long int counting[numberOfThreads];

    for (int i = 0; i < numberOfThreads; ++i)
    {
        counting[i] = 0;
    }

    vector<thread> th;

    for (int i = 0; i < numberOfThreads; ++i)
    {
        th.push_back(thread(countBitsWithoutMutex, number, LENGTH_OF_NUMBER * i / numberOfThreads, LENGTH_OF_NUMBER * (i + 1) / numberOfThreads, ref(counting[i])));
    }

    for (auto& t : th)
    {
        t.join();
    }

    for (int i = 0; i < numberOfThreads; ++i)
    {
        count += counting[i];
    }
}


void filler(bool number[LENGTH_OF_NUMBER], long long begin, long long end)
{
    for (long long i = begin; i < end; ++i)
    {
        if(rand() % 2 == 1)
            number[i] = true;
        else
            number[i] = false;
    }
}
int main()
{
    srand(time(nullptr));
    auto number = new bool[LENGTH_OF_NUMBER];

    thread th1(filler, number, 0 , LENGTH_OF_NUMBER / 2);
    thread th2(filler, number, LENGTH_OF_NUMBER / 2, LENGTH_OF_NUMBER);

    th1.join();
    th2.join();

    cout << "Number is filled" << endl;

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        countBitsWithMutex(number, 0, LENGTH_OF_NUMBER, ref(count));
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout <<"One thread count " <<count <<" elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        threadCountWithMutex(number, ref(count), 2);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Two threads count with mutex " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        threadCountWithoutMutex(number, ref(count), 2);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Two threads count without mutex " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        threadCountWithMutex(number, ref(count), 4);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Four threads count with mutex " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        threadCountWithoutMutex(number, ref(count), 4);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Four threads count without mutex " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        threadCountWithMutex(number, ref(count), 10);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Ten threads count with mutex " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count = 0;
        auto start = chrono::steady_clock::now();
        threadCountWithoutMutex(number, ref(count), 10);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Ten threads count without mutex " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }




}
