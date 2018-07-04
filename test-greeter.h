#pragma once

#include "tiny2-object.h"

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