#include "Components/circle_collider.cpp"
#include "Components/rigitbody.cpp"
#include "Debug/logit.cpp"
#include "Math/transform.cpp"
#include "Math/vec2.cpp"
#include "Solvers/render_solver.cpp"
#include"include.hpp"
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

	test.GetEntity(0)->transform.position.x = 100;
	test.GetEntity(0)->transform.position.y = 100;

	std::vector<svg::vec2<double>> shape;
	shape.push_back({-10, 0});
	shape.push_back({10, 0});
	shape.push_back({20, -30});
	shape.push_back({-20, -30});

	test.GetEntity(0)->AddComponent<svg::ConvexRender>(shape, svg::vec3<unsigned char>(0, 0, 0), svg::Transform({0, 0}, -120));

	test.CreateEntity("Secondborn");

	shape.clear();

	shape.push_back({-400, 0});
	shape.push_back({400, 0});
	shape.push_back({400, -30});
	shape.push_back({-400, -30});

	test.GetEntity(1)->AddComponent<svg::ConvexRender>(shape, svg::vec3<unsigned char>(0, 100, 0), svg::Transform({0, 0}, 0));
	test.GetEntity(1)->transform = svg::Transform({320, 480}, 0);

	test.CreateEntity("Thirdborn");
	test.GetEntity(2)->AddComponent<svg::CircleRender>(20, svg::vec3<unsigned char>(255, 255, 000), svg::Transform({0, 0}, 0));
	test.GetEntity(2)->transform = svg::Transform({550, 100}, 0);

    test.AddSolver<svg::RenderSolver>("Viewer", 10, renderer);
	test.AddSolver<svg::PhysicsSolver>("Physer", 0.01, 1);

	int mouseX = 0;
	int mouseY = 0;

    SDL_Event event;

	bool quit = false;

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
				test.GetEntity(test.EntitiesCount() - 1)->GetComponent<svg::Rigitbody>()->velocity = {40, -25.0};
				test.GetEntity(test.EntitiesCount() - 1)->GetComponent<svg::Rigitbody>()->forse = {0, 10.0};
				break;
        }

		for(unsigned long i = 1; i < test.EntitiesCount(); i++)
		{
			svg::Rigitbody* rb = test.GetEntity(i)->GetComponent<svg::Rigitbody>();

			if(rb != NULL && rb->transform.position.y > 400)
			{
				svg::logit("Delleted");
				test.KillEntity(i);
				break;
			}	
		}
		
	}

    close(window, screen_surface, renderer);

    return 0;
}