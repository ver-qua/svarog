#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include<thread>
#include<iostream>
#include<vector>

#include "Components/circle_collider.cpp"
#include "Components/circle_render.cpp"
#include "Components/convex_collider.cpp"
#include "Components/convex_render.cpp"
#include "Components/render.cpp"
#include "Math/transform.cpp"
#include "Solvers/physics_solver.cpp"
#include "Solvers/render_solver.cpp"
#include"include.hpp"

// Инициализирует SDL2
bool init(SDL_Window*& window, SDL_Renderer*& renderer, int screen_width, int screen_height)
{
	if(window != NULL and renderer != NULL)
	{
		svg::logit("Window or screen renderer pointers are not NULL");
        return false;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		svg::logit("Can't initialize");
		return false;	
	}

	window = SDL_CreateWindow("Playing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
 
 	if(window == NULL)
	{
		svg::logit("Can't create window");
		return false;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(renderer == NULL)
	{
		svg::logit("Can't create renderer");
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	
	return true;
}

void close(SDL_Window*& window, SDL_Surface*& screen_surface, SDL_Renderer*& renderer)
{
	// Убираем рендерер
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Очищаем окно
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main()
{
    const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	// Объявляем окно
	SDL_Window* window = NULL;
	// Объявляем поверхность
	SDL_Surface* screen_surface = NULL;
	// Объявляем рендерер
	SDL_Renderer* renderer = NULL;
    
    // Инициализация
	if(!init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return 1;

    svg::Scene test("Test");
    test.CreateEntity("Firstborn");

	test.GetEntity(0)->transform.position.x = 100;
	test.GetEntity(0)->transform.position.y = 100;
	test.GetEntity(0)->transform.rotation = 30;

	test.GetEntity(0)->AddComponent<svg::ConvexRender>();
	test.GetEntity(0)->AddComponent<svg::CircleRender>();
	test.GetEntity(0)->AddComponent<svg::ConvexCollider>();
	test.GetEntity(0)->AddComponent<svg::CircleCollider>();

	test.GetEntity(0)->GetComponent<svg::ConvexRender>()->transform.rotation = 180;
	test.GetEntity(0)->GetComponent<svg::ConvexRender>()->transform.position = {100, 0};
	test.GetEntity(0)->GetComponent<svg::ConvexRender>()->color = {0, 0, 0};

	test.GetEntity(0)->GetComponent<svg::CircleRender>()->transform.position = {-100, 0};

    test.AddSolver<svg::RenderSolver>("Viewer", 10, renderer, svg::RenderSolver::Flags::None);
	test.AddSolver<svg::PhysicsSolver>("Physer", 1000);

	int mouseX = 0;
	int mouseY = 0;

    SDL_Event event;

	bool quit = false;

	double angle = 0;

	while(!quit)
	{
		SDL_PollEvent(&event);
		
		switch (event.type)
        {
			case SDL_QUIT:
				quit = true;
				svg::logit("Logging out", "Main thread");
			case SDL_MOUSEMOTION:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				test.GetEntity(0)->transform.position.x = mouseX;
				test.GetEntity(0)->transform.position.y = mouseY;
				test.GetEntity(0)->transform.rotation += 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				test.CreateEntity("Unnamed");
				test.GetEntity(test.EntitiesCount() - 1)->transform.position.x = mouseX;
				test.GetEntity(test.EntitiesCount() - 1)->transform.position.y = mouseY;
				test.GetEntity(test.EntitiesCount() - 1)->transform.rotation = angle;
				if((int)angle % 20 == 0)
					test.GetEntity(test.EntitiesCount() - 1)->AddComponent<svg::ConvexRender>();
				else
				 	test.GetEntity(test.EntitiesCount() - 1)->AddComponent<svg::CircleRender>();
				angle += 10;
				break;
        }
	}

    close(window, screen_surface, renderer);

    return 0;
}