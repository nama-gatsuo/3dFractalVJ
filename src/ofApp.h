#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void windowResized(int w, int h);
private:
    ofShader shader;
    ofVboMesh mesh;
    
    ofEasyCam cam;
    
    ofxPanel panel;
    ofParameter<float> mr2;
    ofParameter<float> fr2;
    ofParameter<float> fl;
    ofParameter<float> scale;
    ofParameter<float> rep;
    ofParameter<float> dt;
    
    ofEasyCam caml;
    float t;
};
