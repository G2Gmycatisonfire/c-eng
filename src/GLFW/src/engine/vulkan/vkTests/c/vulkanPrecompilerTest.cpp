//
// Created by Vlad on 17/08/2020.
//

#include <engineVulkanPreproc.h>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.h>
#include <iostream>

using namespace engine;

class A {
public:

    virtual void f () const {
        std::cout << "plm\n";
    }
};

class B : public A {
public:

    void f () const override {
        std::cout << "coaie\n";
    }
};

int main() {

//    VShaderCompiler compiler;
//
//    std::cout << compiler.getInputDirectoryPath() << '\n';
//    std::cout << compiler.getOutputDirectoryPath() << '\n';
//
//    compiler.setConfigurationFileJSON( std::string(__VULKAN_SHADERS_PATH__).append("/config/vkTriangleShaderComp.json") );
//    compiler.build();
//
//    for(const auto & target : compiler.getTargets()) {
//        auto vect = target.getLayoutBindings();
//
//        for ( const auto & description : vect ) {
//            std::cout << description.stageFlags << '\n'
//                << description.descriptorCount << '\n'
//                << description.descriptorType << '\n'
//                << description.binding << "\n\n\n";
//        }
//    }

    B object;

    std::vector < A * > arr;

    arr.push_back( & object );

    for ( const auto * obj : arr ) {
        dynamic_cast < const B * > ( obj )->f();
    }

    return 0;
}