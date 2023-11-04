#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

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

    std::cout << image.getSize().x << " x " << image.getSize().y << std::endl;

    std::cout << "R: " << static_cast<int>(image.getPixel(0, 0).r) << std::endl;
    std::cout << "G: " << static_cast<int>(image.getPixel(0, 0).g) << std::endl;
    std::cout << "B: " << static_cast<int>(image.getPixel(0, 0).b) << std::endl;

    std::exit(EXIT_SUCCESS);
}