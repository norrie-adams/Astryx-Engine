# Astryx Engine Coding Standards

This document outlines the code style, formatting, and best practices for the Astryx Engine codebase. Adhering to these standards ensures the code remains clean, readable, and maintainable as the engine grows.

---

## 1. Naming Conventions

We use specific casing styles to instantly identify the scope and type of an identifier.

| Identifier Type | Case Style | Example |
| :--- | :--- | :--- |
| **Classes / Structs** | PascalCase | `RenderEngine`, `BufferLayout` |
| **Functions / Methods** | camelCase | `initialize()`, `bindShader()` |
| **Local Variables** | camelCase | `vertexCount`, `shaderSource` |
| **Private/Protected Members** | `m_` + camelCase | `m_windowWidth`, `m_isActive` |
| **Global / Static Variables** | `s_` + camelCase | `s_allocatedMemory` |
| **Constants / Macros** | ALL_CAPS | `MAX_BONES`, `AST_ASSERT` |
| **Enums and Enum Members** | PascalCase | `BufferType::VertexBuffer` |

---

## 2. Formatting & Layout

To keep code visually consistent, we follow a strict structural layout:

* **Indentation:** Use **4 spaces** instead of tabs.
* **Brace Style:** Allman style (braces on a new line) for classes, namespaces, and functions. 
* **Control Flow Braces:** Braces are mandatory for `if`, `else`, `for`, and `while` statements, even for single-line blocks.

```cpp
namespace Astryx
{
    class Renderer
    {
    public:
        void drawIndexed(uint32_t count)
        {
            if (count == 0)
            {
                return; 
            }
            
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
    };
}
```

## 3. Modern C++ Best Practices
Because Astryx targets C++20, we leverage modern language features to write safer, faster code.

#### Memory Management
* No Raw new or delete: Use std::unique_ptr or std::shared_ptr to manage heap allocations. Raw pointers should only be used as non-owning, observing pointers.

* Prefer std::make_unique and std::make_shared over manual smart pointer instantiation.

#### Type Safety and Performance
* Use explicit fixed-width integers (int32_t, uint32_t, uint64_t) from <cstdint> instead of naked int or long when size matters (especially in graphics data layouts).

* Pass complex objects, structs, and strings by const& (const reference) to avoid costly copies.

* Mark member functions as const if they do not modify the object's state.

* Always use override when implementing a virtual function in a derived class.

#### Comments & Documentation

* Use // for everything (No Doxygen)