#pragma once
#include "scene/Registry.hpp"

class UIManager {
    public:
        UIManager(std::shared_ptr<Registry> registry) : m_Registry(registry) {};
        ~UIManager() = default;
        void drawUI();

    private:
        void drawDebugPanel();

    protected:
        std::shared_ptr<Registry> m_Registry;
};