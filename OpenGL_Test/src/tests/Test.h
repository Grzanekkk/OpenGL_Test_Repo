#pragma once

#include <functional>
#include <vector>
#include <string>

namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu
	{
	public:
		TestMenu(Test*& currentTestPointer);
		virtual void OnImGuiRender();

	private:
		Test* m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Test;
	};
}