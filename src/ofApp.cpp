#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    windowResized(ofGetWidth(), ofGetHeight());
    
    shader.load("shader/shader");
    shader.begin();
    shader.setUniform2f("size", ofGetWidth(), ofGetHeight());
    shader.end();
    
    panel.setup();
    panel.add(t_mr2.set("minRadius2",0.1, 0.01, 2.0));
    panel.add(t_fr2.set("fixedRadius2", 0.9, 0.01, 3.0));
    panel.add(t_fl.set("foldingLimit", 0.9, 0.01, 3.0));
    panel.add(t_scale.set("scale", -3.12, -5.0, 5.0));
    panel.add(t_rep.set("repeat", 0.0, 0.0, 8.0));
    panel.add(t_offset.set("offset", ofVec3f(0.5), ofVec3f(-2.0), ofVec3f(2.0)));
    
    t = 0.0;
    cPos.to(cam.getPosition()*0.1);
}

//--------------------------------------------------------------
void ofApp::update(){
    //t += dt.get();
    
    cPos.update();
    cam.setPosition(cPos);
    cam.begin();
    cam.end();
    
    mr2.to(t_mr2.get()); mr2.update();
    fr2.to(t_fr2.get()); fr2.update();
    fl.to(t_fl.get()); fl.update();
    scale.to(t_scale.get()); scale.update();
    rep.to(t_rep.get()); rep.update();
    
    offset.to(t_offset); offset.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    shader.begin();
    shader.setUniform3f("cp", cam.getPosition());
    shader.setUniform1f("minRadius2", mr2.get());
    shader.setUniform1f("fixedRadius2", fr2.get());
    shader.setUniform1f("foldingLimit", fl.get());
    shader.setUniform1f("scale", scale.get());
    shader.setUniform1f("rep", rep.get());
    shader.setUniform3f("offset", offset);
    
    mesh.draw();
    shader.end();
    
    panel.draw();
    //ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 600, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == ' ') {
        randomize();
    } else if (key == 'f') {
        ofToggleFullscreen();
    }
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    mesh.clearVertices();
    mesh.clearTexCoords();

    mesh.addVertex(ofVec3f(0, 0, 0));
    mesh.addTexCoord(ofVec2f(0, ofGetHeight()));
    mesh.addVertex(ofVec3f(0, ofGetHeight(), 0));
    mesh.addTexCoord(ofVec2f(0, 0));
    mesh.addVertex(ofVec3f(ofGetWidth(), 0, 0));
    mesh.addTexCoord(ofVec2f(ofGetWidth(), ofGetHeight()));
    mesh.addVertex(ofVec3f(ofGetWidth(), ofGetHeight(), 0));
    mesh.addTexCoord(ofVec2f(ofGetWidth(), 0));
    
    shader.begin();
    shader.setUniform2f("size", ofGetWidth(), ofGetHeight());
    shader.end();
}

void ofApp::randomize() {
    ofVec3f v = ofVec3f(ofRandom(.0, 1.0),ofRandom(.0, 1.0),ofRandom(.0, 1.0));
    v.normalize();
    v *= ofRandom(7.0, 13.0);
    cPos.to(ofPoint(v.x, v.y, v.z));
    
    t_mr2.set(ofRandom(0.0, 0.5));
    t_fr2.set(ofRandom(0.8, 2.5));
    t_fl.set(ofRandom(0.5, 1.0));
    t_scale.set(ofRandom(-3.0, -2.5));
    t_offset.set(ofVec3f(ofRandom(-1.0, 1.0)));
}

