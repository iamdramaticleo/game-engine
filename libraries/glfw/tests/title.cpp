#include "window_instance.hpp"
#include "platform_instance.hpp"

int main()
{
    auto& platform = core::PlatformInstance::instance();
    auto& window   = core::WindowInstance::instance();

    const base::window_config config { "English 日本語 русский язык 官話", { 400, 400 } };
    const auto factory = core::PlatformFactory::create_factory();

    platform.init(factory);
    window.create(factory, config);

    gladLoadGL();

    while (window.is_active())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        window.update();
        platform.update();
    }

    window.destroy();
    platform.release();

    return EXIT_SUCCESS;
}