#include "tiny2-object.h"
#include "test-greeter.h"
#include "test-titlegreeter.h"

int main(int argc, char** argv) {
  TObject* o = TO_NEW(TObject);
  TO_UNREF(o);

  Greeter* g = TO_NEW(Greeter);
  TO_CALL(Greeter, g, greet, "World");
  TO_UNREF(g);

  TitleGreeter* tg = TO_NEW(TitleGreeter, "Mr ");
  TOV_CALL(Greeter, tg, vgreet, "World");
  TO_UNREF(tg);
  return 0;
}