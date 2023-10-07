#pragma once
#include <filesystem>

#include "Bento/Renderer/Texture.h"

namespace Bento {

	class ContentBrowserPanel {

	public:
		ContentBrowserPanel();

		void OnImGuiRender();

	private:
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_FolderIcon;
		Ref<Texture2D> m_FileIcon;
	};

}