#include "AppEvent.h"

std::string Chisato::WindowResizeEvent::GetName() const noexcept {
    return std::format(
        "[Event]: Window Resize ({},{})",
        size.first, size.second
    );
}

std::string Chisato::WindowCloseEvent::GetName() const noexcept { return "[Event]: Window Close"; }

std::string Chisato::AppTickEvent::GetName() const noexcept{
    return std::format("[Event]: Application Tick");
}

std::string Chisato::AppUpdateEvent::GetName() const noexcept{
    return std::format("[Event]: Application Update");
}

std::string Chisato::AppRenderEvent::GetName() const noexcept {
    return std::format("[Event]: Application Render");
}