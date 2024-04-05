#pragma once
#include<glad/glad.h>

namespace cst {
	struct CSTAPI buffer :no_copy{
		virtual ~buffer() {}
		virtual buffer& bind() = 0;
	};


	
	struct element_size_type {
		size_t size{}, count{};
		GLenum gl_type = GL_NONE;
		auto operator<=>(const element_size_type&) const = default;
	};

	inline namespace detail {
		template<class T,size_t Count>
		constexpr GLenum _get_gl_count() {
			if constexpr(std::is_same_v<T,float>) {
				if constexpr (Count == 1) return GL_FLOAT;
				else if constexpr (Count == 2) return GL_FLOAT_VEC2;
				else if constexpr (Count == 3) return GL_FLOAT_VEC3;
				else if constexpr (Count == 4) return GL_FLOAT_VEC4;
				else return GL_NONE;
			}
			else if constexpr(std::is_same_v<T,int>) {
				if constexpr (Count == 1) return GL_INT;
				else if constexpr (Count == 2) return GL_INT_VEC2;
				else if constexpr (Count == 3) return GL_INT_VEC3;
				else if constexpr (Count == 4) return GL_INT_VEC4;
				else return GL_NONE;
			}
			else if constexpr(std::is_same_v<T,unsigned>) {
				if constexpr (Count == 1) return GL_UNSIGNED_INT;
				else if constexpr (Count == 2) return GL_UNSIGNED_INT_VEC2;
				else if constexpr (Count == 3) return GL_UNSIGNED_INT_VEC3;
				else if constexpr (Count == 4) return GL_UNSIGNED_INT_VEC4;
				else return GL_NONE;
			}
			else if constexpr (std::is_same_v<T, bool>) {
				if constexpr (Count == 1) return GL_BOOL;
				else if constexpr (Count == 2) return GL_BOOL_VEC2;
				else if constexpr (Count == 3) return GL_BOOL_VEC3;
				else if constexpr (Count == 4) return GL_BOOL_VEC4;
				else return GL_NONE;
			}

			else if constexpr(std::is_same_v<T,float[2][2]>) {return GL_FLOAT_MAT2;}
			else if constexpr(std::is_same_v<T,float[3][3]>) {return GL_FLOAT_MAT3;}
			else if constexpr(std::is_same_v<T,float[4][4]>) {return GL_FLOAT_MAT4;}
			else if constexpr(std::is_same_v<T,float[2][3]>) {return GL_FLOAT_MAT2x3;}
			else if constexpr(std::is_same_v<T,float[2][4]>) {return GL_FLOAT_MAT2x4;}
			else if constexpr(std::is_same_v<T,float[3][2]>) {return GL_FLOAT_MAT3x2;}
			else if constexpr(std::is_same_v<T,float[3][4]>) {return GL_FLOAT_MAT3x4;}
			else if constexpr(std::is_same_v<T,float[4][2]>) {return GL_FLOAT_MAT4x2;}
			else if constexpr(std::is_same_v<T,float[4][3]>) {return GL_FLOAT_MAT4x3;}
			else return GL_NONE;
		}
	}


	namespace shader_type {
		inline constexpr element_size_type Custom = {};

		template<size_t Count = 1>inline constexpr element_size_type Bool = {1,Count,_get_gl_count<bool,1>()};

		template<size_t Count = 1> inline constexpr element_size_type Float = {4,Count,_get_gl_count<float,1>()};
		template<size_t Count = 1> inline constexpr element_size_type Int = { 4,Count,_get_gl_count<int,1>()};

		template<size_t Count>inline constexpr element_size_type Vec = { 4,Count ,_get_gl_count<float,Count>};
		template<size_t Count>inline constexpr element_size_type Mat = { 4,Count*Count,_get_gl_count<float[Count][Count],Count>()};

	}


	struct CSTAPI buffer_layout_element {
		element_size_type type = {};
		std::string name = "None";

		size_t size = 0;
		size_t count = 0;
		size_t offset = 0;

		GLenum gl_type = GL_NONE;
		bool normalized = false;
	};

	struct CSTAPI buffer_layout {
		buffer_layout() = default;
		buffer_layout(std::initializer_list<buffer_layout_element>&& init):elements(std::move(init)) {
			size_t offset = 0;
			for (auto& element : elements) {

				if(element.type !=shader_type::Custom) {
					element.size = element.type.size * element.type.count;
					element.count = element.type.count;
					element.gl_type = element.type.gl_type;
					
				}

				element.offset = offset;
				offset += element.size;
			}
			stride = offset;
		}

		auto begin()const noexcept { return elements.begin(); }
		auto end()const noexcept { return elements.end(); }

		std::vector<buffer_layout_element> elements;
		size_t stride = 0;
	};



	struct CSTAPI vertex_buffer : buffer {
		vertex_buffer(size_t count) :size(count) {}
		virtual ~vertex_buffer() = default;
		inline static ptr<vertex_buffer> create(const float* data,size_t size);

		
		virtual vertex_buffer& bind_layout(const buffer_layout&) = 0;
		size_t size;

		auto& get_layout()const noexcept { return buffer_layout_; }
	protected:
		buffer_layout buffer_layout_;
	};

	struct CSTAPI index_buffer : buffer {
		index_buffer(size_t count) :count(count) {}

		virtual ~index_buffer() = default;
		inline static ptr<index_buffer> create(const unsigned* data, size_t count);

		size_t count;
	};


}