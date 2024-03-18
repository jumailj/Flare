#include "ContentBrowserPanel.h"

#include <imgui.h>

#include <codecvt>
#include <filesystem>
#include <string>
#include <locale>

#include <Flare/Core/Log.h>


namespace Flare{

    // once we have projects, change this

    extern const std::filesystem::path g_AssetPath = "Resource";

    ContentBrowserPanel::ContentBrowserPanel()
    : m_CurrentDirectory(g_AssetPath)
    {
        m_DirectoryIcon = Texture2D::Create("Resource/icons/ContentBrowser/DirectoryIcon.png");                               
        m_FileIcon = Texture2D::Create("Resource/icons/ContentBrowser/FileIcon.png");

    }

    void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path(g_AssetPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 32.0f;
		static float thumbnailSize = 46.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, g_AssetPath);
			std::string filenameString = relativePath.filename().string();
			
			ImGui::PushID(filenameString.c_str());
			Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
				std::wstring widePath = converter.from_bytes(relativePath.string());

				const wchar_t* itemPath = widePath.c_str();
				
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();

				// LOG_TRACE(" wide path = {0}", (const char*)itemPath);
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
					m_CurrentDirectory /= path.filename();

			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();

		}

		ImGui::Columns(1);

		// ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		// ImGui::SliderFloat("Padding", &padding, 0, 32);

		// TODO: status bar
		
		ImGui::End();
	}

}