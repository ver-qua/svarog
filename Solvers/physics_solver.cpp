#ifndef _PHYSICS_SOLVER_H_
#define _PHYSICS_SOLVER_H_

#include<chrono>
#include <string>
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
        std::vector<Entity*> _entities_to_collide;

        void _CollideEnities(Entity* entity1, Entity* entity2);

        bool _AABBCheck(Collider* collider1, Entity* entity1, Collider* collider2, Entity* entity2);

    public:

        PhysicsSolver(const std::string& name, unsigned long milliseconds_delay, bool work = true);

        template<typename ST>
        void Solve(ST* scene);

        template<typename ST>
        void Init(ST* scene);
    };

    PhysicsSolver::PhysicsSolver(const std::string& name, unsigned long milliseconds_delay, bool work) : Solver::Solver(name, milliseconds_delay, work)
    {}

    template<typename ST>
    void PhysicsSolver::Solve(ST* scene)
    {
        for(unsigned long i = 0; i < _entities_to_collide.size(); i++)
            for(unsigned long j = i + 1; j < _entities_to_collide.size(); i++)
                _CollideEnities(_entities_to_collide[i], _entities_to_collide[j]);

        _entities_to_collide[0]->GetComponents<Collider>()[1]->GetAABB(Transform());        

        logit("Solved frame", "PhysicsSolver");
    }

    template<typename ST>
    void PhysicsSolver::Init(ST* scene)
    {
        
        for(unsigned long i = 0; i < scene->EntitiesCount(); i++)
        {
            Entity* current_entity = scene->GetEntity(i);

            if(current_entity->GetComponent<Collider>() != NULL)
                _entities_to_collide.push_back(current_entity);
        }
        logit("Initialized", "PhysicsSolver");
    }

    //Колхоз

    void PhysicsSolver::_CollideEnities(Entity* entity1, Entity* entity2)
    {
        std::vector<Collider*> entity_colliders1 = entity1->GetComponents<Collider>();
        std::vector<Collider*> entity_colliders2 = entity2->GetComponents<Collider>();
        
        logit("Checking entities", "PhysicsSolver");

        for(auto& entity_collider1 : entity_colliders1)
        {
            for(auto& entity_collider2 : entity_colliders2)
            {   
                //if(_AABBCheck(entity_collider1, entity1, entity_collider2, entity2))
                  //  logit("Found Collision!", "PhysicsSolver");
                logit("Checking entities", "PhysicsSolver");
                entity_collider1->GetAABB(Transform());
                entity_collider2->GetAABB(Transform());
            }   
        }
    }

    bool PhysicsSolver::_AABBCheck(Collider* collider1, Entity* entity1, Collider* collider2, Entity* entity2)
    {
        Transform full_transform = entity1->transform;
        Rigitbody* rigitbody = entity1->GetComponent<Rigitbody>();

        if(rigitbody != NULL)
            full_transform += rigitbody->transform;

        std::array<vec2<double>, 2> AABB1 = collider1->GetAABB(full_transform);
        
        full_transform = entity2->transform;
        rigitbody = entity2->GetComponent<Rigitbody>();

        if(rigitbody != NULL)
            full_transform += rigitbody->transform;

        std::array<vec2<double>, 2> AABB2 = collider2->GetAABB(full_transform);

        // Выходим без пересечения, потому что найдена разделяющая ось 0 - max 1 - min
        if(AABB1[0].x < AABB2[1].x or AABB1[1].x > AABB2[0].x)
            return false;

        if(AABB1[0].y < AABB2[1].y or AABB1[1].y > AABB2[0].y)
            return false;
        
        // Если оба условия true, значит произошла коллизия
        return true;
    }
}

#endif