#include "window_instance.hpp"

void WindowInstance::create(const std::shared_ptr<base::PlatformFactory>& factory, const window_config& config)
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
    _state = window_state::closed;
}

bool WindowInstance::is_active() const
{
    return _state == window_state::active;
}

WindowInstance& WindowInstance::instance()
{
    static WindowInstance instance;
    return instance;
}
