#pragma once

class UIManager {
    public:
        UIManager() = default;
        ~UIManager() = default;
        void drawUI();

    private:
        void drawDebugPanel();
};