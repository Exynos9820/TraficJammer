#pragma once

#include "Tree.h"

class CloverTree : public Tree {
  public:
    CloverTree(const TreeConfig& config) : Tree(config) {}
    void Render() override;
    const Collider GetCollider() override;
};
