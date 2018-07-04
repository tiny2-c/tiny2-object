#include "test-titlegreeter.h"

#include <stdio.h>

static TitleGreeter* titlegreeter_constructor(TitleGreeter* self, const char* title);
static void titlegreeter_destructor(TitleGreeter* self);
static void titlegreeter_init_vtable(TitleGreeterVTable* v);
static void titlegreeter_vgreet(TitleGreeter* self, const char* who);

TO_MTABLE_DEFINE(TitleGreeter, titlegreeter_constructor, titlegreeter_destructor, titlegreeter_init_vtable)
TO_MTABLE_DEFINE_END(TitleGreeter)

TO_VTABLE_DEFINE(TitleGreeter)
TO_VTABLE_DEFINE_END(TitleGreeter)

static TitleGreeter* titlegreeter_constructor(TitleGreeter* self, const char* title) {
  TO_SETUP(TitleGreeter, self, titlegreeter_destructor);
  TO_INIT(Greeter, self);
  self->title = title;
  return self;
}

static void titlegreeter_destructor(TitleGreeter* self) {}

static void titlegreeter_init_vtable(TitleGreeterVTable* v) {
  TO_VTABLE_INIT(v, TitleGreeter, Greeter);
  TO_VTABLE_SETP(v, TitleGreeter, Greeter, GreeterVGreet, vgreet, titlegreeter_vgreet);
}

static void titlegreeter_vgreet(TitleGreeter* self, const char* who) {
  printf("Hello, %s%s\n", self->title, who);
}