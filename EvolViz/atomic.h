#pragma once
#include <mutex>
namespace utils {

template <class T>
class atomic
{
public:
	atomic() {}
	atomic(T& content) : content_(content) {}

	T load() {
		std::lock_guard<std::mutex> lock(mutex_);
		return content_;
	}

    void store(T new_content) {
		std::lock_guard<std::mutex> lock(mutex_);
		content_ = new_content;
	}

	operator T () {
		return load();
	}

private:
	T content_;
	std::mutex mutex_;
};

} // namespace utils
