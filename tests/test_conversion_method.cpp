#include <array>
#include <unordered_map>
#include <algorithm>

#include <doctest/doctest.h>
#include <SFML/Graphics.hpp>

#include "conversion_method.hpp"
#include "color.hpp"

const doctest::String color_as_string(const Color& color) {
    const doctest::String red( std::to_string(color.r).c_str() );
    const doctest::String green( std::to_string(color.g).c_str() );
    const doctest::String blue( std::to_string(color.b).c_str() );

    return doctest::String("(") + red + doctest::String(", ") + green + doctest::String(", ") + blue + doctest::String(")");
}

TEST_CASE("ConversionMethod") {
    GIVEN("ConversionMethod is constructed as ConversionMethod::AVERAGE_METHOD.") {
        const ConversionMethod conversion_method{ ConversionMethod::AVERAGE_METHOD };

        WHEN("The `convert()` method is called on it with the RGBA color (255, 0, 0, 255).") {
            const ConversionMethod::GrayscaleColor grayscale_color{
                conversion_method.convert(Color(255, 0, 0, 255))
            };

            THEN("A grayscale color is returned with an intensity of 85 and an alpha of 255.") {
                const auto [intensity, alpha] = grayscale_color;

                CHECK(intensity == 85);
                CHECK(alpha == 255);
            }
        }
    }

    GIVEN("ConversionMethod is constructed as ConversionMethod::AVERAGE_METHOD.") {
        const ConversionMethod conversion_method{ ConversionMethod::AVERAGE_METHOD };

        WHEN("The `convert()` method is called on it with the RGBA color (0, 255, 0, 255).") {
            const ConversionMethod::GrayscaleColor grayscale_color{
                conversion_method.convert(Color(0, 255, 0, 255))
            };

            THEN("A grayscale color is returned with an intensity of 85 and an alpha of 255.") {
                const auto [intensity, alpha] = grayscale_color;

                CHECK(intensity == 85);
                CHECK(alpha == 255);
            }
        }
    }

    GIVEN("ConversionMethod is constructed as ConversionMethod::AVERAGE_METHOD.") {
        const ConversionMethod conversion_method{ ConversionMethod::AVERAGE_METHOD };

        WHEN("The `convert()` method is called on it with the RGBA color (0, 0, 255, 255).") {
            const ConversionMethod::GrayscaleColor grayscale_color{
                conversion_method.convert(Color(0, 0, 255, 255))
            };

            THEN("A grayscale color is returned with an intensity of 85 and an alpha of 255.") {
                const auto [intensity, alpha] = grayscale_color;

                CHECK(intensity == 85);
                CHECK(alpha == 255);
            }
        }
    }

    GIVEN("ConversionMethod is constructed as ConversionMethod::AVERAGE_METHOD.") {
        const ConversionMethod conversion_method{ ConversionMethod::AVERAGE_METHOD };

        WHEN("The `convert()` method is called on it with the RGBA color (255, 0, 255, 0).") {
            const ConversionMethod::GrayscaleColor grayscale_color{
                conversion_method.convert(Color(255, 0, 255, 0))
            };

            THEN("A grayscale color is returned with an intensity of 170 and an alpha of 0.") {
                const auto [intensity, alpha] = grayscale_color;

                CHECK(intensity == 170);
                CHECK(alpha == 0);
            }
        }
    }

    GIVEN("ConversionMethod is constructed as ConversionMethod::AVERAGE_METHOD.") {
        const ConversionMethod conversion_method{ ConversionMethod::AVERAGE_METHOD };

        WHEN("The `convert()` method is called on it with the RGBA color (127, 13, 210, 67).") {
            const ConversionMethod::GrayscaleColor grayscale_color{
                conversion_method.convert(Color(127, 13, 210, 67))
            };

            THEN("A grayscale color is returned with an intensity of 116 and an alpha of 67.") {
                const auto [intensity, alpha] = grayscale_color;

                CHECK(intensity == 116);
                CHECK(alpha == 67);
            }
        }
    }
}