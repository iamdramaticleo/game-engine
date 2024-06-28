#pragma once
#pragma region declaration
namespace gl
{
    class Buffer;
}
#pragma endregion

namespace base
{
    class buffer_data
    {
    public:
        friend class gl::Buffer;

        template <typename buffer_t> static buffer_data create_from_buffer(const std::vector<buffer_t>& buffer)
        {
            return { buffer.data(), static_cast<uint32_t>(buffer.size() * sizeof(buffer_t)) };
        }
        template <typename buffer_t> static buffer_data create_from_data(const buffer_t* data)
        {
            return { data, sizeof(buffer_t) };
        }

    private:
        buffer_data(const void* data, const uint32_t size)
            : _data { data }
            , _size { size }
        {
        }

        const void* _data { };
        uint32_t    _size { };
    };
}