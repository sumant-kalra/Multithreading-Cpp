#define MUTEX_MAIN 0
#if MUTEX_MAIN

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

// [4]

/// Shared Resource - Object of FileOut
class FileOut
{
private:
    std::mutex mu;
    std::ofstream m_file;

public:
    FileOut()
    {
        m_file.open("out.txt", std::ofstream::out | std::ofstream::ate);
        if (!m_file.is_open())
        {
            std::cerr << "File could not be opened\n";
            exit(-1);
        }
    }
    ~FileOut()
    {
        m_file.close();
    }
    void print(const std::string &message, int i)
    {
        std::lock_guard<std::mutex> myLock(mu);
        m_file << message << " " << i << "\n";
    }
};

void function(FileOut &file)
{
    for (int i = -100; i < 0; ++i)
        file.print("From the child thread: ", i);
}

int main()
{
    /// Shared Resource - Object of FileOut
    FileOut file;
    std::thread t1(function, std::ref(file));

    for (int i = 0; i < 100; ++i)
        file.print("From the main thread: ", i);

    t1.join();

    return 0;
}

// [2] & [3]
#if 0
std::mutex mu;

static void print(const std::string &message, int i)
{
    std::lock_guard<std::mutex> lock(mu);
    // mu.lock();
    std::cout << message << " " << i << "\n";
    // mu.unlock();
}

static void function()
{
    for (int i = -100; i < 0; ++i)
        print("From the child thread: ", i);
}

int main()
{
    std::thread t1(function);

    for (int i = 0; i <= 100; ++i)
        print("From the main thread: ", i);

    t1.join();

    return 0;
}
#endif

// [1]
#if 0
static void function()
{
    for (int i = -100; i < 0; ++i)
        std::cout << "From the child thread: " << i << "\n";
}

int main()
{
    std::thread t1(function);

    for (int i = 0; i <= 100; i++)
        std::cout << "From the main thread: " << i << "\n";

    t1.join();

    return 0;
}
#endif

#endif