#pragma once

#include "Tree.h"

class RadialRoundTree : public Tree {
  public:
    RadialRoundTree(const TreeConfig& config) : Tree(config) {}
    void Render() override;
};
