#pragma once

#include <stdbool.h>
#include <stddef.h>

/*
 * Macros
 */ 

#define TO_CLASS_DECL(T)                  \
  typedef struct T ## MTable T ## MTable; \
  typedef struct T ## VTable T ## VTable; \
  typedef struct T T;

#define TO_CLASS(T, P, PN) \
  typedef struct T {       \
    P PN;                  \
    T ## VTable * _vtable;

#define TO_CLASS_WITH_PRIVATE(T, P, PN)       \
  typedef struct T ## MTable T ## MTable;     \
  typedef struct T ## _private T ## _private; \
  typedef struct T {                          \
    P PN;                                     \
    T ## _private * _private;                 \
    T ## VTable * _vtable;

#define TO_CLASS_PROPERTY(T, n) \
  T n;

#define TO_CLASS_END(T) \
  } T;

#define TO_MTABLE(T)                 \
  typedef struct T ## MTable {       \
    T ## Constructor _constructor; \
    TObjectDestructor _destructor;   \
    T ## InitVTable _init_vtable;  \

#define TO_MTABLE_METHOD(T, f) \
  T f;

#define TO_MTABLE_END(T) \
  } T ## MTable; \
  extern T ## MTable T ## _mtable;

#define TO_MTABLE_DEFINE(T, C, D, V)       \
  T ## MTable T ## _mtable = {             \
    ._constructor = (T ## Constructor) C,  \
    ._destructor  = (TObjectDestructor) D, \
    ._init_vtable = (T ## InitVTable) V,   \

#define TO_MTABLE_DEFINE_METHOD(T, n, f) \
  .n = (T) f,

#define TO_MTABLE_DEFINE_END(T) \
  };

#define TO_VTABLE(T, P)        \
  typedef struct T ## VTable { \
    P ## VTable _parent;       \
    bool _initialized;

#define TO_VTABLE_METHOD(T, f) \
  T f;

#define TO_VTABLE_END(T) \
  } T ## VTable;        \
  extern T ## VTable T ## _vtable; 

#define TO_VTABLE_DEFINE(T)    \
  T ## VTable T ## _vtable = { \
    ._initialized = false,

#define TO_VTABLE_DEFINE_METHOD(T, n) \
  .n = (T) NULL,

#define TO_VTABLE_DEFINE_END(T) \
  };

#define TO_VTABLE_INIT(v, T, P)                                                            \
  if (!(((P ## VTable *) v)->_initialized)) (P ## _mtable)._init_vtable((P ## VTable*) v); \
  v->_initialized = true;

#define TO_VTABLE_INHERIT(v, T, P, n) \
  ((P ## VTable) *v).n = (P ## VTable).n; \

#define TO_VTABLE_SET(v, T, M, n, m) \
  v->n = (M) m;

#define TO_VTABLE_SETP(v, T, P, M, n, m) \
  ((P ## VTable *) (v))->n = (M) m;

#define TO_SETUP(T, o, D)                                 \
  ((TObject*) o)->top_destructor = (TObjectDestructor) D; \
  o->_vtable = &(T ## _vtable);                           \
  if (!((T ## _vtable)._initialized)) { TO(T, o)->_init_vtable(&(T ## _vtable)); }

#define TO_DESTROY_PARENT(P, s) \
  (P ## _mtable)._destructor((TObject*) s);

#define TO_NEW(T, ...) \
  (T*) TO_INIT(T, to_new_sz(sizeof(T), #T), ##__VA_ARGS__)

#define TO_INIT(T, o, ...) \
  (T ## _mtable)._constructor((T*) o, ##__VA_ARGS__)

#define TO(T, o) (&(T ## _mtable))

#define TO_CALL(T, o, m, ...) \
  TO(T, o)->m((T*) (o), ##__VA_ARGS__)

#define TOV(T, o) ((T ## VTable*) (o->_vtable))

#define TOV_CALL(T, o, m, ...) \
  TOV(T, o)->m((T*) (o), ##__VA_ARGS__)

#define TO_REF(o) TO_CALL(TObject, o, ref);
#define TO_UNREF(o) TO_CALL(TObject, o, unref);

#ifndef TINY2_NO_SHORTCUTS
  #define $CLASS_DECL TO_CLASS_DECL
  #define $class_decl TO_CLASS_DECL

  #define $CLASS TO_CLASS
  #define $class TO_CLASS

  #define $CLASS_WITH_PRIVATE TO_CLASS_WITH_PRIVATE
  #define $class_with_private TO_CLASS_WITH_PRIVATE

  #define $CLASS_PROPERTY TO_CLASS_PROPERTY
  #define $class_property TO_CLASS_PROPERTY

  #define $CLASS_END TO_CLASS_END
  #define $class_end TO_CLASS_END 

  #define $MTABLE TO_MTABLE
  #define $mtable TO_MTABLE

  #define $MTABLE_METHOD TO_MTABLE_METHOD
  #define $mtable_method TO_MTABLE_METHOD

  #define $MTABLE_END TO_MTABLE_END
  #define $mtable_end TO_MTABLE_END

  #define $MTABLE_DEFINE TO_MTABLE_DEFINE
  #define $mtable_define TO_MTABLE_DEFINE

  #define $MTABLE_DEFINE_METHOD TO_MTABLE_DEFINE_METHOD
  #define $mtable_define_method TO_MTABLE_DEFINE_METHOD
  
  #define $MTABLE_DEFINE_END TO_MTABLE_DEFINE_END
  #define $mtable_define_end TO_MTABLE_DEFINE_END

  #define $VTABLE TO_VTABLE
  #define $vtable TO_VTABLE

  #define $VTABLE_METHOD TO_VTABLE_METHOD
  #define $vtable_method TO_VTABLE_METHOD

  #define $VTABLE_END TO_VTABLE_END
  #define $vtable_end TO_VTABLE_END

  #define $VTABLE_DEFINE TO_VTABLE_DEFINE
  #define $vtable_define TO_VTABLE_DEFINE

  #define $VTABLE_DEFINE_METHOD TO_VTABLE_DEFINE_METHOD
  #define $vtable_define_method TO_VTABLE_DEFINE_METHOD

  #define $VTABLE_DEFINE_END TO_VTABLE_DEFINE_END
  #define $vtable_define_end TO_VTABLE_DEFINE_END

  #define $VTABLE_INIT TO_VTABLE_INIT
  #define $vtable_init TO_VTABLE_INIT

  #define $VTABLE_INHERIT TO_VTABLE_INHERIT
  #define $vtable_inherit TO_VTABLE_INHERIT

  #define $VTABLE_SET TO_VTABLE_SET
  #define $vtable_set TO_VTABLE_SET

  #define $VTABLE_SETP TO_VTABLE_SETP
  #define $vtable_setp TO_VTABLE_SETP

  #define $SETUP TO_SETUP
  #define $setup TO_SETUP

  #define $DESTROY_PARENT TO_DESTROY_PARENT
  #define $destroy_parent TO_DESTROY_PARENT

  #define $NEW TO_NEW
  #define $new TO_NEW
  
  #define $INIT TO_INIT
  #define $init TO_INIT

  #define $ TO_CALL
  #define $$ TOV_CALL

  #define $REF TO_REF
  #define $ref TO_REF
  
  #define $UNREF TO_UNREF
  #define $unref TO_UNREF
#endif

/*
 * TObject
 */

TO_CLASS_DECL(TObject);

typedef TObject* (*TObjectConstructor)(TObject*);
typedef void (*TObjectDestructor)(TObject*);
typedef void (*TObjectInitVTable)(TObjectVTable*);
typedef void (*TObjectRef)(TObject*);
typedef void (*TObjectUnref)(TObject*);

TO_CLASS(TObject, int, refcount)
  TO_CLASS_PROPERTY(bool, dying)
  TO_CLASS_PROPERTY(TObjectDestructor, top_destructor)
TO_CLASS_END(TObject)
TO_MTABLE(TObject)
  TO_MTABLE_METHOD(TObjectRef, ref)
  TO_MTABLE_METHOD(TObjectRef, unref)
TO_MTABLE_END(TObject)
typedef struct TObjectVTable {
  bool _initialized;
} TObjectVTable;
extern TObjectVTable TObject_vtable; 

/*
 * Allocator
 */

TObject* to_new_sz(size_t sz, const char* name);
TObject* to_init(void* obj);