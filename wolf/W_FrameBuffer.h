#ifndef W_FRAMEBUFFER_H
#define W_FRAMEBUFFER_H

#include "W_Types.h"
#include "W_Buffer.h"
#include <iostream>

namespace wolf
{
    class FrameBuffer : public Buffer
    {
        friend class BufferManager;

    public:
        virtual void Bind();
        virtual void Write(const void *p_pData, int p_iLength = -1);

        void setWindowSize(const glm::vec2 p_vWinSize);
        void setWindowSize(unsigned int p_iWinWidth, unsigned int p_iWinHeight);

        void BindDefault();
        // Disabled glViewport() in W_App.cpp
        void RenderBind();
        void Blit();

    private:
        FrameBuffer();
        ~FrameBuffer();

        void CreateImage();
        void CreateDepthBuffer();
        void CheckFrameBuffer();

        GLuint m_uiBuffer;
        GLuint m_uiImage;
        GLuint m_uiDepthBuf;

        unsigned int m_iWinWidth = 1280;
        unsigned int m_iWinHeight = 720;
        // int m_iWidth = 1280;
        // int m_iHeight = 720;
        int m_iWidth = 320;
        int m_iHeight = 180;
    };
}

#endif