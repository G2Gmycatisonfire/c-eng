//
// Created by vladl on 05/08/2020.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb-image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <vkTests/obj/VulkanTriangleApplication.h>


using namespace engine;

int main() {
    VulkanTriangleApplication app(1024, 768);

    try{
        app.addValidationLayer( VValidationLayer::KHRONOS_VALIDATION );
        app.run();
    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}