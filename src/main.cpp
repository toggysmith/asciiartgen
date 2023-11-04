#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::Image image;

    image.loadFromFile("./data/test_image.png");

    std::cout << image.getSize().x << " x " << image.getSize().y << std::endl;

    std::cout << "R: " << static_cast<int>(image.getPixel(0, 0).r) << std::endl;
    std::cout << "G: " << static_cast<int>(image.getPixel(0, 0).g) << std::endl;
    std::cout << "B: " << static_cast<int>(image.getPixel(0, 0).b) << std::endl;

    return 0;
}