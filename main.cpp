#include <iostream>
#include <complex>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Timer.h"

#define ITERATIONS 100
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define MAGNITUDE_THRESHOLD 2

// std::tuple<float, float>
// return  std::make_tuple(0.0f, 0.0f);

double linear_interpolation(const double value, const double old_min, const double old_max, const double new_min, const double new_max)
{
    return (new_min) + ((new_max) - (new_min)) * ((value) - (old_min)) / ((old_max) - (old_min));
}

bool escapes(const std::complex<double> val)
{
    return std::abs(val) > MAGNITUDE_THRESHOLD;
}
// https://linux.die.net/man/3/va_arg => Get input from the command line
int main()
{
    double x_min = -2;
    double y_min = -2;
    double x_max = 2;
    double y_max = 2;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Mandelbrot Set");
    window.setVerticalSyncEnabled(true);

    // Create the image we want to draw
    sf::Image image({WINDOW_WIDTH, WINDOW_HEIGHT}, sf::Color::Black);

    Timer timer;

    // TODO: Look into compiling with nvcc to split and delegate calculations to the graphics card
    // TODO: Turn rendering into its own function, which would return the image to be drawn
    // iterate over all pixels, row by row
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // TODO: Check if nested loops are actually bad for performance (for equal number of iterations)
        for (int y = 0; y < WINDOW_HEIGHT; y++)
        {
            int iteration = 0;

            std::complex<double> z(0.0, 0.0);

            // Get a finer and finer representation of the set
            while (iteration++ < ITERATIONS)
            {
                const double c_real = linear_interpolation(x, 0, WINDOW_WIDTH, x_min, x_max);
                const double c_imag = linear_interpolation(y, 0, WINDOW_HEIGHT, y_min, y_max);
                std::complex<double> c(c_real, c_imag);

                z = std::pow(z,2) + c;

                if (escapes(z)) {
                    auto color = static_cast<uint8_t>(255 * iteration / ITERATIONS);
                    image.setPixel({static_cast<unsigned>(x), static_cast<unsigned>(y)}, sf::Color(color, color, color));
                    break;
                }
            }
        }
    }

    timer.stop();
    timer.print();

    if (image.saveToFile("mandelbrot.jpg")) {
        std::cout << "Image saved successfully!" << std::endl;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image)) {
        std::cerr << "Failed to load texture from image\n";
        return -1;
    }

    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // TODO: Dispatch event with dynamic list of handlers, as per Gaetan's example.
            // TODO: Look for a better pattern though,
            // TODO: Handle zooming and panning with rerendering
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}