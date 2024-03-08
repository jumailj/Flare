workspace "Flare"
    architecture"x64"
    toolset "gcc"  --use c++ compiler
    configurations {"Debug", "Release", "Ship"}
    startproject "Sandbox"

    outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Folder Name: Debug/Relese/Ship | Linux | 64x

    IncludeDir = {}
    IncludeDir["glfw"] = "Flare/vendor/glfw/include"
    IncludeDir["glad"] = "Flare/vendor/glad/include"
    IncludeDir["ImGui"] = "Flare/vendor/imgui"
    IncludeDir["glm"] = "Flare/vendor/glm"
    IncludeDir["stb_image"] = "Flare/vendor/stb_image"
    IncludeDir["v8"] = "Flare/vendor/v8/include"
    IncludeDir["entt"] = "Flare/vendor/entt/include"    
    IncludeDir["yaml-cpp"] = "Flare/vendor/yaml-cpp/include"
    IncludeDir["nativefiledialog"] = "Flare/vendor/nativefiledialog/src/include"
    IncludeDir["ImGuizmo"] = "Flare/vendor/ImGuizmo"

    group "Dependencies"
        include "Flare/vendor/glfw"
        include "Flare/vendor/glad"
        include "Flare/vendor/imgui"
        include "Flare/vendor/yaml-cpp"
        include "Flare/vendor/nativefiledialog"
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
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/stb_image/stb_image.h",
        "%{prj.name}/vendor/stb_image/stb_image.cpp",

        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",

        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp",

    }


    -- removing vendor files from source
    -- removefiles {
    --     "%{prj.name}/vendor/**h",
    --     "%{prj.name}/vendor/**cpp"
    -- }

    -- includedirs { "/home/jumail/Documents/Flare/Flare/vendor/spdlog/include", "/home/world" }
    includedirs { 
        "%{prj.name}/src",   
        "Flare/vendor/spdlog/include", 
        "%{IncludeDir.glfw}", 
        "%{IncludeDir.glad}", 
        "%{IncludeDir.glm}", 
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.v8}",
        "%{IncludeDir.entt}",
        "%{IncludeDir['yaml-cpp']}", -- [] becaue it's cotain hyphens
        "%{IncludeDir.nativefiledialog}",
        "%{IncludeDir.ImGuizmo}",
    }

    -- externalincludedirs { "../lua/include", "../zlib" }

    libdirs{
        "%{prj.name}/vendor/v8/x86-lib"
    }

    -- links{"glfw", "Xrandr", "Xi", "GLU", "GL", "X11", "dl", "pthread", "stdc++fs" }, [new -ldl -lGL (adding this can cause crashes)]
    -- gtk should be installed on Linux
    links{ 
        "GL", 
        "glfw",
        "glad",
        "ImGui",
        "pthread",
        "v8_monolith",
        "yaml-cpp",
        "NativeFileDialog",
        "gtk-3",
        "glib-2.0",
        "gobject-2.0",
        "gtk-3",
        "gdk-3",
        "pangocairo-1.0",
        "gdk_pixbuf-2.0",
        "cairo",
        "pango-1.0",
        "atk-1.0",
        "gio-2.0",
        "gobject-2.0",
        "glib-2.0",
        "X11",
        "pthread",
        "dl",
    } 

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



--       --       Flare-Editor        --           --

 project "Flare-Editor" 
       location "Flare-Editor"
       kind "ConsoleApp"
       language "C++"
       staticruntime "on"
       cppdialect "c++17"
       systemversion "latest"
   
   
       targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
       objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   
       files {

           "%{prj.name}/src/**.h",
           "%{prj.name}/src/**.cpp"
       }


       includedirs {
        "Flare/vendor/spdlog/include",
        "{prj.name}/src", 
        "Flare/src", 
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}", 
        "%{IncludeDir.glad}",
        "%{IncludeDir.v8}",
        "%{IncludeDir.entt}",
        "%{IncludeDir['yaml-cpp']}", 
        "%{IncludeDir.nativefiledialog}",
        "%{IncludeDir.ImGuizmo}",
        }

        libdirs{
            "Flare/vendor/v8/x86-lib"
        }
   
       -- externalincludedirs { "../lua/include", "../zlib" }
        links{
            "Flare",
            "glfw",
            "glad",
            "ImGui",
            "png",
            "v8_monolith",
            "yaml-cpp",
            "NativeFileDialog",
            "gtk-3",
            "glib-2.0",
            "gobject-2.0",
            "gtk-3",
            "gdk-3",
            "pangocairo-1.0",
            "gdk_pixbuf-2.0",
            "cairo",
            "pango-1.0",
            "atk-1.0",
            "gio-2.0",
            "gobject-2.0",
            "glib-2.0",
            "X11",
            "pthread",
            "dl"
    }  


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


-- todo, dependencies issues
--       same dependence files are included in flare and sandbox
--       dependences like glfw glew imgui are included in flare.
--       but also included in sandbox, sandbox should link only
--       flare. no other libs.

--          --                               --           --



--         --    SANDBOX (RUN-TIME)        --      ---
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

       includedirs {
        "Flare/vendor/spdlog/include",
        "{prj.name}/src", 
        "Flare/src", 
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}", 
        "%{IncludeDir.glad}",
        "%{IncludeDir.v8}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.nativefiledialog}",
        "%{IncludeDir.ImGuizmo}",
        }

        -- externalincludedirs{
        --     "%{prj.name}/vendor/v8/x86-lib"
        -- }
        libdirs{
            "Flare/vendor/v8/x86-lib"
        }
   
       -- externalincludedirs { "../lua/include", "../zlib" }
        links{
        "Flare",
        "glfw",
        "glad",
        "ImGui",
        "png",
        "v8_monolith",
        "NativeFileDialog",
        "gtk-3",
        "glib-2.0",
        "gobject-2.0",
        "gtk-3",
        "gdk-3",
        "pangocairo-1.0",
        "gdk_pixbuf-2.0",
        "cairo",
        "pango-1.0",
        "atk-1.0",
        "gio-2.0",
        "gobject-2.0",
        "glib-2.0",
        "X11",
        "pthread",
        "dl"
    }  

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


-- todo, dependencies issues
--       same dependence files are included in flare and sandbox
--       dependences like glfw glew imgui are included in flare.
--       but also included in sandbox, sandbox should link only
--       flare. no other libs.
