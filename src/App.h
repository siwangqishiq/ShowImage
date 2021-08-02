#pragma once

#include "Shader.h"
#include <memory>
#include "glm/ext/matrix_clip_space.hpp"

struct TextureInfo{
	int srcWidth;
	int srcHeight;
	int channel;
	GLuint textureId;
	unsigned char *data;
};

class ShowImage;

class App{
private:
    std::string mPath;
public:
    App(std::string path): mPath(path){
        orthMatrix = glm::ortho(0.0f , static_cast<float>(screenWidth) , 0.0f , static_cast<float>(screenHeight));
    }

    int screenWidth = 1280;
    int screenHeight = 800;

    std::shared_ptr<ShowImage> showImage;

    virtual void init();

    virtual void tick();

    virtual void free();

    TextureInfo loadTexture(std::string path , bool releaseData);

    glm::mat4 orthMatrix;//正交视图 投影矩阵
};







