#include "Components/circle_render.cpp"
#include "Components/rigitbody.cpp"
#include "Core/entity.cpp"
#include "Debug/logit.cpp"
#include "Math/transform.cpp"
#include "Math/vec2.cpp"
#include "Solvers/render_solver.cpp"
#include"include.hpp"
#include <SDL2/SDL_events.h>
#include <algorithm>
#include <vector>

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
	
	test.CreateEntity("Secondborn");

	for(unsigned long i = 0; i < 640; i += 25)
	{
		for(unsigned long j = 0; j <= 480; j += 25)
		{
			test.CreateEntity("Dot");
			test.GetEntity(1)->AddComponent<svg::CircleRender>(2, svg::vec3<unsigned char>(100, 100, 100), svg::Transform(svg::vec2<double>(i, j), 0));
		}
	}

    test.AddSolver<svg::RenderSolver>("Viewer", 10, renderer);
	test.AddSolver<svg::PhysicsSolver>("Physer", 0.01, 1);

	int mouseX = 0;
	int mouseY = 0;

    SDL_Event event;

	bool quit = false;

	bool mouse_down = false;

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
				break;

			case SDL_MOUSEBUTTONDOWN:
				test.CreateEntity("Unnamed");
				test.GetEntity(test.EntitiesCount() - 1)->transform.position.x = mouseX;
				test.GetEntity(test.EntitiesCount() - 1)->transform.position.y = mouseY;
				test.GetEntity(test.EntitiesCount() - 1)->AddComponent<svg::CircleRender>();
				test.GetEntity(test.EntitiesCount() - 1)->AddComponent<svg::Rigitbody>();
				mouse_down = true;
				break;

			case SDL_MOUSEBUTTONUP:
				mouse_down = false;
				break;
        }

		if(mouse_down)
		{
			for(unsigned long i = 1; i < test.EntitiesCount(); i++)
			{
				svg::Entity* ent = test.GetEntity(i);
				svg::Rigitbody* rb = ent->GetComponent<svg::Rigitbody>();

				if(rb != NULL)
				{
					rb->forse = (svg::vec2<double>(mouseX, mouseY) - (ent->transform.position + rb->transform.position)) / 10;
				}
			}
		}
		else
		{
			for(unsigned long i = 1; i < test.EntitiesCount(); i++)
			{
				svg::Entity* ent = test.GetEntity(i);
				svg::Rigitbody* rb = ent->GetComponent<svg::Rigitbody>();

				if(rb != NULL)
				{
					rb->forse = svg::vec2<double>();
				}
			}
		}
	}

    close(window, screen_surface, renderer);

    return 0;
}