#pragma once

#include "Tree.h"

class BushyTree : public Tree {
  public:
    BushyTree(const TreeConfig& config) : Tree(config) {}
    void Render() override;
};
