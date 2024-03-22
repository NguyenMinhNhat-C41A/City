#include "Polys.h"

Polys::Polys()
{
}

Polys::~Polys()
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

void Polys::update(const float dt)
{
}

void Polys::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{
    if (!this->isConstructingVertices)
    {
        glm::mat4 mWorld = glm::mat4(1.0f);
        this->m_pProgram->SetUniform("projection_view", mProj * mView);
        this->m_pProgram->SetUniform("world", mWorld);
        this->m_pProgram->SetUniform("worldIT", glm::transpose(glm::inverse(mWorld)));
        this->m_pProgram->SetUniform("tex", 0);
        this->m_pProgram->SetUniform("u_diffuseLightDirection", glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));
        this->m_pProgram->SetUniform("u_diffuseLightColour", glm::vec3(0.25f, 0.25f, 0.25f));
        this->m_pProgram->Bind();
        this->m_pDecl->Bind();
        for (int i = 0; i < this->textures.size(); i++)
        {
            this->textures.at(i)->Bind(0);
            glDrawArrays(GL_TRIANGLES, this->texIndices.at(i), this->texIndices.at(i + 1) - this->texIndices.at(i));
        }
    }
}

void Polys::render(const glm::mat4 &mProj, const glm::mat4 &mView, const glm::vec3 &lightDiffDir, const glm::vec3 &lightDiffCol, const glm::vec3 &lightAmbCol)
{
    if (!this->isConstructingVertices)
    {
        glm::mat4 mWorld = glm::mat4(1.0f);
        this->m_pProgram->SetUniform("projection_view", mProj * mView);
        this->m_pProgram->SetUniform("world", mWorld);
        this->m_pProgram->SetUniform("worldIT", glm::transpose(glm::inverse(mWorld)));
        this->m_pProgram->SetUniform("tex", 0);
        this->m_pProgram->SetUniform("u_diffuseLightDirection", glm::normalize(glm::vec3(lightDiffDir)));
        this->m_pProgram->SetUniform("u_diffuseLightColour", glm::vec3(lightDiffCol));
        this->m_pProgram->SetUniform("u_ambientLightColour", glm::vec3(lightAmbCol));
        this->m_pProgram->Bind();
        this->m_pDecl->Bind();
        for (int i = 0; i < this->textures.size(); i++)
        {
            this->textures.at(i)->Bind(0);
            glDrawArrays(GL_TRIANGLES, this->texIndices.at(i), this->texIndices.at(i + 1) - this->texIndices.at(i));
        }
    }
}

void Polys::render(const glm::mat4 &mProj, const glm::mat4 &mView, Lighting *lighting)
{
    if (!this->isConstructingVertices)
    {
        glm::mat4 mWorld = glm::mat4(1.0f);
        this->m_pProgram->SetUniform("projection_view", mProj * mView);
        this->m_pProgram->SetUniform("world", mWorld);
        this->m_pProgram->SetUniform("worldIT", glm::transpose(glm::inverse(mWorld)));
        this->m_pProgram->SetUniform("tex", 0);
        this->m_pProgram->SetUniform("u_diffuseLightDirection", lighting->getDiffuseLightDirection());
        this->m_pProgram->SetUniform("u_diffuseLightColour", lighting->getDiffuseLightColour());
        this->m_pProgram->SetUniform("u_ambientLightColour", lighting->getAmbientLightColour());
        for (int i = 0; i < lighting->getPointLightCount(); i++)
        {
            this->m_pProgram->SetUniform("u_pointLightPosRange" + std::to_string(i + 1), glm::vec4(lighting->getPointLightPositions().at(i), lighting->getPointLightRanges().at(i)));
            this->m_pProgram->SetUniform("u_pointLightColour" + std::to_string(i + 1), lighting->getPointLightColours().at(i));
            this->m_pProgram->SetUniform("u_pointLightAttenuation" + std::to_string(i + 1), lighting->getPointLightAttenuations().at(i));
            this->m_pProgram->SetUniform("u_pointLightAmbient" + std::to_string(i + 1), lighting->getPointLightAmbients().at(i));
        }
        this->m_pProgram->Bind();
        this->m_pDecl->Bind();

        glClearColor(0.3f, 0.3f, 0.3f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < this->textures.size(); i++)
        {
            this->textures.at(i)->Bind(0);
            glDrawArrays(GL_TRIANGLES, this->texIndices.at(i), this->texIndices.at(i + 1) - this->texIndices.at(i));
        }
    }
}

void Polys::endInitialisation()
{
    this->texIndices.push_back(this->vertices.size());
    if (!this->m_pProgram)
    {
        this->m_pProgram = wolf::ProgramManager::CreateProgram("data/city.vsh", "data/city.fsh");
        this->m_pVB = wolf::BufferManager::CreateVertexBuffer(this->vertices.data(), sizeof(PolyVertex) * this->vertices.size());
        this->m_pDecl = new wolf::VertexDeclaration();
        this->m_pDecl->Begin();
        this->m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        this->m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        this->m_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
        this->m_pDecl->SetVertexBuffer(m_pVB);
        this->m_pDecl->End();
    }
}

void Polys::addTexture(const std::string tex, const int mapIndex)
{
    if (this->isConstructingVertices)
    {
        this->textures.push_back(wolf::TextureManager::CreateTexture("data/textures/" + tex));
        this->textures.at(this->textures.size() - 1)->SetFilterMode(wolf::Texture::FM_Nearest);
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

void Polys::addPoly04(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles)
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

        glm::vec4 pos1 = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
        glm::vec4 pos2 = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
        glm::vec4 pos3 = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        glm::vec4 pos4 = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
        glm::vec4 pos5 = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
        glm::vec4 pos6 = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);

        glm::vec3 vecX = glm::vec3(pos6.x, pos6.y, pos6.z) - glm::vec3(pos5.x, pos5.y, pos5.z);
        glm::vec3 vecY = glm::vec3(pos4.x, pos4.y, pos4.z) - glm::vec3(pos5.x, pos5.y, pos5.z);
        glm::vec3 normal = glm::normalize(glm::cross(vecX, vecY));
        // std::cout << "poly 04 normal - x: " << normal.x << "; y: " << normal.y << "; z: " << normal.z << std::endl;

        PolyVertex v1 = {pos1.x, pos1.y, pos1.z, 0.0f, height, normal.x, normal.y, normal.z};
        PolyVertex v2 = {pos2.x, pos2.y, pos2.z, width, height, normal.x, normal.y, normal.z};
        PolyVertex v3 = {pos3.x, pos3.y, pos3.z, width, 0.0f, normal.x, normal.y, normal.z};
        PolyVertex v4 = {pos4.x, pos4.y, pos4.z, width, 0.0f, normal.x, normal.y, normal.z};
        PolyVertex v5 = {pos5.x, pos5.y, pos5.z, 0.0f, 0.0f, normal.x, normal.y, normal.z};
        PolyVertex v6 = {pos6.x, pos6.y, pos6.z, 0.0f, height, normal.x, normal.y, normal.z};

        this->vertices.push_back(v1);
        this->vertices.push_back(v2);
        this->vertices.push_back(v3);
        this->vertices.push_back(v4);
        this->vertices.push_back(v5);
        this->vertices.push_back(v6);
    }
};

void Polys::addPoly03(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles, const int normSide, const int slantSide)
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

        glm::vec4 pos1 = glm::vec4(1.0f);
        glm::vec4 pos2 = glm::vec4(1.0f);
        glm::vec4 pos3 = glm::vec4(1.0f);

        glm::vec3 vecX = glm::vec3(1.0f);
        glm::vec3 vecY = glm::vec3(1.0f);
        glm::vec3 normal = glm::vec3(1.0f);

        if (slantSide == 1)
        {
            if (normSide == 1)
            {
                pos1 = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
                pos2 = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
                pos3 = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);

                vecY = glm::vec3(pos1.x, pos1.y, pos1.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                vecX = glm::vec3(pos3.x, pos3.y, pos3.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                normal = glm::normalize(glm::cross(vecX, vecY));
                // std::cout << "poly 03C1 normal - x: " << normal.x << "; y: " << normal.y << "; z: " << normal.z << std::endl;

                PolyVertex v1 = {pos1.x, pos1.y, pos1.z, 0.0f, height, normal.x, normal.y, normal.z};
                PolyVertex v2 = {pos2.x, pos2.y, pos2.z, width, height, normal.x, normal.y, normal.z};
                PolyVertex v3 = {pos3.x, pos3.y, pos3.z, 0.0f, 0.0f, normal.x, normal.y, normal.z};

                this->vertices.push_back(v1);
                this->vertices.push_back(v2);
                this->vertices.push_back(v3);
            }

            else
            {
                pos1 = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
                pos2 = mTranslate * mRotate * glm::vec4(0.0f, h, -w, 1.0f);
                pos3 = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);

                vecY = glm::vec3(pos1.x, pos1.y, pos1.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                vecX = glm::vec3(pos3.x, pos3.y, pos3.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                normal = glm::normalize(glm::cross(vecX, vecY));
                // std::cout << "poly 03C2 normal - x: " << normal.x << "; y: " << normal.y << "; z: " << normal.z << std::endl;

                PolyVertex v1 = {pos1.x, pos1.y, pos1.z, 0.0f, height, normal.x, normal.y, normal.z};
                PolyVertex v2 = {pos2.x, pos2.y, pos2.z, width, height, normal.x, normal.y, normal.z};
                PolyVertex v3 = {pos3.x, pos3.y, pos3.z, 0.0f, 0.0f, normal.x, normal.y, normal.z};

                this->vertices.push_back(v1);
                this->vertices.push_back(v2);
                this->vertices.push_back(v3);
            }
        }

        else
        {
            if (normSide == 1)
            {
                pos1 = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
                pos2 = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);
                pos3 = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);

                vecY = glm::vec3(pos1.x, pos1.y, pos1.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                vecX = glm::vec3(pos3.x, pos3.y, pos3.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                normal = glm::normalize(glm::cross(vecX, vecY));
                // std::cout << "poly 03C3 normal - x: " << normal.x << "; y: " << normal.y << "; z: " << normal.z << std::endl;

                PolyVertex v1 = {pos1.x, pos1.y, pos1.z, 0.0f, height, normal.x, normal.y, normal.z};
                PolyVertex v2 = {pos2.x, pos2.y, pos2.z, width, height, normal.x, normal.y, normal.z};
                PolyVertex v3 = {pos3.x, pos3.y, pos3.z, width, 0.0f, normal.x, normal.y, normal.z};

                this->vertices.push_back(v1);
                this->vertices.push_back(v2);
                this->vertices.push_back(v3);
            }
            else
            {
                pos1 = mTranslate * mRotate * glm::vec4(0.0f, -h, -w, 1.0f);
                pos2 = mTranslate * mRotate * glm::vec4(0.0f, h, w, 1.0f);
                pos3 = mTranslate * mRotate * glm::vec4(0.0f, -h, w, 1.0f);

                vecY = glm::vec3(pos1.x, pos1.y, pos1.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                vecX = glm::vec3(pos3.x, pos3.y, pos3.z) - glm::vec3(pos2.x, pos2.y, pos2.z);
                normal = glm::normalize(glm::cross(vecX, vecY));
                // std::cout << "poly 03C4 normal - x: " << normal.x << "; y: " << normal.y << "; z: " << normal.z << std::endl;

                PolyVertex v1 = {pos1.x, pos1.y, pos1.z, 0.0f, height, normal.x, normal.y, normal.z};
                PolyVertex v2 = {pos2.x, pos2.y, pos2.z, width, 0.0f, normal.x, normal.y, normal.z};
                PolyVertex v3 = {pos3.x, pos3.y, pos3.z, width, height, normal.x, normal.y, normal.z};

                this->vertices.push_back(v1);
                this->vertices.push_back(v2);
                this->vertices.push_back(v3);
            }
        }
    }
}

void Polys::beginConstructingVertices()
{
    this->isConstructingVertices = true;
}

void Polys::endConstructingVertices()
{
    this->isConstructingVertices = false;
}