#include "window_instance.hpp"

namespace core
{
    void WindowInstance::create(const std::shared_ptr<base::PlatformFactory>& factory, const base::window_config& config)
    {
        _window = factory->create_window();
        _window->create(config);
        _window->activate();
    }

    void WindowInstance::destroy() const
    {
        _window->destroy();
    }

    void WindowInstance::close() const
    {
        _window->_state = base::window_state::closed;
    }

    std::any WindowInstance::handle() const
    {
        return _window->handle();
    }

    bool WindowInstance::is_active() const
    {
        return _window->_state == base::window_state::active;
    }

    WindowInstance& WindowInstance::instance()
    {
        static WindowInstance instance;
        return instance;
    }

    void WindowInstance::update() const
    {
        _window->update();
    }
}
