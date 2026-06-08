#include "CollisionManager.h"
#include "Collision.h"
#include "Object.h"

CollisionManager* CollisionManager::managerPtr = nullptr;
std::mutex CollisionManager::mtx;
std::vector<Object*> CollisionManager::objects;

void CollisionManager::Update() {
    // for now simple implementation - just test all the pairs of the objts

    for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            auto& obj1 = objects[i];
            auto& obj2 = objects[j];

            // we need to test all poisibilities
            // if any of them is trigger - skip for now
            if (obj1->GetColliderType() == ColliderType::TRIGGER or
                obj2->GetColliderType() == ColliderType::TRIGGER) {
                continue;
            }

            const CollisionManifold manifold =
                GetCollisionManifold(obj1->GetCollider(), obj2->GetCollider());

            if (manifold.depth <= 0) {
                continue;
            }

            bool k1 = obj1->GetColliderType() == ColliderType::KINEMATIC;
            bool k2 = obj2->GetColliderType() == ColliderType::KINEMATIC;
            // If both kinematic split the push 50/50; if only one is kinematic it absorbs the full
            // depth
            float push = k1 && k2 ? 0.5f : 1.0f;

            if (k1) {
                obj1->Stop();
                obj1->Move(manifold.normal * (manifold.depth * push));
            }

            if (k2) {
                obj2->Stop();
                obj2->Move(manifold.normal * (-manifold.depth * push));
            }
        }
    }
}
