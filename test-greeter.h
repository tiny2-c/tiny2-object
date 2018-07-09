#pragma once

#include "tiny2-object.h"

$class_decl(Greeter)

typedef Greeter* (*GreeterConstructor)(Greeter* self);
typedef void (*GreeterInitVTable)(GreeterVTable* v);
typedef void (*GreeterGreet)(Greeter* self, const char* who);
typedef void (*GreeterVGreet)(Greeter* self, const char* who);

$class(Greeter, TObject, _parent)
$class_end(Greeter)

$mtable(Greeter)
  $mtable_method(GreeterGreet, greet)
$mtable_end(Greeter)

$vtable(Greeter, TObject)
  $vtable_method(GreeterVGreet, vgreet)
$vtable_end(Greeter)