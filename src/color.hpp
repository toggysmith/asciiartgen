#ifndef ASCIIARTGEN_COLOR_HPP
#define ASCIIARTGEN_COLOR_HPP

#include <cstdint>

#include <SFML/Graphics.hpp>

class Color {
    public:
        Color(const std::uint8_t, const std::uint8_t, const std::uint8_t, const std::uint8_t);
        Color(const sf::Color&);
        bool operator==(const Color&) const;

        const std::uint8_t r;
        const std::uint8_t g;
        const std::uint8_t b;
        const std::uint8_t a;
};

template<>
struct std::hash<Color> {
    std::size_t operator()(const Color& color) const {
        return static_cast<std::size_t>(color.r + color.g + color.b + color.a);
    }
};

#endif