#pragma once

namespace CVE {
	class Renderer;

	class ConfigWindow {
	public:
		ConfigWindow(Renderer* renderer);

		void draw();

		Renderer* renderer;
	};
}