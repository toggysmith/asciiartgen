#include "conversion_method.hpp"

/**
 * @brief Based on the selected conversion method, convert an RGBA color to grayscale.
 * 
 * This examines the current selected conversion method in the internal enum and uses
 * it to perform the appropriate conversion.
 * 
 * @param color The RGBA color.
 * @return The grayscale color.
 */
ConversionMethod::GrayscaleColor
ConversionMethod::convert(const Color color) const {
    switch (e) {
        case Enum::AVERAGE_METHOD: return ConversionMethod::average_method(color);
        case Enum::WEIGHTED_METHOD: return ConversionMethod::weighted_method(color);
        // WHY: We don't want the program to crash if a conversion method isn't defined
        //      for this enum case, but we do wanted to be warned about it. Ideally, the
        //      program wouldn't be able to compile without a matching handler for each
        //      enum case. This can done using macros but it's overkill for this project.
        default: {
            std::cerr << "No conversion method defined for called enum, so defaulting to average method.\n";
            return ConversionMethod::average_method(color);
        }
    }
}

/**
 * @brief Use average of RGB channels to convert color to grayscale.
 * 
 * This takes the RGB channels and averages them to get a grayscale
 * color while maintaining the alpha channel.
 * 
 * @param color The RGBA color.
 * @return The grayscale color.
 */
ConversionMethod::GrayscaleColor
ConversionMethod::average_method(const Color color) const {
    const GrayscaleIntensity grayscale_intensity{
        static_cast<GrayscaleIntensity>((color.r + color.g + color.b) / 3.0)
    };
    const GrayscaleAlpha grayscale_alpha{ color.a };

    return { grayscale_intensity, grayscale_alpha };
}

/**
 * @brief Use average of RGB channels, with weights attached, to convert color to grayscale.
 * 
 * This takes the RGB channels, applies weights to them based on their
 * wavelength/luminosity, and averages them to get a grayscale color
 * while maintaining the alpha channel.
 * 
 * @param color The RGBA color.
 * @return The grayscale color.
 */
ConversionMethod::GrayscaleColor
ConversionMethod::weighted_method(const Color color) const {
    // WHY: The red, green, and blue channels do not contribute equally to the final image.
    //      These coefficients reflect the fact that 'green' light is the major component
    //      of luminance, responsible for the majority of light perceived by humans, and
    //      'blue' light is the smallest component.
    //
    // NOTE: For more information, see
    //       https://en.wikipedia.org/wiki/Relative_luminance#Relative_luminance_and_perceptual_spaces.
    const double red_channel_coefficient{ 0.299 };
    const double green_channel_coefficient{ 0.587 };
    const double blue_channel_coefficient{ 0.114 };

    const double weighted_red_channel{ static_cast<double>(color.r) * red_channel_coefficient };
    const double weighted_green_channel{ static_cast<double>(color.g) * green_channel_coefficient };
    const double weighted_blue_channel{ static_cast<double>(color.b) * blue_channel_coefficient };

    const GrayscaleIntensity grayscale_intensity{
        static_cast<GrayscaleIntensity>(weighted_red_channel + weighted_green_channel + weighted_blue_channel / 3.0)
    };
    const GrayscaleAlpha grayscale_alpha{ color.a };

    return { grayscale_intensity, grayscale_alpha };
}