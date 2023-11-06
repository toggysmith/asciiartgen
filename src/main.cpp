#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

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

    std::exit(EXIT_SUCCESS);
}