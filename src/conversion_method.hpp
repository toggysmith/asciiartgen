#ifndef ASCIIARTGEN_CONVERSION_METHOD_HPP
#define ASCIIARTGEN_CONVERSION_METHOD_HPP

#include <cstdint>
#include <tuple>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "color.hpp"

/**
 * @brief An 'enum class' for selecting what method to use to convert RGBA
 * colors to grayscale.
 * 
 * This is a class, which behaves like an enum, and allows methods to be
 * called on that 'enum'. The primary method which can be called is
 * `convert()`.
 */
class ConversionMethod {
    public:
        enum Enum {
            AVERAGE_METHOD,
            WEIGHTED_METHOD,
        };

        constexpr ConversionMethod() = default;
        // WHY: Allow this class to be constructed with an initial Enum constant.
        constexpr ConversionMethod(Enum e) : e(e) {};
        // WHY: Allow comparisons with other Enum constants.
        constexpr operator Enum() const { return e; };
        // WHY: Disallow comparisons such as `if (e)`.
        explicit operator bool() const = delete;

        using GrayscaleIntensity = std::uint8_t;
        using GrayscaleAlpha = std::uint8_t;
        using GrayscaleColor = std::pair<GrayscaleIntensity, GrayscaleAlpha>;

        GrayscaleColor convert(const Color) const;
    
    private:
        Enum e;

        GrayscaleColor average_method(const Color) const;
        GrayscaleColor weighted_method(const Color) const;
};

#endif