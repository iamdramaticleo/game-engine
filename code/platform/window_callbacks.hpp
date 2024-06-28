#pragma once

namespace core
{
    class WindowCallbacks
    {
    public:
        static void on_size(int32_t width, int32_t height);
        static void on_close();

    private:
        WindowCallbacks() = delete;
    };
}