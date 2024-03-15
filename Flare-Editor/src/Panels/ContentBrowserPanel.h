#pragma once

#include <filesystem>


namespace Flare{

    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();
        
        void OnImGuiRender();

    private:

        std::filesystem::path m_CurrentDirectory;

    };

}