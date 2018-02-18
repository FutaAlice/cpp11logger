#include <thread>
#include <list>
#include "logger.h"

using namespace std;
using namespace logger;

int main()
{
    list<shared_ptr<thread>> oThreads;

    /*
     * console
     */
    for (int i = 0; i < 10; i++)
    {
        oThreads.push_back(shared_ptr<thread>(new thread([=]() {
            for (int j = 0; j < 100; ++j)
                debug() << "Thread " << i << ", Message " << j;
        })));
    }
    for (int i = 0; i < 100; i++)
        debug() << "Main thread, Message " << i;
    for (auto oThread : oThreads)
        oThread->join();

    debug(Level::Info) << "output to console, done.";
    debug(Level::Info) << "press any to continue this test.";
    getchar();
    oThreads.clear();
    /*
     * file log
     */
    for (int i = 0; i < 10; i++)
    {
        oThreads.push_back(shared_ptr<thread>(new thread([=]() {
            for (int j = 0; j < 100; ++j)
                record() << "Thread " << i << ", Message " << j;
        })));
    }
    for (int i = 0; i < 100; i++)
        record() << "Main thread, Message " << i;
    for (auto oThread : oThreads)
        oThread->join();

    debug(Level::Info) << "done.";
    getchar();
    return 0;
}
