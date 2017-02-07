
#include "ofxTextParticleUC.h"

#pragma mark - Particle

//--------------------------------------------------------------
Particle::Particle(ofVec3f _position, ofColor _color){
    this->setup(_position, _color);
}

//--------------------------------------------------------------
void Particle::setup(ofVec3f _position, ofColor _color){
    color = _color;
    
    position = ofVec3f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(-500, 500));
    target = _position;
    radius = 1.0;
    easing = ofRandom(0.25, 0.05);
    
    position.x += ofRandom(-20, 20);
    position.y += ofRandom(-20, 20);
}

//--------------------------------------------------------------
void Particle::update(){
    position.x = position.x + (target.x - position.x) * easing;
    position.y = position.y + (target.y - position.y) * easing;
    position.z = position.z + (target.z - position.z) * easing;
}

//--------------------------------------------------------------
void Particle::draw(){
    ofSetColor(color);
    ofDrawSphere(position.x, position.y, position.z, radius);
}

//--------------------------------------------------------------
void Particle::drawNoise(){
    ofSetColor(color);
    ofVec3f noisedCenter = position + ofNoise(ofRandom(10), ofRandom(10))*5;
    ofDrawSphere(noisedCenter.x, noisedCenter.y, noisedCenter.z, radius);
}

//--------------------------------------------------------------
void Particle::addVertex(){
    ofNoFill();
    ofSetColor(color);
    ofVertex(position.x, position.y, position.z);
}

//--------------------------------------------------------------
void Particle::addVertexNoise(){
    ofNoFill();
    ofSetColor(color);
    ofVec3f noisedCenter = position + ofNoise(ofRandom(10), ofRandom(10))*5;
    ofVertex(noisedCenter.x, noisedCenter.y, noisedCenter.z);
}

//--------------------------------------------------------------
void Particle::setColor(ofColor _color){
    color = _color;
}

//--------------------------------------------------------------
void Particle::setRadius(float _radius){
    radius = _radius;
}

#pragma mark - ofxTextParticleUC

//--------------------------------------------------------------
ofxTextParticleUC::ofxTextParticleUC(string _text, ofVec3f _position, string _fontPath, int _fSize){
    this->setup(_text, _position, _fontPath, _fSize);
}

//--------------------------------------------------------------
ofxTextParticleUC::ofxTextParticleUC(const ofxTextParticleUC &obj){
    this->setup(obj.text_msg, obj.position, obj.fontPath, obj.fontSize);
}

//--------------------------------------------------------------
void ofxTextParticleUC::setup(string _text, ofVec3f _position, string _fontPath, int _fSize){
    text_msg = _text;
    position = _position;
    fontSize = _fSize;
    fontPath = _fontPath;
    
    // particle size
    particleRadius = 1.;
    ofColor particleColor= ofColor::white;
    
    font.load(fontPath, fontSize, true, true);
    
    // set word
    setWord(text_msg);
    threshould = 8.0;
    
    vector<ofTTFCharacter> str = font.getStringAsPoints(text_msg);
    
    ofVec3f textCenter = ofVec3f(font.stringWidth(text_msg)/2, 0, 0);
    ofVec3f shift = position - textCenter;
    
    for(int i = 0; i < str.size(); i ++){
        
        for(int j = 0; j < str[i].getOutline().size(); j ++){
            
            ofVec3f p0, p1, p2;
            
            for(int k = 0; k <= str[i].getOutline()[j].size(); k ++){
                ofVec3f pos;
                
                if(k < str[i].getOutline()[j].size()){
                    pos = ofVec3f(str[i].getOutline()[j].getVertices()[k]);
                }
                else{
                    pos = p0;
                }
                
                if(k == 0){
                    p0 = pos;
                    p1 = pos;
                    p2 = pos;
                }
                else{
                    float length = diffPoints(pos, p1);
                    
                    float addX = (pos.x - p1.x) * (particleRadius / length);
                    float addY = (pos.y - p1.y) * (particleRadius / length);
                    
                    for(int n = 0; n < (length / particleRadius); n ++){
                        p1 += ofVec3f(addX, addY, 0);
                        
                        float diff = diffPoints(p1, p2);
                        if(diff > threshould){
                            particles.push_back(Particle(shift + p1, particleColor));
                            p2 = p1;
                        }
                    }
                    
                    p1 = pos;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::update(){
    for(Particle &p: particles){
        p.update();
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::draw(){
    for(Particle &p: particles){
        p.draw();
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::drawNoise(){
    for(Particle &p: particles){
        p.drawNoise();
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::drawVertex(){
    ofBeginShape();
    for(int i = 0; i < particles.size(); i ++){
        particles[i].addVertex();
    }
    ofEndShape(true);
}

//--------------------------------------------------------------
void ofxTextParticleUC::drawVertexNoise(){
    ofBeginShape();
    for(int i = 0; i < particles.size(); i ++){
        particles[i].addVertexNoise();
    }
    ofEndShape(true);
}

//--------------------------------------------------------------
void ofxTextParticleUC::changeEvent(float _threshould, ofColor _color){
    particles.clear();
    
    setWord(text_msg);
    threshould = _threshould;
    
    vector<ofTTFCharacter> str = font.getStringAsPoints(text_msg);
    
    ofVec3f textCenter = ofVec3f(font.stringWidth(text_msg)/2, 0, 0);
    ofVec3f shift = position - textCenter;
    
    for(int i = 0; i < str.size(); i ++){
        
        for(int j = 0; j < str[i].getOutline().size(); j ++){
            
            ofVec3f p0, p1, p2;
            
            for(int k = 0; k <= str[i].getOutline()[j].size(); k ++){
                ofVec3f pos;
                
                if(k < str[i].getOutline()[j].size()){
                    pos = ofVec3f(str[i].getOutline()[j].getVertices()[k]);
                }
                else{
                    pos = p0;
                }
                
                if(k == 0){
                    p0 = pos;
                    p1 = pos;
                    p2 = pos;
                }
                else{
                    float length = diffPoints(pos, p1);
                    
                    float addX = (pos.x - p1.x) * (particleRadius / length);
                    float addY = (pos.y - p1.y) * (particleRadius / length);
                    
                    for(int n = 0; n < (length / particleRadius); n ++){
                        p1 += ofVec3f(addX, addY);
                        
                        float diff = diffPoints(p1, p2);
                        if(diff > threshould){
                            particles.push_back(Particle(shift + p1, _color));
                            p2 = p1;
                        }
                    }
                    p1 = pos;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::setWord(string _text){
    text_msg = _text;
}

//--------------------------------------------------------------
void ofxTextParticleUC::setColor(ofColor _color){
    for(Particle &p: particles){
        p.setColor(_color);
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::setRadius(float _radius){
    for(Particle &p: particles){
        p.setRadius(_radius);
    }
}

//--------------------------------------------------------------
void ofxTextParticleUC::setThreshould(float _threshould){
    threshould = _threshould;
}

//--------------------------------------------------------------
ofVec3f ofxTextParticleUC::getStringSize(){
    ofVec3f stringWidth;
    
    float width = font.stringHeight(text_msg);
    float height= font.stringHeight(text_msg);
    stringWidth = ofVec3f(width, height, 0);
    
    return stringWidth;
}

//--------------------------------------------------------------
float ofxTextParticleUC::diffPoints(ofVec2f p1, ofVec2f p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
