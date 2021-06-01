#include <Renderer.h>

int main() {
    CVE::Renderer renderer;

    try {
        renderer.init(1920, 1080);
        renderer.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
