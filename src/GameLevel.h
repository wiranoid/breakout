#pragma once

#include "SpriteRenderer.h"
#include "Brick.h"
#include <string>
#include <memory>
#include <vector>

class GameLevel {
public:
    GameLevel(const std::string& path, int levelWidth, int levelHeight);
    ~GameLevel();

    void render(SpriteRenderer& renderer);
    bool isCompleted();

    // getters
    std::vector<std::unique_ptr<Brick>>& bricks() { return bricks_; }
private:
    std::vector<std::unique_ptr<Brick>> bricks_;

    std::vector<std::vector<int>> loadTiles(const std::string& path);
    void initLevel(std::vector<std::vector<int>>& tiles, int levelWidth, int levelHeight);
};
