#define _GNU_SOURCE

#include "tiny2-object.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Allocator
 */

TObject* to_new_sz(size_t sz, const char* name) {
  TObject* self = malloc(sz);
  if (!self) {
    char* err;
    asprintf(&err, "to_new_sz(%zu, %s)", sz, name);
    perror(err);
    free(err);
    exit(1);
  }
  return self;
}

/*
 * TObject
 */

static TObject* tobject_constructor(TObject* self);
static void tobject_destructor(TObject* self);
static void tobject_init_vtable(TObjectVTable* v);
static void tobject_ref(TObject* self);
static void tobject_unref(TObject* self);

TO_MTABLE_DEFINE(TObject, tobject_constructor, tobject_destructor, tobject_init_vtable)
  TO_MTABLE_DEFINE_METHOD(TObjectRef, ref, tobject_ref)
  TO_MTABLE_DEFINE_METHOD(TObjectRef, unref, tobject_unref)
TO_MTABLE_DEFINE_END(TObject)

TObjectVTable TObject_vtable = {
  ._initialized = false,
};

static TObject* tobject_constructor(TObject* self) {
  TO_SETUP(TObject, self, tobject_destructor);
  self->refcount = 1;
  return self;
}

static void tobject_destructor(TObject* self) {}

static void tobject_init_vtable(TObjectVTable* v) {
  v->_initialized = true;
}

static void tobject_ref(TObject* self) {
  ++(self->refcount);
}

static void tobject_unref(TObject* self) {
  --(self->refcount);
  if (self->refcount <= 0) {
    self->top_destructor(self);
    free(self);
  }
}