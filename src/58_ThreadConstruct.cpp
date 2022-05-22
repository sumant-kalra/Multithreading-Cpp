#define THREAD_CONSTRUCTION 0
#if THREAD_CONSTRUCTION

#include <iostream>
#include <thread>

// SN 0 : Refer the excel sheet listing the problems
#if 0
static bool keyPressed = 0;

static void printConsole()
{
    using namespace std::literals::chrono_literals;
    while (!keyPressed)
    {
        std::cout << "Please press the enter key...\n";
        std::this_thread::sleep_for(1s);
    }
    std::cout << "Enter key is pressed!\n";
}

int main(int argc, char *argv[])
{
    std::thread t1(printConsole);

    std::cin.get();
    keyPressed = true;

    t1.join();
    return 0;
}
#endif

// SN 1
#if 0
static void print1()
{
    std::cout << "Beauty is only skin deep\n";
}

int main(int argc, char *argv[])
{
    std::thread t1(print1);

    if (t1.joinable())
        t1.join();
    return 0;
}
#endif

// SN 2
#if 0
static void print2()
{
    std::cout << "Beauty is only skin deep.\n";
}

int main(int argc, char *argv[])
{
    std::thread t1(print2);
    std::cout << "Where there is no trust, there is no love.\n";
    t1.join();
    return 0;
}
#endif

// SN 3
#if 0
class Print3
{
public:
    void operator()()
    {
        std::cout << "Beauty is only skin deep\n";
    }
};

int main()
{
    std::thread t1((Print3()));

    std::cout << "Where there is no trust, there is no love\n";
    t1.join();
}
#endif

// SN 4
#if 0
class Print4
{
public:
    void operator()(std::string message)
    {
        std::cout << std::this_thread::get_id() << " : " << message << "\n";
    }
};

int main(int argc, char *argv[])
{

    std::string s("Beauty is only skin deep.");
    std::thread t2(Print4(), s);

    std::cout << std::this_thread::get_id() << " : "
              << "Where there is no trust, there is no love.\n";

    std::cout << "t2 threadId: " << t2.get_id() << "\n";

    t2.join();

    std::cout << "The number of concurrent threads supported: " << std::thread::hardware_concurrency() << "\n";

    return 0;
}
#endif

// SN 5
#if 0
class Print5
{
public:
    void operator()(std::string message)
    {
        message = "Trust is the mother of deceit";
        std::cout << std::this_thread::get_id() << " : " << message << "\n";
    }
};

int main(int argc, char *argv[])
{
    std::string s("Beauty is only skin deep");
    std::thread t1(Print5(), std::move(s));

    t1.join();
    return 0;
}
#endif

#endif
