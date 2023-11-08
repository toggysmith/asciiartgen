#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "conversion_method.hpp"

/**
 * @brief Validate whether the arguments meet the expected format.
 * 
 * The arguments are expected to be in the format `-f X` where `-f`
 * indicates the second argument is a filename and `X` is the
 * filename.
 * 
 * @param arguments The arguments.
 * @return Whether or not the arguments are valid.
 */
const bool validate_arguments(const std::vector<std::string> arguments) {
    const bool are_there_two_arguments{ arguments.size() == 2 };
    
    if (!are_there_two_arguments) {
        std::cerr << "There should be two arguments.\n";
        return false;
    } else {
        return true;
    }
}

using CharacterImage = std::vector<std::vector<char>>;

const CharacterImage
convert_grayscale_image_to_character_image(const sf::Image grayscale_image) {
    const static std::string characters_sorted_by_darkness{
        "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "
    };

    const auto convert_pixel_to_char{
        [](const Color& color) {
            const int darkness{ color.r };
            const int alpha{ color.a };

            if (alpha < 255 * 0.5) {
                return ' ';
            }

            return characters_sorted_by_darkness.at(
                (characters_sorted_by_darkness.size() - 1) * (darkness / 255.0)
            );
        }
    };

    CharacterImage character_image(grayscale_image.getSize().y, std::vector<char>(grayscale_image.getSize().x));

    for (unsigned int x{ 0 }; x < grayscale_image.getSize().x; x++) {
        for (unsigned int y{ 0 }; y < grayscale_image.getSize().y; y++) {
            character_image[y][x] = convert_pixel_to_char(grayscale_image.getPixel(x, y));
        }
    }

    return character_image;
}

sf::Image resize_image(sf::Image input_image, const std::uint64_t width, const std::uint64_t height) {
    sf::Image image;
    image.create(width, height, sf::Color::Black);

    for (int x{ 0 }; x < width; x++) {
        for (int y{ 0 }; y < height; y++) {
            int source_x{ static_cast<int>(round(static_cast<double>(x) / static_cast<double>(width) * static_cast<double>(input_image.getSize().x))) };
            int source_y{ static_cast<int>(round(static_cast<double>(y) / static_cast<double>(height) * static_cast<double>(input_image.getSize().y))) };

            source_x = std::min(source_x, static_cast<int>(input_image.getSize().x - 1));
            source_y = std::min(source_y, static_cast<int>(input_image.getSize().y - 1));

            auto target_pixel_color = input_image.getPixel(source_x, source_y);
            image.setPixel(x, y, target_pixel_color);
        }
    }

    return image;
}

int main(int argc, char* argv[]) {
    // WHY: It's safer + more convenient to deal with a C++ container.
    std::vector<std::string> arguments(argv, (argv) + argc);

    // WHY: We don't want the first 'argument' which is always the executable name.
    arguments.erase(arguments.begin());

    if (!validate_arguments(arguments)) {
        std::exit(EXIT_FAILURE);
    }

    for (const auto argument : arguments) {
        std::cout << argument << "\n";
    }

    sf::Image image;

    image.loadFromFile(arguments[1]);

    // WHY: To demonstrate that the average method of RGBA-to-grayscale works.
    sf::Image grayscale_average_method_image{ image };
    for (std::uint64_t x{ 0 }; x < image.getSize().x; x++) {
        for (std::uint64_t y{ 0 }; y < image.getSize().y; y++) {
            const auto [intensity, alpha] = ConversionMethod(ConversionMethod::AVERAGE_METHOD).convert(Color(image.getPixel(x, y)));
            grayscale_average_method_image.setPixel(x, y, sf::Color(intensity, intensity, intensity, alpha));
        }
    }
    grayscale_average_method_image.saveToFile("data/grayscale_average_method.png");

    // WHY: To demonstrate that the weighted method of RGBA-to-grayscale works.
    sf::Image grayscale_weighted_method_image{ image };
    for (std::uint64_t x{ 0 }; x < image.getSize().x; x++) {
        for (std::uint64_t y{ 0 }; y < image.getSize().y; y++) {
            const auto [intensity, alpha] = ConversionMethod(ConversionMethod::WEIGHTED_METHOD).convert(Color(image.getPixel(x, y)));
            grayscale_weighted_method_image.setPixel(x, y, sf::Color(intensity, intensity, intensity, alpha));
        }
    }
    grayscale_weighted_method_image.saveToFile("data/grayscale_weighted_method.png");

    // WHY: To demonstrate that an image can be resized.
    const double scale_factor{ 2.5 };
    sf::Image resized_image{ resize_image(grayscale_weighted_method_image, static_cast<double>(grayscale_weighted_method_image.getSize().x) / scale_factor, static_cast<double>(grayscale_weighted_method_image.getSize().y) / scale_factor) };

    // WHY: To demonstrate that a grayscale image can be converted to an ASCII character image.
    CharacterImage character_image{ convert_grayscale_image_to_character_image(resized_image) };

    for (const auto row : character_image) {
        for (const auto col : row) {
            std::cout << col;
        }

        std::cout << "\n";
    }

    std::exit(EXIT_SUCCESS);
}