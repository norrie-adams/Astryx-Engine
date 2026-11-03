#include "RendererStats.hpp"
#include <cstdint>

RendererStats rendererStats;

void ClearRendererStats() {
    rendererStats.drawCalls = 0;
}