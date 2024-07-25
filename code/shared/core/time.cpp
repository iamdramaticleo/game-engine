#include "time.hpp"

namespace core
{
    void Time::init()
    {
        _offset = _start = time_clock::now();
    }

    void Time::update()
    {
        const auto current = time_clock::now();

        _total_time = std::chrono::duration<float>(current -  _start).count();
        _delta_time = std::chrono::duration<float>(current - _offset).count();

        _offset = current;
    }

    float Time::total_time()
    {
        return _total_time;
    }

    float Time::delta_time()
    {
        return _delta_time;
    }
}