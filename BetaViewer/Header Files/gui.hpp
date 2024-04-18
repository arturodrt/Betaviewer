/** @file      gui.hpp
 *  @brief     Header file for GUI functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/27
 */

 /* Header guard ------------------------------------------------------------------------------ */
#ifndef GUI_H_
#define GUI_H_
/* Includes ---------------------------------------------------------------------------------- */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "phoslibs.hpp"
#include "serialComms.hpp"

/* Define ------------------------------------------------------------------------------------ */
/* Exported Macro ---------------------------------------------------------------------------- */
/* Exported types ---------------------------------------------------------------------------- */
/* Exported enums ---------------------------------------------------------------------------- */
/* Exported struct --------------------------------------------------------------------------- */
/* Global variables -------------------------------------------------------------------------- */
/* Exported function prototypes -------------------------------------------------------------- */


/**
 * @brief Initializes ImGui for rendering on a GLFW window.
 *
 * This function initializes ImGui for rendering on a GLFW window. It creates a GLFW
 * window with the specified dimensions and title, sets up OpenGL, initializes ImGui
 * context, and configures platform/renderer bindings for ImGui.
 *
 * @param[in,out] xWindow: Double pointer to a GLFWwindow object.
 *                         Upon successful execution, this pointer will be updated
 *                         to point to the newly created GLFW window.
 */
void vInitImGui(GLFWwindow **xWindow);

/**
 * @brief Shuts down ImGui and GLFW, cleaning up resources.
 *
 * This function shuts down ImGui and GLFW, cleaning up any resources allocated
 * during initialization. It destroys the ImGui context, releases platform/renderer
 * bindings, and destroys the GLFW window. Finally, it terminates GLFW.
 *
 * @param[in] xWindow: A double pointer to a GLFWwindow object.
 *                     The function expects the pointer to point to a valid GLFW window
 *                     created previously. Upon successful execution, the window pointer
 *                     will be set to NULL.
 */
void vImGuiShutdown(GLFWwindow **xWindow);


/**
 * @brief Renders the depth matrix using ImGui.
 *
 * This function displays the depth matrix as a grid of color buttons using ImGui.
 * Each button represents a depth value, with colors indicating the normalized depth value.
 * 
 */
void vRenderMatrix(void);

/**
 * @brief Updates the depth matrix with the provided data.
 *
 * This function parses the provided string data and updates the depth matrix
 * with the parsed values. The data is assumed to be in CSV (comma-separated values) format,
 * where each value represents the depth at a specific matrix position.
 *
 * @param data A string containing the data to update the depth matrix.
 *             The data is expected to be in CSV format with MATRIX_SIZE*MATRIX_SIZE values.
 *
 */
void vUpdateMatrix(const std::string& data);

/**
 * @brief Main loop of the application.
 *
 * This function contains the main loop of the application, which continuously
 * polls for events, updates the user interface, and renders frames until the
 * GLFW window is flagged for closure.
 *
 * @param xWindow Pointer to the GLFW window handle.
 *
 */
void vMainLoop(GLFWwindow **xWindow);


void vRender3DMatrix(void);

#endif /* GUI_H_ */
