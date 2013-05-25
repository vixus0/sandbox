#include <FL/Fl.H>
#include <FL/Gl.H>

// Subclass Fl_Gl_Window for OpenGL drawing
class GlWin : public Fl_Gl_Window {
    void draw();
    int handle(int);

  public:
    GlWin(int x, int y, int w, int h, const char *l)
      : Fl_Gl_Window(x,y,w,h,l) {}

};

void GlWin::draw() {
  // valid() turned on by FLTK after draw returns
  if (!valid()) {
    // set up projection and viewport
    // w() and h() for window width/height
  }
  
  // do drawing
}

int main(int argc, char** argv) {
  GlWin* win = new GlWin(30,30,320,240,"win");
  win->show(argc,argv);
  return Fl::run();
}
