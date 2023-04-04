#ifndef _SOLVER_H_
#define _SOLVER_H_

#include<chrono>
#include<string>

#include"../Core/scene.cpp"

namespace svg
{
    class Scene;

    class Solver
    {
    public:

        std::string name;

        std::chrono::milliseconds milliseconds_delay;

        bool work;

        Solver(const std::string& name, unsigned long milliseconds_delay, bool work = true);

        template<typename ST>
        void Solve(ST* scene);

        template<typename ST>
        void Init(ST* scene);
    };

    Solver::Solver(const std::string& name, unsigned long milliseconds_delay, bool work) : name(name), milliseconds_delay(std::chrono::milliseconds(milliseconds_delay)), work(work)
    {}

    template<typename ST>
    void Solver::Solve(ST* scene)
    {}

    template<typename ST>
    void Init(ST* scene)
    {}
}

#endif