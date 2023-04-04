#ifndef _SCENE_H_
#define _SCENE_H_

/*
################################################################################################
Проблемы с многопоточностью. Сейчас запрещенно получать доступ к сцене вне солвера после старта первого. Это может привести к неопределённому поведению.
################################################################################################
*/

#include<string>
#include<vector>
#include<memory>
#include<thread>
#include<mutex>

#include"entity.cpp"
#include"../Solvers/solver.cpp"

#include"../Debug/logit.cpp"


namespace svg
{
    class Scene
    {
        std::vector<std::unique_ptr<Entity>> _entities;
        std::vector<std::unique_ptr<Solver>> _solvers;
        std::vector<std::unique_ptr<std::thread>> _solvers_threads;
        mutable std::mutex _mute;
        
        // Блокирование доступа к сцене
        void _Lock();

        // Блокирование доступа к сцене
        void _Unlock();

    public:

        std::string name;

        explicit Scene(const std::string& name);

        const unsigned int EntitiesCount();

        const unsigned int SolversCount();

        template<typename ... Arg>
        void CreateEntity(Arg&& ... num);

        Entity* GetEntity(unsigned int index);

        bool KillEntity(unsigned int index);

        // Удаление всех сущьностей
        unsigned long KillEnities();

        template<typename SolverType, typename ... Agrs>
        void AddSolver(Agrs&& ... params);

        template <typename SolverType>
        SolverType* GetSolver(unsigned int index);

        bool RemoveSolver(unsigned int index);

        // Удаление всех солверов
        unsigned long RemoveSolvers();

        void Close();

        ~Scene();
    };

    Scene::Scene(const std::string& name) : name(name)
    {}

    //Колхоз
    
    void Scene::_Lock()
    {
        _mute.lock();
    }

    void Scene::_Unlock()
    {
        _mute.unlock();
    }

    const unsigned int Scene::EntitiesCount()
    {
        return _entities.size();
    }

    const unsigned int Scene::SolversCount()
    {
        return _solvers.size();
    }

    template<typename ... Agrs>
    void Scene::CreateEntity(Agrs&& ... params)
    {
        _entities.emplace_back(std::make_unique<Entity>(std::forward<Agrs>(params)...));
    }

    Entity* Scene::GetEntity(unsigned int index)
    {   
        if(index < _entities.size())
            return _entities[index].get();
        
        return nullptr;
    }

    bool Scene::KillEntity(unsigned int index)
    {   
        if(index < _entities.size())
        {
            _entities.erase(_entities.begin() + index);
            return true;
        }
        
        return false;
    }

    unsigned long Scene::KillEnities()
    {
        unsigned long count = _entities.size();

        _entities.clear();

        return count;
    }

    //Колхоз

    template<typename SolverType, typename ... Agrs>
    void Scene::AddSolver(Agrs&& ... params)
    {        
        _solvers.emplace_back(std::make_unique<SolverType>(std::forward<Agrs>(params)...));

        SolverType* solver_ptr = static_cast<SolverType*>(_solvers[_solvers.size() - 1].get());
        solver_ptr->Init(this);

        _solvers_threads.emplace_back(std::make_unique<std::thread>([solver_ptr, this]()
        {
            while(true)
            {
                if(!solver_ptr->work)
                    break;

                std::this_thread::sleep_for(solver_ptr->milliseconds_delay);

                this->_Lock();
                solver_ptr->Solve(this);
                this->_Unlock();

            }
        }));
    }

    //Колхоз

    template <typename SolverType>
    SolverType* Scene::GetSolver(unsigned int index)
    {
        if(index < _solvers.size())
            return static_cast<SolverType*>(_solvers[index].get());
        
        return nullptr;
    }

    bool Scene::RemoveSolver(unsigned int index)
    {   
        if(index < _solvers.size())
        {
            _solvers.erase(_solvers.begin() + index);
            return true;
        }
        
        return false;
    }

    unsigned long Scene::RemoveSolvers()
    {
        unsigned long count = _solvers.size();

        _solvers.clear();

        return count;
    }

    Scene::~Scene()
    {
        for(unsigned int i = 0; i < _solvers.size(); i++)
            _solvers[i]->work = false;

        for(unsigned int i = 0; i < _solvers_threads.size(); i++)
            if(_solvers_threads[i]->joinable())
                _solvers_threads[i]->join();
    }
}

#endif