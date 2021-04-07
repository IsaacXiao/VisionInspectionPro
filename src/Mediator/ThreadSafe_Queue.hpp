#ifndef THREADSAFE_QUEUE_HPP
#define THREADSAFE_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

template<typename T>
class ThreadSafe_Queue
{
private:
	mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
    bool running_{true};
public:
	ThreadSafe_Queue() = default;
	//自定义了拷贝操作，编译器不会生成移动操作
    ThreadSafe_Queue(ThreadSafe_Queue const& other)
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue=other.data_queue;
    }

    /// <summary>
    /// 如果点击停止之后，线程还在等待最后一帧
    /// 则给它个空的让它结束此次等待
    /// 修改运行状态后它下次就不会再等了
    /// 用这种方式停止等待
    /// 也适合其他任何类似场景
    /// 如此对外提供接口使得这个类的可复用性更高
    /// </summary>
    void StopWaiting()
    { 
        std::unique_lock<std::mutex> lk(mut);
        data_queue.push(T());
        running_ = false;
        data_cond.notify_one();
    }

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

	/*void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk,[this]{return !data_queue.empty();});
		value=data_queue.front();
		data_queue.pop();
	}*/

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        if(running_)
            data_cond.wait(lk, [this] { return !data_queue.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty)
            return false;
        value=data_queue.front();
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

#endif