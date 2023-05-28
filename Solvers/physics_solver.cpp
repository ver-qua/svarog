#ifndef _PHYSICS_SOLVER_H_
#define _PHYSICS_SOLVER_H_

#include<string>

#include<chrono>
#include<limits>
#include<string>
#include<type_traits>
#include<vector>

#include"../Core/scene.cpp"
#include"../Core/entity.cpp"
#include"../Components/collider.cpp"
#include"../Components/circle_collider.cpp"
#include"../Components/convex_collider.cpp"
#include"../Components/rigitbody.cpp"
#include"../Math/vec2.cpp"
#include"../Components/rigitbody.cpp"
#include"solver.cpp"

namespace svg
{
    class Scene;

    class PhysicsSolver : public Solver
    {  
    public:

        double integration_step;

        PhysicsSolver(const std::string& name, double integration_step, unsigned long milliseconds_delay, bool work = true);

        template<typename ST>
        void Solve(ST* scene);

        template<typename ST>
        void Init(ST* scene);
    };

    PhysicsSolver::PhysicsSolver(const std::string& name, double integration_step, unsigned long milliseconds_delay, bool work) : Solver::Solver(name, milliseconds_delay, work), integration_step(integration_step)
    {}

    template<typename ST>
    void PhysicsSolver::Solve(ST* scene)
    {
        for(unsigned long i = 0; i < scene->EntitiesCount(); i++)
        {
            Entity* entity = scene->GetEntity(i);

            Rigitbody* rigitbody = entity->GetComponent<Rigitbody>();

            if(rigitbody == NULL)
                continue;

            rigitbody->transform.position += rigitbody->velocity * integration_step;
            rigitbody->velocity += rigitbody->acceleration * integration_step;
            rigitbody->acceleration = rigitbody->forse / rigitbody->physic_material.mass;
        }
    }

    template<typename ST>
    void PhysicsSolver::Init(ST* scene)
    {
        logit("Initialized", "PhysicsSolver");
    }
}

#endif