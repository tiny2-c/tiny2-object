# tiny2-object

An OOP implementation for C.

# Building

```bash
$ git clone https://github.com/handicraftsman/tiny2-object
$ cd tiny2-object
$ mkdir build && cd build
$ make
$ sudo make install
```

# Usage sample

## Greeter class

```c
/* greeter.h */
#pragma once

#include <tiny2-object.h>

TO_CLASS_DECL(Greeter)

typedef Greeter* (*GreeterConstructor)(Greeter* self);
typedef void (*GreeterInitVTable)(GreeterVTable* v);
typedef void (*GreeterGreet)(Greeter* self, const char* who);
typedef void (*GreeterVGreet)(Greeter* self, const char* who);

TO_CLASS(Greeter, TObject, _parent)
TO_CLASS_END(Greeter)

TO_MTABLE(Greeter)
  TO_MTABLE_METHOD(GreeterGreet, greet)
TO_MTABLE_END(Greeter)

TO_VTABLE(Greeter, TObject)
  TO_VTABLE_METHOD(GreeterVGreet, vgreet)
TO_VTABLE_END(Greeter)
```

```c
/* greeter.c */
#include "greeter.h"

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
```

## TitleGreeter class

```c
/* titlegreeter.h */
#pragma once

#include <tiny2-object.h>
#include "greeter.h"

TO_CLASS_DECL(TitleGreeter)

typedef TitleGreeter* (*TitleGreeterConstructor)(TitleGreeter*, const char*);
typedef void (*TitleGreeterInitVTable)(TitleGreeterVTable* v);

TO_CLASS(TitleGreeter, Greeter, _parent)
  TO_CLASS_PROPERTY(const char*, title)
TO_CLASS_END(TitleGreeter)

TO_MTABLE(TitleGreeter)
TO_MTABLE_END(TitleGreeter)

TO_VTABLE(TitleGreeter, Greeter)
TO_VTABLE_END(TitleGreeter)
```

```c
/* titlegreeter.c */
#include "titlegreeter.h"

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
  TO_INIT(Greeter, self);
  TO_SETUP(TitleGreeter, self, titlegreeter_destructor);
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
```

## Main file

```c
/* main.c */
#include <tiny2-object.h>
#include "greeter.h"
#include "titlegreeter.h"

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
```

## Will print

```
Hello, World
Hello, Mr World
```