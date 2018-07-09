#pragma once

#include "tiny2-object.h"
#include "test-greeter.h"

$class_decl(TitleGreeter)

typedef TitleGreeter* (*TitleGreeterConstructor)(TitleGreeter*, const char*);
typedef void (*TitleGreeterInitVTable)(TitleGreeterVTable* v);

$class(TitleGreeter, Greeter, _parent)
  $class_property(const char*, title)
$class_end(TitleGreeter)

$mtable(TitleGreeter)
$mtable_end(TitleGreeter)

$vtable(TitleGreeter, Greeter)
$vtable_end(TitleGreeter)