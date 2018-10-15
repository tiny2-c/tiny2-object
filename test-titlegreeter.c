#include "test-titlegreeter.h"

#include <stdio.h>

static TitleGreeter* titlegreeter_constructor(TitleGreeter* self, const char* title);
static void titlegreeter_destructor(TitleGreeter* self);
static void titlegreeter_init_vtable(TitleGreeterVTable* v);
static void titlegreeter_vgreet(TitleGreeter* self, const char* who);

$mtable_define(TitleGreeter, titlegreeter_constructor, titlegreeter_destructor, titlegreeter_init_vtable)
$mtable_define_end(TitleGreeter)

$vtable_define(TitleGreeter)
$vtable_define_end(TitleGreeter)

static TitleGreeter* titlegreeter_constructor(TitleGreeter* self, const char* title) {
  $init(Greeter, self);
  $setup(TitleGreeter, self, titlegreeter_destructor);
  $reg(TitleGreeter, Greeter);
  self->title = title;
  return self;
}

static void titlegreeter_destructor(TitleGreeter* self) {
  $destroy_parent(Greeter, self);
}

static void titlegreeter_init_vtable(TitleGreeterVTable* v) {
  $vtable_init(v, TitleGreeter, Greeter);
  $vtable_setp(v, TitleGreeter, Greeter, GreeterVGreet, vgreet, titlegreeter_vgreet);
}

static void titlegreeter_vgreet(TitleGreeter* self, const char* who) {
  printf("Hello, %s%s\n", self->title, who);
}