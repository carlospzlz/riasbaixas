#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <vector>
#include <ngl/Camera.h>
#include "Object.h"

class CameraManager
{

private:
    std::vector<ngl::Camera*> m_allCameras;
    std::vector<ngl::Camera*> m_FPCameras;
    std::vector<ngl::Camera*> m_spectatorCameras;
    ngl::Camera *m_backCamera;
    Object *m_target;
    int m_indexCurrentCamera;
    float m_previousYComponent;
    float m_previousZComponent;

public:
    CameraManager();
    ~CameraManager();
    void loadCameras();
    void setTarget(Object *_target);
    ngl::Camera *getFirstCamera();
    ngl::Camera *getCurrentCamera();
    ngl::Camera *getNextCamera();
    ngl::Camera *getBackCamera();
    void updateCameras();
    void addCamera(ngl::Camera *_cam);

};

#endif // CAMERAMANAGER_H
