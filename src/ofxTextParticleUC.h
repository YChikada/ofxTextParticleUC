
#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#pragma mark - Particle

class Particle{
    
public:
    
    Particle(ofVec3f _position, ofColor _color);
    
    void setup(ofVec3f _position, ofColor _color);
    void update();
    void draw();
    void drawNoise();
    
    void addBang();
    void addVertex();
    void addVertexNoise();
    
    void setVelocity(ofVec3f _velocity);
    void setColor(ofColor _color);
    void setRadius(float _radius);
    
    void setMode(int _mode);
    
    ofVec3f position;
    ofVec3f target;
    ofVec3f velocity;
    ofVec3f acceleration;
    
    float radius;
    ofColor color;
    bool flag = true;
    float easing;
    
};

#pragma mark - ofxTextParticleUC

class ofxTextParticleUC{
    
public:
    
    ofxTextParticleUC(string _text, ofVec3f _position, string _fontPath, int _fSize);
    ofxTextParticleUC(const ofxTextParticleUC &obj);
    
    void setup(string _text, ofVec3f _position, string _fontPath, int _fSize);
    void update();
    void draw();
    void drawNoise();
    
    void drawVertex();
    void drawVertexNoise();
    
    void changeEvent(float _threshould, ofColor _color);
    void addBang();
    
    void setWord(string _text);
    void setColor(ofColor _color);
    void setRadius(float _radius);
    void setThreshould(float _threshould);
    void setMode(int _mode);
    
    ofVec3f getStringSize();
    
private:
    
    float diffPoints(ofVec2f p1, ofVec2f p2);
    
    ofVec3f position;
    
    ofxTrueTypeFontUC font;
    string fontPath;
    string text_msg;
    float fontSize;
    vector<Particle> particles;
    
    float particleRadius;
    float threshould;
};
