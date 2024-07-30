#include <game/sys/camera.hpp>
// #include <ecs/cmp/entity.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>

// void CameraSystem::init(EntityManager &em) {
//     // En el init deberiamos calcular el rango de vision de las camaras
// }

bool CameraSystem::update(ECS::EntityManager &em)
{
    // Hay que mirar porque cambia el angulo de la camara cada vez que se cambia de W a S
    // Aqui lo que deberiamos es pillar entidad por su id y devolver la posicion donde esta el player
    // en este caso como todavia no tenemos un getEntidadById pues lo ponemos a pelo
    auto &e = em.getEntityVector().at(0);
    [[maybe_unused]] auto &pc = em.getComponents<PhysicsComponent>();
    for (auto &camera : em.getComponents<CameraComponent>())
    {
        if (camera.idCam == CameraComponent::currentCam)
        {
            if (e.getState() == ECS::EntityState::CAM_MOVING_FORWARDS)
                cameraMovForward(camera, ECS::CAMERA_SPEED);
            else if (e.getState() == ECS::EntityState::CAM_MOVING_BACKWARDS)
                cameraMovForward(camera, -ECS::CAMERA_SPEED);
            else if (e.getState() == ECS::EntityState::CAM_MOVING_RIGTH)
                cameraMovRigth(camera, ECS::CAMERA_SPEED);
            else if (e.getState() == ECS::EntityState::CAM_MOVING_LEFT)
                cameraMovRigth(camera, -ECS::CAMERA_SPEED);

            if (e.getState() == ECS::EntityState::CAM_ROTATE_RIGTH)
                cameraRotateRigth(camera, ECS::CAMERA_SPEED_ROTATION);
            else if (e.getState() == ECS::EntityState::CAM_ROTATE_LEFT)
                cameraRotateRigth(camera, -ECS::CAMERA_SPEED_ROTATION);
            else if (e.getState() == ECS::EntityState::CAM_ROTATE_FORWARDS)
                cameraRotateForward(camera, ECS::CAMERA_SPEED_ROTATION);
            else if (e.getState() == ECS::EntityState::CAM_ROTATE_BACKWARDS)
                cameraRotateForward(camera, -ECS::CAMERA_SPEED_ROTATION);

            if (e.getState() == ECS::EntityState::CAM_UP)
                cameraGoUp(camera, ECS::CAMERA_SPEED_UP_DOWN);
            else if (e.getState() == ECS::EntityState::CAM_DOWN)
                cameraGoUp(camera, -ECS::CAMERA_SPEED_UP_DOWN);

            if (e.getState() == ECS::EntityState::CAM_ZOOM_UP)
                cameraZoom(camera, ECS::CAMERA_SPEED_ZOOM);
            else if (e.getState() == ECS::EntityState::CAM_ZOOM_DOWN)
                cameraZoom(camera, -ECS::CAMERA_SPEED_ZOOM);

            if (e.getState() == ECS::EntityState::CAM_FOVY_UP)
                cameraFovy(camera, ECS::CAMERA_SPEED_FOVY);
            else if (e.getState() == ECS::EntityState::CAM_FOVY_DOWN)
                cameraFovy(camera, -ECS::CAMERA_SPEED_FOVY);

            if (e.getState() == ECS::EntityState::CAM_RESET)
                cameraResetValues(camera);
        }
    }

    return true;
}
void CameraSystem::cameraMovForward(CameraComponent &cam, float distance)
{
    ECS::Vector3 forward = getCameraForward(cam);

    forward.y = 0;
    forward = normalize(forward);

    forward = scale(forward, distance);

    cam.cameraPosition = add(cam.cameraPosition, forward);
    cam.cameraTarget = add(cam.cameraTarget, forward);
}
void CameraSystem::cameraRotateRigth(CameraComponent &cam, float angle)
{
    // Rotation axis
    ECS::Vector3 up = getCameraUp(cam);

    // View vector
    ECS::Vector3 targetPosition = substract(cam.cameraTarget, cam.cameraPosition);

    // Rotate view vector around up axis
    targetPosition = rotateByAxisAngle(targetPosition, up, angle);

    // cam.cameraPosition = substract(cam.cameraTarget, targetPosition);
    cam.cameraTarget = add(cam.cameraPosition, targetPosition);
}
ECS::Vector3 CameraSystem::rotateByAxisAngle(ECS::Vector3 v, ECS::Vector3 axis, float angle)
{
    // Using Euler-Rodrigues Formula
    // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula

    ECS::Vector3 result = v;

    // Vector3Normalize(axis);
    float length = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (length == 0.0f)
        length = 1.0f;
    float ilength = 1.0f / length;
    axis.x *= ilength;
    axis.y *= ilength;
    axis.z *= ilength;

    angle /= 2.0f;
    float a = sinf(angle);
    float b = axis.x * a;
    float c = axis.y * a;
    float d = axis.z * a;
    a = cosf(angle);
    ECS::Vector3 w = {b, c, d};

    // Vector3CrossProduct(w, v)
    ECS::Vector3 wv = {w.y * v.z - w.z * v.y, w.z * v.x - w.x * v.z, w.x * v.y - w.y * v.x};

    // Vector3CrossProduct(w, wv)
    ECS::Vector3 wwv = {w.y * wv.z - w.z * wv.y, w.z * wv.x - w.x * wv.z, w.x * wv.y - w.y * wv.x};

    // Vector3Scale(wv, 2*a)
    a *= 2;
    wv.x *= a;
    wv.y *= a;
    wv.z *= a;

    // Vector3Scale(wwv, 2)
    wwv.x *= 2;
    wwv.y *= 2;
    wwv.z *= 2;

    result.x += wv.x;
    result.y += wv.y;
    result.z += wv.z;

    result.x += wwv.x;
    result.y += wwv.y;
    result.z += wwv.z;

    return result;
}
void CameraSystem::cameraMovRigth(CameraComponent &cam, float distance)
{
    ECS::Vector3 right = getCameraRight(cam);

    right.y = 0;
    right = normalize(right);

    right = scale(right, distance);

    cam.cameraPosition = add(cam.cameraPosition, right);
    cam.cameraTarget = add(cam.cameraTarget, right);
}
ECS::Vector3 CameraSystem::getCameraRight(CameraComponent &cam)
{
    ECS::Vector3 forward = getCameraForward(cam);
    ECS::Vector3 up = getCameraUp(cam);

    return normalize(crossProduct(forward, up));
}
ECS::Vector3 CameraSystem::crossProduct(ECS::Vector3 v1, ECS::Vector3 v2)
{
    ECS::Vector3 result = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};

    return result;
}
ECS::Vector3 CameraSystem::getCameraUp(CameraComponent &cam)
{
    return normalize(cam.cameraUp);
}
ECS::Vector3 CameraSystem::getCameraForward(CameraComponent &cam)
{
    return normalize(substract(cam.cameraTarget, cam.cameraPosition));
}
ECS::Vector3 CameraSystem::normalize(ECS::Vector3 vec)
{
    ECS::Vector3 result = vec;

    float length = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (length != 0.0f)
    {
        float ilength = 1.0f / length;

        result.x *= ilength;
        result.y *= ilength;
        result.z *= ilength;
    }

    return result;
}
ECS::Vector3 CameraSystem::substract(ECS::Vector3 vec1, ECS::Vector3 vec2)
{
    ECS::Vector3 result = {vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z};

    return result;
}
float CameraSystem::dotProduct(ECS::Vector3 vec1, ECS::Vector3 vec2)
{
    float result = {(vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z)};

    return result;
}
ECS::Vector3 CameraSystem::scale(ECS::Vector3 v, float scalar)
{
    ECS::Vector3 result = {v.x * scalar, v.y * scalar, v.z * scalar};

    return result;
}
ECS::Vector3 CameraSystem::add(ECS::Vector3 v1, ECS::Vector3 v2)
{
    ECS::Vector3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};

    return result;
}
void CameraSystem::cameraRotateForward(CameraComponent &cam, float angle)
{
    // Up direction
    ECS::Vector3 up = getCameraUp(cam);

    // View vector
    ECS::Vector3 targetPosition = substract(cam.cameraTarget, cam.cameraPosition);

    // if (lockView)
    // {
    // In these camera modes we clamp the Pitch angle
    // to allow only viewing straight up or down.

    // Clamp view up
    float maxAngleUp = getAngle(up, targetPosition);
    maxAngleUp -= 0.001f; // avoid numerical errors
    if (angle > maxAngleUp)
        angle = maxAngleUp;

    // Clamp view down
    float maxAngleDown = getAngle(negate(up), targetPosition);
    maxAngleDown *= -1.0f;  // downwards angle is negative
    maxAngleDown += 0.001f; // avoid numerical errors
    if (angle < maxAngleDown)
        angle = maxAngleDown;
    // }

    // Rotation axis
    ECS::Vector3 right = getCameraRight(cam);

    // Rotate view vector around right axis
    targetPosition = rotateByAxisAngle(targetPosition, right, angle);

    // if (rotateAroundTarget)
    // {
    //     // Move position relative to target
    //     camera->position = Vector3Subtract(camera->target, targetPosition);
    // }
    // else // rotate around camera.position
    // {
    //     // Move target relative to position
    cam.cameraTarget = add(cam.cameraPosition, targetPosition);
    // }
}
float CameraSystem::getAngle(ECS::Vector3 v1, ECS::Vector3 v2)
{
    float result = 0.0f;

    ECS::Vector3 cross = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
    float len = sqrtf(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
    float dot = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    result = atan2f(len, dot);

    return result;
}
ECS::Vector3 CameraSystem::negate(ECS::Vector3 v)
{
    ECS::Vector3 result = {-v.x, -v.y, -v.z};

    return result;
}
void CameraSystem::cameraGoUp(CameraComponent &cam, float distance)
{
    ECS::Vector3 up = getCameraUp(cam);

    // Scale by distance
    up = scale(up, distance);

    // Move position and target
    cam.cameraPosition = add(cam.cameraPosition, up);
    cam.cameraTarget = add(cam.cameraTarget, up);
}
void CameraSystem::cameraZoom(CameraComponent &cam, float delta)
{
    float distance = distanceVector(cam.cameraPosition, cam.cameraTarget);

    // Apply delta
    distance += delta;

    // Distance must be greater than 0
    if (distance <= 0)
        distance = 0.001f;

    // Set new distance by moving the position along the forward vector
    ECS::Vector3 forward = getCameraForward(cam);
    cam.cameraPosition = add(cam.cameraTarget, scale(forward, -distance));
}
void CameraSystem::cameraFovy(CameraComponent &cam, float fovy)
{
    cam.cameraFovy += fovy;
}
float CameraSystem::distanceVector(ECS::Vector3 v1, ECS::Vector3 v2)
{
    float result = 0.0f;

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    result = sqrtf(dx * dx + dy * dy + dz * dz);

    return result;
}
void CameraSystem::cameraResetValues(CameraComponent &cam)
{
	cam.cameraPosition.x = ECS::CAMERA_POSITION.x;
	cam.cameraPosition.y = ECS::CAMERA_POSITION.y;
	cam.cameraPosition.z = ECS::CAMERA_POSITION.z;
	cam.cameraTarget.x = ECS::CAMERA_TARGET.x;
	cam.cameraTarget.y = ECS::CAMERA_TARGET.y;
	cam.cameraTarget.z = ECS::CAMERA_TARGET.z;
	cam.cameraUp.x = ECS::CAMERA_UP.x;
	cam.cameraUp.y = ECS::CAMERA_UP.y;
	cam.cameraUp.z = ECS::CAMERA_UP.z;
	cam.cameraFovy = ECS::CAMERA_FOVY;
}