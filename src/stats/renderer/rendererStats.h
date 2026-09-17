#pragma once

#include <cstdint>

struct RendererStats 
{
    uint32_t drawCalls = 0;
};

void ClearRendererStats();

extern RendererStats rendererStats;