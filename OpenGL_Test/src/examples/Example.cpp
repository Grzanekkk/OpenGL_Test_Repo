#include "Example.h"
#include "imgui/imgui.h"

namespace example
{

	TestMenu::TestMenu(Example*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Test)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}
