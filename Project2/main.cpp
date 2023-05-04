/*
 * To run the project:
 * 1) You need to have a c++ compiler installed.
 * 2) Install SDL2 and SDL2_Image
 * 3) Finally, run g++ main.cpp -std=c++20 -lSDL2 -lSDL2_Image
 *
 * All the png files representing the answers will be
 * generated inside the same folder
 */
 
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

constexpr int WIDTH = 200;
constexpr int HEIGHT = 200;

void draw_circle()
{
    // create target surface
    SDL_Surface *output_surface = SDL_CreateRGBSurface(0,
            WIDTH, HEIGHT, 32,
            0, 0, 0, 0);

    // create software renderer that renders to target surface
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(output_surface);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // logic to draw the circle
    for (int y=0; y<HEIGHT; y++)
    {
        for (int x=0; x<WIDTH; x++)
        {
            double d_x = static_cast<double>(x);
            double d_y = static_cast<double>(y);

            bool f1 = (pow((d_x/100.0 - 1.0) - 1.0/200.0, 2) + pow((1.0 - d_y/100.0) - 1.0/200.0, 2) - pow(1.0,2) < 0);
            bool f2 = (pow((d_x/100.0 - 1.0) - 1.0/200.0, 2) + pow((1.0 - d_y/100.0) + 1.0/200.0, 2) - pow(1.0,2) < 0);
            bool f3 = (pow((d_x/100.0 - 1.0) + 1.0/200.0, 2) + pow((1.0 - d_y/100.0) - 1.0/200.0, 2) - pow(1.0,2) < 0);
            bool f4 = (pow((d_x/100.0 - 1.0) + 1.0/200.0, 2) + pow((1.0 - d_y/100.0) + 1.0/200.0, 2) - pow(1.0,2) < 0);

            if ((1-f1)*f4 + (1-f3)*f2 + (1-f2)*f1 + (1-f4)*f3)
            {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
   
    // Save target surface to PNG file
    IMG_SavePNG(output_surface, "Circle.png");

    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(output_surface);
}

void draw_spiral_a()
{
    // create target surface
    SDL_Surface *output_surface = SDL_CreateRGBSurface(0,
            WIDTH, HEIGHT, 32,
            0, 0, 0, 0);

    // create software renderer that renders to target surface
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(output_surface);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for (double t=0; t<=100; t+=0.1)
    {
        int x = static_cast<int>(t * sin(t));
        int y = static_cast<int>(t * cos(t));
        SDL_RenderDrawPoint(renderer, x+100, 100-y);
    }

    // Save target surface to PNG file
    IMG_SavePNG(output_surface, "Spiral_a.png");

    //Destroy objects
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(output_surface);
}

void draw_spiral_b()
{
    SDL_Surface *output_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(output_surface);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (double t=0; t<=100; t+=1/sqrt((t*t+1)))
    {
        int x = static_cast<int>(t * cos(t));
        int y = static_cast<int>(t * sin(t));

        SDL_RenderDrawPoint(renderer, x+100, 100-y);
    }

    IMG_SavePNG(output_surface, "Spiral_b.png");

    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(output_surface);
}

void draw_region()
{
    SDL_Surface *output_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(output_surface);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y=0; y<HEIGHT; y++)
    {
        for (int x=0; x<WIDTH; x++)
        {
            double a = static_cast<double>(x)/200.0;
            double b = 1 - static_cast<double>(y)/200.0;

            bool first_condition = a + b > 1;
            bool second_condition = a*a + (b-1)*(b-1) - 1 <= 0;
            bool third_condition = (a-1)*(a-1) + b*b - 1 <= 0;

            if (first_condition && second_condition && third_condition)
                SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    
    IMG_SavePNG(output_surface, "Region.png");

    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(output_surface);

}

void draw_hyperbole()
{
    SDL_Surface *output_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(output_surface);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y=0; y<HEIGHT; y++)
    {
        for (int x=0; x<WIDTH; x++)
        {
            double a = static_cast<double>(x)/50.0 - 2.0;
            double b = 2.0 - static_cast<double>(y)/50.0;
            
            bool c1 = pow(b - 1.0/50.0,2) - pow(a - 1.0/50.0, 3) + (a - 1.0/50.0) < 0;
            bool c2 = pow(b + 1.0/50.0,2) - pow(a + 1.0/50.0, 3) + (a + 1.0/50.0) < 0;
            bool c3 = pow(b + 1.0/50.0,2) - pow(a - 1.0/50.0, 3) + (a - 1.0/50.0) < 0;
            bool c4 = pow(b - 1.0/50.0,2) - pow(a + 1.0/50.0, 3) + (a + 1.0/50.0) < 0;

            if ((1-c1)*c4 + (1-c3)*c2 + (1-c2)*c1 + (1-c4)*c3)
                SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    IMG_SavePNG(output_surface, "Hyperbole.png");

    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(output_surface);
}

int main()
{
    // Initialize SDL and SDL_Image
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cerr << "Failed at SDL_Init. Error: " << SDL_GetError() << std::endl;

    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((flags & initStatus) != flags)
        std::cerr << "SDL2_Image format not available. Error: " << IMG_GetError() << std::endl;

    draw_circle();
    draw_spiral_a();
    draw_spiral_b();
    draw_region();
    draw_hyperbole();

    // Clean up before the program is finished
    IMG_Quit();
    SDL_Quit();

    return 0;
}
