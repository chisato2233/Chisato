namespace cst {
	namespace time {
		using namespace std::chrono;
		namespace {
			time_point<steady_clock> start;
			time_point<steady_clock> last_frame_time;
			
			nanoseconds deltaTime;
		}

		inline auto std_now()	{ return steady_clock::now() - start; }
		inline auto std_delta() { return deltaTime; }
		
		inline auto now()	-> float { return duration_cast<milliseconds>(std_now()).	count() / 1000.f; }
		inline auto delta() -> float { return duration_cast<milliseconds>(std_delta()).	count() / 1000.f; }

		inline void init() { last_frame_time = start = steady_clock::now(); }

		inline void update() {
			auto now= steady_clock::now();
			deltaTime = now - last_frame_time;
			last_frame_time = now;
		}
		
	}
}