#include <memory>
#include <thread>
#include <iostream>

#if defined(KIRI_TASKING_OPENMP)
#include <omp.h>
#endif

static unsigned int sMaxNumberOfThreads = std::thread::hardware_concurrency();

namespace kiri_math_mini {

void setMaxNumberOfThreads(unsigned int numThreads) {
#if defined(KIRI_TASKING_OPENMP)
    omp_set_num_threads(numThreads);
#endif
    sMaxNumberOfThreads = std::max(numThreads, 1u);
}

unsigned int maxNumberOfThreads() {
    return sMaxNumberOfThreads;
}

} // namespace kiri_math_mini