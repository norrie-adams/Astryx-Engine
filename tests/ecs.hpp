#pragma once
#include "ecs/System.h"
#include "ecs/Registry.h"
#include "AstryxTest.hpp"
#include <vector>

class ECSTests : public AstryxTest {
    public:
    // Remove entites helper function
    std::vector<Entity> getDeadEntities() const {
        auto copy = testRegistry->m_reusedEntities;
        std::vector<Entity> elements;
        while (copy.size() != 0) {
            elements.push_back(copy.front());
            copy.pop();
        }
        return elements;
    };

    // Remove component helper function

};