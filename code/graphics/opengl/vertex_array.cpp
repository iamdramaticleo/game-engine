#include "vertex_array.hpp"
#include "macros.hpp"

namespace gl
{
    void VertexArray::attribute(const base::vertex_attribute& attribute, int32_t stride) const
    {
        glEnableVertexArrayAttrib(_handle, attribute.index);
        glVertexAttribPointer(attribute.index,  attribute.size, attribute.type, FALSE, stride,
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
