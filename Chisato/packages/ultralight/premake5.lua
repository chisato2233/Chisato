project "Ultralight"

    kind "Utility"
    language "C++"

    includedirs {
        "%{IncludeDir.ultralight}"
    }

    files {
        "Chisato/packages/ultralight/include/**.h",
        "Chisato/packages/ultralight/include/**.cpp" -- 如果有 CPP 文件也可以包括
    }