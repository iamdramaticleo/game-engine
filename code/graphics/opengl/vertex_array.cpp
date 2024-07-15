#include "vertex_array.hpp"

namespace gl
{
    void VertexArray::attribute(const base::vertex_attribute& attribute, const int32_t stride) const
    {
        glEnableVertexArrayAttrib(_handle, attribute.index);
        glVertexAttribPointer(attribute.index,  attribute.size, attribute.type, 0, stride,
           reinterpret_cast<const void*>(static_cast<uintptr_t>(attribute.offset)));
    }

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
