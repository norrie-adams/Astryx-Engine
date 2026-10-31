#pragma once
#include "ecs/Registry.h"
#include "ecs/System.h"
#include "gtest/gtest.h"
#include <memory>

class AstryxTest : public ::testing::Test {
protected:
    void SetUp() override {
        testRegistry = std::make_shared<Registry>();
        testSystem = std::make_shared<System>(testRegistry);
    }
    std::shared_ptr<Registry> testRegistry;
    std::shared_ptr<System> testSystem;
};