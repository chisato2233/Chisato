#pragma once
#include "buffer.h"
#include"vertex_array.h"
#include"shader.h"
#include"texture.h"
#include "Platforms/OpenGL/gl_buffer.h"
#include "Platforms/OpenGL/gl_vertex_array.h"
#include "Platforms/OpenGL/gl_shader.h"
#include"Platforms/OpenGL/gl_texture.h"


#include"Renderer.h"



namespace cst {
	using namespace rendering;

	inline auto vertex_buffer::create(const float* vertices, size_t size) ->ptr<vertex_buffer> {
		
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_vertex_buffer>(vertices, size);
		}

		return nullptr;
	}


	inline auto index_buffer::create(const unsigned* data, size_t size) ->ptr<index_buffer> {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_index_buffer>(data, size);
		}

		return nullptr;
	}

	inline auto vertex_array::create() ->ptr<vertex_array> {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_vertex_array>();
		}

		return nullptr;
	}
	inline auto shader::create(std::filesystem::path shader_file_path)->ptr<shader> {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_shader>(shader_file_path);
		}

		return nullptr;
	}

	inline auto shader::create(const ptr<vertex_shader>& v_shader,const ptr<fragment_shader>& f_shader ) ->ptr<shader> {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_shader>(v_shader,f_shader);
		}

		return nullptr;
	}

	inline auto vertex_shader::create(const std::string_view src) ->ptr<vertex_shader> {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_vertex_shader>(src);
		}

		return nullptr;
	}
	inline auto fragment_shader::create(const std::string_view src) ->ptr<fragment_shader> {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_fragment_shader>(src);
		}

		return nullptr;
	}


	inline auto texture_2D::create(std::filesystem::path path) ->ptr<texture_2D > {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_texture_2D>(std::filesystem::absolute(path));
		}

		return nullptr;
	}

	ptr<texture_2D> texture_2D::create(void* data, uint width, uint height, int channels) {
		switch (renderer::current_render_api) {
		case render_api::None:
		{
			debug::log<>::error("render_api::None is not supported");
		}break;

		case render_api::OpenGL:
			return std::make_shared<gl_texture_2D>(data, width, height, channels);
		}

		return nullptr;
	}
}
