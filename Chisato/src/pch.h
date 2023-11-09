#pragma once

#ifdef CST_PLATFORM_WINDOWS
	#include<Windows.h>
#endif 

//std
#include<iostream>
#include<memory>
#include<utility>
#include<algorithm>
#include<ranges>
#include<chrono>
#include<functional>
#include<format>
#include<concepts>

//stl
#include<string>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<stack>
#include<sstream>
#include<variant>

//opengl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <imgui.h>


//my lib
#include<ChisatoCore/Core.h>
#include<ChisatoCore/Events/event_lib.h>
//#include<ChisatoCore/Layers/layer_lib.h>
#include<ChisatoCore/Tools/ToolLib.h>
#include<ChisatoCore/platforms.h>
