#include "App.h"
#include "ShowImage.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void App::init(){
    showImage = std::make_shared<ShowImage>(this);
    showImage->init();
    showImage->reloadImage(mPath);
}

void App::tick(){
    glClearColor(1.0f , 1.0f , 1.0f ,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    showImage->renderImage();
}

void App::free(){
    showImage->free();
}

TextureInfo App::loadTexture(std::string path , bool releaseData){
    TextureInfo info;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *imageData = nullptr;

    imageData = stbi_load(path.c_str() , &info.srcWidth , &info.srcHeight , 
            &info.channel , 0);
    
    if(imageData){
        info.data = imageData;
    }else{
        std::cout << "load texture " << path << " failed!" << std::endl;
        return info;
    }

    GLint format;
    std::cout << "channel = " << info.channel << std::endl;
    if(info.channel == 3){//3通道
        format = GL_RGB;
    }else if(info.channel == 4){ //4通道 
        format = GL_RGBA;
    }

    glGenTextures(1 , &info.textureId);

    glBindTexture(GL_TEXTURE_2D , info.textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D , 0 , format , info.srcWidth , info.srcHeight ,0 , 
        format, GL_UNSIGNED_BYTE , info.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D , 0);

    if(releaseData){
        stbi_image_free(imageData);
    }

    
    return info;
}







