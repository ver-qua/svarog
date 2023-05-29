#ifndef _RENDER_SOLVER_H_
#define _RENDER_SOLVER_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include<SDL2/SDL_video.h>

#include<chrono>
#include <math.h>
#include<string>
#include<vector>

#include"../Core/scene.cpp"
#include"solver.cpp"
#include"../Components/render.cpp"
#include"../Components/convex_render.cpp"
#include"../Components/circle_render.cpp"
#include"../Components/rigitbody.cpp"

#include"../Debug/logit.cpp"


namespace svg
{
    class Scene;

    class RenderSolver : public Solver
    {
        void _RenderGimbal(Entity* entity);

        void _RenderConvexRenders(Entity* entity);

        void _RenderCircleRenders(Entity* entity);

        SDL_Renderer* _renderer;

    public:

        enum Flags
        {
            None = 0,
            RenderGimbals = 1 << 0,
            RenderNormals = 1 << 1,
            RenderColliders = 1 << 2
        };

        int flags;

        RenderSolver(const std::string& name, unsigned long milliseconds_delay, SDL_Renderer* renderer, int flags, bool work = true);

        template<typename ST>
        void Solve(ST* scene);

        template<typename ST>
        void Init(ST* scene);
    };

    RenderSolver::RenderSolver(const std::string& name, unsigned long milliseconds_delay, SDL_Renderer* renderer, int flags = Flags::None, bool work) 
        : Solver::Solver(name, milliseconds_delay, work), _renderer(renderer), flags(flags)
    {}

    template<typename ST>
    void RenderSolver::Solve(ST* scene)
    {
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(_renderer);

        for(unsigned long i = 0; i < scene->EntitiesCount(); i++)
        {
            Entity* entity = scene->GetEntity(i);

            Render *render = entity->GetComponent<Render>();
            
            if(render == NULL)
            {
                _RenderGimbal(entity);
                continue;
            }

            _RenderConvexRenders(entity);

            _RenderCircleRenders(entity);

            if(flags & Flags::RenderGimbals)
                _RenderGimbal(entity);
        }

        SDL_RenderPresent(_renderer);
    }

    template<typename ST>
    void RenderSolver::Init(ST* scene)
    {
        logit("Initialized", "RenderSolver");
    }

    void RenderSolver::_RenderGimbal(Entity* entity)
    {
        Transform entity_transform = entity->transform;

        Rigitbody* entity_rigitbpdy = entity->GetComponent<Rigitbody>();

        if(entity_rigitbpdy != NULL)
            entity_transform += entity_rigitbpdy->transform;

        // Точки гимбла
        vec2<double> hiest(entity_transform.position.x, entity_transform.position.y + 10);
        vec2<double> lowest(entity_transform.position.x, entity_transform.position.y - 10);
        vec2<double> right(entity_transform.position.x + 10, entity_transform.position.y);
        vec2<double> left(entity_transform.position.x - 10, entity_transform.position.y);
        
        // Вращаем точки
        hiest.rotate(entity_transform.rotation, entity_transform.position);
        lowest.rotate(entity_transform.rotation, entity_transform.position);
        right.rotate(entity_transform.rotation, entity_transform.position);
        left.rotate(entity_transform.rotation, entity_transform.position);

        // Две серые линии 
        thickLineRGBA(_renderer, hiest.x, hiest.y, lowest.x, lowest.y, 2, 127, 127, 127, 255);
        thickLineRGBA(_renderer, right.x, right.y, left.x, left.y, 2, 127, 127, 127, 255);

        // Зелёные кружочки
        filledCircleRGBA(_renderer, hiest.x, hiest.y, 2, 0, 255, 0, 255);
        filledCircleRGBA(_renderer, lowest.x, lowest.y, 2, 0, 255, 0, 255);

        // Красные кружочки
        filledCircleRGBA(_renderer, right.x, right.y, 2, 255, 0, 0, 255);
        filledCircleRGBA(_renderer, left.x, left.y, 2, 255, 0, 0, 255);
    }

    void RenderSolver::_RenderConvexRenders(Entity* entity)
    {
        Transform entity_transform = entity->transform;

        Rigitbody* entity_rigitbpdy = entity->GetComponent<Rigitbody>();

        // Получаем полную трансформацию тела
        if(entity_rigitbpdy != NULL)
            entity_transform += entity_rigitbpdy->transform;

        std::vector<ConvexRender*> renders = entity->GetComponents<ConvexRender>();

        for(auto& render : renders)
        {
            // Получаем полную трансформацию рндера
            Transform render_transform = entity_transform + render->transform;

            unsigned long points_count = render->shape.size();

            Sint16 points_x[points_count];
            Sint16 points_y[points_count];

            // Вращение точек и запись из в массив
            for(unsigned long i = 0; i < points_count; i++)
            {
                vec2<double> rotated_point = (render_transform.position + render->shape[i]).rotated(render_transform.rotation, render_transform.position);

                points_x[i] = rotated_point.x;
                points_y[i] = rotated_point.y;
            }

            filledPolygonRGBA(_renderer, points_x, points_y, points_count, render->color.x, render->color.y, render->color.z, 255);
            
            if(!(flags & Flags::RenderNormals))
                continue;
            
            for(unsigned long i = 0; i < points_count; i++)
            {
                unsigned long next = (i + 1) % points_count;
                vec2<double> nomal_vector = vec2<double>(points_y[i] - points_y[next], points_x[next] - points_x[i]);
                nomal_vector.normalize();
                nomal_vector *= 10;
                thickLineRGBA(_renderer, (points_x[i] + points_x[next]) / 2, (points_y[i] + points_y[next]) / 2, (points_x[i] + points_x[next]) / 2 + nomal_vector.x, (points_y[i] + points_y[next]) / 2 + nomal_vector.y, 2, 0, 0, 255, 255);
            }
        }
    }

    void RenderSolver::_RenderCircleRenders(Entity* entity)
    {
        Transform entity_transform = entity->transform;

        Rigitbody* entity_rigitbpdy = entity->GetComponent<Rigitbody>();

        // Получаем полную трансформацию тела
        if(entity_rigitbpdy != NULL)
            entity_transform += entity_rigitbpdy->transform;

        std::vector<CircleRender*> renders = entity->GetComponents<CircleRender>();

        for(auto& render : renders)
        {
            // Получаем полную трансформацию рндера
            Transform render_transform = entity_transform + render->transform;

            filledCircleRGBA(_renderer, render_transform.position.x, render_transform.position.y, render->radius, render->color.x, render->color.y, render->color.z, 255);

            if(!(flags & Flags::RenderNormals))
                continue;

            vec2<double> nomal_vector(1, 1);
            nomal_vector *= 10;
            nomal_vector.rotate(render_transform.rotation);

            thickLineRGBA(_renderer, render_transform.position.x, render_transform.position.y, nomal_vector.x + render_transform.position.x, nomal_vector.y + render_transform.position.y, 2, 0, 0, 255, 255);
        }
    }
}

#endif