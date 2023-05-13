#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	this->number_of_targets = 360;
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->target_list.clear();
	this->color_list.clear();


	for (int deg = 15; deg < 360 + 15; deg += 30) {

		for (int i = 0; i < 30; i++) {

			auto radius = ofMap(ofNoise(glm::vec3(cos(deg * DEG_TO_RAD) * 0.75, sin(deg * DEG_TO_RAD) * 0.75, i * 0.018 + ofGetFrameNum() * 0.02)), 0, 1, 80, 320);

			auto target = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			this->target_list.push_back(target + ofGetWindowSize() * 0.5);

			this->color_list.push_back(glm::vec3(1, 1, 1));
		}
	}

	/*
	for (int i = 0; i < this->number_of_targets; i++) {

		auto radius = ofRandom(200, 300);
		auto deg = ofRandom(360) + ofGetFrameNum() * ofRandom(0.25, 0.8) * (ofRandom(1) < 0.5 ? 1 : -1);

		auto target = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		this->target_list.push_back(target + ofGetWindowSize() * 0.5);

		this->color_list.push_back(glm::vec3(
			ofNoise(ofRandom(1000), ofGetFrameNum() * 0.015),
			ofNoise(ofRandom(1000), ofGetFrameNum() * 0.015),
			ofNoise(ofRandom(1000), ofGetFrameNum() * 0.015)));
	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->target_list[0].x, this->number_of_targets);
	this->shader.setUniform3fv("colors", &this->color_list[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}