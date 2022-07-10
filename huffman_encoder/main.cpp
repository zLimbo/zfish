#include "huffman_encoder.h"

void test();
void test2(int argc, char** argv);

int main(int argc, char** argv) {
    //	test();					// 本地测试

    test2(argc, argv);  // 界面拖动

    return 0;
}

// 本地测试
void test() {
    HuffmanEncoder* hecp = new HuffmanEncoder("test\\pic.png");

    hecp->run();
    //	hecp->printInfo();

    int n = 0;
    for (int i = 0; i < n; ++i) {
        HuffmanEncoder* hecp2 =
            new HuffmanEncoder(hecp->getOutputFileName(), true);
        hecp2->run();
        delete hecp;
        hecp = hecp2;
    }

    delete hecp;
}

// 读取输入（可在界面中拖动）
void test2(int argc, char** argv) {
    if (argc < 2)
        exit(-1);

    HuffmanEncoder* hecp = new HuffmanEncoder(argv[1]);

    hecp->run();

    delete hecp;
    getchar();  // 防止运行界面闪退
}
