#pragma once

//System includes
#include <vector>

//GLM includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Engine includes
#include <RenderComponent.h>

using namespace Xylena;

class FlowerRenderComponent: public RenderComponent {
    
private:
    static FlowerRenderComponent *component;
    ComponentUID uid;
    
    VBO renderVBO;
    EBO renderEBO;
    VBO positionsVBO;
    
    ShaderUniform mvpUniform;
    
    glm::mat4 ortho;
    
    ShaderProgram program;
    
    std::vector<glm::vec4> instanceData;
    
    void initRenderer();
    
    glm::mat4 calculateMatrix(float x, float y, float rotation, float size);
    
public:
    
    FlowerRenderComponent();
    
    void bind();
    void unbind();
    
    void preRender();
    void render(GameObject *gameObject);
    
    ComponentUID getComponentUID() { return uid; }
    
    static FlowerRenderComponent* getComponent();
};
