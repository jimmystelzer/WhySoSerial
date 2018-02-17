#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "WhySoSerial.h"

int main(int argc, char **argv) {
  Fl_Double_Window *window = make_window();
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
