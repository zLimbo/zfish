#ifndef LABYRINTH_H_INCLUDED
#define LABYRINTH_H_INCLUDED

#include "../algorithm"
#include <cstdlib>
#include <ctime>
using namespace std;
typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;

typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN;

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }

struct Cell {
    int x, y;
    Status status;
    ESWN incoming, outgoing;
    Cell(int xx = 0, int yy = 0) : x(xx), y(yy) {}
};

#define LABY_MAX 20
Cell laby[LABY_MAX][LABY_MAX];  // labyrinth

void initMap() {
    srand((unsigned)time(NULL));
    for (int x = 0; x < LABY_MAX; ++x)
        for (int y = 0; y < LABY_MAX; ++y) {
            laby[x][y].x = x;
            laby[x][y].y = y;
            if (x == 0 || y == 0 || x == LABY_MAX - 1 || y == LABY_MAX - 1)
                laby[x][y].status = WALL;
            else
                laby[x][y].status = (rand() % 5) == 0 ? WALL : AVAILABLE;
        }
}

void showMap() {
    int cnt = -1;
    for (int x = 0; x < LABY_MAX; ++x) {
        for (int y = 0; y < LABY_MAX; ++y) {
            if (laby[x][y].status == WALL)
                cout << "##";
            else if (laby[x][y].status == ROUTE) {
                if (laby[x][y].incoming == UNKNOWN ||
                    laby[x][y].outgoing == UNKNOWN)
                    cout << "oo";
                else if (laby[x][y].outgoing == SOUTH)
                    cout << "v" << (++cnt % 10);
                else if (laby[x][y].outgoing == NORTH)
                    cout << "^" << (++cnt % 10);
                else if (laby[x][y].outgoing == EAST)
                    cout << ">" << (++cnt % 10);
                else if (laby[x][y].outgoing == WEST)
                    cout << "<" << (++cnt % 10);
            } else if (laby[x][y].status == BACKTRACKED)
                cout << "  ";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

inline Cell *neighbor(Cell *cell) {
    switch (cell->outgoing) {
        case EAST:
            return cell + 1;
        case SOUTH:
            return cell + LABY_MAX;
        case WEST:
            return cell - 1;
        case NORTH:
            return cell - LABY_MAX;
        default:
            exit(-1);
    }
}

inline Cell *advance(Cell *cell) {
    Cell *next;
    switch (cell->outgoing) {
        case EAST:
            next = cell + 1;
            next->incoming = WEST;
            break;
        case SOUTH:
            next = cell + LABY_MAX;
            next->incoming = NORTH;
            break;
        case WEST:
            next = cell - 1;
            next->incoming = WEST;
            break;
        case NORTH:
            next = cell - LABY_MAX;
            next->incoming = SOUTH;
            break;
        default:
            exit(-1);
    }
    return next;
}

bool labyrinth(Cell *s, Cell *t) {
    if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false;
    Stack<Cell *> path;
    s->incoming = UNKNOWN;
    s->status = ROUTE;
    path.push(s);
    do {
        Cell *c = path.top();
        if (c == t) return true;
        while (NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
            if (AVAILABLE == neighbor(c)->status) break;
        if (NO_WAY <= c->outgoing) {
            c->status = BACKTRACKED;
            c = path.pop();
        } else {
            path.push(c = advance(c));
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
    } while (!path.empty());

    return false;
}

void findLaby(int x1, int y1, int x2, int y2) {
    Cell *s = &laby[x1][y1];
    Cell *t = &laby[x2][y2];
    if (labyrinth(s, t))
        showMap();
    else
        cout << "There is no route.\n" << endl;
}

#endif  // LABYRINTH_H_INCLUDED
