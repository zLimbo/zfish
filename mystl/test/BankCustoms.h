#ifndef BANKCUSTOMS_H_INCLUDED
#define BANKCUSTOMS_H_INCLUDED

#include "../Queue.h"
#include <cstdlib>
#include <ctime>

struct Customer {
    int window;
    unsigned int time;
};

int bestWindow(Queue<Customer> *windows, int nWin) {
    int minSize = windows[0].size();
    int optiWin = 0;
    for (int i = 1; i < nWin; ++i)
        if (minSize > windows[i].size()) {
            minSize = windows[i].size();
            optiWin = i;
        }
    return optiWin;
}

void showWin(Queue<Customer> *windows, int nWin, int now) {
    cout << "\nNow timw : " << now << endl;
    for (int i = 0; i < nWin; ++i) {
        cout << "Win " << i << " : ";
        cout << windows[i].size() << endl;
    }
}

void simulate(int nWin, int serTime) {
    srand((unsigned)time(NULL));
    Queue<Customer> *windows = new Queue<Customer>[nWin];
    for (int now = 0; now < serTime; ++now) {
        if (rand() % (1 + nWin)) {
            Customer c;
            c.time = 1 + rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
        for (int i = 0; i < nWin; ++i)
            if (!windows[i].empty())
                if (--windows[i].front().time <= 0) windows[i].dequeue();
        showWin(windows, nWin, now);
    }
    delete[] windows;
}

#endif  // BANKCUSTOMS_H_INCLUDED
