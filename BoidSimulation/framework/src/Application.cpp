// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Application.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Application.h"
#include "Utilities.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../imgui/include/imgui.h"
#include "../imgui/include/imgui_impl_glfw_gl3.h"


/// <summary>
/// Creates the specified a name.
/// </summary>
/// <param name="a_name">a name.</param>
/// <param name="a_width">a width.</param>
/// <param name="a_height">a height.</param>
/// <param name="a_bFullscreen">a b fullscreen.</param>
/// <returns>bool.</returns>
bool Application::create(const char* a_name, int a_width, int a_height, bool a_bFullscreen)
{
	// initialise glfw systems
	if (glfwInit() != GL_TRUE)
	{
		std::cout << "Unable to initialize GLFW" << std::endl;
		return false;
	}
	
	// create a windowed mode window and its OpenGL context
	m_window = glfwCreateWindow(a_width, a_height, a_name, ( a_bFullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Unable to create a GLFW Window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });
	

	int major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
	int minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
	int revision = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_REVISION);
	std::cout << "OpenGL Version " << major << "." << minor << "." << revision << std::endl;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfwGL3_Init(m_window, true);
	ImGui::StyleColorsDark();

	// initialise glew systems to wrangle GL extensions
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}

	bool result = onCreate();
	if (result == false)
	{
		glfwTerminate();
	}
	return result;
}

/// <summary>
/// Runs the specified a name.
/// </summary>
/// <param name="a_name">a name.</param>
/// <param name="a_width">a width.</param>
/// <param name="a_height">a height.</param>
/// <param name="a_bFullscreen">a b fullscreen.</param>
void Application::run(const char* a_name, int a_width, int a_height, bool a_bFullscreen)
{
	if (create(a_name, a_width, a_height, a_bFullscreen))
	{
		Utility::resetTimer();
		m_running = true;
		do
		{
			float deltaTime = Utility::tickTimer();
			ImGui_ImplGlfwGL3_NewFrame();

			Update(deltaTime);

			Draw();

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(m_window);
			glfwPollEvents();

		} while (m_running == true && glfwWindowShouldClose(m_window) == 0);

		Destroy();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}