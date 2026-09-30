#include "Parallel.hpp"

RowWorkerPool::RowWorkerPool(const std::size_t workerCount)
{
    workers.reserve(workerCount);

    for (std::size_t workerId = 0; workerId < workerCount; ++workerId)
        workers.emplace_back(&RowWorkerPool::WorkerLoop, this, workerId);
}

RowWorkerPool::~RowWorkerPool()
{
    for (auto& worker : workers)
        worker.join();
}

void RowWorkerPool::WorkerLoop(const std::size_t workerId)
{
    std::size_t observedGeneration = 0;

    {
        std::unique_lock lock{workersRemainingMutex};
        workAvailable.wait(lock, [this, &observedGeneration]
        {
            return poolGeneration != observedGeneration;
        });

        observedGeneration = poolGeneration;
    }

    const auto baseRowsCount = (endRow - startRow) / workers.size();
    const auto extraCounts = (endRow - startRow) % workers.size();
    const auto start = workerId * baseRowsCount + std::min(workerId, extraCounts); //to handle modulos
    const auto end = start + baseRowsCount + (workerId < extraCounts ? 1 : 0); //add end index to first workers

    currentTask(workerId, start, end);

    std::lock_guard lock{workersRemainingMutex};
    --workersRemaining;

    if (workersRemaining == 0)
        workFinished.notify_one();
}

void RowWorkerPool::ParallelForRows(const std::size_t firstRow, const std::size_t endRow, const RowTask& task)
{
    currentTask = task;
    
    std::unique_lock lock{workersRemainingMutex};
    startRow = firstRow;
    this->endRow = endRow;
    workersRemaining = workers.size();
    ++poolGeneration;
    workAvailable.notify_all();

    workFinished.wait(lock, [this]()
    {
        return workersRemaining == 0;
    });
}
