#include "Parallel.hpp"

#include <algorithm>
#include <stdexcept>

RowWorkerPool::RowWorkerPool(const std::size_t workerCount)
{
    if (workerCount == 0)
        throw std::invalid_argument("RowWorkerPool requires at least one worker");

    workers.reserve(workerCount);

    for (std::size_t workerId = 0; workerId < workerCount; ++workerId)
        workers.emplace_back(&RowWorkerPool::WorkerLoop, this, workerId);
}

RowWorkerPool::~RowWorkerPool()
{
    {
        std::lock_guard lock{workersRemainingMutex};
        stopping = true;
    }
    workAvailable.notify_all();

    for (auto& worker : workers)
        worker.join();
}

void RowWorkerPool::WorkerLoop(const std::size_t workerId)
{
    std::size_t observedGeneration = 0;

    while (true)
    {
        RowTask task;
        std::size_t firstRow{};
        std::size_t lastRow{};
        {
            std::unique_lock lock{workersRemainingMutex};
            workAvailable.wait(lock, [this, &observedGeneration]
            {
                return stopping || poolGeneration != observedGeneration;
            });

            if (stopping)
                return;

            observedGeneration = poolGeneration;
            firstRow = startRow;
            lastRow = endRow;
            task = currentTask;
        }

        const auto rowCount = lastRow - firstRow;
        const auto baseRowsCount = rowCount / workers.size();
        const auto extraCounts = rowCount % workers.size();
        const auto start = firstRow + workerId * baseRowsCount + std::min(workerId, extraCounts);
        const auto end = start + baseRowsCount + (workerId < extraCounts ? 1 : 0);

        task(workerId, start, end);

        bool allWorkersFinished = false;
        {
            std::lock_guard lock{workersRemainingMutex};
            allWorkersFinished = --workersRemaining == 0;
        }

        if (allWorkersFinished)
            workFinished.notify_one();
    }
}

void RowWorkerPool::ParallelForRows(const std::size_t firstRow, const std::size_t endRow, const RowTask& task)
{
    std::unique_lock lock{workersRemainingMutex};
    if (endRow < firstRow)
        throw std::invalid_argument("endRow must not be less than firstRow");

    currentTask = task;
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
