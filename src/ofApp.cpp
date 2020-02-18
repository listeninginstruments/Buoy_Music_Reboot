#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    ofSetBackgroundColor(0);
    
    delayStart(60);
    
    sender.setup(HOST, PORT);
    
    text_x = 50;
    text_y = 0;
    
    curr_n = 0;
    
    ttf.load("mono.ttf", 6);
    title.load("mono.ttf", 18);
    
    // Rain Events at 9/11
    
    ofFile file("test_buoy-400-rain.json");
    //ofFile file("test_buoy-1000.json");
    
    if(file.exists()){
        file >> jsn;
    }
    
    check_list[0] = "\"pH\"";
    check_list[1] = "\"Wind Speed\"";
    check_list[2] = "\"Surface Water Temperature\"";
    check_list[3] = "\"Dissolved Oxygen Saturation (DOSat) at Surface\"";
    check_list[4] = "\"Temp. at 43ft\""; //36ft sensors stops at some point in the summer
    check_list[5] = "\"DOSat at 43ft\"";
    check_list[6] = "\"Temp. at 82ft\"";
    check_list[7] = "\"DOSat at 82ft\"";
    check_list[8] = "\"Daily Rain\"";
    check_list[9] = "\"Conductivity\"";
    
   
    
}

//--------------------------------------------------------------
void ofApp::advanceData(){
    curr_n++;
   if(curr_n >= jsn.size()){
       curr_n = 0;
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
        
        title.drawString(buoy["name"], 0, 0);
        ofPopMatrix();
        
        //cout << buoy["name"] << endl; //this is the date / time
        for (auto & data: buoy["data"]){
            // should just be one thing at this level
            for (auto & sensor: data){
                
                ofPushMatrix();
                ofTranslate(text_x += 22, text_y);
                ofRotateZDeg(-90);
                
                ofSetColor(255);
                
                for(int c=0; c<how_many_values; c++){
                    if(check_list[c] == ofToString(sensor["name"]) ){
                        ofSetColor(255, 0, 255);
                    }
                }
                
               
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
                
                //cout << sensor["name"] << " :: " << sensor["value"] << endl;
                
                
                //cout << sensor["value"] << " :: " << ofToFloat(sensor["value"]) << endl;
                
                checkVals(ofToString(sensor["name"]), ofToFloat(sensor["value"]));
                
                
                
                //cout << sensor["name"] << endl;
            }
        }
    
   
    // cout << curr_n << endl;
    //}
}

//--------------------------------------------------------------
void ofApp::checkVals(std::string name, float value){
    // cout << name << " :: " << value << endl;
    for(int v=0; v < how_many_values; v++){
        if(name == check_list[v]){
           // cout << "MATCHED: " << v << "       " << name << " :: " << value << endl;
            
            // MAP HERE
            float tmp_val = value;
            
            if(ofIsStringInString(name, "pH")){
                //cout << "FOUND pH: " << value << endl;
                tmp_val = ofMap(value, 7.0, 9.0, 30, 90);
            }
            
            if(ofIsStringInString(name, "DOS")){
                //cout << "FOUND DOS: " << value << endl;
                tmp_val = ofMap(value, -1, 110, 40, 80);
            }
            
            if(ofIsStringInString(name, "Rain")){
                //cout << "FOUND Rain: " << value << endl;
                if(value >= 0.1){
                    tmp_val = ofMap(value, 0.1, 1.5, 40, 110);
                }
                //NOTE add limit in Max4Live so othing is triggered if 0 is sent
            }
            
    
            valsToSend[v] = tmp_val;
        }
    }
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
    //cout << "delay fire" << endl;

    
    //cout << "////////////////////////////////////////////////" << endl;
    advanceData();
    //cout << "////////////////////////////////////////////////" << endl;
    
    
    /*
    wind = floor(ofRandom(80,89));
    temp = floor(ofRandom(90,99));
    ph = floor(ofRandom(100,109));
    humidity = floor(ofRandom(110,119));
    rain = floor(ofRandom(120,129));
    */
    /*
    for(int i=0; i<10; i++){
        valsToSend[i] = floor(ofRandom(0,100));
    }
     */
    
    /*
    for(int i=0; i<10; i++){
        valsToSend[i] = floor(ofRandom(0,100));
    }
     */
    
    sendVals();
}

//--------------------------------------------------------------
void ofApp::sendVals(){
    
    ofxOscMessage pd;
    pd.setAddress("/buoy");
    
    for(int i=0; i<how_many_values; i++){
        //cout << "from sendVals: " << valsToSend[i] << endl;
        pd.addFloatArg(valsToSend[i]);
    }
    
    /*
    pd.addFloatArg(temp);
    pd.addFloatArg(ph);
    pd.addFloatArg(humidity);
    pd.addFloatArg(rain);
     */
    
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
