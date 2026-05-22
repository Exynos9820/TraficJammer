#pragma once

#include "Tree.h"

class SimpleRoundTree : public Tree {
  public:
    SimpleRoundTree(const TreeConfig& config) : Tree(config) {}
    void Render() override;
};
