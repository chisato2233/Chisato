#pragma once
#include <Ultralight/Ultralight.h>
#include <AppCore/Platform.h>
#include "ChisatoCore/Rendering/Renderer.h"
#include <GL/gl.h>

namespace cst::web {
	namespace ul { using namespace ultralight; }

	struct CSTAPI app {
		static void init() {
			using namespace ul;
			Config config;

			auto path = file_path::web_path / "resources/";
			config.resource_path_prefix = path.string().c_str();
			

			Platform::instance().set_config(config);
			Platform::instance().set_font_loader(GetPlatformFontLoader());
			Platform::instance().set_file_system(GetPlatformFileSystem(file_path::web_path.string().c_str()));

			auto log_path = file_path::web_path / "log" / "ultralight.log";
			Platform::instance().set_logger(GetDefaultLogger(log_path.string().c_str()));

			web_renderer = Renderer::Create();

			ViewConfig view_config;
			view_config.is_accelerated = false;

			view = web_renderer->CreateView(500, 500, view_config, nullptr);
			view->LoadHTML("<h1>Hello World!</h1>");

			glGenTextures(1, &cst::web::app::texture_id);
			glBindTexture(GL_TEXTURE_2D, cst::web::app::texture_id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		static void update() {
			web_renderer->Update();
			web_renderer->Render(); // Ensure we call Render as well

			auto* surface = static_cast<ultralight::BitmapSurface*>(view->surface());

			if (!surface->dirty_bounds().IsEmpty()) {
				ul::RefPtr<ul::Bitmap> bitmap = surface->bitmap();
				void* pixels = bitmap->LockPixels();

				uint32_t width = bitmap->width();
				uint32_t height = bitmap->height();
				uint32_t stride = bitmap->row_bytes();

				glBindTexture(GL_TEXTURE_2D, texture_id);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

				bitmap->UnlockPixels();
				surface->ClearDirtyBounds();
			}
			render();
		}

		static void render() {
			glBindTexture(GL_TEXTURE_2D, texture_id);

			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}

		inline static ul::RefPtr<ul::Renderer> web_renderer;
		inline static ul::RefPtr<ul::View> view;
		inline static GLuint texture_id;
	};
}
