#pragma once

#include "Object.h"
#include <mutex>
#include <vector>

class CollisionManager {
  private:
    CollisionManager() {}

    static std::mutex mtx;

    static CollisionManager* managerPtr;

    static std::vector<Object*> objects;

  public:
    // Singleton - so no copy constructor
    CollisionManager(const CollisionManager& manager) = delete;

    static CollisionManager* getInstance() {
        if (managerPtr == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (managerPtr == nullptr) {
                managerPtr = new CollisionManager();
            }
        }
        return managerPtr;
    }

    static void AddObject(Object* object) { objects.push_back(object); }

    static void Update();
};
