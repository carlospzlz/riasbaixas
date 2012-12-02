#include <cassert>
#include "CameraManager.h"


CameraManager::CameraManager()
{
    m_indexCurrentCamera = 0;
    m_target = NULL;
    m_angle = 45;
    m_near = 0.05;
    m_far = CAMERAMANAGER_FAR_CLIPPING_PLANE;

}

CameraManager::~CameraManager()
{
    //std::vector<ngl::Camera*>::iterator lastCamera = m_camerasCircularQueue.end();
    //for (std::vector<ngl::Camera*>::iterator currentCamera=m_camerasCircularQueue.begin(); currentCamera!=lastCamera;++currentCamera)
    //    delete *currentCamera;

    //delete m_backCamera;
}

void CameraManager::loadCameras(int _w, int _h)
{
    //far clipping plane 350

    //camera from back
    ngl::Camera* cameraFromTheBack = new ngl::Camera(ngl::Vec3(0,8,14),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    cameraFromTheBack->setShape(m_angle, _w/(float)_h, m_near, m_far, ngl::PERSPECTIVE);
    m_spectatorCameras.push_back(cameraFromTheBack);
    m_camerasCircularQueue.push_back(m_spectatorCameras.back());

    //aerial camera
    ngl::Camera* aerialCamera = new ngl::Camera(ngl::Vec3(0,20,0),ngl::Vec3(0,0,0),ngl::Vec3(0,0,-1),ngl::PERSPECTIVE);
    aerialCamera->setShape(m_angle, _w/(float)_h, m_near, m_far, ngl::PERSPECTIVE);
    m_spectatorCameras.push_back(aerialCamera);
    m_camerasCircularQueue.push_back(m_spectatorCameras.back());

    //first person camera
    ngl::Camera* fpCamera = new ngl::Camera(ngl::Vec3(0,1,0),ngl::Vec3(0,0,-6),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    fpCamera->setShape(m_angle, _w/(float)_h, m_near, m_far, ngl::PERSPECTIVE);
    m_FPCameras.push_back(fpCamera);
    m_camerasCircularQueue.push_back(m_FPCameras.back());

    //side camera
    ngl::Camera* cameraFromTheSide = new ngl::Camera(ngl::Vec3(-10,0,0),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    cameraFromTheSide->setShape(m_angle, _w/(float)_h, m_near, m_far, ngl::PERSPECTIVE);
    m_spectatorCameras.push_back(cameraFromTheSide);
    m_camerasCircularQueue.push_back(m_spectatorCameras.back());

    //special back camera
    m_backCamera = new ngl::Camera(ngl::Vec3(0,1,0),ngl::Vec3(0,0,6),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    m_backCamera->setShape(m_angle, _w/(float)_h, m_near, m_far, ngl::PERSPECTIVE);
    m_FPCameras.push_back(m_backCamera);

    m_currentCamera = m_camerasCircularQueue[0];
}

void CameraManager::setShape(int _w, int _h)
{
    std::vector<ngl::Camera*>::iterator lastCamera = m_camerasCircularQueue.end();
    for(std::vector<ngl::Camera*>::iterator currentCamera = m_camerasCircularQueue.begin(); currentCamera!=lastCamera;++currentCamera)
    {
        (*currentCamera)->setShape(m_angle,_w/(float)_h,m_near,m_far,ngl::PERSPECTIVE);
    }
    m_backCamera->setShape(m_angle,_w/(float)_h,m_near,m_far,ngl::PERSPECTIVE);
}

void CameraManager::setTarget(Object *_target)
{
    m_target = _target;
}

void CameraManager::changeToBackCamera()
{
    m_currentCamera = m_backCamera;
}

void CameraManager::leaveBackCamera()
{
    assert(m_indexCurrentCamera>=0 && m_indexCurrentCamera<m_camerasCircularQueue.size());
    m_currentCamera = m_camerasCircularQueue[m_indexCurrentCamera];
}

void CameraManager::nextCamera()
{
    assert(m_indexCurrentCamera>=0 && m_indexCurrentCamera<m_camerasCircularQueue.size());
    if (++m_indexCurrentCamera==m_camerasCircularQueue.size())
            m_indexCurrentCamera = 0;
    m_currentCamera = m_camerasCircularQueue[m_indexCurrentCamera];
}

void CameraManager::addCamera(ngl::Camera* _cam)
{
    m_spectatorCameras.push_back(_cam);
    m_camerasCircularQueue.push_back(_cam);
}

void CameraManager::updateCameras()
{
    ngl::Vec4 eyeDisplacement;
    std::vector<ngl::Camera*>::iterator lastCamera;
    ngl::Vec4 targetPos = m_target->getPosition();
    ngl::Vec4 targetPreviousPos = m_target->getPreviousPos();

    //update spectator cameras
    assert(m_target);
    eyeDisplacement = ngl::Vec4(0,0, targetPos.m_z-targetPreviousPos.m_z,1);
    lastCamera = m_spectatorCameras.end();
    for (std::vector<ngl::Camera*>::iterator currentCamera=m_spectatorCameras.begin(); currentCamera!=lastCamera;++currentCamera)
    {
        (*currentCamera)->setEye((*currentCamera)->getEye()+eyeDisplacement);
    }

    //update first person cameras
    eyeDisplacement = ngl::Vec4(targetPos.m_x-targetPreviousPos.m_x ,targetPos.m_y-targetPreviousPos.m_y, targetPos.m_z-targetPreviousPos.m_z,1);
    lastCamera = m_FPCameras.end();
    for (std::vector<ngl::Camera*>::iterator currentCamera=m_FPCameras.begin(); currentCamera!=lastCamera;++currentCamera)
    {
        (*currentCamera)->setEye((*currentCamera)->getEye()+eyeDisplacement);
    }

}


