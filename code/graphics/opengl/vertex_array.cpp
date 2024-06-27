#include "vertex_array.hpp"

namespace gl
{
    void VertexArray::create()
    {
        glCreateVertexArrays(1, &_handle);
    }

    void VertexArray::destroy()
    {
        glDeleteVertexArrays(1, &_handle);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(_handle);
    }
}
