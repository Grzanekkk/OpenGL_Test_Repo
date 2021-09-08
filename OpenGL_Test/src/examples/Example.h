#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace example
{
	class Example
	{
	public:
		Example() {}
		virtual ~Example() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Example
	{
	public:
		TestMenu(Example*& currentTestPointer);
		virtual void OnImGuiRender();

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test" << name << std::endl;

			m_Test.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Example*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Example*()>>> m_Test;
	};
}
