#ifndef _KIRI_MATH_PARALLEL_H_
#define _KIRI_MATH_PARALLEL_H_

#define KIRI_TASKING_OPENMP

namespace kiri_math_mini {

//! Execution policy tag.
enum class ExecutionPolicy {
    kSerial,
    kParallel
};

//! Fills from \p begin to \p end with \p value in parallel.
template <typename RandomIterator, typename T>
void parallelFill(const RandomIterator &begin, const RandomIterator &end,
                  const T &value,
                  ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Makes a for-loop from \p beginIndex \p to endIndex in parallel.
template <typename IndexType, typename Function>
void parallelFor(IndexType beginIndex, IndexType endIndex,
                 const Function &function,
                 ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Makes a range-loop from \p beginIndex \p to endIndex in parallel.
template <typename IndexType, typename Function>
void parallelRangeFor(IndexType beginIndex, IndexType endIndex,
                      const Function &function,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Makes a 2D nested for-loop in parallel.
template <typename IndexType, typename Function>
void parallelFor(IndexType beginIndexX, IndexType endIndexX,
                 IndexType beginIndexY, IndexType endIndexY,
                 const Function &function,
                 ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Makes a 2D nested range-loop in parallel.
template <typename IndexType, typename Function>
void parallelRangeFor(IndexType beginIndexX, IndexType endIndexX,
                      IndexType beginIndexY, IndexType endIndexY,
                      const Function &function,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Makes a 3D nested for-loop in parallel.
template <typename IndexType, typename Function>
void parallelFor(IndexType beginIndexX, IndexType endIndexX,
                 IndexType beginIndexY, IndexType endIndexY,
                 IndexType beginIndexZ, IndexType endIndexZ,
                 const Function &function,
                 ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Makes a 3D nested range-loop in parallel.
template <typename IndexType, typename Function>
void parallelRangeFor(IndexType beginIndexX, IndexType endIndexX,
                      IndexType beginIndexY, IndexType endIndexY,
                      IndexType beginIndexZ, IndexType endIndexZ,
                      const Function &function,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Performs reduce operation in parallel.
template <typename IndexType, typename Value, typename Function, typename Reduce>
Value parallelReduce(IndexType beginIndex, IndexType endIndex,
                     const Value &identity, const Function &func,
                     const Reduce &reduce,
                     ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Sorts a container in parallel.
template <typename RandomIterator>
void parallelSort(RandomIterator begin, RandomIterator end,
                  ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Sorts a container in parallel with a custom compare function.
template <typename RandomIterator, typename CompareFunction>
void parallelSort(RandomIterator begin, RandomIterator end,
                  CompareFunction compare,
                  ExecutionPolicy policy = ExecutionPolicy::kParallel);

//! Sets maximum number of threads to use.
void setMaxNumberOfThreads(unsigned int numThreads);

//! Returns maximum number of threads to use.
unsigned int maxNumberOfThreads();

} // namespace kiri_math_mini

#include "inl/parallel-inl.h"

#endif // _KIRI_MATH_PARALLEL_H_