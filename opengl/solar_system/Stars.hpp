//
// Stars.hpp
// SolarSystem
//

#ifndef __STARS_HPP__
#define __STARS_HPP__

#include <GL/glut.h>

class Star {
public:
    GLfloat _radius;
    GLfloat _speed, _selfSpeed;
    GLfloat _distance;
    GLfloat _rgbColor[4];

    Star *_parentStar;
    Star(GLfloat radius, GLfloat distantce, GLfloat speed, GLfloat selfSpeed,
         Star *parentStar);
    void drawStar();
    virtual void draw() {
        drawStar();
    }
    virtual void update(long timeSpan);

protected:
    GLfloat _alphaSelf, _alpha;
};

class Planet : public Star {
public:
    Planet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed,
           Star *parentStar, GLfloat rgbColor[3]);
    void drawPlanet();
    virtual void draw() {
        drawPlanet();
        drawStar();
    }
};

class LightPlanet : public Planet {
public:
    LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed,
                GLfloat selfSpeed, Star *parentStar, GLfloat rgbColor[3]);
    void drawLight();
    virtual void draw() {
        drawLight();
        drawPlanet();
        drawStar();
    }
};

#endif
