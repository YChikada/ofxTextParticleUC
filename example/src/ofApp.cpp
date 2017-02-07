#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 画面設定
    ofBackground(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    
    string str = "こんにちは";
    ofVec3f position = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0);
    textParticles.push_back(ofxTextParticleUC( str, position, "./font/MS PMincho.ttf", 150 ));
    
    // event
    threshould.addListener(this, &ofApp::onChangeEvent);
    
    // gui
    gui.setup();
    gui.add(threshould.setup("threshould", 10.0, 0.0, 50.0));
    gui.add(radius.setup("radius", 1.0, 0.0, 5.0));
    gui.add(color.setup("color", ofColor(255, 255, 255, 255),ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255) ));
    gui.add(bNoise.setup("bNoise", false));
    gui.add(pFlag.setup("pFlag", true));
    
}

//--------------------------------------------------------------
void ofApp::onChangeEvent(float & value){
    for(ofxTextParticleUC &t: textParticles){
        t.changeEvent(threshould, color);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(ofxTextParticleUC &t: textParticles){
        t.update();
        t.setRadius(radius);
        t.setColor(color);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < textParticles.size(); i ++){
        
        if(pFlag){
            if(bNoise){
                textParticles[i].drawNoise();
            }
            else{
                textParticles[i].draw();
            }
        }
        else{
            if(bNoise){
                textParticles[i].drawVertexNoise();
            }
            else{
                textParticles[i].drawVertex();
            }
        }
    }
    
    if(isGui){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
            
        case 'g':
            isGui = !isGui;
            break;
            
    }
}
