#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include <stdlib.h>
#include <vector>


using namespace std;
const float width = 640.0;
const float height = 480.0;
const float deltat = .10f;
const int fps = 40;
bool showPolygon = true;

typedef struct t_vec2f {
	float x;	// Posisi X
	float y;	// Posisi Y

	t_vec2f(const t_vec2f& initPos) : x(initPos.x), y(initPos.y) {}
	t_vec2f(float initX, float initY) : x(initX), y(initY) {}

	t_vec2f* operator +=(const t_vec2f& o) {
		this->x += o.x;
		this->y += o.y;
		return this;
	}

	t_vec2f operator *(float o) {
		return t_vec2f(this->x * o, this->y * o);
	}
} vec2f;


class Point {
public:
	vec2f pos;
	vec2f speed;

	Point(vec2f initPos, vec2f initSpeed) : pos(initPos), speed(initSpeed) {}

	void draw() {
		// Gambar point disini
		glBegin(GL_POINTS);
		glVertex2f(pos.x, pos.y);
		glEnd();
	}

	void update() {
		// Update posisi, update speed, dan mantul disini
		pos.x += speed.x;
		if (pos.x > width - deltat) {
			speed.x = -speed.x;
		}
		if (pos.x < -width + deltat) {
			speed.x = abs(speed.x);
		}
		pos.y += speed.y;
		if (pos.y >= height - deltat) {
			speed.y = -speed.y;
		}
		if (pos.y <= -height + deltat) {
			speed.y = abs(speed.y);
		}
	}

};

vector <Point> points;

void display() {
	glPointSize(5.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, .0, .0);
	if (showPolygon) {
		glBegin(GL_POLYGON);
		for (auto& point : points) {
			glVertex2f(point.pos.x, point.pos.y);
		}
		glEnd();
	}
	glColor3d(1.0, 1.0, 1.0);
	for (auto& point : points) {
		point.draw();
	}


	glutSwapBuffers();
}


void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / fps, timer, 0);
	for (auto& point : points) {
		point.update();
	}

}


void myinit() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-640.0, 640, -480, 480);

	vec2f center(0.0f, 0.0f);
	vec2f speed[] = { vec2f(10.0f,0.0f), vec2f(0.0f,10.0f), vec2f(10.0f,10.0f) };

	//declare points here
	points.push_back(Point(center, speed[0]));
	points.push_back(Point(center, speed[1]));
	points.push_back(Point(center, speed[2]));
}

void onLeftMouseClicked(int x, int y) {
	cout << "mouse diklik pada (" << x << "," << y << ")" << endl;
}

void mouseHandler(int button, int state, int x, int y) {
	if (!button && !state) {
		onLeftMouseClicked(x, y);
	}
}

void keyboardHandler(unsigned char key, int x, int y) {
	cout << "Tombol " << key << " Ditekan" << endl;
	if (key == ' ') {
		showPolygon = !showPolygon;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Animasi Epic");
	glutDisplayFunc(display);

	glutMouseFunc(mouseHandler);
	glutKeyboardFunc(keyboardHandler);
	myinit();
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}