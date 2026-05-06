#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include"renderer/ShaderProgram.h"
#include"renderer/Texture2D.h"
#include"resources/ResourceManager.h"
#include<glm/vec2.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>






GLfloat points[] = {
      0.0,  50.f, 0.0f, 
      50.f,-50.f, 0.0f, 
     -50.f,-50.f, 0.0f  
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

glm::vec2 gWSize(640.f, 480.f); 

//int gWindowWidth = 640.f  ;
//int gWindowHeight = 480.f;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int sizeX  , int sizeY)
{
    gWSize.x = sizeX;// Update the global variable gWindowWidth with the new width of the window
    gWSize.y = sizeY;// Update the global variable gWindowHeight with the new height of the window
    // Set the viewport to cover the new window dimensions, ensuring that the rendered content scales appropriately with the window size
	glViewport(0, 0, gWSize.x, gWSize.y);
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
    GLFWwindow* pwindow = glfwCreateWindow(gWSize.x, gWSize.y, "BattleSity-II", nullptr, nullptr);
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


		auto tex =resourceManager.loadTexture("DefaultTexture", "res/textures/new_atlas_128x128.png");


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

		glm::mat4 modeMatrix_1 = glm::mat4(1.f); 
		modeMatrix_1 = glm::translate(modeMatrix_1, glm::vec3(100.f, 50.f, 0.f));

        glm::mat4 modeMatrix_2 = glm::mat4(1.f);
        modeMatrix_2 = glm::translate(modeMatrix_2, glm::vec3(590.f, 50.f, 0.f));

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(gWSize.x), 0.f, static_cast<float>(gWSize.y), -100.f, 100.f);

		pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);



        /* Loop until the user closes the window ====================================================================== */
        while (!glfwWindowShouldClose(pwindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao); 
			tex->bind();

			pDefaultShaderProgram->setMatrix4("modelMat", modeMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3); 

            pDefaultShaderProgram->setMatrix4("modelMat", modeMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);



            /* Swap front and back buffers */
            glfwSwapBuffers(pwindow);



            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}