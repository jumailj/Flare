project "Flare-ScriptCore" 
    location "../Flare-ScriptCore"
    kind "SharedLib"
    language "C#"
    dotnetframework "4.0"

    targetdir ("../Resource/Scripts")
	objdir ("../Resource/Scripts/Intermediate")

    --pchheader "Flare/stdafx.h"
    --pchsource "Flare/stdafx.cpp"

    files {

        "Source/**.cs",
        "Properties/**.cs",
    }


    filter "configurations:Debug"
       optimize "Off"
       symbols  "Default"

   filter "configurations:Release"
       optimize "On"
       symbols  "Default"


   filter "configurations:Ship"
       optimize "Full"
       symbols  "off"


