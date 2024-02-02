workspace "Flare"
    architecture"x64"
    toolset "gcc"  --use c++ compiler
    configurations {"Debug", "Release", "Ship"}
    startproject "Flare"

    outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Folder Name: Debug/Relese/Ship | Linux | 32x/64x

    IncludeDir = {}
    IncludeDir["glfw"] = "Flare/vendor/glfw/include"
    IncludeDir["glad"] = "Flare/vendor/glad/include"

    group "Dependencies"
        include "Flare/vendor/glfw"
        include "Flare/vendor/glad"
    group ""

project "Flare" 
    location "Flare"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "c++17"
    systemversion "latest"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    --pchheader "Flare/stdafx.h"
    --pchsource "Flare/stdafx.cpp"

    files {
        -- "%{prj.name}/**.h",
        -- "%{prj.name}/**.cpp"
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }


    -- removing vendor files from source
    removefiles {
        "%{prj.name}/vendor/**h",
        "%{prj.name}/vendor/**cpp"
    }

    -- includedirs { "/home/jumail/Documents/Flare/Flare/vendor/spdlog/include", "/home/world" }
    includedirs { "%{prj.name}/src",   "Flare/vendor/spdlog/include", "%{IncludeDir.glfw}", "%{IncludeDir.glad}" }

    -- externalincludedirs { "../lua/include", "../zlib" }

    -- links{"glfw", "Xrandr", "Xi", "GLU", "GL", "X11", "dl", "pthread", "stdc++fs" }, [new -ldl -lGL (adding this can cause crashes)]
    links{ "GL", "GLU", "glfw", "glad" ,"m" ,"dl" ,"X11" ,"pthread" ,"Xi" ,"Xrandr" ,"Xinerama" ,"Xxf86vm" ,"Xcursor"}

    filter "configurations:Debug"
       defines "FLARE_DEBUG"
       runtime "Debug"
       symbols  "on"

   filter "configurations:Release"
       defines "FLARE_RELEASE"
       runtime "Release"
       symbols  "off"


   filter "configurations:Ship"
       defines "FLARE_DEBUG"
       runtime "Release"
       symbols  "off"
