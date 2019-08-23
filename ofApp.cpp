#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	
	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);

	for (char c = 'A'; c <= 'Z'; c++) {

		this->chara_path.push_back(font.getCharacterAsPoints(c, true, false));
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofNoFill();

	auto outer = 0;
	for (auto radius = 80; radius < ofGetWidth(); radius++) {

		auto deg_span = 14;
		auto font_size = (2 * PI * radius / 360) * deg_span;

		if (outer < radius - font_size * 0.5) {

			ofGetFill() ? ofNoFill() : ofFill();
			ofRotate(ofGetFrameNum() * 0.1);
			int char_index = 0;

			for (auto deg = 0; deg < 360; deg += deg_span) {

				auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				char_index = (char_index + 1) % this->chara_path.size();

				ofPushMatrix();
				ofTranslate(location);
				ofRotate(deg + 90);

				auto outline = this->chara_path[char_index].getOutline();

				ofBeginShape();
				for (int line_index = 0; line_index < outline.size(); line_index++) {

					if (line_index != 0) { ofNextContour(true); }

					auto vertices = outline[line_index].getVertices();
					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						auto point = (vertices[vertices_index] / 100 * font_size) + glm::vec2(font_size * -0.5, font_size * 0.5);
						ofVertex(point);
					}
				}
				ofEndShape(true);

				ofPopMatrix();
			}

			outer = radius + font_size * 0.5;
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}