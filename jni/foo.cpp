#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
const int TEST_NUM_THREADS=32;

class Timer {
public:
    Timer(std::vector<std::chrono::microseconds>& record_)
        :start(std::chrono::high_resolution_clock::now()),
        record(record_)
    {
    }
    ~Timer()
    {
        const std::chrono::time_point<std::chrono::high_resolution_clock>
            end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds diff 
            = std::chrono::duration_cast
                <std::chrono::microseconds>(end - start);
        record.push_back(diff);
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::vector<std::chrono::microseconds>& record;
};
static size_t get_average_time(const std::vector<std::vector<std::chrono::microseconds>>& record)
{
    size_t time = 0;
    size_t count = 0;
    for(const auto& durations : record){
        count += durations.size();
        for(const auto& d : durations){
            time += d.count();
        }
    }
    return time/count;
}
static void foo(std::vector<std::chrono::microseconds>& record)
{
    Timer t(record);
    throw std::runtime_error("x");
}

int main(int argc, char**) {
    for(int t = 1;t<=64;t=t<<1){
       std::vector<std::vector<std::chrono::microseconds>> record(t);
       #pragma omp parallel for num_threads(t)
        for(int i=0;i<10000;i++){
            try {
                foo(record[omp_get_thread_num()]);
            }catch (...){
            }
        }
        std::cout<<"threads="<<t<<" average_time="<<get_average_time(record)<<"us"<<std::endl;
    }
    return EXIT_SUCCESS;
}
