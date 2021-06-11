#include "ConfigWindow.h"
#include "Renderer.h"
#include "imgui.h"

#include <iostream>

namespace CVE {
	ConfigWindow::ConfigWindow(Renderer* renderer) : renderer(renderer) {

	}

	void ConfigWindow::draw() {
		ImGui::Begin("Performance");

		ImGui::Text("Frame time: %f s", renderer->frameTime);
		ImGui::Text("FPS: %f", 1.0f / renderer->frameTime);
		
        drawFrameTimePlot();

		ImGui::End();



		ImGui::Begin("Settings");

		ImGui::Text("MSAA: %d", renderer->msaaSamples);
		ImGui::Text("Total vertex buffer memory: %d", renderer->totalVertexBufferMemoryNeeded);
		ImGui::Text("Total index buffer memory: %d", renderer->totalIndexBufferMemoryNeeded);
		ImGui::SliderInt("Number of instances", &renderer->numInstances, 0, 50000);

		ImGui::End();

		ImGui::ShowDemoWindow();
	}

    void ConfigWindow::drawFrameTimePlot() {
        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static float refresh_time = 0.0;
        static float maxValue = 0.01;
        if (renderer->frameTime > maxValue) maxValue = renderer->frameTime;
        if (refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
        {
            values[values_offset] = renderer->frameTime;
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, 0.0f, maxValue + 0.01f, ImVec2(0, 80.0f));
        }
    }
}