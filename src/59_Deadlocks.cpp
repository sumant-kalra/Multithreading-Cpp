#define ONCE_MAIN 0
#define ONCE_REQ_MAIN 0
#define UNIQUE_LOCK_MAIN_1 0
#define DEADLOCKS_MAIN_1 0

#if ONCE_MAIN

#include <fstream>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>

class File
{
private:
    std::ofstream m_file;
    std::mutex m_mu;
    std::once_flag m_once;

public:
    File() = default;

    void print(const std::string &message, int i)
    {
        std::call_once(m_once,
                       [&]()
                       {
                           if (!m_file.is_open())
                           {
                               m_file.open("output.txt");
                           }
                       });

        std::unique_lock<std::mutex> lock(m_mu);
        m_file << message << " " << i << "\n";
    }

    ~File()
    {
        m_file.close();
    }
};

void function(File &f)
{
    for (int i = -100; i < 0; ++i)
        f.print("Child Thread ", i);
}

int main(int argc, char const *argv[])
{
    File f;

    std::thread t1(function, std::ref(f));

    for (int i = 0; i < 100; ++i)
        f.print("Main Thread ", i);

    t1.join();

    return 0;
}

#endif

#if ONCE_REQ_MAIN

#include <fstream>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>

class File
{
private:
    std::ofstream m_file;
    std::mutex m_mu;
    std::mutex m_mu_open;

public:
    File() = default;

    void print(const std::string &message, int i)
    {
        std::unique_lock<std::mutex> lock2(m_mu_open);
        if (!m_file.is_open())
        {
            m_file.open("output.txt");
        }

        std::unique_lock<std::mutex> lock(m_mu);
        m_file << message << " " << i << "\n";
    }

    ~File()
    {
        m_file.close();
    }
};

void function(File &f)
{
    for (int i = -100; i < 0; ++i)
        f.print("Child Thread ", i);
}

int main(int argc, char const *argv[])
{
    File f;

    std::thread t1(function, std::ref(f));

    for (int i = 0; i < 100; ++i)
        f.print("Main Thread ", i);

    t1.join();

    return 0;
}

#endif

#if UNIQUE_LOCK_MAIN_1

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

class File
{
private:
    std::ofstream m_fileOut;
    std::mutex mu;

public:
    File() : m_fileOut("outFile.txt")
    {
        if (!m_fileOut.is_open())
        {
            std::cerr << "[ERROR]: Could not open the file\n";
            exit(-1);
        }
    }

    void print(const std::string &message, int i)
    {
        std::unique_lock<std::mutex> lock1(mu, std::defer_lock);
        lock1.lock();
        m_fileOut << message << " " << i << "\n";
        lock1.unlock();
    }

    ~File()
    {
        m_fileOut.close();
    }
};

void function(File &f)
{
    for (int i = 0; i < 1000; ++i)
        f.print("Child Thread: ", i);
}

int main(int argc, char const *argv[])
{
    File f;

    std::thread t1(function, std::ref(f));

    for (int i = -1000; i < 0; ++i)
        f.print("Main Thread: ", i);

    t1.join();

    return 0;
}

#endif

#if DEADLOCKS_MAIN_1

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
        std::lock(m_mu, m_mu2);
        std::lock_guard<std::mutex> lock1(m_mu, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(m_mu2, std::adopt_lock);
        m_file << message << ": " << i << "\n";
    }

    void print2(const std::string &message, int i)
    {
#if 0
/// Deadlock
        std::lock_guard<std::mutex> lock2(m_mu2);
        std::lock_guard<std::mutex> lock1(m_mu);
#endif
        std::lock(m_mu, m_mu2);
        std::lock_guard<std::mutex> lock1(m_mu, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(m_mu2, std::adopt_lock);
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