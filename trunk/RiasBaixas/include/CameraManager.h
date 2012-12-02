#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <vector>
#include <ngl/Camera.h>
#include "Object.h"

#define CAMERAMANAGER_FAR_CLIPPING_PLANE 60


class CameraManager
{

private:
    std::vector<ngl::Camera*> m_camerasCircularQueue;
    std::vector<ngl::Camera*> m_FPCameras;
    std::vector<ngl::Camera*> m_spectatorCameras;
    ngl::Camera *m_backCamera;
    ngl::Camera *m_currentCamera;
    Object *m_target;
    int m_indexCurrentCamera;
    float m_angle;
    float m_near;
    float m_far;

public:
    CameraManager();
    ~CameraManager();
    void loadCameras(int _w, int _h);
    void setTarget(Object *_target);
    ngl::Camera *getCurrentCamera() { return m_currentCamera; }
    void nextCamera();
    void changeToBackCamera();
    void leaveBackCamera();
    float getFar() { return m_far; }
    void updateCameras();
    void setShape(int _w, int _h);
    void addCamera(ngl::Camera *_cam);
    bool isBackCameraActive() { return m_currentCamera==m_backCamera; }

};

#endif // CAMERAMANAGER_H
