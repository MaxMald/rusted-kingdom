#include "rkApplication.h"

int main()
{
  rk::Application app;

  app.prepare();
  app.run("MainScene");
  app.destroy();
}