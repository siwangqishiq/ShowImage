#pragma once

#include <memory>
#include "Shader.h"
#include "App.h"

class ShowImage{
private:
    std::string imagePath;

    App *mContext;

    float left = 0.0f;
    float top = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    float texCoords[6 * 2] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f
    };
    
    float vertices[6 * 2] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f
    };

    Shader shader;

    unsigned int vao;
    unsigned int vbo[2];

    unsigned int textureId = 0;

public:
    ShowImage(App *context);

    void init();

    void reloadImage(std::string path);

    void renderImage();

    void free();
};








