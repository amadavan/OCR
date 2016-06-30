#ifndef OCR_UTIL_TIMER_H_
#define OCR_UTIL_TIMER_H_

#include <chrono>

namespace ocr {
	class Timer {
	public:
		typedef std::chrono::high_resolution_clock high_resolution_clock;
		typedef std::chrono::milliseconds milliseconds;
		typedef std::chrono::nanoseconds nanoseconds;
		Timer() {}
		~Timer() {}

		void start() {
			start_time_ = high_resolution_clock::now();
			running_ = true;
		}

		nanoseconds elapsed_ns() {
			if ( running_ ) {
				return high_resolution_clock::now() - start_time_;
			}
			else {
				return end_time_ - start_time_;
			}
		}

		milliseconds elapsed_ms() {
			return std::chrono::duration_cast<milliseconds>(elapsed_ns());
		}

		void stop() {
			end_time_ = high_resolution_clock::now();
			running_ = false;
		}

	private:
		high_resolution_clock::time_point start_time_;
		high_resolution_clock::time_point end_time_;
		bool running_;
	};
}

#endif // OCR_UTIL_TIMER_H_