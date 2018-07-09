#include "tiny2-object.h"
#include "test-greeter.h"
#include "test-titlegreeter.h"

int main(int argc, char** argv) {
  TObject* o = $new(TObject);
  $unref(o);

  Greeter* g = $new(Greeter);
  $(Greeter, g, greet, "World");
  $unref(g);

  TitleGreeter* tg = $new(TitleGreeter, "Mr ");
  $$(Greeter, tg, vgreet, "World");
  $unref(tg);
  return 0;
}