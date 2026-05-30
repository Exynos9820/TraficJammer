#include "Tree.h"
#include "Collision.h"

void Tree::Update(const std::chrono::microseconds& ms) {}

const Collider Tree::GetCollider() {
    float radius = m_config.size * 0.5f;
    return CircleCollider{{m_position.x + radius, m_position.y + radius}, radius};
}
