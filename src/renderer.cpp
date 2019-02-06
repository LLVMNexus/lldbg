#include "renderer.hpp"

#include <stdio.h>
#include "imgui.h"
#include "examples/imgui_impl_freeglut.h"
#include "examples/imgui_impl_opengl2.h"
#include <GL/freeglut.h>

namespace lldbg {

void my_display_code()
{
    static float f = 0.0f;
    static int counter = 0;

    //TODO: update this with a callback instead of grab every frame
    const int window_width = glutGet(GLUT_WINDOW_WIDTH);
    const int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    ImGui::SetNextWindowPos(ImVec2(0.f,0.f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(window_width, window_height), ImGuiSetCond_Always);
    // Create a window called "Hello, world!" and append into it.
    ImGui::Begin("Hello, world!", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    static int selected = 0;
    ImGui::BeginChild("left pane", ImVec2(300, 0), true);
    for (int i = 0; i < 100; i++)
    {
        char label[128];
        sprintf(label, "MyObject %d", i);
        if (ImGui::Selectable(label, selected == i))
            selected = i;
    }
    ImGui::EndChild();
    ImGui::SameLine();

    // right
    ImGui::BeginGroup();

    ImGui::BeginChild("item view", ImVec2(window_width - 600, 600)); // Leave room for 1 line below us
    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("main.cpp"))
        {

            const char* t = "#include <stdio.h>\n"
                            "int main( int argc, const char* argv[] )\n"
                            "{\n"
                            "    int sum = 0;\n"
                            "    for(int i = 0; i < 10; i++)\n"
                            "    {\n"
                            "    	sum += i;\n"
                            "    }\n"
                            "}\n";

            ImGui::TextWrapped(t);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("lib.h"))
        {
            ImGui::Text("ID: 0123456789");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();

    // right
    ImGui::BeginChild("log view", ImVec2(window_width - 600, 0)); // Leave room for 1 line below us
    if (ImGui::BeginTabBar("##Tabsasdf", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Console"))
        {
            ImGui::TextWrapped("Console History");
            ImGui::TextWrapped("Console History");
            ImGui::TextWrapped("Console History");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Log"))
        {
            ImGui::TextWrapped("Log Message");
            ImGui::TextWrapped("Log Message");
            ImGui::TextWrapped("Log Message");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();

    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();

    ImGui::BeginChild("right pane", ImVec2(0, 0), true);
    if (ImGui::BeginTabBar("##Tabs2", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Threads"))
        {
            for (int i = 0; i < 4; i++)
            {
                char label[128];
                sprintf(label, "Thread %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    if (ImGui::BeginTabBar("##Tabs3", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Stack Trace"))
        {
            for (int i = 0; i < 8; i++)
            {
                char label[128];
                sprintf(label, "Func %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    if (ImGui::BeginTabBar("##Tabs11", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Locals"))
        {
            for (int i = 0; i < 4; i++)
            {
                char label[128];
                sprintf(label, "Local %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Registers"))
        {
            for (int i = 0; i < 4; i++)
            {
                char label[128];
                sprintf(label, "Registers %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    if (ImGui::BeginTabBar("##Tabs5", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Watchpoints"))
        {
            for (int i = 0; i < 4; i++)
            {
                char label[128];
                sprintf(label, "Watch %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Breakpoints"))
        {
            for (int i = 0; i < 4; i++)
            {
                char label[128];
                sprintf(label, "Break %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChild();
    ImGui::SameLine();

    ImGui::EndGroup();

    ImGui::End();
}

void glut_display_func()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplFreeGLUT_NewFrame();

    my_display_code();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    // glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
    glutPostRedisplay();
}


void initialize_renderer(int argc, char** argv) {
    // Create GLUT window
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Dear ImGui FreeGLUT+OpenGL2 Example");

    // std::cout << "window width: " << glutGet(GLUT_WINDOW_WIDTH) << std::endl;
    // std::cout << "window height: " << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;

    // Setup GLUT display function
    // We will also call ImGui_ImplFreeGLUT_InstallFuncs() to get all the other functions installed for us,
    // otherwise it is possible to install our own functions and call the imgui_impl_freeglut.h functions ourselves.
    glutDisplayFunc(glut_display_func);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // disable all rounding
    ImGui::GetStyle().WindowRounding = 0.0f;// <- Set this on init or use ImGui::PushStyleVar()
    ImGui::GetStyle().ChildRounding = 0.0f;
    ImGui::GetStyle().FrameRounding = 0.0f;
    ImGui::GetStyle().GrabRounding = 0.0f;
    ImGui::GetStyle().PopupRounding = 0.0f;
    ImGui::GetStyle().ScrollbarRounding = 0.0f;
    ImGui::GetStyle().TabRounding = 0.0f;

    // Setup Platform/Renderer bindings
    ImGui_ImplFreeGLUT_Init();
    ImGui_ImplFreeGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();
}

void destroy_renderer(void) {
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplFreeGLUT_Shutdown();
    ImGui::DestroyContext();
}

}
