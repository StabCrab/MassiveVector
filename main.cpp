#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>

#define LENGTH_OF_NUMBER 1000000000
using namespace std;

void countBits(bool *number, long long int begin, long long int end, unsigned long long int& count)
{
    for (long long i = begin; i < end; ++i)
    {
        if (number[i])
            count++;
    }
}

void twoThreadCount(bool* number, unsigned long long int& count)
{
    unsigned long long int count1 = 0;
    unsigned long long int count2 = 0;

    thread th1(countBits, number, 0, LENGTH_OF_NUMBER / 2, ref(count1));
    thread th2(countBits, number, LENGTH_OF_NUMBER / 2, LENGTH_OF_NUMBER, ref(count2));

    th1.join();
    th2.join();

    count = count1 + count2;
}

void fourThreadCount(bool* number, unsigned long long int& count)
{
    unsigned long long int count1 = 0;
    unsigned long long int count2 = 0;
    unsigned long long int count3 = 0;
    unsigned long long int count4 = 0;

    thread th1(countBits, number, 0, LENGTH_OF_NUMBER / 4, ref(count1));
    thread th2(countBits, number, LENGTH_OF_NUMBER / 4, LENGTH_OF_NUMBER / 2, ref(count2));
    thread th3(countBits, number, LENGTH_OF_NUMBER / 2, LENGTH_OF_NUMBER / 4 * 3, ref(count3));
    thread th4(countBits, number, LENGTH_OF_NUMBER / 4 * 3, LENGTH_OF_NUMBER, ref(count4));

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    count = count1 + count2 + count3 +count4;
}

void tenThreadCount(bool* number, unsigned long long int& count)
{
    unsigned long long int count1 = 0;
    unsigned long long int count2 = 0;
    unsigned long long int count3 = 0;
    unsigned long long int count4 = 0;
    unsigned long long int count5 = 0;
    unsigned long long int count6 = 0;
    unsigned long long int count7 = 0;
    unsigned long long int count8 = 0;
    unsigned long long int count9 = 0;
    unsigned long long int count10 = 0;



    thread th1(countBits, number, 0, LENGTH_OF_NUMBER / 10, ref(count1));
    thread th2(countBits, number, LENGTH_OF_NUMBER / 10, LENGTH_OF_NUMBER / 5, ref(count2));
    thread th3(countBits, number, LENGTH_OF_NUMBER / 5, LENGTH_OF_NUMBER / 10 * 3, ref(count3));
    thread th4(countBits, number, LENGTH_OF_NUMBER / 10 * 3, LENGTH_OF_NUMBER / 10 * 4, ref(count4));
    thread th5(countBits, number, LENGTH_OF_NUMBER / 10 * 4, LENGTH_OF_NUMBER / 2, ref(count5));
    thread th6(countBits, number, LENGTH_OF_NUMBER / 2, LENGTH_OF_NUMBER / 10 * 6, ref(count6));
    thread th7(countBits, number, LENGTH_OF_NUMBER / 10 * 6, LENGTH_OF_NUMBER / 10 * 7, ref(count7));
    thread th8(countBits, number, LENGTH_OF_NUMBER / 10 * 7, LENGTH_OF_NUMBER / 10 * 8, ref(count8));
    thread th9(countBits, number, LENGTH_OF_NUMBER / 10 * 8, LENGTH_OF_NUMBER / 10 * 9, ref(count9));
    thread th10(countBits, number, LENGTH_OF_NUMBER / 10 * 9, LENGTH_OF_NUMBER, ref(count10));


    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();

    count = count1 + count2 + count3 +count4 + count5 + count6 + count7 +count8 + count9 + count10;
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
        countBits(number, 0 ,LENGTH_OF_NUMBER, ref(count));
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout <<"One thread count " <<count <<" elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count;
        auto start = chrono::steady_clock::now();
        twoThreadCount(number, ref(count));
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Two threads count " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count;
        auto start = chrono::steady_clock::now();
        fourThreadCount(number, ref(count));
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Four threads count " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }

    {
        unsigned long long int count;
        auto start = chrono::steady_clock::now();
        tenThreadCount(number, ref(count));
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<< "Ten threads count " << count << " elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }




}
