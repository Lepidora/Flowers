#include "FlowerRenderComponent.h"

//GLM includes
#include "glm/gtx/string_cast.hpp"

//Engine includes
#include <OpenGL.h>
#include <Render.h>
#include <StageCamera.h>
#include <StageHandler.h>
#include <ShaderHandler.h>
#include <WindowHandler.h>
#include <FileHandler.h>

//Shader includes
#include <DefaultShaders.h>

//Local includes
#include "FlowerSpawner.h"

FlowerRenderComponent *FlowerRenderComponent::component = nullptr;

FlowerRenderComponent::FlowerRenderComponent() {
    
    uid = ComponentHandler::generateUID(this);
    initRenderer();
    
}

const float textureVertices[] {
    //  X      Y     Z       U      V
    -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
    1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,   1.0f, 1.0f
};

GLuint arrayElements[] = {
    0, 1, 2,
    2, 3, 0
};

void FlowerRenderComponent::initRenderer() {
    
    VAO textureArrayID;
    glGenVertexArrays(1, &textureArrayID);
    glBindVertexArray(textureArrayID);
    
    std::string flowerVert = FileHandler::readTextFile("flower.vert");
    std::string flowerFrag = FileHandler::readTextFile("flower.frag");
    
    ShaderProgram textureProgram = ShaderHandler::compileProgram("texture", flowerVert.c_str(), flowerFrag.c_str());
    glUseProgram(textureProgram);
    
    VBO vertexBufferID;
    EBO elementArrayID;
    
    glGenBuffers(1, &elementArrayID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayID);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrayElements), arrayElements, GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);
    
    ShaderAttribute worldPositionAttribute = ShaderHandler::getAttribute(textureProgram, "worldspacePosition");
    
    glVertexAttribPointer(worldPositionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, NULL);
    glEnableVertexAttribArray(worldPositionAttribute);
    
    ShaderAttribute vertexUV = ShaderHandler::getAttribute(textureProgram, "vertexUV");
    
    glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 5, (const GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(vertexUV);
    
    VBO dataBuffer;
    
    glGenBuffers(1, &dataBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
    
    ShaderAttribute dataAttribute = ShaderHandler::getAttribute(textureProgram, "data");
    
    glVertexAttribPointer(dataAttribute, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
    
    glEnableVertexAttribArray(dataAttribute);
    
    glVertexAttribDivisor(dataAttribute, 1);
    
    positionsVBO = dataBuffer;
    
    ShaderUniform mvpMatrix = ShaderHandler::getUniform(textureProgram, "mvp");
    
    mvpUniform = mvpMatrix;
    
    ShaderUniform textureSampler = ShaderHandler::getUniform(textureProgram, "textureSampler");
    glUniform1i(textureSampler, 0);
    
    glBindVertexArray(0);
    
    renderVBO = vertexBufferID;
    renderVAO = textureArrayID;
    renderEBO = elementArrayID;
    program = textureProgram;
    
    printf("Shader errors\n");
    
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        printf("GL error code: %d\n", err);
    }
    
}

void FlowerRenderComponent::bind() {
    glBindVertexArray(renderVAO);
}

void FlowerRenderComponent::unbind() {
    glBindVertexArray(NULL);
}

void FlowerRenderComponent::preRender() {
    
    Coordinate windowSize = WindowHandler::getMainWindow()->getWindowSize();
    StageCameraPtr camera = StageHandler::getCurrentStage()->getActiveCamera();
    
    Coordinate viewport = camera->getViewportSize();
    float scalingFactor = camera->getScalingFactor();
    
    float viewportX = viewport.getX();
    float viewportY = viewport.getY();
    
    ortho = glm::ortho(0.0f, viewportX * scalingFactor, 0.0f, viewportY * scalingFactor, -1.0f, 1.0f);
}

void FlowerRenderComponent::render(GameObject *gameObject) {
    
    FlowerSpawner *spawner = dynamic_cast<FlowerSpawner *>(gameObject);
    
    if (!spawner) {
        printf("Cannot cast object to spawner, skipping render\n");
        return;
    } else {
        //printf("Rendering\n");
        //return;
    }
    
    std::vector<Flower> flowers = spawner->getFlowers();
    
    int flowerCount = flowers.size();
    
    if (instanceData.size() != flowerCount) {
        instanceData.clear();
        instanceData.resize(flowerCount);
    }
    
    StageCameraPtr stageCamera = StageHandler::getCurrentStage()->getActiveCamera();
    
    float scalingFactor = stageCamera->getScalingFactor();
    
    TexturePtr objectTexture;
    
    for (int i = 0; i < flowerCount; i++) {
        
        Flower flower = flowers[i];
        
        TexturePtr texture = flower.texture;
        objectTexture = texture;
        
        int index = flower.index;
        
        float x = flower.x;
        float y = flower.y;
        
        float xOffset = flower.xOffset;
        float yOffset = flower.yOffset;
        
        float rotation = flower.angle;
        
        float size = flower.size;
        
        glm::vec4 data = glm::vec4((x + xOffset) / scalingFactor, (y + yOffset) / scalingFactor, (float)index, 0);
        
        instanceData[i] = data;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * instanceData.size(), &instanceData[0], GL_DYNAMIC_DRAW);
    
    bind();
    
    glm::mat4 spriteMatrix;
    
    spriteMatrix = spriteMatrix * ortho;
    
    spriteMatrix = glm::scale(spriteMatrix, glm::vec3(24.0f, 24.0f, 1.0f));
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(spriteMatrix));
    
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_2D, objectTexture->getNextTexture());
    
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instanceData.size());
}

glm::mat4 FlowerRenderComponent::calculateMatrix(float x, float y, float rotation, float size) {
    
    glm::mat4 spriteMatrix;
    
    spriteMatrix = spriteMatrix * ortho;
    
    spriteMatrix = glm::translate(spriteMatrix, glm::vec3(x, y, 0.0));
    
    spriteMatrix = glm::scale(spriteMatrix, glm::vec3(size/2, size/2, 1.0f));
    
    return spriteMatrix;
}

FlowerRenderComponent * FlowerRenderComponent::getComponent() {

    if (!component) {
        component = new FlowerRenderComponent();
    }
    
    return component;
}
