#pragma once

#include <vector>
#include <concepts>
#include <memory>
//#include <engines/graphic/GraphicEngine.hpp>
#include <engines/graphic/TEntity.hpp>

template <typename T>
concept EntityType = std::derived_from<T, TEntity>;

struct TNodeTree;

struct TNode
{
    using key_type = std::size_t;

    struct DELETER
    {
        void operator()(TNode *node) 
        {
            node->~TNode();
        }
    };
    
    TNode(TNodeTree &tree) :  nodeTree{tree} {}
    // Cambiar y poner id
    TNode(TNodeTree &nodeTree, key_type parentId, key_type id, const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 sca);
    ~TNode();
    // Añadimos un hijo al array de children
    void addChild(key_type childToAdd);
    // Borramos el hijo del vector
    void removeChild(key_type childToRemove);
    void clearChild();
    // Devolvemos el padre
    key_type getParent() { return parent; }

    // Falta la matriz de transformacion como variable pero no la ponemos
    // porque se calcula cada vez que se itera

    const glm::vec3 getPosition() const;
    const glm::vec3 getRotation() const;
    const glm::vec3 getScale() const;
    key_type getId() { return id; }

    void setPosition(const glm::vec3 position);
    void setRotation(const glm::vec3 rotation);
    void setScale(const glm::vec3 scale);
    void setUpdateMatrix(bool updateMatrix);
    glm::vec3 getModelDirection();
    //void updateAbsolutePosition();

    // setParent, setVisible

    // Recorremos el arbol, nodo actual y los hijos del nodo
    void treeIterator(GraphicEngine *ge);
    // Se recalcula la matrix de transformacion
    const glm::mat4 getRelativeMatrix();
    // Sumamos la posicion
    void translate(const glm::vec3 posToTranslate);
    // Sumamos la rotacion
    void rotate(const glm::vec3 rotToTranslate);
    void rotateInterpolate(const glm::vec3 rotToTranslate);
    // Sumamos al escalado
    void scaleVec(const glm::vec3 scaToTranslate);

    // Hacemos que la funcion sea un template haga un casteo dinamico para el tipo que sea de la entidad
    template <EntityType typeE>
    typeE *getEntity() const { return dynamic_cast<typeE*>(entity.get()); }
    void setEntity(std::unique_ptr<TEntity> entity);

    void setVisible(bool visible_) { visible = visible_; }

    std::vector<key_type> getChildrenList() { return childrenList; }

private:
    key_type id{0};
    TNodeTree &nodeTree;
    
    // Vectores de posicion, rotacion y escalado
    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 rotation{0.f, 0.f, 0.f};
    // Para que se vea, si lo inicializamos a 0 no se ve
    glm::vec3 scale{1.f, 1.f, 1.f};

    glm::vec3 rotationVector{0.f};
    glm::mat4 viewMatrixPlayer{0.f};
    glm::vec3 entityForward{0.f};
    glm::vec3 lastRotation{0.f};

    // Guardamos las posiciones de los hijos
    std::vector<key_type> childrenList;

    // Puntero al padre si es null no se dibuja ya que no se recorre
    key_type parent{0};

    // Esto es lo que le da el formato como objeto 3D
    std::unique_ptr<TEntity> entity{nullptr};

    // Para saber si el Nodo es visible o no
    bool visible{true};

    // Con este bool nos ahorramos el calculo de la matriz a cada frame, para optimizacion
    bool updateMatrix{false};

    friend struct TNodeTree;
};