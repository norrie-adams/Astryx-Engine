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
    EXPECT_EQ(testRegistry->m_ComponentPools.size(), 1);
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
    ASSERT_EQ(testRegistry->m_ComponentPools.size(), 1);

    testRegistry->deleteEntity(actualID);
    EXPECT_EQ(testRegistry->m_ComponentPools.size(), 0);
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