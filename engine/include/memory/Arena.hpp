#pragma once
#include <cstddef>

class Arena {
    private:
        std::byte* m_Buffer;
        std::size_t m_Offset;
        std::size_t m_Capacity;
    public:
        explicit Arena(std::size_t size) : m_Buffer(static_cast<std::byte*>(::operator new(size))), m_Capacity(size), m_Offset(0) {};
        void* allocate(std::size_t size);
};  