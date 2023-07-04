#include"pch.h"
#include "AppEvent.h"

std::string Chisato::Events::WindowResizeEvent::GetName() const noexcept {
    return std::format(
        "[Event]: Window Resize\n"
        "[Size]: ({},{})",
        width, hight
    );
}

std::string Chisato::Events::WindowCloseEvent::GetName() const noexcept{
    return std::format(
        "[Event]: Window Close"
    );
}

std::string Chisato::Events::AppTickEvent::GetName() const noexcept{
    return std::format("[Event]: Application Tick");
}

std::string Chisato::Events::AppUpdateEvent::GetName() const noexcept{
    return std::format("[Event]: Application Update");
}

std::string Chisato::Events::AppRenderEvent::GetName() const noexcept {
    return std::format("[Event]: Application Render");
}