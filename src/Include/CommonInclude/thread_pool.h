
#ifndef THREAD_POOL_H
#define THREAD_POOL_H


#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <assert.h>

#define  MAX_THREAD_NUM 256


class threadpool
{
    using Task = std::function<void()>;
    // 线程池
    std::vector<std::thread> pool_;
    // 任务队列
    std::queue<Task> tasks_;
    // 同步
    std::mutex lock_;
    // 条件阻塞
    std::condition_variable condition_;
    // 是否关闭提交
    std::atomic<bool> stoped_;
    //空闲线程数量
    std::atomic<int>  n_idle_;
public:
    inline threadpool(unsigned short size) :stoped_{ false }
    {
        n_idle_ = size < 1 ? 1 : size;
        for (size = 0; size < n_idle_; ++size)
        {   //初始化线程数量
            pool_.emplace_back(
                [this]
            { // 工作线程函数
                while (!this->stoped_)
                {
                    std::function<void()> task;
                    {   // 获取一个待执行的 task
                        std::unique_lock<std::mutex> lock{ this->lock_ };// unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
                        this->condition_.wait(lock,
                            [this] {
                            return this->stoped_.load() || !this->tasks_.empty();
                        }
                        ); // wait 直到有 task
                        if (this->stoped_ && this->tasks_.empty())
                            return;
                        task = std::move(this->tasks_.front()); // 取一个 task
                        this->tasks_.pop();
                    }
                    n_idle_--;
                    task();
                    n_idle_++;
                }
            });
        }
    }
    inline ~threadpool()
    {
        stoped_.store(true);
        condition_.notify_all(); // 唤醒所有线程执行
        for (std::thread& thread : pool_) 
        {
            //thread.detach(); // 让线程“自生自灭”
            if (thread.joinable())
                thread.join(); // 等待任务结束， 前提：线程一定会执行完
        }
    }
public:
    // 提交一个任务
    // 调用.get()获取返回值会等待任务执行完,获取返回值
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
    {
        if (stoped_.load())    
            throw std::runtime_error("commit on ThreadPool is stopped.");

        using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
        auto task = std::make_shared<std::packaged_task<RetType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );    // wtf !
        std::future<RetType> future = task->get_future();
        {    // 添加任务到队列
            std::lock_guard<std::mutex> lock{ lock_ };
            tasks_.emplace(
                [task]()
            { // push(Task{...})
                (*task)();
            }
            );
        }
        condition_.notify_one(); // 唤醒一个线程执行

        return future;
    }
    //空闲线程数量
    int idlCount() { return n_idle_; }
};




#endif