/**
 * @brief ~~Stolen~~ _Borrowed_ in part from https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue
*/

#include <queue>
#include <mutex>
#include <optional>

template<typename T> class ThreadSafeQueue {
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    size_t capacity;

    // Moved out of public interface to prevent races between this
    // and pop().
    bool empty() const {
        return queue_.empty();
    }

    public:

        ThreadSafeQueue(size_t capacity) {
            this->queue_ = std::queue<T>();
            this->mutex_ = std::mutex();
            this->capacity = capacity;
        }

        ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete ;
        ThreadSafeQueue& operator=(const ThreadSafeQueue<T> &) = delete ;

        ThreadSafeQueue(ThreadSafeQueue<T>&& other) {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_ = std::move(other.queue_);
        }

    virtual ~ThreadSafeQueue() { }

    unsigned long size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    /**
     * @brief Pushes to the queue iff doing so would not cause the queue
     * to go over capacity. Otherwise returns false.
    */
    bool conditional_push(const T &item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.size() >= this->capacity) {
            return false;
        }
        queue_.push(item);
    }

    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return {};
        }
        T tmp = queue_.front();
        queue_.pop();
        return tmp;
    }
};