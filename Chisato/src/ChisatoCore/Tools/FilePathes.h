#pragma once
namespace cst {
	namespace file_path {
		inline std::filesystem::path project_root_path;
		inline std::filesystem::path engine_root_path;
		inline std::filesystem::path game_root_path;

		inline std::filesystem::path engine_src_path;
		inline std::filesystem::path game_src_path;


		inline std::filesystem::path resource_path;
		inline std::filesystem::path shader_path;
		inline std::filesystem::path web_path;



		inline void init() {
			project_root_path = std::filesystem::current_path().parent_path();
			game_root_path = std::filesystem::current_path();
			engine_root_path = project_root_path / "Chisato";

			engine_src_path = engine_root_path / "src";
			game_src_path = game_root_path / "src";

			resource_path = engine_root_path / "Resources";
			shader_path = resource_path / "Shaders";
			web_path = resource_path / "Web";
		}



	}
}