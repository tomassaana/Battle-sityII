#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{


    /* Initialize the library */
    if (!glfwInit()) {      
        return -1;
        }



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set the major version of the OpenGL context to 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Set the minor version of the OpenGL context to 6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set the OpenGL profile to core, which means that deprecated features will not be available


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pwindow = glfwCreateWindow(640, 480, "BattleSity-II", nullptr, nullptr);
    if (!pwindow)
	{
		std::cout << "Failed to create GLFW window !!!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pwindow);
	// gladLoadGLLoader is a function provided by the GLAD library, which is used to load OpenGL function pointers at runtime.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD" << std::endl;
        return -1;
	}

	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl; // Print the renderer information to the console
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl; // Print the vendor information to the console 
	std::cout << "OpenGL shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; // Print the shading language version information to the console
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; // Print the OpenGL version information to the console

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color to a specific RGBA value (in this case, a shade of teal)


    /* Loop until the user closes the window ====================================================================== */
    while (!glfwWindowShouldClose(pwindow))
    {
        /* Render here */
        // openGL function to clear the color buffer, 
        // which is the buffer that holds the color values for each pixel on the screen. 
        // This is typically done at the beginning of each frame to clear the previous frame's 
        // contents and prepare for drawing the new frame.
		glClear(GL_COLOR_BUFFER_BIT);
         
        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}