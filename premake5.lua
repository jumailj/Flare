workspace "Flare"
    architecture"x64"
    toolset "gcc"
    configurations {"Debug", "Release", "Ship"}


    outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Flare" 
    location "Flare"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        runtime "Debug"
        symbols  "on"

        filter "configurations:Release"
        defines "ENGINE_DEBUG"
        runtime "Debug"
        symbols  "on"


        filter "configurations:Ship"
        defines "ENGINE_DEBUG"
        runtime "Debug"
        symbols  "on"
        