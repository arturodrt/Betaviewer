/** @file      BetaViewer.c
 *  @brief     Beta Viewer Entry Point.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/22
 */

/* Includes ---------------------------------------------------------------------------------- */
#include "gui.hpp"
/* Private define ---------------------------------------------------------------------------- */
/* Define matrix size */
/* Private typedef --------------------------------------------------------------------------- */
/* Private macro ----------------------------------------------------------------------------- */
/* Private enum ------------------------------------------------------------------------------ */
/* Private struct ---------------------------------------------------------------------------- */
/* Private variables ------------------------------------------------------------------------- */
/* Serial port handle */
/* Matrix to store depth values */

/* Private function prototypes --------------------------------------------------------------- */

int main() 
{
    GLFWwindow *xWindow = NULL;

    vInitImGui(&xWindow);

    if (!openCOMPort()) {
        vImGuiShutdown(&xWindow);
        return 1;
    }

    /* Main loop */
    vMainLoop(&xWindow);

    vImGuiShutdown(&xWindow);

    return 0;
}
/* ------------------------------------------------------------------------------------------- */
