#include "Process.h"
#define N_PROCESSES 6
#define MIN_NODES 10
#define MAX_NDOES 40

class Main
{
    public:
    std::vector<Process> processes;

    void round_robin()
    {
        while (!processes.empty())
        {
            Process process = processes[0];
            processes.erase(processes.begin());
            process.print();

            for (int i = 0; i < process.priority; ++i)
            {
                if (process.isOver()) break;
                process.run();
            }
            if (process.isOver()) continue;
            processes.push_back(process);
        }
    }

    void work_load_balance()
    {
        Process min = get_min_process();
        std::vector<int> priorities;
        for (int i = 0; i < processes.size(); ++i)
        {
            int priority = ceil(processes[i].flyeye->getE().size() / min.flyeye->getE().size());
            processes[i].priority = priority;
        }
            
    }

    Process get_min_process()
    {
        Process min = processes[0];
        for (auto process:processes)
            if (min.flyeye->getV() > process.flyeye->getV())
                min = process;
        return min;
    }

    void create_processes(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::srand(seed);
            Process p(i, 0, MIN_NODES+rand()%(MAX_NDOES-MIN_NODES+1));
            processes.push_back(p);
        }
    }

    void run()
    {
        create_processes(N_PROCESSES);
        work_load_balance();
        round_robin();
        std::cout << "Execution finished. Press any key in terminal to continue\n";
    }
};

int main()
{
    Main m;
    m.run();
    std::cin.get();
    return 0;
}