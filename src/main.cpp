#include "clone.hpp"
#include "objlib/object.hpp"
#include "objlib/template.hpp"
#include "scene/scene.hpp"
#include <chrono>
#include <imgui.h>
// #include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <string>
#include <string_view>

using namespace Toolbox::Object;

int main(int argc, char **argv) {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    Toolbox::Scene::SceneInstance scene("C:/Users/Kyler-Josh/Dropbox/Master_Builds/Eclipse_"
                                        "Master/files/data/scene/dolpic9.szs_ext/scene");

    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Scene loaded in " << ms_int.count() << "ms\n";

    scene.dump(std::cout);

    //IMGUI_CHECKVERSION();

    //ImGui::CreateContext();
    //ImGuiIO &io    = ImGui::GetIO();
    //io.DisplaySize = {500, 300};

    //// ImGui_ImplGlfw_InitForOpenGL();
    //// ImGui_ImplOpenGL3_Init("#version 330");

    //while (true) {
    //    static bool show_demo_window = true;
    //    // ImGui_ImplOpenGL3_NewFrame();
    //    ImGui::NewFrame();
    //    ImGui::Begin("Junior's Toolbox", &show_demo_window);
    //    ImGui::Text("Hello, world!");
    //    ImGui::End();
    //    ImGui::Render();
    //}

    //ImGui::DestroyContext();

    return 0;
}