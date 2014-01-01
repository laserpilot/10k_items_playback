#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    dualMovie = false;
    
    scaleMovie = 4; //this scales the fbo's and movies by a quarter. Value of 2 would halve their resolution

    //Load movies
    movie.loadMovie("/Users/laser/Desktop/10k items HD 60fps.mov");
    movie.play();
    
    //For more randomness, play 2 movies but offset one of them by a small amount of time
    if(dualMovie){
        movie2.loadMovie("/Users/laser/Desktop/10k items HD 60fps.mov");
        movie2.play();
        movie.setFrame((int)ofRandom(movie.getTotalNumFrames()));
    }
    
    
    //Allocate the FBO's that will be written into
    for (int i=0; i<12; i++) {
        for(int j=0; j<12; j++){
            frameStore[i][j].allocate(movie.getWidth()/scaleMovie,movie.getHeight()/scaleMovie,GL_RGB); //be careful here! allocating 12x12fbos which will possibly eat up allll of your video ram - we are cutting it down to half the movie size here, but it could probably be cut down to a half
            
            frameStore[i][j].begin();
            ofClear(0, 0, 0, 0);
            frameStore[i][j].end();
        }
    }
    
    numRows = 5;
    numColumns = 5;

}

//--------------------------------------------------------------
void ofApp::update(){

    movie.update();
    if(dualMovie){
        movie2.update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    for (int i =0; i<12; i++){
        int ranFbo = ofRandom(0,11);
        frameStore[i][ranFbo].begin();
        ofClear(0,0,0);
        if(dualMovie){
            //add a random frame from the first or second movie player if doing 2 movies
            if (ranFbo>6) {
                movie.draw(0, 0, movie.getWidth()/scaleMovie,movie.getHeight()/scaleMovie);
            }else{
                movie2.draw(0, 0, movie.getWidth()/scaleMovie,movie.getHeight()/scaleMovie);
            }
        }else{
           movie.draw(0, 0, movie.getWidth()/scaleMovie,movie.getHeight()/scaleMovie); 
        }

        frameStore[i][ranFbo].end();
    }

    

    int counter = 0;
    for(int i=0; i<numRows; i++){ //3 columns
        for (int j=0; j<numColumns; j++) {
            int ranFbo = ofRandom(0,11);
            frameStore[counter%12][ranFbo].draw(j*(ofGetWidth()/numColumns), i*(ofGetHeight()/numRows), ofGetWidth()/numColumns, .75*ofGetWidth()/numColumns);
            counter++;//regardless of number of columns, lets just keep this looping
        }

    }
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()),20,20);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key=='f') {
        ofToggleFullscreen();
    }
    if(key=='r'){
        movie.setFrame((int)ofRandom(movie.getTotalNumFrames()));
    }
    if (key=='1') {
        numColumns++;
        numColumns = ofClamp(numColumns, 1, 30);
    }
    if (key=='2') {
        numColumns--;
        numColumns = ofClamp(numColumns, 1, 30);
    }
    if (key=='3') {
        numRows++;
        numColumns = ofClamp(numRows, 1, 30);
    }
    if (key=='4') {
        numRows--;
        numRows = ofClamp(numRows, 1, 30);
    }

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
