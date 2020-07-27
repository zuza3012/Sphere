#include <iostream>
#define GLEW_STATIC // najpierw zainkludowac GLEW a potem GLFW!
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <math.h>
#include <typeinfo>
#include <string.h>

const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat *slice_array(GLfloat *array, int start, int end) {
    int numElements = (end - start + 1);
    int numBytes = sizeof(int) * numElements;

    GLfloat *slice = (GLfloat*)malloc(numBytes);
    memcpy(slice, array + start, numBytes);

    std::cout << "slice: " << std::endl;

      for(int i = 0; i < end; i++){
        
        std::cout << slice[i] << " ";

        if( 0 == (i+1) % 3  )
            std::cout << "\n";
        
    }
    
    std::cout << ""<< std::endl;


    return slice;
}

GLfloat* DraWCircle(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat r, GLuint number_of_triangles){
    if( 1.0f > r){
        std::cout << "Radius must be less or equal than 1\n" << "I will use default radius" << std::endl;   
        r = 1.0f;
    }

    GLuint number_of_points = number_of_triangles + 2;
    GLuint verticesSize = number_of_points * 3;
    GLfloat* vertices = new GLfloat[verticesSize];
  
    vertices[0] = x0;
    vertices[1] = y0;
    vertices[2] = z0;

    for(int i = 1; i < number_of_points; i++){
        GLfloat alpha = 2 * M_PI * i / number_of_triangles * 180 / 3.14;
        //std::cout << alpha << std::endl;
        vertices[3*i ] = x0 + r * cos(2 * M_PI * (i -1) / number_of_triangles );
        vertices[3*i + 1] = y0 + r * sin(2 * M_PI * (i - 1)/ number_of_triangles );
        vertices[3*i + 2] = z0;
        //std::cout <<  vertices[3*i + 3] << " " <<  vertices[3*i + 4] << " " <<  vertices[3*i + 5] << " kupa " << z0 << "\n";

    }
    std::cout << "s: " << sizeof(vertices) <<  std::endl;

     for(int i = 0; i < number_of_points; i++){
        //std::cout << vertices[3*i] << " " << vertices[3*i+1] << " " << vertices[3*i+2] << "\n";

    }

    /*
    GLuint size = number_of_triangles + 2;
    GLfloat* vx = new GLfloat[size-1];
    GLfloat* vy = new GLfloat[size-1];
    GLfloat* vz = new GLfloat[size-1];
    
    GLfloat** vertices = new GLfloat*[size];
    for(int i = 0; i < size; ++i)
        vertices[i] = new GLfloat[3];

    
    for(int i = 0; i < size - 1; i++){
       // GLfloat alpha = 2 * M_PI * i / number_of_triangles * 180 / 3.14;
        //std::cout << alpha << std::endl;
        vx[i] = x0 + r * cos((GLfloat) 2 * M_PI * i / number_of_triangles);
        vy[i] = y0 + r * sin((GLfloat) 2 * M_PI * i / number_of_triangles);
        vz[i] = z0;
        std::cout <<  vx[i] << " " <<  vy[i] << " " <<  vz[i] << " kupa " << z0 << "\n";

    }
    std::cout << "spr" << std::endl;
    
    for(int i = 0; i < size; i++){
        //std::cout << "i: " << i << std::endl;
        if(0 == i){
            vertices[i][0] = x0;
            vertices[i][1] = y0;
            vertices[i][2] = z0;
            std::cout << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << std::endl;
            //std::cout << "kupcia" << std::endl;
            continue;
        }
           
        vertices[i][0] = vx[i-1];
        vertices[i][1] = vy[i-1];
        vertices[i][2] = vz[i-1];

        std::cout << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << std::endl;

    }*/
    /*
    std::cout << "sizeof(vertices) " << sizeof(vertices) << "\n";
    std::cout << "sizeof(vertices[0]) " << sizeof(vertices[0]) << "\n";
    std::cout << "sizeof(vertices[0][0]) " << sizeof(vertices[0][0]) << "\n";

    int rows = sizeof vertices / sizeof(vertices[0]);

    int cols = sizeof vertices[0]/sizeof(vertices[0][0]);

    std::cout << "rows: " << rows << std::endl;
    std::cout << "cols: " << cols<< std::endl;

     for(int i = 0; i < 8; i++){
        for(int j = 0; j < 3; j++)
            std::cout << vertices[i][j] << " ";
        std::cout << "\n";
    }
    */
    
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
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f, 0.86f, 0.0f,
        -0.5f, 0.86f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -0.5f, -0.86f, 0.0f,
        0.5f, -0.86f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    std::cout << std::endl;
    std::cout << "test" << std::endl;

    for(int i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++){
        
        std::cout << vertices[i] << " ";

        if( 0 == (i+1) % 3  )
            std::cout << "\n";
        
    }

    std::cout << std::endl;
  
    GLfloat* circle =  new GLfloat[24];
    int n = 100;
    circle = DraWCircle(0,0,0,1,n);
    
    
   // GLfloat* circle_slice = slice_array(circle,0,24);

   
    
     // print
    // rows = 3;
    // cols = 8;
    /*
    std::cout << "s: " << sizeof(circle) <<  std::endl;
    for(int i = 0; i < 24; i++){
        
        std::cout << circle_slice[i] << " ";

        if( 0 == (i+1) % 3  )
            std::cout << "\n";
        
    }
    */
    
    

    //std::cout << "typeinfo test " << typeid(vertices).name() << std::endl;
    //std::cout << "typeinfo circle " << typeid(circle).name() << std::endl;

      // vertex buffer - przechowuje veterxy
    GLuint VBO, VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO); // generowanie id do buffora
    
    

    // najpierw bind VAO, potem bind bind buffer + set attrib pointer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    size_t vertex_size = sizeof(GLfloat) * n * 3 * 3;
    glBufferData(GL_ARRAY_BUFFER,(GLsizeiptr)vertex_size, circle, GL_DYNAMIC_DRAW); // dodoajemy dane do bufora

    
    // mowimy openGL jak interpretowac dane
    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, /*3 * sizeof(GLfloat)*/ 0,(GLvoid *) 0);
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
        glDrawArrays(GL_TRIANGLE_FAN,0, n+2);
        
        //glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circle) / sizeof(GLfloat));
         
        glBindVertexArray(0);

        
        
        glfwSwapBuffers(window); // zamienia color buffery
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0;

}