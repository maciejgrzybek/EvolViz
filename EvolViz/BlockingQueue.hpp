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

template <class Type>
class QueueContainer
{
protected:
	void add(const Type& element)
	{
		container.push(element);
	}

	void add(Type&& element)
	{
		container.push(std::move(element));
	}

	const Type& front() const
	{
		return container.front();
	}

	Type& front()
	{
		return container.front();
	}

	void removeFirstElement()
	{
		return container.pop();
	}

	bool empty() const
	{
		return container.empty();
	}

private:
	std::queue<Type> container;
};

template <class Type, class Comparator = std::less<Type> >
class PriorityQueueContainer
{
protected:
	void add(const Type& element)
	{
		container.push(element);
	}

	void add(Type&& element)
	{
		container.push(std::move(element));
	}

	const Type& front() const
	{
		return container.top();
	}

    Type& front()
    {
        return const_cast<Type&>(container.top());
    }

	void removeFirstElement()
	{
		return container.pop();
	}

	bool empty() const
	{
		return container.empty();
	}

private:
	std::priority_queue<Type, std::vector<Type>, Comparator> container;
};

template <class Type, class WaitingPolicy = NoTimeoutWait, class ContainerPolicy = QueueContainer<Type> >
class BlockingQueue : private WaitingPolicy,
				      private ContainerPolicy
{
public:
	void push(const Type& value)
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
            this->add(value);
		}
		condVar_.notify_one();
	}

	void push(Type&& value)
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
            this->add(std::move(value));
		}
		condVar_.notify_one();
	}

    bool pop(Type& result)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		// wait until underlying container (queue) become non-empty
        this->wait(condVar_, lock, [this]{ return !this->empty(); });
        if (this->empty())
            return false;
        result = std::move(this->front());
        this->removeFirstElement();
        return true;
	}

private:
	std::condition_variable condVar_;
	std::mutex mutex_;
};

} // namespace common

