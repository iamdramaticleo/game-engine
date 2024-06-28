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
        assert(target != UNIFORM_BUFFER);

        glBindBuffer(target, _handle);
    }

    void Buffer::data(const base::buffer_data& buffer, const uint32_t usage) const
    {
        glNamedBufferData(_handle, buffer._size, buffer._data, usage);
    }
}
