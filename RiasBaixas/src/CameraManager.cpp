#include <cassert>
#include "CameraManager.h"


CameraManager::CameraManager()
{
    m_indexCurrentCamera = 0;
    m_target = NULL;
    m_far = CAMERAMANAGER_FAR_CLIPPING_PLANE;
}

CameraManager::~CameraManager()
{
    std::vector<ngl::Camera*>::iterator lastCamera = m_allCameras.end();
    for (std::vector<ngl::Camera*>::iterator currentCamera=m_allCameras.begin(); currentCamera!=lastCamera;++currentCamera)
        delete *currentCamera;

    delete m_backCamera;
}

void CameraManager::loadCameras()
{
    //far clipping plane 350

    //camera from back
    ngl::Camera *cameraFromTheBack = new ngl::Camera(ngl::Vec3(0,12,12),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    cameraFromTheBack->setShape(45,(float)720.0/576.0,0.05,350,ngl::PERSPECTIVE);
    m_allCameras.push_back(cameraFromTheBack);
    m_spectatorCameras.push_back(cameraFromTheBack);

    //aerial camera
    ngl::Camera *aerialCamera = new ngl::Camera(ngl::Vec3(0,16,0),ngl::Vec3(0,0,0),ngl::Vec3(0,0,-1),ngl::PERSPECTIVE);
    aerialCamera->setShape(45,(float)720.0/576.0,0.05,m_far,ngl::PERSPECTIVE);
    m_allCameras.push_back(aerialCamera);
    m_spectatorCameras.push_back(aerialCamera);

    //first person camera
    ngl::Camera *fpCamera = new ngl::Camera(ngl::Vec3(0,1,0),ngl::Vec3(0,0,-6),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    fpCamera->setShape(45,(float)720.0/576.0,0.05,m_far,ngl::PERSPECTIVE);
    m_allCameras.push_back(fpCamera);
    m_FPCameras.push_back(fpCamera);

    //side camera
    ngl::Camera *cameraFromTheSide = new ngl::Camera(ngl::Vec3(-10,0,0),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    cameraFromTheSide->setShape(45,(float)720.0/576.0,0.05,m_far,ngl::PERSPECTIVE);
    m_allCameras.push_back(cameraFromTheSide);
    m_spectatorCameras.push_back(cameraFromTheSide);

    //special back camera
    m_backCamera = new ngl::Camera(ngl::Vec3(0,1,0),ngl::Vec3(0,0,6),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    m_backCamera->setShape(45,(float)720.0/576.0,0.05,m_far,ngl::PERSPECTIVE);
    m_FPCameras.push_back(m_backCamera);
}

void CameraManager::setTarget(Object *_target)
{
    m_target = _target;
}

ngl::Camera* CameraManager::getFirstCamera()
{
    assert(m_allCameras.size()!=0);
    return m_allCameras[0];
}

ngl::Camera* CameraManager::getCurrentCamera()
{
    assert(m_indexCurrentCamera>=0 && m_indexCurrentCamera<m_allCameras.size());
    return m_allCameras[m_indexCurrentCamera];
}

ngl::Camera* CameraManager::getBackCamera()
{
    assert(m_backCamera!=NULL);
    return m_backCamera;
}

ngl::Camera* CameraManager::getNextCamera()
{
    assert(m_indexCurrentCamera>=0 && m_indexCurrentCamera<m_allCameras.size());
    if (++m_indexCurrentCamera==m_allCameras.size())
            m_indexCurrentCamera = 0;
    return m_allCameras[m_indexCurrentCamera];
}

void CameraManager::addCamera(ngl::Camera* _cam)
{
    m_allCameras.push_back(_cam);
    m_spectatorCameras.push_back(_cam);
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


