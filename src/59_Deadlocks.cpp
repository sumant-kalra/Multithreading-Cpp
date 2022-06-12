#define DEADLOCKS_MAIN 1
#if DEADLOCKS_MAIN

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>

class File
{
private:
    std::ofstream m_file;
    std::mutex m_mu;
    std::mutex m_mu2;

public:
    File() : m_file("outFile.txt")
    {
        if (!m_file.is_open())
        {
            std::cerr << "[ERROR] Failed to open the file\n";
            exit(-1);
        }
    }

    void print(const std::string &message, int i)
    {
        std::lock_guard<std::mutex> lock1(m_mu);
        std::lock_guard<std::mutex> lock2(m_mu2);
        m_file << message << ": " << i << "\n";
    }

    void print2(const std::string &message, int i)
    {
#if 0
/// Deadlock
        std::lock_guard<std::mutex> lock2(m_mu2);
        std::lock_guard<std::mutex> lock1(m_mu);
#endif
        std::lock_guard<std::mutex> lock1(m_mu);
        std::lock_guard<std::mutex> lock2(m_mu2);
        m_file << message << ": " << i << "\n";
    }

    ~File()
    {
        m_file.close();
    }
};

void fn(File &obj)
{
    for (int i = -100; i < 0; ++i)
        obj.print("Printing from the child thread", i);
}

int main(int argc, char const *argv[])
{
    File file;
    std::thread t1(fn, std::ref(file));

    for (int i = 0; i < 100; ++i)
        file.print2("Printing from the parent thread", i);

    t1.join();

    return 0;
}
#endif