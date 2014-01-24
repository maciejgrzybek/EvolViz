#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace common
{

class NoTimeoutWait
{
protected:
	template <class Predicate>
	void wait(std::condition_variable& cv, std::unique_lock<std::mutex>& l,
				Predicate pred)
	{
		cv.wait(l, pred);
	}
};

template <int Milliseconds>
class TimeoutWait
{
protected:
	template <class Predicate>
	void wait(std::condition_variable& cv, std::unique_lock<std::mutex>& l,
				Predicate pred)
	{
		cv.wait_for(l, std::chrono::milliseconds(Milliseconds), pred);
	}
};

template <class Type, class WaitingPolicy = NoTimeoutWait>
class BlockingQueue : private WaitingPolicy
{
public:
	void push(const Type& value)
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
			queue_.push(value);
		}
		condVar_.notify_one();
	}

	void push(Type&& value)
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
			queue_.push(std::move(value));
		}
		condVar_.notify_one();
	}

	void pop(Type& result)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		// wait until underlying container (queue) become non-empty
		this->wait(condVar_, lock, [this]{ return !queue_.empty(); });
		result = std::move(queue_.front());
		queue_.pop();
	}

private:
	std::condition_variable condVar_;
	std::mutex mutex_;
	std::queue<Type> queue_; // underlying container
};

} // namespace common

