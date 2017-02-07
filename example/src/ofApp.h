#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxTextParticleUC.h"

class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void onChangeEvent(float & value);
    
    vector<ofxTextParticleUC> textParticles;
    
    // gui
    ofxPanel gui;
    ofxFloatSlider threshould;
    ofxFloatSlider radius;
    ofxColorSlider color;
    ofxToggle bNoise;
    ofxToggle pFlag;
    
    bool isGui = true;
    
};
