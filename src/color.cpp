#include "color.hpp"

Color::Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a)
    : r(r), g(g), b(b), a(a) {}

Color::Color(const sf::Color& color)
    : r(static_cast<uint8_t>(color.r)), g(static_cast<uint8_t>(color.g)), b(static_cast<uint8_t>(color.b)), a(static_cast<uint8_t>(color.a)) {}

bool Color::operator==(const Color& other) const {
    return (r == other.r && g == other.g && b == other.b && a == other.a);
}