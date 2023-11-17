project "GLAD" 
    kind "StaticLib"
    language "C"
    staticruntime "on"
    warnings "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "src/glad.c"
	}

	defines
	{
			"_GLFW_X11"
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
        
