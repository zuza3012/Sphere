#include <iostream>
#define GLEW_STATIC // najpierw zainkludowac GLEW a potem GLFW!
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <math.h>

const GLuint WIDTH = 800, HEIGHT = 600;



GLfloat * DraWCircle(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat r, GLuint number_of_triangles){

    GLuint number_of_points = number_of_triangles + 2;
    GLuint verticesSize = number_of_points * 3;
    GLfloat* vertices = new GLfloat[verticesSize]();
    vertices[0] = x0;
    vertices[1] = y0;
    vertices[2] = z0;

    for(int i = 0; i < number_of_points - 1; i++){
        GLfloat alpha = 2 * M_PI * i / number_of_triangles * 180 / 3.14;
        //std::cout << alpha << std::endl;
        vertices[3*i + 3] = x0 + r * cos(2 * M_PI * i  / number_of_triangles );
        vertices[3*i + 4] = y0 + r * sin(2 * M_PI * i/ number_of_triangles );
        vertices[3*i + 5] = z0;
        std::cout <<  vertices[3*i + 3] << " " <<  vertices[3*i + 4] << " " <<  vertices[3*i + 5] << " kupa " << z0 << "\n";

    }

     for(int i = 0; i < number_of_points; i++){
        std::cout << vertices[3*i] << " " << vertices[3*i+1] << " " << vertices[3*i+2] << "\n";

    }

    return vertices;
}

std::string ReadTextFile(std::string& filepath){
    std::string text;
    std::ifstream fileStream(filepath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Error while opening a file " << filepath << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        text.append(line + "\n");
    }

    fileStream.close();

    return text;
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char *argv[]){
    if(!glfwInit()) 
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow * window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Someday you will see spheres", NULL, NULL);

    if(!window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(5);
    glfwSetKeyCallback(window, key_callback);

    if(glewInit() != GLEW_OK)
        std::cout << "Failed to initialize GLEW!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    glewExperimental = GL_TRUE;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height); 
    glViewport(0,0, width, height);// lewy dolny rog
    
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string shader_path = getenv("PWD");
    std::string vertex_rel_path = "/../res/shaders/vertex.glsl";
    std::string fragment_rel_path = "/../res/shaders/fragment.glsl";
    std::string vertexPath = shader_path + vertex_rel_path;
    std::string fragmentPath = shader_path + fragment_rel_path;
    
    std::string vertexSource = ReadTextFile(vertexPath);
    std::string fragmentSource = ReadTextFile(fragmentPath);

    const char *v_str = vertexSource.c_str();
    const char *f_str = fragmentSource.c_str();
    
    glShaderSource(vertexShader, 1, &v_str, NULL);
    glCompileShader(vertexShader);

    // check compilation of vertex shader
    GLint sucess;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &sucess);

    if(!sucess){
        glGetShaderInfoLog(vertexShader,512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

    }
    // fragment shader

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &f_str, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &sucess);

    // check compilation of fragment shader
    if(!sucess){
        glGetShaderInfoLog(fragmentShader,512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

    }
    // shader program, linking
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&sucess);
    if(!sucess){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    
    glDeleteShader(vertexShader); // niepotrzebne po zalinkowaniu
    glDeleteShader(fragmentShader); // niepotrzebne po zalinkowaniu
    
     
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    GLfloat* circle = DraWCircle(0,0,0,3,6);
  
      // vertex buffer - przechowuje veterxy
    GLuint VBO, VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO); // generowanie id do buffora
    
    

    // najpierw bind VAO, potem bind bind buffer + set attrib pointer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW); // dodoajemy dane do bufora


    // mowimy openGL jak interpretowac dane
    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat),(GLvoid *) 0);
                                // 0 - location = 0 dla position
                                // 3 bo vec3
                                // typ
                                // normalizacja
                                // stride (ilosc rzeczy w 1 "dawce danych" * sizeof)
                                // offset 

    glEnableVertexAttribArray(0); 
    

    glBindBuffer(GL_ARRAY_BUFFER, 0);// unbind buffer
    glBindVertexArray(0); // unbing vao
    
    
    
/*
    for(int i = 0; i < 7; i++){
        std::cout << arr[3*i] << " " << arr[3*i+1] << " " << arr[3*i+2] << "\n";

    }
  */ 


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
       
        // clear color buffer
        glClearColor(0.2f, 0.3f, 0.6f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);// wyczysc kolor buffer

         // draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circle) / sizeof(GLfloat));
         
        glBindVertexArray(0);

        
        
        glfwSwapBuffers(window); // zamienia color buffery
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0;

}