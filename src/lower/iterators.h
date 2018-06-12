#ifndef TACO_LOWER_ITERATORS_H
#define TACO_LOWER_ITERATORS_H

#include "iteration_graph.h"
#include "tensor_path.h"
#include "storage/iterator.h"

#include <map>
#include <vector>
#include <memory>

namespace taco {
class TensorVar;

namespace ir {
class Expr;
}

namespace lower {

/// Tracks the per-edge iterators of the tensor paths of an iteration graph.
class Iterators {
public:
  Iterators();

  Iterators(const IterationGraph& graph,
            const std::map<TensorVar,ir::Expr>& tensorVariables);

  /// Returns the root iterator.
  /// TODO: Should each path have a 0 step that's the root, so that we can use
  /// operator[] to get the root (with step 0)?
  const storage::Iterator& getRoot(const TensorPath&) const;

  /// Returns the iterator for the step.
  const storage::Iterator& operator[](const TensorPathStep&) const;

  /// Returns the iterators for the steps.
  std::vector<storage::Iterator>
  operator[](const std::vector<TensorPathStep>&) const;

private:
  std::map<TensorPath, storage::Iterator> roots;
  std::map<TensorPathStep, storage::Iterator> iterators;
  std::vector<std::unique_ptr<ModePack>> modePacks;
};


/// Returns the iterators over full dimensions
std::vector<storage::Iterator>
getFullIterators(const std::vector<storage::Iterator>&);

/// Returns the idx vars of the iterators.
std::vector<ir::Expr> getIdxVars(const std::vector<storage::Iterator>&);

}}
#endif
