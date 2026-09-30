#pragma once

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

class RowWorkerPool
{
public:
    using RowTask = std::function<void(
    std::size_t workerId,
    std::size_t startRow,
    std::size_t endRow)>; //exclusize

private:
    void WorkerLoop(const std::size_t workerId);
    std::size_t startRow{};
    std::size_t endRow{};
    std::size_t poolGeneration{};
    std::vector<std::thread> workers;
    std::mutex workersRemainingMutex;
    std::size_t workersRemaining{};
    std::condition_variable workAvailable;
    std::condition_variable workFinished;
    RowTask currentTask;
    bool stopping{};

public:
    explicit RowWorkerPool(const std::size_t workerCount);
    ~RowWorkerPool();
    
    RowWorkerPool(const RowWorkerPool&) = delete;
    RowWorkerPool& operator=(const RowWorkerPool&) = delete;

    void ParallelForRows(const std::size_t firstRow, const std::size_t endRow, const RowTask& task);
};