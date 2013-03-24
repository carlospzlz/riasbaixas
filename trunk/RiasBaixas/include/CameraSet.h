#ifndef CAMERSET_H
#define CAMERASET_H

/**
 * @file CameraSet.h
 * @brief this class is responsible to manage all the cameras that the user can use
 * to watch the scene of the 3D game
 */

#include <vector>
#include <ngl/Camera.h>
#include "Object.h"

/**
 * @class CameraSet
 * @brief this class is the responsible of managing all the cameras that the user can use
 * to watch the scene of the 3D game
 */
class CameraSet
{

private:
    const static float s_angle;
    /**
     * @brief near clipping plane of the cameras
     */
    const static float s_near;
    /**
     * @brief far clipping plane of the cameras
     */
    const static float s_far;
    /**
     * @brief circular queue of cameras that the user can iterate over
     */
    std::vector<ngl::Camera*> m_camerasCircularQueue;
    /**
     * @brief first person cameras which will update all the components of its position
     */
    std::vector<ngl::Camera*> m_FPCameras;
    /**
     * @brief spectator cameras which will only update the position in the Z axis
     */
    std::vector<ngl::Camera*> m_spectatorCameras;
    /**
     * @brief special camera to look back
     */
    ngl::Camera *m_backCamera;
    /**
     * @brief current camera in use
     */
    ngl::Camera *m_currentCamera;
    /**
     * @brief target which defines the look of all of the cameras
     */
    Object *m_target;
    /**
     * @brief index of the normal current camera in the circular queue
     */
    int m_indexCurrentCamera;
    /**
     * @brief angle of the cameras
     */

public:
    CameraSet();
    ~CameraSet();
    /**
     * @brief load a set of default cameras
     */
    void loadCameras(int _w, int _h);
    /**
     * @brief set the target to observe
     */
    void setTarget(Object *_target);
    /**
     * @brief return a pointer to the current camera
     */
    ngl::Camera *getCurrentCamera() { return m_currentCamera; }
    /**
     * @brief iterate over the circular queue of cameras
     */
    void nextCamera();
    /**
     * @brief change the current camera to the back camera
     */
    void changeToBackCamera();
    /**
     * @brief change the current camera to the normal cameras
     */
    void leaveBackCamera();
    /**
     * @brief get the far clipping plane of the cameras
     */
    float getFar() { return s_far; }
    /**
     * @brief update the position of the cameras according to the target
     */
    void updateCameras();
    /**
     * @brief set the shape of the cameras. Used when resizing window
     */
    void setShape(int _w, int _h);
    /**
     * @brief add a new camera
     */
    void addCamera(ngl::Camera *_cam);
    /**
     * @brief check if the current camera is the back camera
     */
    bool isBackCameraActive() { return m_currentCamera==m_backCamera; }

};

#endif // CAMERASET_H
