class Base1 {
public:
    int base1_1;
    int base1_2;

    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};

class Base2 {
public:
    int base2_1;
    int base2_2;

    virtual void base2_fun1() {}
    virtual void base2_fun2() {}
};

// 多继承
class Derive1 : public Base1, public Base2 {
public:
    int derive1_1;
    int derive1_2;

    // 基类虚函数覆盖
    virtual void base1_fun1() {}
    virtual void base2_fun2() {}

    // 自身定义的虚函数
    virtual void derive1_fun1() {}
    virtual void derive1_fun2() {}
};

class Derive2 : public Derive1 {
public:
    int derive2_1;
    int derive2_2;

    // 基类虚函数覆盖
    virtual void base1_fun2() {}
    virtual void base2_fun1() {}

    // 自身定义的虚函数
    virtual void derive2_fun1() {}
    virtual void derive2_fun2() {}
};

int main() {
    Base1 *d = new Derive2();
    d->base1_fun2();
    Derive1 d2;
    d2.base1_fun2();
}