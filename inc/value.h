#ifndef SL_VALUE_H
#define SL_VALUE_H

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "st.h"

struct sl_vm;

#define SL_MAX_INT (INT_MAX / 2)
#define SL_MIN_INT (INT_MIN / 2)

typedef union slval {
    intptr_t i;
}
SLVAL;

typedef enum sl_primitive_type {
    SL_T__INVALID = 0,
    SL_T_NIL,
    SL_T_FALSE,
    SL_T_TRUE,
    SL_T_CLASS,
    SL_T_OBJECT,
    SL_T_STRING,
    SL_T_INT,
    SL_T_FLOAT,
    SL_T_BIGNUM,
    SL_T_METHOD,
    SL_T_BOUND_METHOD,
    SL_T_ARRAY,
    SL_T_DICT
}
sl_primitive_type_t;

typedef struct sl_object {
    SLVAL klass;
    sl_primitive_type_t primitive_type;
    st_table_t* instance_variables;
    st_table_t* singleton_methods;
    void* data;
}
sl_object_t;

typedef struct sl_class {
    sl_object_t base;
    SLVAL name;
    SLVAL super;
    SLVAL in;
    st_table_t* constants;
    st_table_t* class_variables;
    st_table_t* instance_methods;
    sl_object_t*(*allocator)(struct sl_vm*);
}
sl_class_t;

typedef struct sl_string {
    sl_object_t base;
    /* utf8: */
    uint8_t* buff;
    size_t buff_len;
    size_t char_len;
}
sl_string_t;

typedef struct sl_method {
    sl_object_t base;
    SLVAL name;
    SLVAL klass;
    int is_c_func;
    int arity;
    union {
        struct {
            struct sl_vm_section* section;
            struct sl_vm_exec_ctx* parent_ctx;
        } sl;
        struct {
            SLVAL(*func)(/* vm, self, ... */);
        } c;
    } as;
}
sl_method_t;

typedef struct sl_bound_method {
    sl_method_t method;
    SLVAL self;
}
sl_bound_method_t;

#define SL_IS_INT(val) ((val).i & 1)

int
sl_get_int(SLVAL val);

sl_object_t*
sl_get_ptr(SLVAL val);

SLVAL
sl_make_int(struct sl_vm* vm, int n);

SLVAL
sl_make_ptr(sl_object_t* ptr);

SLVAL
sl_expect(struct sl_vm* vm, SLVAL obj, SLVAL klass);

sl_primitive_type_t
sl_get_primitive_type(SLVAL val);

SLVAL
sl_allocate(struct sl_vm* vm, SLVAL klass);

int
sl_is_truthy(SLVAL val);

int
sl_hash(struct sl_vm* vm, SLVAL val);

#endif
