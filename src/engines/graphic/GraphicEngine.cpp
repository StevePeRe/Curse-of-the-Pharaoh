#include <GLAD/src/glad.h>
#include <GLFW/glfw3.h>
#include <engines/graphic/GraphicEngine.hpp>
#include <engines/graphic/TNodeTree.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/src/imgui.h>
#include <imgui/src/imgui_impl_glfw.h>
#include <imgui/src/imgui_impl_opengl3.h>
#include <iostream>

GraphicEngine::GraphicEngine(std::string windowName, unsigned int width, unsigned int heigth, bool fullScreen)
{
    // Crear ventana
    window_ = std::make_unique<Window>();
    window_->init(windowName, width, heigth, fullScreen);
    treeNode = std::make_unique<TNodeTree>();
    resManager = std::make_unique<ResourceManager_>();
    // resManager->add<RShader>("interface");
    interface = std::make_unique<UserInterface>(resManager->add<RShader>("interface"));
    sceneNode = addSceneNode()->getId();
    mouse = std::make_unique<MouseEngine>(window_.get());
    userText = std::make_unique<UserText>();

    glfwSetKeyCallback(window_->getWindow(), keyCallback);
    glfwSetWindowCloseCallback(window_->getWindow(), windowCloseCallback);
    glfwSetFramebufferSizeCallback(window_->getWindow(), framebuffer_size_callback);
    // glfwSetCursorPosCallback(window_.getWindow(), mouse_position_callback);
    // initImGui(true);
}
void GraphicEngine::keyCallback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
    if (action == GLFW_PRESS)
    {
        keyboardState.keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keyboardState.keys[key] = false;
    }
}
void GraphicEngine::windowCloseCallback([[maybe_unused]] GLFWwindow *window)
{
    closeWindow = true;
    glfwSetWindowShouldClose(window, GLFW_FALSE);
}
bool GraphicEngine::isMouseButtonPressed(int button)
{
    return mouse->isMouseButtonPressed(window_->getWindow(), button);
}
float GraphicEngine::getMouseWheelMove()
{
    return mouse->getMouseWheelMove();
}
bool GraphicEngine::isKeyPressed(int key)
{
    return keyboardState.isKeyPressed(key);
}
bool GraphicEngine::isKeyDown(int key)
{
    return keyboardState.isKeyDown(key);
}
bool GraphicEngine::isKeyReleased(int key)
{
    return keyboardState.isKeyReleased(key);
}
bool GraphicEngine::isRunning()
{
    return !glfwWindowShouldClose(window_->getWindow());
}
void GraphicEngine::drawAll()
{
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    // Se activa para que todo lo que se vaya a dibujar en pantalla
    // solo se dibuja las caras que se ven en la camara
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    if (treeNode != nullptr && drawModels)
        treeNode->getById(sceneNode)->treeIterator(this);

    updateEmiters(sceneNode);
    // std::cout << "Res manager: " << resManager->size<RShader>() << std::endl;

    // Permite que se mezclen texturas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Se desactiva para que la interfaz se dibuje bien
    glDisable(GL_CULL_FACE);

    interface->draw();

    keyboardState.update();

    drawAllText();

    mouse->resetMouseWheel();

    if (initImGui_)
    {
        if (ImGui::GetCurrentContext())
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    closeWindow = false;

    // std::cout << "Mouse x: " << mouse->getPosition().x << std::endl;
    // std::cout << "Mouse y: " << mouse->getPosition().y << std::endl;
}
void GraphicEngine::endScene()
{
    glfwSwapBuffers(window_->getWindow());
    glfwPollEvents();
    glClearColor(0.0f, 46.0f / 255.0f, 106.0f / 255.0f, 0.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    clearUserInterface();
    clearText();
}
void GraphicEngine::updateEmiters(TNode::key_type id)
{
    auto *node = getNode(id);
    for (auto &child_id : node->getChildrenList())
    {
        auto *child = getNode(child_id);
        if (auto *emitter = child->getEntity<T_EParticleEmiter>())
        {
            emitter->update(this, child_id);
            continue;
        }

        updateEmiters(child_id);
    }
}
bool GraphicEngine::buttonClick(float initX, float initY, float distanceX, float distanceY)
{
    if ((getMousePosition().y > ((initY * ((getWindowHeigth() / 1080.0f)))) && getMousePosition().y < ((initY * ((getWindowHeigth() / 1080.0f))) + distanceY) &&
         getMousePosition().x > ((initX * ((getWindowWidth() / 1920.0f)))) && getMousePosition().x < ((initX * ((getWindowWidth() / 1920.0f))) + distanceX)))
    {
        return true;
    }

    return false;
}
void GraphicEngine::resizeWindow(unsigned int width, unsigned int heigth)
{
    window_->resizeWindow(width, heigth);

    GLFWmonitor *monitor = glfwGetActiveMonitor(window_->getWindow());

    int x_m{}, y_m{}, width_m{}, height_m{};
    glfwGetMonitorWorkarea(monitor, &x_m, &y_m, &width_m, &height_m);
    if (width > width_m || heigth > height_m)
    {
        width = width_m;
        heigth = height_m;
    }
    glfwSetWindowAttrib(window_->getWindow(), GLFW_DECORATED, GLFW_TRUE);

    glfwSetWindowMonitor(window_->getWindow(), NULL, x_m, y_m + 30, width, heigth, GLFW_DONT_CARE);

    // if (width == 1920)
    // {
    //     glfwSetWindowPos(window_->getWindow(), 0, 0);
    // }
    // else
    // {
    //     glfwSetWindowPos(window_->getWindow(), 960 - (width / 2), 540 - (heigth / 2));
    // }
}
void GraphicEngine::fullScreenWindow()
{
    GLFWmonitor *monitor = glfwGetActiveMonitor(window_->getWindow());
    GLFWvidmode const *mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window_->getWindow(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}
void GraphicEngine::moveWindow(int posX, int posY)
{
    glfwSetWindowPos(window_->getWindow(), posX, posY);
}
TNode *GraphicEngine::addSceneNode(BUILD_NODE_C)
{
    TNode::key_type newNode = treeNode->createNode(parent, id, position, rotation, scale);
    return treeNode->getById(newNode);
}

TNode::key_type GraphicEngine::addSceneCamera(glm::vec3 lookAt, BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    auto camera = std::make_unique<T_ECamera>();

    if (!camera)
        return 0;

    camera->setTarget(lookAt);
    camera->setPosition(position);

    newNode->setEntity(std::move(camera));

    cameras.push_back(newNode->getId());

    return newNode->getId();
}

TNode::key_type GraphicEngine::addSceneModel(std::string fileName, std::string textureName, std::string materialName, glm::vec3 lightColor, glm::vec3 lightDirection, float diffuse, float ambient, float specular, BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    // Hay que mirarlo
    RModel *modelToLoad = resManager->add<RModel>(fileName);

    if (!modelToLoad)
        return 0;

    auto model = std::make_unique<T_EMesh>(modelToLoad, lightColor, lightDirection, diffuse, ambient, specular);

    // Falta cargar la textura
    if (!textureName.empty())
    {
        RMaterial *material = resManager->add<RMaterial>(materialName);
        RTexture *texture = resManager->add<RTexture>(textureName);
        //RTexture *textureLigth = resManager->add<RTexture>("./media/textures/ParedLuz.png");
        if (texture)
            modelToLoad->addTexture(texture, material);
    }

    newNode->setEntity(std::move(model));

    return newNode->getId();
}
TNode::key_type GraphicEngine::addSceneSkinModel(std::string fileName, std::string textureName, BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    // Hay que mirarlo
    RSkinModel *modelToLoad = resManager->add<RSkinModel>(fileName);

    if (!modelToLoad)
        return 0;

    auto model = std::make_unique<T_AnimationMesh>(modelToLoad);

    // Falta cargar la textura
    if (!textureName.empty())
    {
        RTexture *texture = resManager->add<RTexture>(textureName);
        RMaterial *material = resManager->add<RMaterial>("./media/models/vida.mtl");
        if (texture)
            modelToLoad->addTexture(texture, material);
    }

    newNode->setEntity(std::move(model));

    return newNode->getId();
}
RAnimation *GraphicEngine::addSceneAnimation(std::string fileName, std::string model)
{
    RSkinModel *modelSkin = resManager->add<RSkinModel>(model);

    if (modelSkin == nullptr)
        return nullptr;

    RAnimation *animation = resManager->add<RAnimation>(fileName);

    if (animation == nullptr)
        return nullptr;

    animation->loadAnimation(fileName, modelSkin);

    return animation;
}
TNode::key_type GraphicEngine::addSceneParticle(BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    // Hay que mirarlo
    auto particle = std::make_unique<SParticle>(0);

    if (!particle)
        return 0;

    newNode->setEntity(std::move(particle));

    return newNode->getId();
}
TNode::key_type GraphicEngine::addSceneParticleEmiter(glm::vec3 color, BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    auto particle = std::make_unique<T_EParticleEmiter>(*treeNode);

    if (!particle)
        return 0;

    particle->color = color;

    newNode->setEntity(std::move(particle));

    return newNode->getId();
}
RTexture *GraphicEngine::addTexture(std::string fileName, TNode::key_type node)
{
    // RModel *modelToLoad = resManager->add<RModel>(fileName);

    // if (!modelToLoad)
    //     return 0;

    // auto model = std::make_unique<T_EMesh>(modelToLoad, glm::vec3{0.0f,0.0f,0.0f});

    // Falta cargar la textura
    if (!fileName.empty())
    {
        RTexture *texture = resManager->add<RTexture>(fileName);
        RMaterial *material = resManager->add<RMaterial>("./media/models/vida.mtl");
        if (texture)
        {
            T_EMesh *mesh_ = getNode(node)->getEntity<T_EMesh>();
            mesh_->mesh->addTexture(texture, material);
        }
    }

    // getNode(node)->setEntity(std::move(model));

    return nullptr;
    // if (!fileName.empty())
    // {

    //     RTexture *texture = resManager->add<RTexture>(fileName);
    //     if (texture)
    //         getNode(node)->getEntity<T_EMesh>()->mesh->addTexture(texture);
    // }
}
void GraphicEngine::framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
TNode::key_type GraphicEngine::addSceneLigth(BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    auto ligth = std::make_unique<T_ELight>();

    if (!ligth)
        return 0;

    newNode->setEntity(std::move(ligth));

    return newNode->getId();
}
TNode::key_type GraphicEngine::addSceneSkyBox(std::array<std::string, 6> files, BUILD_NODE_C)
{
    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    auto skybox = std::make_unique<T_ESkyBox>(files);

    if (skybox.get() == nullptr)
    {
        return 0;
    }

    newNode->setEntity(std::move(skybox));

    return newNode->getId();
}
TNode::key_type GraphicEngine::addSceneBillboard(std::string fileName, BUILD_NODE_C)
{
    RTexture *texture;

    TNode *newNode = addSceneNode(parent, id, position, rotation, scale);

    if (!newNode)
        return 0;

    // Falta cargar la textura
    if (!fileName.empty())
    {
        texture = resManager->add<RTexture>(fileName);
    }

    auto billboard = std::make_unique<T_EBillboard>(texture->id);

    newNode->setEntity(std::move(billboard));

    return newNode->getId();
}
void GraphicEngine::addSceneText(std::string text, std::string font, float posX, float posY, float textSize, glm::vec3 color)
{
    // if (getText(text))
    //     return;
    auto texto = std::make_unique<TextData>(text, font, posX, posY, textSize, color);
    userText->addText(std::move(texto));
}
void GraphicEngine::setActiveCamera(size_t idCam)
{
    currentCam = idCam;
}
TNode *GraphicEngine::getActiveCamera()
{
    return treeNode->getById(cameras[currentCam]);
}
TNode *GraphicEngine::getNode(TNode::key_type id)
{
    return treeNode->getById(id);
}
UImage *GraphicEngine::addSceneImage(std::string fileName, float x, float y)
{
    if (fileName.empty())
        return nullptr;

    RTexture *texture = resManager->add<RTexture>(fileName);

    if (texture->width == 0 || texture->heigth == 0)
        return nullptr;

    auto img = interface->addImage(std::move(std::make_unique<UImage>(texture, glm::vec2{x, y}, window_->getWidth(), window_->getHeigth())));

    return img;
}
glm::vec2 GraphicEngine::getMousePosition()
{
    return mouse->getPosition();
}
bool GraphicEngine::isMouseReleased()
{
    return mouse->isMouseReleased();
}
bool GraphicEngine::setImageVisibility(UImage *image, bool visible)
{
    return interface->setImageVisibility(image, visible);
}
void GraphicEngine::setImagePosition(UImage *image, float posX, float posY)
{
    interface->setImagePosition(image, posX, posY);
}
void GraphicEngine::mouse_position_callback([[maybe_unused]] GLFWwindow *window, double xpos, double ypos)
{
    mousePos = {xpos, ypos};
}
void GraphicEngine::clearUserInterface()
{
    interface->clear();
}
void GraphicEngine::clearText()
{
    userText->clear();
}
void GraphicEngine::clearImage(UImage *image)
{
    interface->eraseImage(image);
}
void GraphicEngine::clearModels()
{
    treeNode->getById(sceneNode)->clearChild();
    cameras.clear();
    treeNode->resetId();
}
void GraphicEngine::removeModel(TNode::key_type model)
{
    treeNode->deleteNode(model);
}
void GraphicEngine::drawAllText()
{
    std::vector<std::unique_ptr<TextData>>::iterator text_ptr;
    for (text_ptr = userText->textList.begin(); text_ptr != userText->textList.end(); text_ptr++)
    {
        drawText((*text_ptr)->getText(), (*text_ptr)->getFont(), (*text_ptr)->getPosX(), (*text_ptr)->getPosY(), (*text_ptr)->getFontSize(), (*text_ptr)->getColor());
    }
}
bool GraphicEngine::getText(std::string text)
{
    return userText->getText(text);
}
void GraphicEngine::setText(const char *text)
{
    userText->setText(text);
}
void GraphicEngine::drawText(std::string text, std::string font, float posX, float posY, float fontSize, glm::vec3 color)
{
    float saltoLineaY{0.0f};
    float saltoLineaX{0.0f};
    float [[maybe_unused]] posXInit = posX;
    RShader *shader = resManager->add<RShader>("text");

    if (shader == nullptr)
        return;

    RFont *fontText = resManager->add<RFont>(font);

    if (fontText == nullptr)
        return;

    shader->use();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_->getWidth()), 0.0f, static_cast<float>(window_->getHeigth()));
    shader->setMat4("projection", projection);

    shader->setVec3("color", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(fontText->VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c < text.end(); c++)
    {
        char finalC = *c;
        // Create a SCharacter so we can get every value of him
        SCharacter ch = fontText->characters[finalC];

        float xpos = (float)(posX + ch.bearing.x * fontSize) * (window_->getWidth() / 1920.0f) + saltoLineaX;
        float ypos = (float)(posY - (ch.size.y - ch.bearing.y) * fontSize) * (window_->getHeigth() / 1080.0f) + saltoLineaY;

        float w = (float)(ch.size.x * fontSize) * (window_->getWidth() / 1920.0f) + 0.5f;
        float h = (float)(ch.size.y * fontSize) * (window_->getHeigth() / 1080.0f);
        // Update VBO for each character

        if (*c == '*')
        {
            saltoLineaY -= (static_cast<float>(ch.size.y * fontSize)) * 2.f + 17.5f;
            saltoLineaX -= xpos - w - 8.0f - 15.0f;
            ch.textureId = 0;
        }

        // Create quad contains the character at screen
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, fontText->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        posX += (float)((ch.advance >> 6) * fontSize); // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    // Unlink VAO and textures
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void GraphicEngine::draw3dLine(glm::vec3 begin, glm::vec3 end, glm::vec3 color)
{
    auto *shader = resManager->add<RShader>("line");

    float vertices[] = {begin.x, begin.y, begin.z, end.x, end.y, end.z};

    unsigned int VBO{}, VAO{};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader->use();

    auto *c = getActiveCamera()->getEntity<T_ECamera>();
    glm::mat4 view = c->GetViewMatrix();
    glm::mat4 projection = c->getCameraMatrix();

    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setVec3("color", color);

    glBindVertexArray(VAO);
    glLineWidth(2);
    glDrawArrays(GL_LINES, 0, 2);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
void GraphicEngine::drawBoundingBox(glm::vec3 position, float w, float h, float d, glm::vec3 color)
{
    // Lower poligon of the box
    draw3dLine({(position.x - w / 2), (position.y - h / 2), (position.z - d / 2)}, {(position.x + w / 2), (position.y - h / 2), (position.z - d / 2)}, color);
    draw3dLine({(position.x - w / 2), (position.y - h / 2), (position.z - d / 2)}, {(position.x - w / 2), (position.y - h / 2), (position.z + d / 2)}, color);
    draw3dLine({(position.x - w / 2), (position.y - h / 2), (position.z + d / 2)}, {(position.x + w / 2), (position.y - h / 2), (position.z + d / 2)}, color);
    draw3dLine({(position.x + w / 2), (position.y - h / 2), (position.z + d / 2)}, {(position.x + w / 2), (position.y - h / 2), (position.z - d / 2)}, color);

    // Upper poligon of the box
    draw3dLine({(position.x - w / 2), (position.y + h / 2), (position.z - d / 2)}, {(position.x + w / 2), (position.y + h / 2), (position.z - d / 2)}, color);
    draw3dLine({(position.x - w / 2), (position.y + h / 2), (position.z - d / 2)}, {(position.x - w / 2), (position.y + h / 2), (position.z + d / 2)}, color);
    draw3dLine({(position.x - w / 2), (position.y + h / 2), (position.z + d / 2)}, {(position.x + w / 2), (position.y + h / 2), (position.z + d / 2)}, color);
    draw3dLine({(position.x + w / 2), (position.y + h / 2), (position.z + d / 2)}, {(position.x + w / 2), (position.y + h / 2), (position.z - d / 2)}, color);

    // Vertical-Lineal poligon of the box
    draw3dLine({(position.x - w / 2), (position.y - h / 2), (position.z - d / 2)}, {(position.x - w / 2), (position.y + h / 2), (position.z - d / 2)}, color);
    draw3dLine({(position.x + w / 2), (position.y - h / 2), (position.z - d / 2)}, {(position.x + w / 2), (position.y + h / 2), (position.z - d / 2)}, color);
    draw3dLine({(position.x - w / 2), (position.y - h / 2), (position.z + d / 2)}, {(position.x - w / 2), (position.y + h / 2), (position.z + d / 2)}, color);
    draw3dLine({(position.x + w / 2), (position.y - h / 2), (position.z + d / 2)}, {(position.x + w / 2), (position.y + h / 2), (position.z + d / 2)}, color);
}
void GraphicEngine::initImGui(bool install_callbacks)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwMakeContextCurrent(window_->getWindow());
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window_->getWindow(), install_callbacks);

    const char *glsl_version = "#version 130";

    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    initImGui_ = true;

    // if (not ImGui::GetCurrentContext())
    // {
    //     IMGUI_CHECKVERSION();
    //     ImGui::CreateContext();
    //     ImGui::StyleColorsDark();
    //     ImGui_ImplGlfw_InitForOpenGL(window_->getWindow(), install_callbacks);
    //     ImGui_ImplOpenGL3_Init(glsl_version);
    //     Callbacks_Installed = install_callbacks;
    // }
    // else if (Callbacks_Installed != install_callbacks)
    // {
    //     if (install_callbacks == true)
    //         ImGui_ImplGlfw_InstallCallbacks(window_->getWindow());
    //     else
    //         ImGui_ImplGlfw_RestoreCallbacks(window_->getWindow());

    //     Callbacks_Installed = install_callbacks;
    // }
}
void GraphicEngine::closeImGui()
{
    if (ImGui::GetCurrentContext() != nullptr)
    {
        initImGui_ = false;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}