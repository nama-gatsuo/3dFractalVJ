#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "CommonUtil.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void renderRM();
    
    void keyPressed(int key);
    void windowResized(int w, int h);
    
    void randomize();
    
private:
    ofShader shader;
    ofVboMesh mesh;
    
    ofEasyCam cam;
    ofFbo fbo;
    
    bool isLoop = true;
    bool isShowPanel;
    ofxPanel panel;
    ofParameter<float> t_mr2;
    ofParameter<float> t_fr2;
    ofParameter<float> t_fl;
    ofParameter<float> t_scale;
    ofParameter<float> t_rep;
    ofParameter<ofVec3f> t_offset;
    
    SmoothValue mr2;
    SmoothValue fr2;
    SmoothValue fl;
    SmoothValue scale;
    SmoothValue rep;
    SmoothPoint offset;
    
    SmoothPoint cPos;
    float t;
};
