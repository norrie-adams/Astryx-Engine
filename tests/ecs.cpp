#include "ecs.hpp"
#include "ecs/Registry.h"
#include "ecs/System.h"
#include "ecs/components/Components.h"
#include <glm/glm.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>


TEST_F(ECSTests, CreateEntity) {
    Entity expectedID = testRegistry->m_EntityCounter;
    Entity actualID = testRegistry->createEntity();

    EXPECT_EQ(expectedID, actualID);
}

TEST_F(ECSTests, DeleteEntity) {
    // Asserts that an Entity was created
    Entity expectedID = testRegistry->m_EntityCounter;
    Entity actualID = testRegistry->createEntity();
    ASSERT_EQ(expectedID, actualID);

    testRegistry->deleteEntity(actualID);
    EXPECT_THAT(getDeadEntities(), ::testing::Contains(actualID));
}

TEST_F(ECSTests, AddComponent) {
    Entity expectedID = testRegistry->m_EntityCounter;
    Entity actualID = testRegistry->createEntity();
    ASSERT_EQ(expectedID, actualID);

    testRegistry->addComponent<Transform>(actualID, Transform{
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.0f)
    });

    ComponentMask testMask;
    uint32_t transformID = testRegistry->getComponentID<Transform>();
    testMask.set(transformID);
    ComponentMask entityMask = testRegistry->m_EntityMasks[actualID];

    EXPECT_EQ(testMask, entityMask);
}

TEST_F(ECSTests, RemoveComponent) {
    Entity expectedID = testRegistry->m_EntityCounter;
    Entity actualID = testRegistry->createEntity();
    ASSERT_EQ(expectedID, actualID);

    testRegistry->addComponent<Transform>(actualID, Transform{
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.0f)
    });

    // Make sure add component works
    ComponentMask testMask;
    uint32_t transformID = testRegistry->getComponentID<Transform>();
    testMask.set(transformID);
    ComponentMask entityMask = testRegistry->m_EntityMasks[actualID];
    bool hasComponent;
    ASSERT_EQ(testMask, entityMask);

    testRegistry->removeComponent<Transform>(actualID);
    entityMask = testRegistry->m_EntityMasks[actualID];

    if (entityMask == testMask) {
        bool hasComponent = true;
    } else { // we want the ELSE statement to run (ik its confusing idrc)
        bool hasComponent = false;
    }

    EXPECT_FALSE(hasComponent);
}

TEST_F(ECSTests, QuerieEntites) {
    Entity expectedID1 = testRegistry->m_EntityCounter;
    Entity entity1 = testRegistry->createEntity();
    ASSERT_EQ(expectedID1, entity1);

    Entity expectedID2 = testRegistry->m_EntityCounter;
    Entity entity2 = testRegistry->createEntity();
    ASSERT_EQ(expectedID2, entity2);

    testRegistry->addComponent<Transform>(entity1, Transform{
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.0f)
    });

    testRegistry->addComponent<Transform>(entity2, Transform{
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.0f)
    });

    std::vector entites = testSystem->matchEntites<Transform>();
    EXPECT_EQ(entites.size(), 2);
}