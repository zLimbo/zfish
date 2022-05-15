#include <iostream>
#include <string>
#include "Vector.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "EightQueen.h"
#include "Labyrinth.h"
#include "BankCustoms.h"
#include "BinTree.h"
#include "Bitmap.h"
#include "Graph.h"
#include "BST.h"
#include "AVL.h"
#include "Splay.h"
#include "GraphMatrix.h"
#include "B-Tree.h"
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    placeQueens(6);
    return 0;
}

/*
//template <typename T>
void read(int x) {
        cout << x << " ";
}





int main() {
      BinTree<int> b;
      Vector<int> v;
      for (int i = 0; i < 100; ++i)
                v.insert(i);
      buildTree(v, b);
      showTree(b.root());

      return 0;
}
*/
/*

int main() {
        AVL<int> a;

        for (int i = 0; i < 100; ++i) {
                a.insert(i);
        }
        showTree(a.root());
        travIn_R(a.root(), read);
        cout << endl;
        travPost_R(a.root(), read);
        cout << endl;
        travPost_I(a.root(), read);
        cout << endl;
        travPost_II(a.root(), read);
        cout << endl;

        return 0;
}
*/
// error: no matching function for call to ��travPost_R(BinNode<int>*,
// <unresolved overloaded function type>)��|
/*

int main() {
        Splay<int> s;
        for (int i = 0; i < 100; ++i)
                s.insert(i);
        showTree(s.root());
        cout << endl;
        s.search(0);
        showTree(s.root());
        cout << endl;
        s.search(2);
        showTree(s.root());
        cout << endl;
        s.remove(6);
        showTree(s.root());


        return 0;
}
*/

/*
int main() {
        GraphMatrix<char, int> gm;
        for (char ch = 'A'; ch <= 'G'; ++ch)
                gm.insert(ch);
        gm.insert('S');

        gm.insert(1, 2, 0, 2);
        gm.insert(1, 5, 0, 4);
        gm.insert(1, 3, 2, 1);
        gm.insert(1, 6, 3, 1);
        gm.insert(1, 8, 4, 5);
        gm.insert(1, 2, 4, 6);
        gm.insert(1, 3, 6, 5);
        gm.insert(1, 6, 6, 1);
        gm.insert(1, 7, 7, 0);
        gm.insert(1, 1, 7, 2);
        gm.insert(1, 9, 7, 3);

        gm.insert(1, 2, 2, 0);
        gm.insert(1, 5, 4, 0);
        gm.insert(1, 3, 1, 2);
        gm.insert(1, 6, 1, 3);
        gm.insert(1, 8, 5, 4);
        gm.insert(1, 2, 6, 4);
        gm.insert(1, 3, 5, 6);
        gm.insert(1, 6, 1, 6);
        gm.insert(1, 7, 0, 7);
        gm.insert(1, 1, 2, 7);
        gm.insert(1, 9, 3, 7);

        gm.show();
        gm.bfs(0);
        cout << endl;
        gm.dfs(0);
        cout << endl;
        Stack<char> *s = gm.tSort(0);
        s->show();

        gm.pfs(0, PrimPU<char, int>());
        cout << endl;
        gm.pfs(0, DijkstraPU<char, int>());

        return 0;
}
*/
/*
int main() {

        BST<int> b;
        b.insert(5);
        for (int i = 0; i < 27; i += 4)
                b.insert(i);
        for (int i = 3; i < 26; i += 4)
                b.insert(i);
        b.insert(13);
        showTree(b.root());

        b.remove(12);
        cout << "\n";
        showTree(b.root());


        return 0;
}
*/
/*

*/
/*
int main() {
        GraphMatrix<int, int> a;
        for (int i = 0; i < 10; ++i)
                a.insert(i);
        for (int i = 0; i < 10; ++i)
                for (int j = 0; j < 10; ++j)
                        a.insert(i, 1, i, j);
        a.show();
        return 0;
}
*/
/*
int main() {
        string s;
        while (cin >> s) {
                Bitmap2 a(128);
                string s2;
                for (int i = 0; i < s.length(); ++i)
                        if(!a.test(s[i])) {
                                s2 += s[i];
                                a.set(s[i]);
                        }
                cout << s2 << endl;
        }


        return 0;
}
*/
/*
void read(int x) {
        cout << x << " ";
}


int main() {
        BinTree<int> a;
        a.insertAsRoot(1);
        BinNode<int>* t = a.insertAsLC(a.root(), 2);

        t = a.insertAsLC(t, 3);
        for (int i = 0; i < 10; ++i)
                t = a.insertAsLC(t, i);
        t = a.root();
        for (int i = 100; i < 110; ++i)
                t = a.insertAsRC(t, i);


        showTree(a.root());



        return 0;
}
*/
/*
void convert(Stack<char>& S, int64_t n, int base) {
        static char digit[] =
                { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'A', 'B', 'C', 'D', 'E', 'F' };
        while (0 < n) {
                int remainder = (int)(n % base);
                S.push(digit[remainder]);
                n /= base;
        }
}

int main() {
        int64_t n = 1850;
        Stack<char> s;
        convert(s, n, 10);
        s.show();
        while (!s.empty()) cout << s.pop();
        cout << endl;

        return 0;
}
*/
/*
int64_t convert(int64_t n, int base) {
        Stack<char> S;
        convert(S, n, base);
        int64_t m = 0;
        while (!S.empty())
                m = m * 10 + S.pop();
        return m;
}

int main() {
        int64_t n = 1000;
        int64_t m = convert(n, 8);
        cout << m << endl;
        n = convert(m, 10);
        cout << n << endl;

        return 0;
}
*/
/*
int main() {
        Queue<int> q;
        cout << q.empty() << endl;
        for (int i = 0; i < 100; ++i)
                q.enqueue(i);
        for (int i = 0; i < 100; ++i)
                cout << q.dequeue() << " ";
        cout << endl;
        return 0;
}
*/
/*
int main() {
        srand((unsigned)time(NULL));
        List<int> a;
        int n = 100;
        for (int i = 0; i < n; ++i)
                a.insertAsLast(i);
        for (int i = 0; i < n; ++i)
                a.insertAsLast(i);
        a.insertAsSucc(a.begin(), 100);
        a.insertAsPred(a.rbegin(), 1000);
        a.sort(a.begin(), a.size(), 2);
        a.uniquify();
        a.show();
        List<int> b(a);
        b.show();
        b.clear();
        b.show();

        return 0;
}

*/

/*
#include <iostream>
#include <cstdio>
using namespace std;

#define DEFAULT_CAPACITY 4   //Ĭ�ϳ�ʼ���ռ��С
typedef int Rank;       //�ȼ�Ϊ����

template <typename T>     //ջ�ṹ
class Stack {
private:
        T *_elem;
        Rank _size;
        int _capacity;
protected:
        void expand() {         //����
                if (_size < _capacity) return;
                T *oldElem = _elem;
                _elem = new T[_capacity <<= 1];
                for (int i = 0; i != _size; ++i)
                        _elem[i] = oldElem[i];
                delete[] oldElem;
        }

public:
        Stack(): _capacity(DEFAULT_CAPACITY), _size(0) {   //����
                _elem = new T[_capacity];
        }
        ~Stack() { delete[] _elem; }     //����
        int size() { return _size; }         //������
        int capacity() { return _capacity; }   //ADT����
        bool empty() { return !_size; }       //�п�
        T top() { return _elem[_size - 1]; }   //ջ��
        void push(const T &e) {                  //��ջ
                expand();
                _elem[_size] = e;
                ++_size;
        }
        T pop() {                                   //��ջ
                if (!_size) return 0;
                T e = _elem[_size - 1];
                --_size;
                return e;
        }
        void show() {                      //debug��
                cout << _size << " " << _capacity << endl;
                for (Rank i = 0; i !=_size; ++i)
                        cout << _elem[i] << " ";
                cout << endl;
        }
};


template <typename T>           //ѭ������ADT
class CirQueue {
private:
        T *_elem;
        int _capacity;
        Rank head;              //ͷ��
        Rank rear;               //β��
protected:
        Rank rNext(Rank r) { return (r + 1) % _capacity; } //����ѭ����������һλ��
        void expand() {                             //����
                if (rNext(rear) != head) return;
                T *oldElem = _elem;
                Rank oldHead = head;
                Rank oldRear = rear;
                int oldCapa = _capacity;
                _elem = new T[_capacity <<= 1];
                head = 0; rear = 0;
                while (oldHead != oldRear) {
                        enqueue(oldElem[oldHead]);
                        oldHead = (oldHead + 1) % oldCapa;
                }
                delete[] oldElem;
        }
public:
        CirQueue(): _capacity(DEFAULT_CAPACITY) {        //����
                _elem = new T[_capacity];
                head = 0;
                rear = 0;
        }
        int size() { return (rear - head + _capacity) % _capacity; } //��С
        int capacity() { return _capacity; }                   //����
        bool empty() { return head == rear; }  //�п�
        void enqueue(const T &e) {                              //���
                expand();
                _elem[rear] = e;
                rear = rNext(rear);
        }
        T dequeue() {                                  //����
                T e = _elem[head];
                head = rNext(head);
                return e;
        }
        T front() { return _elem[rNext(head)]; }   //�׽ڵ�
        void show() {                                         //debug��
                cout << size() << " " << _capacity << endl;
                cout << head << " " << rear << endl;
                Rank iTmp = head;
                while (iTmp != rear) {
                        cout << _elem[iTmp] << " ";
                        iTmp = rNext(iTmp);
                }
        }
};

int main() {
        cout << "�����ж�" << endl;
        char ch;
        Stack<char> s;
        CirQueue<char> q;
        while (true) {
        cout << "������������Ҫ�жϻ��ĵ��ַ�����\"#\"�Ž�������";
        while (cin >> ch && ch != '#') {           //��ջ�����
                s.push(ch);
                q.enqueue(ch);
        }
        bool isPalindrome = true;
        while (!s.empty() && !q.empty()) {         //һһ�ж�
                if (s.pop() != q.dequeue()) {
                        isPalindrome = false;
                        break;
                }
        }
        cout << (isPalindrome ? "���ַ����ǻ���" : "���ַ������ǻ���") << endl;
    }

    return 0;
}

*/
