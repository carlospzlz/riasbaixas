#include <cassert>
#include "CameraSet.h"

const float CameraSet::s_angle = 45;
const float CameraSet::s_near = 0.05;
const float CameraSet::s_far = 60;

CameraSet::CameraSet()
{
    m_indexCurrentCamera = 0;
    m_target = NULL;
}

CameraSet::~CameraSet()
{
    std::cout << "CameraSet: Deleting cameras..." << std::endl;
    std::vector<ngl::Camera*>::iterator lastCamera = m_camerasCircularQueue.end();
    for (std::vector<ngl::Camera*>::iterator currentCamera=m_camerasCircularQueue.begin(); currentCamera!=lastCamera;++currentCamera)
    {
        delete *currentCamera;
    }

    delete m_backCamera;
}

void CameraSet::loadCameras(int _w, int _h)
{

    //camera from back
    ngl::Camera* cameraFromTheBack = new ngl::Camera(ngl::Vec3(0,8,14),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    cameraFromTheBack->setShape(s_angle, _w/(float)_h, s_near, s_far, ngl::PERSPECTIVE);
    m_spectatorCameras.push_back(cameraFromTheBack);
    m_camerasCircularQueue.push_back(m_spectatorCameras.back());

    //aerial camera
    ngl::Camera* aerialCamera = new ngl::Camera(ngl::Vec3(0,20,0),ngl::Vec3(0,0,0),ngl::Vec3(0,0,-1),ngl::PERSPECTIVE);
    aerialCamera->setShape(s_angle, _w/(float)_h, s_near, s_far, ngl::PERSPECTIVE);
    m_spectatorCameras.push_back(aerialCamera);
    m_camerasCircularQueue.push_back(m_spectatorCameras.back());

    //first person camera
    ngl::Camera* fpCamera = new ngl::Camera(ngl::Vec3(0,1,0),ngl::Vec3(0,0,-6),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    fpCamera->setShape(s_angle, _w/(float)_h, s_near, s_far, ngl::PERSPECTIVE);
    m_FPCameras.push_back(fpCamera);
    m_camerasCircularQueue.push_back(m_FPCameras.back());

    //side camera
    ngl::Camera* cameraFromTheSide = new ngl::Camera(ngl::Vec3(-10,0,0),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    cameraFromTheSide->setShape(s_angle, _w/(float)_h, s_near, s_far, ngl::PERSPECTIVE);
    m_spectatorCameras.push_back(cameraFromTheSide);
    m_camerasCircularQueue.push_back(m_spectatorCameras.back());

    //special back camera
    m_backCamera = new ngl::Camera(ngl::Vec3(0,1,0),ngl::Vec3(0,0,6),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    m_backCamera->setShape(s_angle, _w/(float)_h, s_near, s_far, ngl::PERSPECTIVE);
    m_FPCameras.push_back(m_backCamera);

    m_currentCamera = m_camerasCircularQueue[0];
}

void CameraSet::setShape(int _w, int _h)
{
    std::vector<ngl::Camera*>::iterator lastCamera = m_camerasCircularQueue.end();
    for(std::vector<ngl::Camera*>::iterator currentCamera = m_camerasCircularQueue.begin(); currentCamera!=lastCamera;++currentCamera)
    {
        (*currentCamera)->setShape(s_angle,_w/(float)_h,s_near,s_far,ngl::PERSPECTIVE);
    }
    m_backCamera->setShape(s_angle,_w/(float)_h,s_near,s_far,ngl::PERSPECTIVE);
}

void CameraSet::setTarget(Object *_target)
{
    m_target = _target;
}

void CameraSet::changeToBackCamera()
{
    m_currentCamera = m_backCamera;
}

void CameraSet::leaveBackCamera()
{
    assert(m_indexCurrentCamera>=0 && m_indexCurrentCamera<m_camerasCircularQueue.size());
    m_currentCamera = m_camerasCircularQueue[m_indexCurrentCamera];
}

void CameraSet::nextCamera()
{
    assert(m_indexCurrentCamera>=0 && m_indexCurrentCamera<m_camerasCircularQueue.size());
    if (++m_indexCurrentCamera==m_camerasCircularQueue.size())
            m_indexCurrentCamera = 0;
    m_currentCamera = m_camerasCircularQueue[m_indexCurrentCamera];
}

void CameraSet::addCamera(ngl::Camera* _cam)
{
    m_spectatorCameras.push_back(_cam);
    m_camerasCircularQueue.push_back(_cam);
}

void CameraSet::updateCameras()
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
