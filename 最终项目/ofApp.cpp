#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetCircleResolution(100);
    ofNoFill();
    ofSetDepthTest(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();//Let it all start from square one
    ofDrawBitmapString("This is a animation called rainbow", 20, 20);
    ofTranslate(ofGetWidth()/2,ofGetWidth()/2.5);//Adjusting the position of the image generated in the screen
    
    float time = ofGetElapsedTimef();
//    float time = ofGetSystemTimeMillis()/10;

      for(int i=0; i < 900; i+= 5 ){
        // loop Starting from 0, the step size is 3 900 divided by 5. 180 circles in total.
        ofRotateDeg (time);//Let the matrix rotate at an angle of time degrees
          
        ofSetColor (127 + 127 * sin (i*0.01+time),
                    127 + 127 *  sin (i*0.012+time),
                    127 + 127 *  sin (i*0.023+time) );
          //RGB three colour channels; sets the colour for the image
        
        ofDrawCircle(sin(i * 0.01+ time),
                     i   ,
                     i ,
                     50 + 40 * sin(i * 0.005 + time));
          //5 10 15 20 all the way to 100; repeating circles; sin function makes the image move
          
    }
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){ 
//
//}
