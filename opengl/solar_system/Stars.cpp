//
// Stars.cpp
// SolorSystem
//

#include "Stars.hpp"

#include <cmath>
#define PI 3.1415926535

Star::Star(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed,
           Star *parentStar)
    : _radius(radius),
      _distance(distance),
      _speed(speed),
      _selfSpeed(selfSpeed),
      _parentStar(parentStar) {
    for (int i = 0; i < 4; ++i)
        this->_rgbColor[i] = 1.0f;
    if (_speed > 0)
        this->_speed = 360.0f / _speed;
    else
        this->_speed = 0.0f;
}

void Star::drawStar() {
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);

    int n = 1440;

    // save
    glPushMatrix();
    {
        // satallite
        if (_parentStar != nullptr && _parentStar->_distance > 0) {
            glRotatef(_parentStar->_alpha, 0, 0, 1);
            glTranslatef(_parentStar->_distance, 0.0, 0.0);
        }
        // orbit-draw
        glBegin(GL_LINES);
        for (int i = 0; i < n; ++i)
            glVertex2f(_distance * cos(2 * PI * i / n),
                       _distance * sin(2 * PI * i / n));
        glEnd();
        // com-rotate
        glRotatef(_alpha, 0, 0, 1);
        glTranslatef(_distance, 0.0, 0.0);
        // self-rotate
        glRotatef(_alphaSelf, 0, 0, 1);
        // planet-color-draw
        glColor3f(_rgbColor[0], _rgbColor[1], _rgbColor[2]);
        glutSolidSphere(_radius, 40, 32);
    }
    // recovery
    glPopMatrix();
}

void Star::update(long timeSpan) {
    _alpha += timeSpan * _speed;  // com-rotate-angle
    _alphaSelf += _selfSpeed;     // self-rotate-angle
}

Planet::Planet(GLfloat radius, GLfloat distance, GLfloat speed,
               GLfloat selfSpeed, Star *parentStar, GLfloat rgbColor[])
    : Star(radius, distance, speed, selfSpeed, parentStar) {
    for (int i = 0; i < 3; ++i)
        _rgbColor[i] = rgbColor[i];
    _rgbColor[3] = 1.0f;
}

void Planet::drawPlanet() {
    GLfloat mat_ambient[] = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_diffuse[] = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_specular[] = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_emission[] = {_rgbColor[0], _rgbColor[1], _rgbColor[2],
                              _rgbColor[3]};
    GLfloat mat_shininess = 90.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

LightPlanet::LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed,
                         GLfloat selfSpeed, Star *parentStar,

                         GLfloat rgbColor[])
    : Planet(radius, distance, speed, selfSpeed, parentStar, rgbColor) {
    // TODO:
}

void LightPlanet::drawLight() {
    GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
