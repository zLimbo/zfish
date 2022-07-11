#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "src/ThreadPool.h"
#include "src/common.h"

int main(int argc, char **argv) {
    assert(argc >= 3);

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(std::stoi(argv[1]));

    int clientNum = std::stoi(argv[2]);

    std::vector<std::future<std::string>> results(clientNum);
    auto start = std::chrono::system_clock::now();

    // spdlog::set_level(spdlog::level::err);
    ThreadPool pool(4);
    for (int i = 0; i < clientNum; ++i) {
        results[i] = pool.put([i, &serverAddr]() {
            int clientFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            spdlog::info("thread {} start build connect...",
                         getCurrentThreadId());
            int ret =
                connect(clientFd, (sockaddr *)&serverAddr, sizeof(serverAddr));
            assert(ret >= 0);

            std::string text = std::string("client ") + std::to_string(i);
            spdlog::info("connect success! send text: {}", text);
            ret = write(clientFd, text.c_str(), text.size());
            char response[1024];
            ret = read(clientFd, response, sizeof(response));
            spdlog::info("server response: {}", response);
            close(clientFd);
            return std::string(response, ret);
        });
    }

    pool.close();

    using Seconds = std::chrono::duration<double>;
    Seconds spendTime = std::chrono::duration_cast<Seconds>(
        std::chrono::system_clock::now() - start);

    for (int i = 0; i < results.size(); ++i) {
        std::string res = results[i].get();
        spdlog::info("request {}, response: [{}]", i, res);
        std::string text = std::string("client ") + std::to_string(i);
        if (res != text) {
            spdlog::error("error: {} != {}", res, text);
        }
        // EXPECT_EQ(res, text);
    }
    spdlog::info("request {}, spend {}s, tps {}", clientNum, spendTime.count(),
                 clientNum / spendTime.count());

    return 0;
}