#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    delayStart(30);
    
    sender.setup(HOST, PORT);
    
    text_x = 50;
    text_y = 0;
    
    curr_n = 0;
    
    ttf.load("mono.ttf", 6);
    
    ofFile file("test_buoy-1500.json");
    
    if(file.exists()){
        file >> jsn;
    }
}

//--------------------------------------------------------------
void ofApp::drawSensorData(){
    
    ofSetColor(255);
    
    text_y = 0;
    //cout << jsn.size() << endl;
    
    
    
    ofJson buoy = jsn[curr_n];
    
    //for(auto & buoy: jsn){
        //cout << "/////////////////////////////////////////////" << endl;
        text_x = 50;
        text_y += 275;
        
        ofSetColor(255);
        
        ofPushMatrix();
        ofTranslate(text_x, text_y);
        ofRotateZDeg(-90);
        ttf.drawString(buoy["name"], 0, 0);
        ofPopMatrix();
        
        //cout << buoy["name"] << endl; //this is the date / time
        for (auto & data: buoy["data"]){
            // should just be one thing at this level
            for (auto & sensor: data){
                
                ofPushMatrix();
                ofTranslate(text_x += 22, text_y);
                ofRotateZDeg(-90);
                ttf.drawString(sensor["name"], 0, 0);
                ttf.drawString(sensor["value"], -35, 0);
                
                if(sensor["unit"] == "Degree"){
                    ofTranslate(-50, 0);
                    ofRotateZDeg(ofToFloat(sensor["value"]));
                    ofDrawRectangle(0, 0, -200, -12 );
                } else {
                    ofDrawRectangle(-50, 0, -ofToFloat(sensor["value"]), -12 );
                }
                ofPopMatrix();
                //cout << sensor["name"] << + " :: " << sensor["value"] << endl;
            }
        }
    
    curr_n++;
    if(curr_n >= jsn.size()){
        curr_n = 0;
    }
    cout << curr_n << endl;
    //}
}

//--------------------------------------------------------------
void ofApp::delayStart(float s){
    count = 0;
    delay_time = s;
}

//--------------------------------------------------------------
void ofApp::delayTimer(){
    count++;
    if(count > delay_time){
        delayFire();
        count = 0;
    }
}

//--------------------------------------------------------------
void ofApp::delayFire(){
    cout << "delay fire" << endl;

    
    wind = floor(ofRandom(80,89));
    temp = floor(ofRandom(90,99));
    ph = floor(ofRandom(100,109));
    humidity = floor(ofRandom(110,119));
    rain = floor(ofRandom(120,129));
    
    
    sendVals();
}

//--------------------------------------------------------------
void ofApp::sendVals(){
    ofxOscMessage pd;
    pd.setAddress("/buoy");
    pd.addFloatArg(wind);
    pd.addFloatArg(temp);
    pd.addFloatArg(ph);
    pd.addFloatArg(humidity);
    pd.addFloatArg(rain);
    sender.sendMessage(pd);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawSensorData();
    delayTimer();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
