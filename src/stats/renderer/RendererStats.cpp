#include "RendererStats.h"
#include <cstdint>

RendererStats rendererStats;

void ClearRendererStats() {
    rendererStats.drawCalls = 0;
}