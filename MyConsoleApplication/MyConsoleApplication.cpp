
#include <iostream>

// 值多态
#include<variant>
constexpr double pi = 3.14;

struct Circle { double r; };
constexpr double getArea(const Circle& c) {
    return pi * c.r * c.r;
}
constexpr double getPerimeter(const Circle& c) {
    return 2 * pi * c.r;
}

struct Rectangle { double w; double h; };
constexpr double getArea(const Rectangle& c) {
    return c.h * c.w;
}
constexpr double getPerimeter(const Rectangle& c) {
    return 2 * (c.h + c.w);
}
// 为需要进行多态的对象编写重载函数，这样在抉择时就可以进行适配合适的函数，从而实现多态                

using Shape = std::variant<Circle, Rectangle>;
constexpr double getArea(const Shape& c) {
    return std::visit([](const auto& data) {return getArea(data); }, c);
    // getArea到底调用哪个版本，取决于参数c持有的类型，当确定了c所持有的类型时，那么也就确定了调用哪个版本的getArea
}
constexpr double getPerimeter(const Shape& c) {
    return std::visit([](const auto& data) {return getPerimeter(data); }, c);
}

int main() {
    Shape sp = Circle(2);
    auto s = getArea(sp);

    sp = Rectangle(2, 3);
    std::cout << getArea(sp);
}

