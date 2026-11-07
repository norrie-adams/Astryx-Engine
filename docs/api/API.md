# Engine API

This is the engine API. There isn't much of an API yet so its not going to be very long.

### Navigating the UI:

When you launch the engine, in the top left will be the debug panel. To interact with the debug panel hit the "Tab" key. You can add a cube, which, creates a cube. I know its amazing.

### Sandbox

Sandbox is just createEntity and addComponent. Its self explanatory. Below is the example code:

```cpp

uint32_t entityA = testRegistry->createEntity();
testRegistry->addComponent(entityA, Transform{
    .position = glm::vec3(10.0f, 10.0f, 10.0f),
    .rotation = glm::vec3(0.0f),
    .scale = glm::vec3(0.0f)
});

```