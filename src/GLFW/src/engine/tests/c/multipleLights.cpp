//
// Created by vladl on 12/07/2020.
//
#define __DEF_MATERIALS
#define __POINT_LIGHT_SAMPLES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <obj/util/shader/Shader.h>
#include <cmath>
#include <obj/util/diag/Diagnostic.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb-image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <src/GLFW/src/engine/obj/util/obj/stdObj/Camera.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;


float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f , 0.0f, 1.0f, 0.0f,  1.0f,  0.0f
};

float lightVertices[] = {
        -0.5f, -0.5f, -0.5f, // 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, // 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,//  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,//  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  //1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, // 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, // 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f //, 0.0f, 1.0f
};

bool flashlightOn = false;
bool globalLight = false;

struct cube {
    glm::vec3 pos;
    SMaterial material;
};

glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

struct SPointLight {
    glm::vec3 position;
    bool toggle;
};

SPointLight pointLights[] = {
        {glm::vec3( 0.7f,  0.2f,  2.0f), false},
        {glm::vec3( 2.3f, -3.3f, -4.0f), false},
        {glm::vec3(-4.0f,  2.0f, -12.0f), false},
        {glm::vec3( 0.0f,  0.0f, -3.0f), false}
};

glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
};

unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
};

bool firstMouseCallback = true;

unsigned int elementBufferObject;
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

unsigned int lightVAO;
unsigned int lightVBO;
unsigned int lightEBO;

float interpolationVisibility = 0.2f;

uint32 texture1;
uint32 texture2;

engine::Shader *shader;
engine::Shader *lightShader;
engine::Camera *camera;

glm::mat4 matInverse(const glm::mat4&);
glm::mat3 matInverse(const glm::mat3&);

void mouseCallback(GLFWwindow*, double, double);
void mouseButtonCallback(GLFWwindow*, int, int, int);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods);
void render() noexcept;
void update() noexcept;
void prepareVBO();
void deleteShaders();

void linkVertexAttributes();
void linkElementBufferObject();

void checkShaderProgramCompileErrors(unsigned int shaderProgramID);
void checkShaderCompileErrors(unsigned int shaderID);

int imageWidth;
int imageHeight;
int numberOfChannels;
uint8* data;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);

    if(window == nullptr) {
        std::cout << "init window fail\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(! gladLoadGLLoader((GLADloadproc) glfwGetProcAddress )) {
        std::cout << "glad init fail\n";
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetErrorCallback( (GLFWerrorfun) engine::Diagnostic::getErrorCallbackDiagFunc);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processInputCallback);

    glEnable(GL_DEPTH_TEST);

    prepareVBO();

    camera = new engine::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    engine::Shader::setShadersFolder(__SHADERS_PATH__);

    shader = new engine::Shader(
            "/triangle.vert",
            "/triangle.frag",
            true,
            true
    );

    lightShader = new engine::Shader(
            "/light.vert",
            "/light.frag",
            true,
            true
    );

    linkElementBufferObject();
    linkVertexAttributes();
    // 0.1 mb 300k nr 0 < x < 1 m. sort
    // char v[125000] v[x/8] = 1 << (x % 8) ;
    glGenTextures(1, &texture1);

    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // repeat width
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // repeat height

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //bi-linear filter for minimizing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //bi-linear filter for magnifying

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load( (std::string(__TEXTURES_PATH__) + "container2.png").c_str(), &imageWidth, &imageHeight, &numberOfChannels, 0 );
//
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Image load failed" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);

    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load( (std::string(__TEXTURES_PATH__) + "container2_specular.png" ).c_str(), &imageWidth, &imageHeight, &numberOfChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Image load failed" << std::endl;
    }
    stbi_image_free(data);

    shader->use();
//    shader->setInt("texture1", 0);
//    shader->setInt("texture2", 1);

    int frameCounter = 0;
    int second = 1;

    while( !glfwWindowShouldClose(window) ) {
        frameCounter++;

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if(currentFrame > second) {
            std::cout << frameCounter << '\n';
            second++;

            frameCounter = 0;
        }

//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete camera;

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);

    glDeleteProgram(shaderProgram);

    int nrAttrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttrib);

    delete shader;
    delete lightShader;

//    std::cout << nrAttrib << '\n';

    glfwTerminate();

    return 0;
}

void linkElementBufferObject(){
    glGenBuffers(1, &elementBufferObject);
    glGenBuffers(1, &lightEBO);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"

/**
 * glVertexAttribPointer( vertexAttribNumber, size of vertexAttribute, vertexAttrib data type, normalizeData, stride, offset );
 *
 * vertexAttribNumber = which input for the shader program (inputs in shaders) => vertex shader compiled uses location = 0, hence param is 0
 * sizeof vertexAttribute = how many values represent one input val. Vector 3 => 3
 * data type = ...
 * normalizeData = if integer data type, can normalize to 0 for U and -1 for S data. otherwise, false
 * stride = space between consecutive data objects. 3 vectors of 3 coords, packed => 3 * sizeof datatype for jump
 * offset = where does the first param sit from the ptr.
 */
void linkVertexAttributes() {
    glGenVertexArrays(1, &vertexArrayObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

}

#pragma clang diagnostic pop

glm::vec3 forwardMovementVec;

bool up = false;
bool down = false;
bool left = false;
bool right = false;

float ratio = 800.0f / 600.0f;
float fov=60.0f;
void update() noexcept {
    constexpr float movementSpeed = 2.5f;
    float velocity = movementSpeed * deltaTime;

    float origY = camera->getTransform().getLocation().y;

//    glm::vec3 front = camera->getFront();

    if(up && down) {

        //use worldFront, not front for no flying
    } else if (up) {
        camera->getTransform().getLocation() += camera->getWorldFront() * velocity;
//        camera->getTransform().getLocation() += camera->getFront() * velocity;
    } else if (down) {
        camera->getTransform().getLocation() -= camera->getWorldFront() * velocity;
//        camera->getTransform().getLocation() -= camera->getFront() * velocity;
    }

    if(left && right) {

    } else if(left) {
        camera->getTransform().getLocation() -= camera->getRight() * velocity;
    } else if(right) {
        camera->getTransform().getLocation() += camera->getRight() * velocity;
    }


    camera->getTransform().getLocation().y = origY;
}

constexpr float lightScaleConst = 0.1f;

glm::vec3 lightLoc = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightScale = glm::vec3(lightScaleConst, lightScaleConst, lightScaleConst);

inline void render() noexcept {
    int var = 0;
    shader->use();

    glm::mat4 view = camera->getViewMatrix();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);

    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setVec3("viewPosition", camera->getTransform().getLocation());
    shader->setFloat("material.shine", 32);

    SLight lightData = getLightStructByID(4);

    shader->setBool("directionalLight.toggle", globalLight);
    if(globalLight) {
        shader->setVec3("directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader->setVec3("directionalLight.ambient", glm::vec3(0.05f));
        shader->setVec3("directionalLight.diffuse", glm::vec3(0.4f));
        shader->setVec3("directionalLight.specular", glm::vec3(0.5f));
    }

    glm::vec3 pointLightAmbient(0.05f);
    glm::vec3 pointLightDiffuse(0.8f);
    glm::vec3 pointLightSpecular(1.0f);

    for(int i = 0; i < 4; i++) {
        std::string pointLightArrElementName = "pointLights[" + std::to_string(i) + "]";

        shader->setBool(pointLightArrElementName + ".toggle", pointLights[i].toggle);

        if (pointLights[i].toggle) {
            shader->setVec3(pointLightArrElementName + ".position", pointLights[i].position);
            shader->setVec3(pointLightArrElementName + ".ambient", pointLightAmbient);
            shader->setVec3(pointLightArrElementName + ".diffuse", pointLightDiffuse);
            shader->setVec3(pointLightArrElementName + ".specular", pointLightSpecular);

            shader->setFloat(pointLightArrElementName + ".constant", lightData.constant);
            shader->setFloat(pointLightArrElementName + ".linear", lightData.linear);
            shader->setFloat(pointLightArrElementName + ".quadratic", lightData.quadratic);
        }
    }

    shader->setBool("spotLight.toggle", flashlightOn);

    if(flashlightOn) {
        shader->setVec3("spotLight.position", camera->getTransform().getLocation());
        shader->setVec3("spotLight.direction", camera->getFront());
        shader->setVec3("spotLight.ambient", glm::vec3(0.0f));
        shader->setVec3("spotLight.diffuse", glm::vec3(1.0f));
        shader->setVec3("spotLight.specular", glm::vec3(1.0f));

        shader->setFloat("spotLight.constant", lightData.constant);
        shader->setFloat("spotLight.linear", lightData.linear);
        shader->setFloat("spotLight.quadratic", lightData.quadratic);

        shader->setFloat("spotLight.cutoff", glm::cos(glm::radians(12.5f)));
        shader->setFloat("spotLight.outerCutoff", glm::cos(glm::radians(15.0f)));
    }

    shader->setInt("material.diffuse", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    shader->setInt("material.specular", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(vertexArrayObject);

    int i;

    for(auto & cube : cubePositions) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cube);

        float angle = 20.0f * (float) (i++);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        shader->setMat4("TIModel", glm::transpose(glm::inverse(model)));
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    lightShader->use();
    lightShader->setMat4("view", view);
    lightShader->setMat4("projection", projection);

    double angleIncreaseConst = 40.0f;
    double offset = glfwGetTime() * angleIncreaseConst;
//    std::cout << sin(glm::radians(offset)) << '\n';

    for(auto & lightCube : pointLights) {
        lightCube.position = glm::vec3(lightCube.position.x + cos(glm::radians(offset)) * ( 1.5 * deltaTime ),                     lightCube.position.y, lightCube.position.z);
        if( lightCube.toggle ) {
            glm::mat4 lightModel = glm::scale(glm::translate(glm::mat4(1.0f), lightCube.position), glm::vec3(0.1f, 0.1f, 0.1f));
            lightShader->setMat4("model", lightModel);

            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

void deleteShaders() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


/**
 * glBindBuffer 4'th param :
 *  GL_STATIC_DRAW = data set only once, used a lot
 *  GL_DYNAMIC_DRAW = data set and used a lot
 *  GL_STREAM_DRAW = data set only once and used a few times
 */
void prepareVBO() {
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &lightVBO);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport ( 0, 0, width, height );
}

void processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if( action == GLFW_PRESS ) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }

        if( key == GLFW_KEY_W )
            up = true;
        if( key == GLFW_KEY_S )
            down = true;
        if( key == GLFW_KEY_A )
            left = true;
        if( key == GLFW_KEY_D )
            right = true;

        if( key == GLFW_KEY_1 )
            pointLights[0].toggle = !pointLights[0].toggle;
        if( key == GLFW_KEY_2 )
            pointLights[1].toggle = !pointLights[1].toggle;
        if( key == GLFW_KEY_3 )
            pointLights[2].toggle = !pointLights[2].toggle;
        if( key == GLFW_KEY_4 )
            pointLights[3].toggle = !pointLights[3].toggle;
        if( key == GLFW_KEY_5 )
            globalLight = !globalLight;
    } else if ( action == GLFW_RELEASE ) {

        if( key == GLFW_KEY_W )
            up = false;
        if( key == GLFW_KEY_S )
            down = false;
        if( key == GLFW_KEY_A )
            left = false;
        if( key == GLFW_KEY_D )
            right = false;
    }
}

float lastX;
float lastY;

void mouseCallback(GLFWwindow* window, double xPos, double yPos){
    if (firstMouseCallback){
        lastX = (float) xPos;
        lastY = (float) yPos;
        firstMouseCallback = false;
    }
//
    auto xPosF = (float) xPos;
    auto yPosF = (float) yPos;
//
    float xOffset = xPosF - lastX;
    float yOffset = lastY - yPosF;
    lastX = xPosF;
    lastY = yPosF;
//
    constexpr float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camera->processOrientation(xOffset, yOffset, true);
}

bool allLightsToggle = false;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if( action == GLFW_PRESS ) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
            flashlightOn = !flashlightOn;

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            allLightsToggle = !allLightsToggle;
            for( int i = 0; i < 4; i++ )
                pointLights[i].toggle = allLightsToggle;
        }
    }
//    if( action == GLFW_RELEASE )
//        if( button == GLFW_MOUSE_BUTTON_RIGHT )
//            flashlightOn = false;
}