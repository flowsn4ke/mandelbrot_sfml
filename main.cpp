#include <iostream>
#include <complex>
#include <cmath>
#include <SFML/Graphics.hpp>

#define ITERATIONS 100
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define X_MIN (-2)
#define Y_MIN (-2)
#define X_MAX 2
#define Y_MAX 2
#define MAGNITUDE_THRESHOLD 2

// std::tuple<float, float>
// return  std::make_tuple(0.0f, 0.0f);

double linear_interpolation(const double value, const double old_min, const double old_max, const double new_min, const double new_max)
{
    return (new_min) + ((new_max) - (new_min)) * ((value) - (old_min)) / ((old_max) - (old_min));
}

bool escapes(const std::complex<double> val) {
    if (val == std::complex<double>(-0.05, -0.05)) {
        std::cout << "Absolute value: " << std::abs(val) << std::endl;
    }

    return std::abs(val) > MAGNITUDE_THRESHOLD;
}

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

    time_t start, finish;
    time(&start);

    // iterate over all pixels, row by row
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            int iteration = 0;

            std::complex<double> z(0.0, 0.0);

            // Get a finer and finer representation of the set
            while (iteration++ < ITERATIONS) {
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

    if (image.saveToFile("mandelbrot.jpg")) {
        std::cout << "Image saved successfully!" << std::endl;
    }

    time(&finish);
    auto time_taken = static_cast<double>(finish - start);
    std::cout << "Time taken by program is : " << std::fixed << time_taken << std::setprecision(5) << " sec " << std::endl;

    sf::Texture texture;

    if (!texture.loadFromImage(image)) {
        std::cerr << "Failed to load texture from image\n";
        return -1;
    }

    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // else if (event->is<sf::Event::MouseWheelScrolled>()) {
            //     const auto& scrollEvent = std::get<sf::MouseWheelScrollEvent>(*event);
            //     double zoom_factor = (scrollEvent.delta > 0) ? 0.9 : 1.1;
            //
            //     double x_center = (x_min + x_max) / 2.0;
            //     double y_center = (y_min + y_max) / 2.0;
            //
            //     double x_range = (x_max - x_min) * zoom_factor;
            //     double y_range = (y_max - y_min) * zoom_factor;
            //
            //     x_min = x_center - x_range / 2.0;
            //     x_max = x_center + x_range / 2.0;
            //     y_min = y_center - y_range / 2.0;
            //     y_max = y_center + y_range / 2.0;
            // }

        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}