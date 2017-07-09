#include "CollisionDetector.h"
#include <glm/glm.hpp>
#include <numeric>

// AABB - Circle collision
Collision CollisionDetector::checkCollision(const Ball &ball, const GameObject &gameObject) {
    // Get center point circle first
    glm::vec2 center = ball.position() + ball.radius();
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabbHalfExtents(gameObject.size().x / 2, gameObject.size().y / 2);
    glm::vec2 aabbCenter(
            gameObject.position().x + aabbHalfExtents.x,
            gameObject.position().y + aabbHalfExtents.y
    );
    // Get difference vector between both centers
    glm::vec2 difference = center - aabbCenter;
    glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabbCenter + clamped;
    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;

    return glm::length(difference) <= ball.radius() ?
           std::make_tuple(true, CollisionDetector::getVectorDirection(difference), difference) :
           std::make_tuple(false, Direction::UP, glm::vec2(0, 0));
}

// AABB - AABB collision
bool CollisionDetector::checkCollision(const GameObject& gameObject1, const GameObject& gameObject2) {
    // Collision x-axis
    bool collisionX = gameObject1.position().x + gameObject1.size().x >= gameObject2.position().x &&
                      gameObject2.position().x + gameObject2.size().x >= gameObject1.position().x;
    // Collision y-axis
    bool collisionY = gameObject1.position().y + gameObject1.size().y >= gameObject2.position().y &&
                      gameObject2.position().y + gameObject2.size().y >= gameObject1.position().y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

Direction CollisionDetector::getVectorDirection(const glm::vec2 &target) {
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f),	// left
        glm::vec2(1.0f, 0.0f)	// right
    };

    float max = 0.0f;
    int bestMatch = -1;
    for (int i = 0; i < compass->length(); i++) {
        float dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max) {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return static_cast<Direction>(bestMatch);
}
