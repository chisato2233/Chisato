#pragma once


namespace cst {
	using game_time_point = std::chrono::duration<float>;
	struct timer {

		inline static std::chrono::time_point<std::chrono::steady_clock> start_time_point;
		inline static game_time_point frame_time;

		static void init() {
			last_frame_time_ = start_time_point = std::chrono::steady_clock::now();
		}

		static void update() {
			auto now = std::chrono::steady_clock::now();
			frame_time = now - last_frame_time_;
			last_frame_time_ = now;
		}

		static auto now() -> game_time_point {
			using namespace std::chrono;
			return steady_clock::now() - start_time_point;
		}
		static auto delta() noexcept-> game_time_point { return frame_time; }
	private:
		inline static std::chrono::time_point<std::chrono::steady_clock> last_frame_time_;

	};
}