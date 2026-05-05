#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	// gladLoadGLLoader is a function provided by the GLAD library, which is used to load OpenGL function pointers at runtime.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD" << std::endl;
        return -1;
	}
	std::cout << "OpenGL version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color to a specific RGBA value (in this case, a shade of teal)


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // openGL function to clear the color buffer, 
        // which is the buffer that holds the color values for each pixel on the screen. 
        // This is typically done at the beginning of each frame to clear the previous frame's 
        // contents and prepare for drawing the new frame.
		glClear(GL_COLOR_BUFFER_BIT);
         
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}