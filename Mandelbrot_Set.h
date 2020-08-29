#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <thread>
#include <filesystem>

static constexpr int IMAGE_WIDTH = 800;
static constexpr int IMAGE_HEIGHT = 600;

class Mandelbrot
{
public:
    Mandelbrot();
    void updateImage(double zoom, double offsetX, double offsetY, sf::Image& image) const;

private:
    static const int MAX = 1024; // maximum number of iterations for mandelbrot()
                         
    std::array<sf::Color, MAX + 1> colors;

    int mandelbrot(double startReal, double startImag) const;
    sf::Color getColor(int iterations) const;
    void updateImageSlice(double zoom, double offsetX, double offsetY, sf::Image& image, int minY, int maxY) const;
};
