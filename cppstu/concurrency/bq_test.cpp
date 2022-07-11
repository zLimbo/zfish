#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

#include "BlockingQueue.h"

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::erase(v, 2);
    for (int x : v) {
        printf("%d ", x);
    }
    printf("\n");
    BlockingQueue<std::pair<int, int>> bq(10);

    for (int i = 0; i < 10; ++i) {
        bq.put(i, i);
    }

    std::thread consumer([&] {
        while (true) {
            int t = rand() % 3;
            sleep(t);
            auto [x, y] = bq.take();
            printf("consumer take [%d, %d], queue size: %d\n", x, y,
                   (int)bq.size());
        }
    });

    std::thread producer([&] {
        int x = 0;
        while (true) {
            int t = rand() % 3;
            sleep(t);
            bq.put();
            printf("producer put [%d, %d], queue size: %d\n", x, x,
                   (int)bq.size());
            ++x;
        }
    });

    consumer.join();
    producer.join();
    return 0;
}

