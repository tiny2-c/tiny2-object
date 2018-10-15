#define _GNU_SOURCE

#include "tiny2-object.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * djb2
 */

uint64_t to_djb2(const char* str) {
  uint64_t hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}

/*
 * TOTree
 */

typedef struct TOTree TOTree;
typedef struct TOTree {
  TOTree* parent;
  TOTree* left;
  TOTree* right;
  uint64_t value;
} TOTree;

TOTree* to_tree_root = NULL;

static void to_dump_type_node(TOTree* n) {
  if (n == NULL)
    return;
  printf("t: %" PRIu64 " p: %" PRIu64 "\n", n->value, (n->parent != NULL) ? n->parent->value : 0);
  to_dump_type_node(n->left);
  to_dump_type_node(n->right);
}

void to_dump_type_tree() {
  to_dump_type_node(to_tree_root);
}

static void to_ensure_root() {
  if (!to_tree_root) {
    to_tree_root = (TOTree*)malloc(sizeof(TOTree));
    to_tree_root->parent = NULL;
    to_tree_root->left = NULL;
    to_tree_root->right = NULL;
    to_tree_root->value = to_djb2("TObject");
  }
}

static TOTree* to_find(uint64_t t) {
  TOTree* n = to_tree_root;
  while (true) {
    if (n == NULL)
      break;
    if (t == n->value) {
      return n;
    }
    else if (t < n->value) {
      n = n->left;
      continue;
    }
    else if (t > n->value) {
      n = n->right;
      continue;
    }
    break;
  }
  return NULL;
}

static TOTree* to_find_closest(uint64_t t) {
  TOTree* n = to_tree_root;
  while (true) {
    if (n == NULL)
      break;
    if (t == n->value) {
      return n;
    }
    else if (t < n->value) {
      if (n->left == NULL) {
        return n;
      }
      else {
        n = n->left;
        continue;
      }
    }
    else if (t > n->value) {
      if (n->right == NULL) {
        return n;
      }
      else {
        n = n->right;
        continue;
      }
    }
    break;
  }
  return NULL;
}

void to_register(uint64_t t, uint64_t p) {
  to_ensure_root();
  TOTree* c = to_find_closest(t);
  if (c != NULL && c->value == t) {
    return;
  }
  if (c == NULL) {
#ifdef _DEBUG
    printf("<to_register> c is null; weird...\n");
#endif
    return;
  }
  TOTree* nc = (TOTree*)malloc(sizeof(TOTree));
  nc->parent = to_find(p);
  nc->left = NULL;
  nc->right = NULL;
  nc->value = t;
  if (t < c->value) {
    c->left = nc;
  }
  else if (t > c->value) {
    c->right = nc;
  }
}

bool to_is(uint64_t a, uint64_t b) {
  to_ensure_root();
  TOTree* at = to_find(a);
  if (at == NULL) {
#ifdef _DEBUG
    printf("<to_is> cannot find `a` (%" PRIu64 ")\n", a);
#endif
    return false;
  }
  while (true) {
    if (at->value == b) {
      return true;
    }
    else if (at->parent == NULL) {
      return false;
    }
    at = at->parent;
  }
  return false;
}



/*
 * Allocator
 */

TObject* to_new_sz(size_t sz, const char* name) {
  TObject* self = (TObject*)malloc(sz);
  if (!self) {
    char* err;
#define FMT "to_new_sz(%zu, %s)"
#define ARGS sz, name
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    err = _strdup("to_new_sz(size_t sz, const char* name)");
#else
    asprintf(&err, FMT, ARGS);
#endif
#undef ARGS
#undef FMT
    perror(err);
    free(err);
    exit(1);
  }
  self->th = to_djb2(name);
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
  to_ensure_root();
  TO_SETUP(TObject, self, tobject_destructor);
  self->refcount = 1;
  self->dying = false;
  return self;
}

static void tobject_destructor(TObject* self) {}

static void tobject_init_vtable(TObjectVTable* v) {
  v->_initialized = true;
}

static void tobject_ref(TObject* self) {
  if (self == NULL) return;
  ++(self->refcount);
}

static void tobject_unref(TObject* self) {
  if (self == NULL) return;
  if (self->dying) return;
  --(self->refcount);
  if (self->refcount <= 0) {
    self->dying = true;
    self->top_destructor(self);
    free(self);
  }
}