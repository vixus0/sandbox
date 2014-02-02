#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>

float ang = 0.0;

void spin(float s) {
  ang += s;
  if (ang>360.0) ang -= 360.0;
}

// Subclass Fl_Gl_Window for OpenGL drawing
class GlWin : public Fl_Gl_Window {
    void draw();
    void resize(int,int,int,int);
    int handle(int);

  public:
    GlWin(int x, int y, int w, int h, const char *l)
      : Fl_Gl_Window(x,y,w,h,l) {}

};

void GlWin::resize(int x, int y, int w, int h) {
  Fl_Gl_Window::resize(x,y,w,h);
}

void GlWin::draw() {
  // valid() turned on by FLTK after draw returns
  if (!valid()) {
    // set up projection and viewport
    // w() and h() for window width/height
    glViewport(0, 0, (GLsizei) w(), (GLsizei) h());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.0,0.0,0.0,0.0);
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
  
  // do drawing
#ifndef MESA
  glDrawBuffer(GL_FRONT_AND_BACK);
#endif
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(ang, 0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.25,0.25,0.0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.25,0.75,0.0);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.75,0.75,0.0);
  glEnd();
  glPopMatrix();
  glFlush();
#ifndef MESA
  glDrawBuffer(GL_BACK);
#endif
}

int GlWin::handle(int event) {
  switch(event) {
    case FL_KEYBOARD:
      if (*Fl::event_text() == 'j') spin(+2.0);
      else if (*Fl::event_text() == 'k') spin(-2.0);
      Fl::redraw();
      return 1;
    default:
      return Fl_Gl_Window::handle(event);
  } 
}

int main(int argc, char** argv) {
  //Fl::gl_visual(FL_RGB);
  GlWin* win = new GlWin(30,30,320,240,"win");
  win->show(argc,argv);
  return Fl::run();
}
