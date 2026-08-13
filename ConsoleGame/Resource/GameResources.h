#pragma once

#include <string>
#include <vector>


struct HazardResources
{
    std::vector<std::wstring> obstacleKeys;
    std::vector<std::wstring> enemyKeys;
    std::vector<std::wstring> ceilingKeys;
};

struct GameResources
{
    std::vector<std::wstring> mapKeys;
    std::vector<std::wstring> playerKeys;
    std::vector<std::wstring> effectKeys;

    HazardResources hazard;
};
