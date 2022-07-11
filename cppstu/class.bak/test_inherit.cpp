
struct A {
    virtual void vfunc() {}
    int a_ = 1;
};

struct B : virtual public A {
    int b_ = 2;
    virtual void vfunc() {}
};

struct C : virtual public A {
    int c_ = 3;
    virtual void vfunc() {}
};

struct D : public B, public C {
    int d_ = 4;
    virtual void vfunc() {}
};


