#include "ecs/Registry.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

Registry registry;

TEST(EntityTest, CreatesEntity) {
    Entity expectedID = registry.m_EntityCounter;
    Entity actualID = registry.createEntity();

    EXPECT_EQ(expectedID, actualID);
}

TEST(EntityTest, DeletesEntity) {
    // Asserts that an Entity was created
    Entity expectedID = registry.m_EntityCounter;
    Entity actualID = registry.createEntity();
    ASSERT_EQ(expectedID, actualID);

    registry.deleteEntity(actualID);
    EXPECT_THAT(registry.getDeadEntities(), ::testing::Contains(actualID));
}