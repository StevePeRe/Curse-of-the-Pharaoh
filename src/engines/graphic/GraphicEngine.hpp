#pragma once
#include <memory>
#include <engines/graphic/GraphicEngineFachada.hpp>
#include <engines/graphic/ResourceTypes.hpp>
#include <engines/graphic/ResourceManager.hpp>
#include <engines/graphic/ResourceManager.tpp>
#include <engines/graphic/UserInterface.hpp>
#include <engines/graphic/Window.hpp>
#include <engines/graphic/T_ECamera.hpp>
#include <engines/graphic/T_EMesh.hpp>
#include <engines/graphic/T_ELight.hpp>
#include <engines/graphic/T_ESkyBox.hpp>
#include <engines/graphic/T_EBillboard.hpp>
#include <engines/graphic/MouseEngine.hpp>
#include <engines/graphic/KeyboardState.hpp>
#include <engines/graphic/TNodeTree.hpp>
#include <engines/graphic/T_AnimationMesh.hpp>
#include <engines/graphic/UserText.hpp>
#include <engines/graphic/TextData.hpp>
#include <engines/graphic/SParticle.hpp>
#include <engines/graphic/T_EParticleEmiter.hpp>
#include <string>

// #define BUILD_NODE_H TNode::key_type parent = 1, [[maybe_unused]]std::size_t id = -1, glm::vec3 position = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0}, glm::vec3 scale = {1, 1, 1}
// #define BUILD_NODE_C TNode::key_type parent, [[maybe_unused]]std::size_t id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale

struct GraphicEngine : GraphicEngineFachada
{
public:
    GraphicEngine() = default;

    GraphicEngine(std::string windowName, unsigned int width, unsigned int heigth, bool fullScreen);

    bool isRunning();
    void drawAll();
    void endScene();

    TNode *addSceneNode(BUILD_NODE_H);
    TNode::key_type addSceneCamera(glm::vec3 lookAt, BUILD_NODE_H);
    TNode::key_type addSceneModel(std::string fileName, std::string textureName, std::string materialName="./media/models/vida.mtl", glm::vec3 lightColor=glm::vec3{0.923f,0.729f,0.239f}, glm::vec3 lightDirection=glm::vec3{0.0f,1.5f,-1.0f}, float diffuse = 0.9f, float ambient=0.3f, float specular=0.6f, BUILD_NODE_H);
    TNode::key_type addSceneLigth(BUILD_NODE_H);
    TNode::key_type addSceneSkyBox(std::array<std::string, 6>, BUILD_NODE_H);
    TNode::key_type addSceneBillboard(std::string fileName, BUILD_NODE_H);
    TNode::key_type addSceneSkinModel(std::string fileName, std::string textureName, BUILD_NODE_H);
    TNode::key_type addSceneParticle(BUILD_NODE_H);
    
    RTexture* addTexture(std::string fileName, TNode::key_type node);

    // En un futuro se puede poner como parametros el looping todos los valores del hpp de ParticleEmiter para personalizar las particulas
    TNode::key_type addSceneParticleEmiter(glm::vec3 color, BUILD_NODE_H);

    RAnimation *addSceneAnimation(std::string fileName, std::string model);

    TNode *getActiveCamera();
    TNode *getNode(TNode::key_type);
    void setActiveCamera(size_t idCam);

    bool isKeyPressed(int key);
    bool isKeyDown(int key);
    bool isKeyReleased(int key);

    void static framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void static mouse_position_callback(GLFWwindow *window, double xpos, double ypos);
    void static keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void static windowCloseCallback([[maybe_unused]] GLFWwindow *window);

    UImage *addSceneImage(std::string fileName, float x, float y);
    void clearImage(UImage *image);
    void clearUserInterface();
    void clearModels();
    void removeModel(TNode::key_type model);

    glm::vec2 getMousePosition();
    bool isMouseReleased();
    bool setImageVisibility(UImage *image, bool visible);
    void setImagePosition(UImage *image, float posX, float posY);
    bool isMouseButtonPressed(int button);
    float getMouseWheelMove();

    void disableDrawModels() { drawModels = false; };
    void enableDrawModels() { drawModels = true; };

    void drawText(std::string text, std::string font, float posX = 0, float posY = 0, float textSize = 1, glm::vec3 color = {1, 1, 1});
    void addSceneText(std::string text, std::string font, float posX = 0, float posY = 0, float textSize = 1, glm::vec3 color = {1, 1, 1});
    void drawAllText();
    void clearText();
    // Quitar esto
    bool getText(std::string text);
    void setText(const char *text);

    void resizeWindow(unsigned int width, unsigned int heigth);
    void fullScreenWindow();
    void moveWindow(int posX, int posY);

    void draw3dLine(glm::vec3 begin, glm::vec3 end, glm::vec3 color);
    void drawBoundingBox(glm::vec3 position, float w, float h, float d, glm::vec3 color);

    size_t getImgSize() { return interface->getImageList(); }
    int getWindowWidth() { return window_->getWidth(); }
    int getWindowHeigth() { return window_->getHeigth(); }
    GLFWwindow *getWindow() { return window_->getWindow(); }
    bool buttonClick(float initX, float initY, float distanceX, float distanceY);

    void initImGui(bool);
    void closeImGui();

    int getCamSize() { return cameras.size(); }

    void updateEmiters(TNode::key_type node);

    std::unique_ptr<ResourceManager_> resManager;
    static inline glm::vec2 mousePos{0, 0};

    static inline KeyboardState keyboardState;

    static inline bool closeWindow{false};

    bool initImGui_{false};

private:
    std::unique_ptr<TNodeTree> treeNode;
    std::unique_ptr<Window> window_;
    std::unique_ptr<UserInterface> interface;
    std::unique_ptr<MouseEngine> mouse;
    std::vector<TNode::key_type> cameras;
    std::unique_ptr<UserText> userText;
    size_t currentCam{0};
    TNode::key_type sceneNode{0}; // Nodo donde empieza toda la escena

    bool drawModels{true};
    bool Callbacks_Installed{false};
};
