#include "Mandelbrot_Set.h"

Mandelbrot::Mandelbrot()
{
    for (int i = 0; i <= MAX; ++i)
    {
        colors[i] = getColor(i);
    }
}

int Mandelbrot::mandelbrot(double startReal, double startImag) const
{
    double zReal = startReal;
    double zImag = startImag;

    for (int counter = 0; counter < MAX; ++counter)
    {
        double r2 = zReal * zReal;
        double i2 = zImag * zImag;
        if (r2 + i2 > 4.0)
        {
            return counter;
        }
        zImag = 2.0 * zReal * zImag + startImag;
        zReal = r2 - i2 + startReal;
    }
    return MAX;
}

sf::Color Mandelbrot::getColor(int iterations) const
{
    int r, g, b;

    if (iterations < 16)
    {
        r = 4 * (16 - iterations);
        g = 0;
        b = 4 * iterations - 1;
    }
    else if (iterations < 32)
    {
        r = 0;
        g = 16 * (iterations - 16);
        b = 16 * (32 - iterations) - 1;
    }
    else if (iterations < 64)
    {
        r = 8 * (iterations - 32);
        g = 8 * (64 - iterations) - 1;
        b = 0;
    }
    else
    {
        r = 10;
        g = 0;
        b = 0;
    }

    return sf::Color(r, g, b);
}

void Mandelbrot::updateImageSlice(double zoom, double offsetX, double offsetY, sf::Image& image, int minY, int maxY) const
{
    double real = 0 * zoom - IMAGE_WIDTH / 2.0 * zoom + offsetX;
    double imagstart = minY * zoom - IMAGE_HEIGHT / 2.0 * zoom + offsetY;
    for (int x = 0; x < IMAGE_WIDTH; x++, real += zoom)
    {
        double imag = imagstart;
        for (int y = minY; y < maxY; y++, imag += zoom)
        {
            int value = mandelbrot(real, imag);
            image.setPixel(x, y, colors[value]);
        }
    }
}

void Mandelbrot::updateImage(double zoom, double offsetX, double offsetY, sf::Image& image) const
{
    const int STEP = IMAGE_HEIGHT / std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    for (int i = 0; i < IMAGE_HEIGHT; i += STEP)
    {
        threads.push_back(std::thread(&Mandelbrot::updateImageSlice, *this, zoom, offsetX, offsetY, std::ref(image), i, std::min(i + STEP, IMAGE_HEIGHT)));
    }
    for (auto& t : threads)
    {
        t.join();
    }
}
