#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include"renderer/ShaderProgram.h"
#include"renderer/Texture2D.h"
#include"resources/ResourceManager.h"




GLfloat points[] = {
      0.0,  0.5f, 0.0f, 
      0.5f,-0.5f, 0.0f, 
     -0.5f,-0.5f, 0.0f  
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 1.0f 
};

GLfloat texCoords[] = {
    0.5f, 1.0f, 
    1.0f, 0.0f, 
    0.0f, 0.0f
};


int gWindowWidth = 640  ;
int gWindowHeight = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int sizeX  , int sizeY)
{
	gWindowWidth = sizeX;// Update the global variable gWindowWidth with the new width of the window
	gWindowHeight = sizeY;// Update the global variable gWindowHeight with the new height of the window
    // Set the viewport to cover the new window dimensions, ensuring that the rendered content scales appropriately with the window size
	glViewport(0, 0, sizeX, sizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) // Check if the Escape key was pressed
        glfwSetWindowShouldClose(pWindow, true); // Set the window's should-close flag to true, which will cause the main loop to exit and the window to close
}



//==========================================================
int main(int argc, char** argv)
{

	/* Initialize the library */
    if (!glfwInit()) {      
		std::cout << "Failed to initialize GLFW !!!" << std::endl;
        return -1;
     }


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set the major version of the OpenGL context to 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Set the minor version of the OpenGL context to 6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set the OpenGL profile to core, which means that deprecated features will not be available

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pwindow = glfwCreateWindow(gWindowWidth, gWindowHeight, "BattleSity-II", nullptr, nullptr);
    if (!pwindow)
	{
		std::cout << "Failed to create GLFW window !!!" << std::endl;
        glfwTerminate();
        return -1;
    }

        // Set the window size callback to handle window resizing
         glfwSetWindowSizeCallback(pwindow, glfwWindowSizeCallback);
		 glfwSetKeyCallback(pwindow, glfwKeyCallback); // Set the key callback to handle keyboard input  


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

    
    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Failed to load default shader  !!! program !!!" << "DefaultShader" << std::endl;
            return -1;
        }


		auto tex =resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");


        GLuint points_vbo = 0; 
        glGenBuffers(1, &points_vbo); 
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_vbo = 0; 
        glGenBuffers(1, &colors_vbo); 
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); 

        GLuint texCords_vbo = 0;
        glGenBuffers(1, &texCords_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCords_vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);


        GLuint vao = 0; 
        glGenVertexArrays(1, &vao); 
        glBindVertexArray(vao); 

        glEnableVertexAttribArray(0); 
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1); 
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCords_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("tex", 0); 


        /* Loop until the user closes the window ====================================================================== */
        while (!glfwWindowShouldClose(pwindow))
        {
            /* Render here */
            // openGL function to clear the color buffer, 
            // which is the buffer that holds the color values for each pixel on the screen. 
            // This is typically done at the beginning of each frame to clear the previous frame's 
            // contents and prepare for drawing the new frame.
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao); 
			tex->bind();

            glDrawArrays(GL_TRIANGLES, 0, 3); // Issue a draw call to render the vertices as triangles, starting from the first vertex (index 0) and drawing a total of 3 vertices (which form one triangle)


            /* Swap front and back buffers */
            glfwSwapBuffers(pwindow);



            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}