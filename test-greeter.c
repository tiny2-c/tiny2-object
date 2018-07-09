#include "test-greeter.h"

#include <stdio.h>

static Greeter* greeter_constructor(Greeter* self);
static void greeter_destructor(Greeter* self);
static void greeter_init_vtable(GreeterVTable* v);
static void greeter_greet(Greeter* self, const char* who);
static void greeter_vgreet(Greeter* self, const char* who);

$mtable_define(Greeter, greeter_constructor, greeter_destructor, greeter_init_vtable)
  $mtable_define_method(GreeterGreet, greet, greeter_greet)
$mtable_define_end(Greeter)

$vtable_define(Greeter)
  $vtable_define_method(GreeterVGreet, vgreet)
$vtable_define_end(Greeter)

static Greeter* greeter_constructor(Greeter* self) {
  $init(TObject, self);
  $setup(Greeter, self, greeter_destructor);
  return self;
}

static void greeter_init_vtable(GreeterVTable* v) {
  $vtable_init(v, Greeter, TObject);
  $vtable_set(v, Greeter, GreeterVGreet, vgreet, greeter_vgreet);
}

static void greeter_destructor(Greeter* self) {
  $destroy_parent(TObject, self);
}

static void greeter_greet(Greeter* self, const char* who) {
  printf("Hello, %s\n", who);
}

static void greeter_vgreet(Greeter* self, const char* who) {
  printf("Hello, %s\n", who);
}