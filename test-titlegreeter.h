#pragma once

#include "tiny2-object.h"
#include "test-greeter.h"

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