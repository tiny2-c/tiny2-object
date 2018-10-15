#include <stdio.h>

#include "tiny2-object.h"
#include "test-greeter.h"
#include "test-titlegreeter.h"

int main(int argc, char** argv) {
  TObject* o = $new(TObject);

  Greeter* g = $new(Greeter);
  $(Greeter, g, greet, "World");
  
  TitleGreeter* tg = $new(TitleGreeter, "Mr ");
  $$(Greeter, tg, vgreet, "World");
  
  to_dump_type_tree();

  printf("o is a TObject: %d\n", $is(o, TObject));
  printf("o is a Greeter: %d\n", $is(o, Greeter));
  printf("o is a TitleGreeter: %d\n", $is(o, TitleGreeter));

  printf("g is a TObject: %d\n", $is(g, TObject));
  printf("g is a Greeter: %d\n", $is(g, Greeter));
  printf("g is a TitleGreeter: %d\n", $is(g, TitleGreeter));

  printf("tg is a TObject: %d\n", $is(tg, TObject));
  printf("tg is a Greeter: %d\n", $is(tg, Greeter));
  printf("tg is a TitleGreeter: %d\n", $is(tg, TitleGreeter));

  $unref(o);
  $unref(g);
  $unref(tg);

  return 0;
}