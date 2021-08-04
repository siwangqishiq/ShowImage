#include "ShowImage.h"
#include <iostream>

ShowImage::ShowImage(App *context){
    mContext = context;
}

void ShowImage::init(){
    std::string vertexSrc = GLSL( 
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aCoord;

        uniform mat4 orthMatrix;

        out vec2 vCoord;

        void main(){
            vCoord = aCoord;
            gl_Position = orthMatrix * vec4(aPos, 0.0, 1.0);
        }
    );

    std::string fragSrc = GLSL(
        precision mediump float; //

        uniform sampler2D image;

        in vec2 vCoord;

        out vec4 fragColor;
        void main(){
            // fragColor = vec4(1.0f , 0.0f , 0.0f , 1.0f);
            fragColor = vec4(texture(image , vCoord).r , 0.0 , 0.0 , 1.0);
        }
    );

    shader = Shader::buildGPUProgram(vertexSrc , fragSrc);

    glGenVertexArrays(1 , &vao);
    glGenBuffers(2 , vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER , vbo[0]);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0 , 2 , GL_FLOAT , GL_FALSE , 2 * sizeof(float) , (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER , vbo[1]);
    glBufferData(GL_ARRAY_BUFFER , sizeof(texCoords) , texCoords , GL_STATIC_DRAW);
    glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE, 2 * sizeof(float) , (void *)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void ShowImage::reloadImage(std::string path){
    if(textureId == 0){
        
    }

    TextureInfo info = mContext->loadTexture(path , true);
    textureId = info.textureId;

    int imageWidth = info.srcWidth;
    int imageHeight = info.srcHeight;

    std::cout << path << " size : " << imageWidth << " x " << imageHeight << std::endl;

    float ratio = static_cast<float>(imageWidth) / imageHeight;
    if(ratio >= 1.0f){ // width >= height
        width = mContext->screenWidth;
        height = width / ratio;

        left = 0.0f;
        top = mContext->screenHeight/2.0f + height / 2.0f;
    }else{ //width < height
        height = mContext->screenHeight;
        width = height * ratio;

        top = mContext->screenHeight;
        left = mContext->screenWidth /2.0f - width/2.0f;
    }

    // std::cout << "left = " << left << " top = " << top 
    //     << " width = " << width << " height = " << height << std::endl;

    vertices[0] = left + width;
    vertices[1] = top;

    vertices[2] = left + width;
    vertices[3] = top - height;

    vertices[4] = left;
    vertices[5] = top - height;

    vertices[6] = left;
    vertices[7] = top;

    vertices[8] = left + width;
    vertices[9] = top;

    vertices[10] = left;
    vertices[11] = top - height;

    glBindVertexArray(vao); 
    glBindBuffer(GL_ARRAY_BUFFER , vbo[0]);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_DYNAMIC_DRAW);
    glBindVertexArray(0);

    // std::cout << "textureID = " << textureId << std::endl;
    // std::cout << "width = " << info.srcWidth << " height = " << info.srcHeight << std::endl;
}

void ShowImage::renderImage(){
    shader.useShader();
    
    shader.setUniformMat4("orthMatrix", mContext->orthMatrix);

    glBindTexture(GL_TEXTURE_2D , textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);
    
    glDrawArrays(GL_TRIANGLES , 0 , 6);
    glBindVertexArray(0);
}

void ShowImage::free(){
    if(textureId > 0){
        glDeleteTextures(1 , &textureId);
        textureId = 0;
    }
 
    glDeleteVertexArrays(1 , &vao);
    glDeleteBuffers(2 , vbo);
}









