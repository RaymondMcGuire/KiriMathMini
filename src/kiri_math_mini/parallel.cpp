/*** 
 * @Author: Xu.WANG
 * @Date: 2020-10-18 02:04:46
 * @LastEditTime: 2020-11-02 18:16:16
 * @LastEditors: Xu.WANG
 * @Description: 
 * @FilePath: \Kiri\KiriMath\src\kiri_math_mini\parallel.cpp
 */
#include <kiri_math_mini/parallel.h>

#include <memory>
#include <thread>
#include <iostream>

#if defined(KIRI_TASKING_OPENMP)
#include <omp.h>
#endif

static unsigned int sMaxNumberOfThreads = std::thread::hardware_concurrency();

namespace kiri_math_mini
{

    void setMaxNumberOfThreads(unsigned int numThreads)
    {
#if defined(KIRI_TASKING_TBB)
        static std::unique_ptr<tbb::task_scheduler_init> tbbInit;
        if (!tbbInit.get())
            tbbInit.reset(new tbb::task_scheduler_init(numThreads));
        else
        {
            tbbInit->terminate();
            tbbInit->initialize(numThreads);
        }
#elif defined(KIRI_TASKING_OPENMP)
        omp_set_num_threads(numThreads);
#endif
        sMaxNumberOfThreads = std::max(numThreads, 1u);
    }

    unsigned int maxNumberOfThreads() { return sMaxNumberOfThreads; }

} // namespace kiri_math_mini
