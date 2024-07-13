#include "window_instance.hpp"

namespace core
{
    void WindowInstance::create(const std::shared_ptr<base::PlatformFactory>& factory, const base::window_config& config)
    {
        _window = factory->create_window();
        _window->create(config);
    }

    void WindowInstance::destroy() const
    {
        _window->destroy();
    }

    void WindowInstance::update() const
    {
        _window->update();
    }

    void WindowInstance::close()
    {
        _state = base::window_state::closed;
    }

    bool WindowInstance::is_active() const
    {
        return _state == base::window_state::active;
    }

    WindowInstance& WindowInstance::instance()
    {
        static WindowInstance instance;
        return instance;
    }
}