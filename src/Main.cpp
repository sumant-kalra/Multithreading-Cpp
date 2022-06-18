#define MAIN 1
#if MAIN
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

class FileOut
{
private:
    std::ofstream m_file;
    std::mutex m_mutex1;
    std::once_flag m_once;

public:
    FileOut() = default;

    void print1(const std::string &message, int x)
    {

        auto fileOpen = [&]()
        {
            if (!m_file.is_open())
            {
                m_file.open("outFile.txt");
            }
        };

        std::call_once(m_once, fileOpen);

        std::lock_guard<std::mutex> lock1(m_mutex1);
        m_file << message << ": " << x << "\n";
    }

    ~FileOut()
    {
        m_file.close();
    }

    FileOut(const FileOut &file) = delete;
    FileOut &operator=(const FileOut &file) = delete;
};

static void func1(FileOut &file)
{
    for (int i = 0; i < 100; ++i)
    {
        file.print1("From the child thread", i);
    }
}

int main(int argc, char *argv[])
{
    FileOut file;

    std::thread t1(func1, std::ref(file));

    for (int i = -100; i < 0; ++i)
        file.print1("From the main thread", i);

    t1.join();

    return 0;
}
#endif