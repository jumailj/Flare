workspace "Flare"
    architecture"x64"
    toolset "gcc"  --use c++ compiler
    configurations {"Debug", "Release", "Ship"}
    startproject "Flare"

    outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Folder Name: Debug/Relese/Ship | Linux | 32x/64x

    IncludeDir = {}
    IncludeDir["glfw"] = "Flare/vendor/glfw/include"
    IncludeDir["glad"] = "Flare/vendor/glad/include"
    IncludeDir["ImGui"] = "Flare/vendor/imgui"
    IncludeDir["glm"] = "Flare/vendor/glm"

    group "Dependencies"
        include "Flare/vendor/glfw"
        include "Flare/vendor/glad"
        include "Flare/vendor/imgui"
    group ""

project "Flare" 
    location "Flare"
    kind "StaticLib"
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
    includedirs { 
        "%{prj.name}/src",   
        "Flare/vendor/spdlog/include", 
        "%{IncludeDir.glfw}", 
        "%{IncludeDir.glad}", 
        "%{IncludeDir.glm}", 
        "%{IncludeDir.ImGui}" }

    -- externalincludedirs { "../lua/include", "../zlib" }

    -- links{"glfw", "Xrandr", "Xi", "GLU", "GL", "X11", "dl", "pthread", "stdc++fs" }, [new -ldl -lGL (adding this can cause crashes)]
    links{ "GL", "glfw", "glad","ImGui" ,"pthread"} 

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




project "Sandbox" 
       location "Sandbox"
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
   
       -- includedirs { "/home/jumail/Documents/Flare/Flare/vendor/spdlog/include", "/home/world" }
       -- includedirs { "%{prj.name}/src",   "Flare/vendor/spdlog/include", "%{IncludeDir.glfw}", "%{IncludeDir.glad}", "%{IncludeDir.glm}", "%{IncludeDir.ImGui}" }

       includedirs {"Flare/vendor/spdlog/include", "{prj.name}/src", "Flare/src", "%{IncludeDir.ImGui}"}
   
       -- externalincludedirs { "../lua/include", "../zlib" }
   
       links{"Flare", "glfw", "glad", "ImGui"}  



--findings.
       -- Sanbox neede imgui to be linked.  // checked
       -- what if i removed imgui from Flare and add it only in Sandbox? 
       -- it's going to work becasue  we just need to link imgui to sandbox, don't know whant if i add it both flare and sandbox, size increases? // have to check
       -- removing glad ?? it's also getting linking error
       -- removing "glfw" ?? it's also getting linking error
       -- removing "GLU" ?? it's working without glu //good
       -- removing "GL" ?? it's working wihout gl //good


   
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
   