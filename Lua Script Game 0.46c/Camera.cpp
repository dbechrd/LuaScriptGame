#include "Camera.h"
#include <iostream>

using namespace std;

Camera* Camera::pinstance = NULL;
Camera* Camera::Instance()
{
    if (pinstance == NULL)
    {
        pinstance = new Camera();
    }
    cout << "someone accessed (Camera Instance)!\n";
    return pinstance;
}

Camera::Camera()
{
    charToFollow = NULL;

    speed = 4;
    mode = CAM_FREEZE;
}

void Camera::SetChar( Character *follow )
{
    charToFollow = follow;
    speed = charToFollow->Speed();
}

void Camera::Update()
{
    switch( mode )
    {
        case CAM_FREEZE:
            break;
        case CAM_FOLLOW_CHARACTER:
            if( charToFollow != NULL )
            {
                if( rect.y - speed >= (charToFollow->Rect()->y + charToFollow->Rect()->h/2) - rect.h/2 ){
                    rect.y -= speed;
                }else if( rect.y + speed <= (charToFollow->Rect()->y + charToFollow->Rect()->h/2) - rect.h/2 ){
                    rect.y += speed;
                }
                if( rect.x - speed >= (charToFollow->Rect()->x + charToFollow->Rect()->w/2) - rect.w/2 ){
                    rect.x -= speed;
                }else if( rect.x + speed <= (charToFollow->Rect()->x + charToFollow->Rect()->w/2) - rect.w/2 ){
                    rect.x += speed;
                }
            }
            break;
        case CAM_SCRIPT_DRIVEN:
            break;
    }
}
