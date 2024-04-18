/** @file      gui.cpp
 *  @brief     Source file for GUI functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/27
 */
 /* Includes ---------------------------------------------------------------------------------- */
#include "gui.hpp"
#include "serialComms.hpp"

/* Private define ---------------------------------------------------------------------------- */

#define MATRIX_SIZE                     ( 8 )

/* Private typedef --------------------------------------------------------------------------- */
/* Private macro ----------------------------------------------------------------------------- */
/* Private enum ------------------------------------------------------------------------------ */
/* Private struct ---------------------------------------------------------------------------- */
/* Private variables ------------------------------------------------------------------------- */

float fDepthMatrix[MATRIX_SIZE][MATRIX_SIZE];

/* Private function prototypes --------------------------------------------------------------- */
/* Exported functions ------------------------------------------------------------------------ */


void vInitImGui(GLFWwindow** xWindow)
{
    /* Initialize GLFW */
    glfwInit();

    /* Set GLFW to use OpenGL version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a GLFW window */
    *xWindow = glfwCreateWindow(800, 600, "Betaviewer", NULL, NULL);
    if (*xWindow == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(*xWindow);

    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    /* Setup Dear ImGui context */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    /* Setup Dear ImGui style */
    ImGui::StyleColorsDark();

    /* Setup Platform/Renderer bindings */
    ImGui_ImplGlfw_InitForOpenGL(*xWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
/* ------------------------------------------------------------------------------------------- */

void vImGuiShutdown(GLFWwindow** xWindow)
{
    /* Cleanup */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(*xWindow);
    glfwTerminate();
}
/* ------------------------------------------------------------------------------------------- */

void vRenderMatrix(void)
{
    ImGui::Begin("Depth Matrix");
    for (int ucI = MATRIX_SIZE - 1; ucI >= 0; --ucI) // Start from the bottom row (0) and go upwards
    {
        for (int ucJ = MATRIX_SIZE - 1; ucJ >= 0; --ucJ)
        {
            ImGui::PushID(ucI * MATRIX_SIZE + ucJ);
            float normalizedValue = static_cast<float>(fDepthMatrix[ucI][ucJ]) / 2500.0f; // Normalize to the range [0.0, 1.0] assuming 1397 as maximum depth
            ImGui::ColorButton("", ImVec4(normalizedValue, 0.0f, 1.0f - normalizedValue, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoPicker, ImVec2(40, 40));
            ImGui::PopID();
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }
}
/* ------------------------------------------------------------------------------------------- */


// Function to render the 3D matrix
void vRender3DMatrix(void)
{

}

void vUpdateMatrix(const std::string& data) 
{
    std::stringstream ss(data);
    std::string token;

    for (int i = MATRIX_SIZE - 1; i >= 0; --i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (std::getline(ss, token, ',') && !token.empty()) {
                fDepthMatrix[i][j] = std::stof(token);
            }
            else {
                // Handle error: not enough values received
                std::cerr << "Error: Not enough values received from COM port\n";
                return;
            }
        }
    }
}
/* ------------------------------------------------------------------------------------------- */

void vMainLoop(GLFWwindow **xWindow)
{
    ePhosError_t ePhosError;
    bool boUpdateMatrix;
    std::string strReceivedData;

    while (!glfwWindowShouldClose(*xWindow))
    {
        /* Poll for events (like window resizing, keyboard/mouse input, etc.) */
        glfwPollEvents();

        /* Start the ImGui frame */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /*  Display the COM port data in a box */
        ImGui::Text("COM Port Data:");
        ImGui::Separator();
        ImGui::Text("Port Name: COM3");
        ImGui::Text("Baud Rate: 115200");

        ePhosError = eReadSerialData(&boUpdateMatrix, &strReceivedData);
        if (ePhosError != eSuccess)
        {
            ImGui::Separator();
            ImGui::Text("Error reading from COM port");
        }

        // Render the matrix
        vRenderMatrix();
        vRender3DMatrix();
        if (!boUpdateMatrix)
        {
            vUpdateMatrix(strReceivedData);
        }

        ImGui::End();

        /* Rendering */
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap buffers (double buffering) to display the rendered frame */
        glfwSwapBuffers(*xWindow);
    }
}