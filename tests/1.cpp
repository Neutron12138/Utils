#include <iostream>
#include "../utils/utils.hpp"

class MyProcessManager : public utils::ProcessManager
{
public:
    ~MyProcessManager() override = default;

protected:
    void _on_first_frame() override
    {
        std::cout << "[idle frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_frame_count() << std::endl;
    }

    void _on_first_physics_frame() override
    {
        std::cout << "[physics frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_physics_frame_count() << std::endl;
    }

    void _on_frame_updated(double delta) override
    {
        std::cout << "[idle frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_frame_count()
                  << "\tdelta: " << delta << std::endl;
    }

    void _on_physics_frame_updated(double delta) override
    {
        std::cout << "[physics frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_physics_frame_count()
                  << "\tdelta: " << delta << std::endl;
    }
};

int main()
{
    auto manager = std::make_shared<MyProcessManager>();
    manager->set_target_fps(5);
    manager->set_target_physics_fps(10);
    manager->request_first_frame();
    for (; manager->get_physics_frame_count() <= 10; manager->update())
        ;

    return 0;
}
