#include "test-greeter.h"

#include <stdio.h>

static Greeter* greeter_constructor(Greeter* self);
static void greeter_destructor(Greeter* self);
static void greeter_init_vtable(GreeterVTable* v);
static void greeter_greet(Greeter* self, const char* who);
static void greeter_vgreet(Greeter* self, const char* who);

TO_MTABLE_DEFINE(Greeter, greeter_constructor, greeter_destructor, greeter_init_vtable)
  TO_MTABLE_DEFINE_METHOD(GreeterGreet, greet, greeter_greet)
TO_MTABLE_DEFINE_END(Greeter)

TO_VTABLE_DEFINE(Greeter)
  TO_VTABLE_DEFINE_METHOD(GreeterVGreet, vgreet)
TO_VTABLE_DEFINE_END(Greeter)

static Greeter* greeter_constructor(Greeter* self) {
  TO_INIT(TObject, self);
  TO_SETUP(Greeter, self, greeter_destructor);
  return self;
}

static void greeter_init_vtable(GreeterVTable* v) {
  TO_VTABLE_INIT(v, Greeter, TObject);
  TO_VTABLE_SET(v, Greeter, GreeterVGreet, vgreet, greeter_vgreet);
}

static void greeter_destructor(Greeter* self) {}

static void greeter_greet(Greeter* self, const char* who) {
  printf("Hello, %s\n", who);
}

static void greeter_vgreet(Greeter* self, const char* who) {
  printf("Hello, %s\n", who);
}