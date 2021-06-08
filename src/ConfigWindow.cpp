#include "ConfigWindow.h"
#include "Renderer.h"
#include "imgui.h"

#include <iostream>

namespace CVE {
	ConfigWindow::ConfigWindow(Renderer* renderer) : renderer(renderer) {

	}

	void ConfigWindow::draw() {
		ImGui::Begin("Settings");

		ImGui::Text("MSAA: %d", renderer->msaaSamples);
		ImGui::SliderInt("Number of instances", &renderer->numInstances, 0, 50000);

		ImGui::End();

		//ImGui::ShowDemoWindow();
	}
}