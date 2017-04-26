#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.addVertex(ofVec3f(0, 0, 0));
    mesh.addTexCoord(ofVec2f(0, ofGetHeight()));
    mesh.addVertex(ofVec3f(0, ofGetHeight(), 0));
    mesh.addTexCoord(ofVec2f(0, 0));
    mesh.addVertex(ofVec3f(ofGetWidth(), 0, 0));
    mesh.addTexCoord(ofVec2f(ofGetWidth(), ofGetHeight()));
    mesh.addVertex(ofVec3f(ofGetWidth(), ofGetHeight(), 0));
    mesh.addTexCoord(ofVec2f(ofGetWidth(), 0));
    
    shader.load("shader/shader");
    shader.begin();
    shader.setUniform2f("size", ofGetWidth(), ofGetHeight());
    shader.end();
    
    panel.setup();
    panel.add(mr2.set("minRadius2",0.1, 0.01, 2.0));
    panel.add(fr2.set("fixedRadius2", 0.9, 0.01, 3.0));
    panel.add(fl.set("foldingLimit", 0.9, 0.01, 3.0));
    panel.add(scale.set("scale", -3.12, -5.0, 5.0));
    panel.add(rep.set("repeat", 0.0, 0.0, 8.0));
    panel.add(dt.set("dt", 0.01, 0.001, 0.01));
    
    t = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    t += dt.get();
    cam.begin();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    shader.begin();
    shader.setUniform1f("time", t);
    shader.setUniform3f("cp", cam.getPosition() * 0.01);
    shader.setUniform1f("minRadius2", mr2.get());
    shader.setUniform1f("fixedRadius2", fr2.get());
    shader.setUniform1f("foldingLimit", fl.get());
    shader.setUniform1f("scale", scale.get());
    shader.setUniform1f("rep", rep.get());
    
    mesh.draw();
    shader.end();
    
    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

