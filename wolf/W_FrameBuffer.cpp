#include "W_FrameBuffer.h"

namespace wolf
{
    FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &m_uiBuffer);
        Bind();
        CreateImage();
        CreateDepthBuffer();
        CheckFrameBuffer();
        BindDefault();
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_uiBuffer);
    }

    void FrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiBuffer);
    }

    void FrameBuffer::Write(const void *p_pData, int p_iLength)
    {
        Bind();
    }

    void FrameBuffer::setWindowSize(const glm::vec2 p_vWinSize)
    {
        this->m_iWinHeight = p_vWinSize.x;
        this->m_iWinHeight = p_vWinSize.y;
    }

    void FrameBuffer::setWindowSize(unsigned int p_iWinWidth, unsigned int p_iWinHeight)
    {
        this->m_iWinWidth = p_iWinWidth;
        this->m_iWinHeight = p_iWinHeight;
    }

    void FrameBuffer::BindDefault()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::RenderBind()
    {
        glViewport(0, 0, m_iWidth, m_iHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiBuffer);
    }

    void FrameBuffer::Blit()
    {

        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_uiBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, m_iWidth, m_iHeight,
                          0, 0, m_iWinWidth, m_iWinHeight,
                          GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                          GL_NEAREST);
        glViewport(0, 0, m_iWinWidth, m_iWinHeight);
    }

    void FrameBuffer::CreateImage()
    {
        glGenTextures(1, &m_uiImage);
        glBindTexture(GL_TEXTURE_2D, m_uiImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiImage, 0);
    }

    void FrameBuffer::CreateDepthBuffer()
    {
        glGenRenderbuffers(1, &m_uiDepthBuf);
        glBindRenderbuffer(GL_RENDERBUFFER, m_uiDepthBuf);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_iWidth, m_iHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uiDepthBuf);
    }

    void FrameBuffer::CheckFrameBuffer()
    {
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "INCOMPLETE FBO" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
}
