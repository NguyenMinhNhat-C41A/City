#include "flats.h"

Flats::Flats()
{
}

Flats::~Flats()
{
    this->vertices.clear();

    this->texIndices.clear();

    for (auto texture : this->textures)
    {
        wolf::TextureManager::DestroyTexture(texture);
    }
    this->textures.clear();

    delete this->m_pDecl;
    this->m_pDecl = nullptr;
    wolf::ProgramManager::DestroyProgram(this->m_pProgram);
    this->m_pProgram = nullptr;
    wolf::BufferManager::DestroyBuffer(this->m_pVB);
    this->m_pVB = nullptr;
}

void Flats::update(const float dt)
{
}

void Flats::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{
    if (!this->isConstructingVertices)
    {
        glm::mat4 mWorld = glm::mat4(1.0f);
        this->m_pProgram->SetUniform("projection_view", mProj * mView);
        this->m_pProgram->SetUniform("world", mWorld);
        this->m_pProgram->SetUniform("tex", 0);
        this->m_pProgram->Bind();
        this->m_pDecl->Bind();
        for (int i = 0; i < this->textures.size(); i++)
        {
            this->textures.at(i)->Bind(0);
            glDrawArrays(GL_TRIANGLES, this->texIndices.at(i), this->texIndices.at(i + 1) - this->texIndices.at(i));
        }
    }
}

void Flats::addTexture(const std::string tex, const int mapIndex)
{
    if (this->isConstructingVertices)
    {
        this->textures.push_back(wolf::TextureManager::CreateTexture("data/textures/" + tex));
        this->textures.at(this->textures.size() - 1)->SetFilterMode(wolf::Texture::FM_NearestMipmap);
        this->textures.at(this->textures.size() - 1)->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);
        if (this->texIndices.size() <= 0)
        {
            this->texIndices.push_back(mapIndex);
        }
        else if (this->texIndices.at(this->texIndices.size() - 1) != mapIndex)
        {
            this->texIndices.push_back(mapIndex);
        }
        else
        {
            std::cout << "Not added tex: " << tex << std::endl;
        }
    }
}

void Flats::addFlat(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes)
{
    if (this->isConstructingVertices)
    {
        const float w = static_cast<float>(width / 2.0f);
        const float h = static_cast<float>(height / 2.0f);

        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), coords);
        glm::mat4 mRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axes);
        glm::vec4 pos = glm::vec4(1.0f);

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, height});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

        glm::vec3 vecX =
            glm::vec3(this->vertices.at(this->vertices.size() - 1).x, this->vertices.at(this->vertices.size() - 1).y, this->vertices.at(this->vertices.size() - 1).z) - glm::vec3(this->vertices.at(this->vertices.size() - 2).x, this->vertices.at(this->vertices.size() - 2).y, this->vertices.at(this->vertices.size() - 2).z);

        glm::vec3 vecY =
            glm::vec3(this->vertices.at(this->vertices.size() - 3).x, this->vertices.at(this->vertices.size() - 3).y, this->vertices.at(this->vertices.size() - 3).z) - glm::vec3(this->vertices.at(this->vertices.size() - 2).x, this->vertices.at(this->vertices.size() - 2).y, this->vertices.at(this->vertices.size() - 2).z);

        glm::vec3 normal = glm::normalize(glm::cross(vecX, vecY));
    }
};

void Flats::addFlat(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles)
{
    if (this->isConstructingVertices)
    {
        const float w = static_cast<float>(width / 2.0f);
        const float h = static_cast<float>(height / 2.0f);

        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), coords);
        glm::mat4 mRotate = glm::mat4(1.0f);
        mRotate = glm::rotate(mRotate, glm::radians(angles.x), glm::vec3(1.0f, 0.0f, 0.0f));
        mRotate = glm::rotate(mRotate, glm::radians(angles.y), glm::vec3(0.0f, 1.0f, 0.0f));
        mRotate = glm::rotate(mRotate, glm::radians(angles.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::vec4 pos = glm::vec4(1.0f);

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, height});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

        glm::vec3 vecX =
            glm::vec3(this->vertices.at(this->vertices.size() - 1).x, this->vertices.at(this->vertices.size() - 1).y, this->vertices.at(this->vertices.size() - 1).z) - glm::vec3(this->vertices.at(this->vertices.size() - 2).x, this->vertices.at(this->vertices.size() - 2).y, this->vertices.at(this->vertices.size() - 2).z);

        glm::vec3 vecY =
            glm::vec3(this->vertices.at(this->vertices.size() - 3).x, this->vertices.at(this->vertices.size() - 3).y, this->vertices.at(this->vertices.size() - 3).z) - glm::vec3(this->vertices.at(this->vertices.size() - 2).x, this->vertices.at(this->vertices.size() - 2).y, this->vertices.at(this->vertices.size() - 2).z);

        glm::vec3 normal = glm::normalize(glm::cross(vecX, vecY));
    }
};

void Flats::addHalfFlat(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles, const int norm)
{
    if (this->isConstructingVertices)
    {
        const float w = static_cast<float>(width / 2.0f);
        const float h = static_cast<float>(height / 2.0f);

        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), coords);
        glm::mat4 mRotate = glm::mat4(1.0f);
        mRotate = glm::rotate(mRotate, glm::radians(angles.x), glm::vec3(1.0f, 0.0f, 0.0f));
        mRotate = glm::rotate(mRotate, glm::radians(angles.y), glm::vec3(0.0f, 1.0f, 0.0f));
        mRotate = glm::rotate(mRotate, glm::radians(angles.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::vec4 pos = glm::vec4(1.0f);

        if (norm == 1)
        {
            pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
            this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

            pos = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
            this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});

            pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
            this->vertices.push_back({pos.x, pos.y, pos.z, width, height});
        }

        else
        {
            pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
            this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

            pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
            this->vertices.push_back({pos.x, pos.y, pos.z, width, height});

            pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
            this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});
        }
        glm::vec3 vecX =
            glm::vec3(this->vertices.at(this->vertices.size() - 1).x, this->vertices.at(this->vertices.size() - 1).y, this->vertices.at(this->vertices.size() - 1).z) - glm::vec3(this->vertices.at(this->vertices.size() - 2).x, this->vertices.at(this->vertices.size() - 2).y, this->vertices.at(this->vertices.size() - 2).z);

        glm::vec3 vecY =
            glm::vec3(this->vertices.at(this->vertices.size() - 3).x, this->vertices.at(this->vertices.size() - 3).y, this->vertices.at(this->vertices.size() - 3).z) - glm::vec3(this->vertices.at(this->vertices.size() - 2).x, this->vertices.at(this->vertices.size() - 2).y, this->vertices.at(this->vertices.size() - 2).z);

        glm::vec3 normal = glm::vec3(1.0f);

        normal = glm::normalize(glm::cross(vecX, vecY));
    }
}

void Flats::addFlatTextureFit(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes)
{
    if (this->isConstructingVertices)
    {
        const float w = static_cast<float>(width / 2.0f);
        const float h = static_cast<float>(height / 2.0f);

        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), coords);
        glm::mat4 mRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axes);
        glm::vec4 pos = glm::vec4(1.0f);

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 1.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 1.0f, 1.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 1.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 1.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 1.0f});
    }
};

void Flats::addFlatTextureFitHeight(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes)
{
    if (this->isConstructingVertices)
    {
        const float w = static_cast<float>(width / 2.0f);
        const float h = static_cast<float>(height / 2.0f);

        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), coords);
        glm::mat4 mRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axes);
        glm::vec4 pos = glm::vec4(1.0f);

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 1.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 1.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, width, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 1.0f});
    }
};

void Flats::addFlatTextureFitWidth(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes)
{
    if (this->isConstructingVertices)
    {
        const float w = static_cast<float>(width / 2.0f);
        const float h = static_cast<float>(height / 2.0f);

        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), coords);
        glm::mat4 mRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axes);
        glm::vec4 pos = glm::vec4(1.0f);

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 1.0f, height});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 1.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 1.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, 0.0f});

        pos = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        this->vertices.push_back({pos.x, pos.y, pos.z, 0.0f, height});
    }
};

void Flats::endInit()
{
    this->texIndices.push_back(this->vertices.size());
    if (!this->m_pProgram)
    {
        this->m_pProgram = wolf::ProgramManager::CreateProgram("data/cityscape.vsh", "data/cityscape_transparent.fsh");
        this->m_pVB = wolf::BufferManager::CreateVertexBuffer(this->vertices.data(), sizeof(Vertex) * this->vertices.size());

        this->m_pDecl = new wolf::VertexDeclaration();
        this->m_pDecl->Begin();
        this->m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        this->m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        this->m_pDecl->SetVertexBuffer(m_pVB);
        this->m_pDecl->End();
    }
}

void Flats::endInitialisation()
{
    this->texIndices.push_back(this->vertices.size());
    if (!this->m_pProgram)
    {
        this->m_pProgram = wolf::ProgramManager::CreateProgram("data/cityscape.vsh", "data/cityscape_transparent.fsh");
        this->m_pVB = wolf::BufferManager::CreateVertexBuffer(this->vertices.data(), sizeof(Vertex) * this->vertices.size());

        this->m_pDecl = new wolf::VertexDeclaration();
        this->m_pDecl->Begin();
        this->m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        this->m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        this->m_pDecl->SetVertexBuffer(m_pVB);
        this->m_pDecl->End();
    }
}

void Flats::beginConstructingVertices()
{
    this->isConstructingVertices = true;
}

void Flats::endConstructingVertices()
{
    this->isConstructingVertices = false;
}