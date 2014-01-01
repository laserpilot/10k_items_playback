#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    //Allocate the FBO's that will be written into
    for (int i=0; i<12; i++) {
        frameStore[i].allocate(1024,768,GL_RGBA);
        
        frameStore[i].begin();
        ofClear(0, 0, 0, 0);
        frameStore[i].end();
    }
    
    movie.loadMovie("/Users/laser/Desktop/10000 items HD_60fps.mov");
    movie.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int ranFbo = ofRandom(0,11);
    frameStore[ranFbo].begin();
    ofClear(0,0,0);
    movie.draw(0, 0, 1024, 768);
    frameStore[ranFbo].end();
    
    for(int i=0; i<12; i++){
        frameStore[i].draw(i*(ofGetWidth()/12), 0, ofGetWidth()/12, .75*ofGetWidth()/12);
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
