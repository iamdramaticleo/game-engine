#include "buffer.hpp"
#include "macros.hpp"

namespace gl
{
    void Buffer::create()
    {
        glCreateBuffers(1, &_handle);
    }

    void Buffer::destroy()
    {
        glDeleteBuffers(1, &_handle);
    }

    void Buffer::bind(const uint32_t target) const
    {
              assert(target != uniform_buffer);
        glBindBuffer(target, _handle);
    }

    void Buffer::bind(base::buffer_location location) const
    {
        glBindBufferBase(uniform_buffer, static_cast<uint32_t>(location), _handle);
    }

    void Buffer::data(const base::buffer_data& buffer, const uint32_t usage) const
    {
        glNamedBufferData(_handle, buffer.size(), buffer.data(), usage);
    }

    void Buffer::sub_data(const base::buffer_data& buffer, const int32_t offset) const
    {
        glNamedBufferSubData(_handle, offset, buffer.size(), buffer.data());
    }
}