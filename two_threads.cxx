#include <unistd.h>
#include <pthread.h>

#include <cstdlib>
#include <ctime>
#include <limits>

constexpr const long long SIZE = 4096 * 1024;

long long data[SIZE];

void cache_miss_compute() {
    int i = 0;
    while(i < std::numeric_limits<int>::max()) {
        ++i;
        auto index = random() % SIZE;
        ++data[index];
    }

}

void cache_hit_compute() {
    int i = 0;
    while(i < std::numeric_limits<int>::max()) {
        ++i;
        auto index = random() % 8;
        ++data[index];
    }
}

void* thread_func(void* arg) {
    cache_hit_compute();
    return nullptr;
}

int main(int argc, char *argv[]) {
    srandom(time(nullptr));
    pthread_t thread_id;
    pthread_create(&thread_id, nullptr, thread_func, nullptr);

    pthread_join(thread_id, nullptr);
}
