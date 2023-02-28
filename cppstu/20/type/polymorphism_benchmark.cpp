#include <benchmark/benchmark.h>
#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include <thread>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std;
using namespace fmt;

namespace subtype {

struct Shape {
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
};

struct Circle : Shape {
    Circle(double r) : r_(r) {}
    double getArea() const override {
        return numbers::pi * r_ * r_;
    }
    double getPerimeter() const override {
        return 2 * numbers::pi * r_;
    }
    double r_;
};

struct Rectangle : Shape {
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double getArea() const override {
        return w_ * h_;
    }
    double getPerimeter() const override {
        return 2 * (w_ + h_);
    }
    double w_;
    double h_;
};

}  // namespace subtype

namespace ad_hoc {

struct Circle {
    double r;
};

double getArea(const Circle& c) {
    return numbers::pi * c.r * c.r;
}

double getPerimeter(const Circle& c) {
    return 2 * numbers::pi * c.r;
}

struct Rectangle {
    double w;
    double h;
};

double getArea(const Rectangle& r) {
    return r.w * r.h;
}

double getPerimeter(const Rectangle& r) {
    return 2 * (r.w + r.h);
}

using Shape = variant<Circle, Rectangle>;

double getArea(const Shape& s) {
    return visit([](const auto& data) { return getArea(data); }, s);
}

double getPerimeter(const Shape& s) {
    return visit([](const auto& data) { return getPerimeter(data); }, s);
}

}  // namespace ad_hoc

constexpr int num = 1000000;

static void subtypePerf(benchmark::State& state) {
    using namespace subtype;
    size_t len = num;  // state.range(0);
    for (auto _ : state) {
        vector<unique_ptr<Shape>> shapes;
        shapes.reserve(len);
        for (size_t i = 0; i < len; ++i) {
            if (rand() % 100 > 50) {
                shapes.emplace_back(make_unique<Rectangle>(rand() % 10, rand() % 10));
            } else {
                shapes.emplace_back(make_unique<Circle>(rand() % 10));
            }
        }

        for (const auto& shape : shapes) {
            shape->getArea();
            shape->getPerimeter();
            // benchmark::DoNotOptimize(shape->getArea());
            // benchmark::DoNotOptimize(shape->getPerimeter());
        }
    }
}

static void adhocPerf(benchmark::State& state) {
    using namespace ad_hoc;
    size_t len = num;  // state.range(0);
    for (auto _ : state) {
        vector<Shape> shapes;
        shapes.reserve(len);
        for (size_t i = 0; i < len; ++i) {
            if (rand() % 100 > 50) {
                shapes.emplace_back(Rectangle{rand() % 10 * 1.0, rand() % 10 * 1.0});
            } else {
                shapes.emplace_back(Circle{rand() % 10 * 1.0});
            }
        }
        for (const auto& shape : shapes) {
            getArea(shape);
            getPerimeter(shape);
        }
    }
}

BENCHMARK(subtypePerf);
BENCHMARK(adhocPerf);

BENCHMARK_MAIN();
