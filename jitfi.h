typedef char jit_sbyte;
typedef unsigned char jit_ubyte;
typedef short jit_short;
typedef unsigned short jit_ushort;
typedef int jit_int;
typedef unsigned int jit_uint;
typedef long jit_nint;
typedef unsigned long jit_nuint;
typedef long jit_long;
typedef unsigned long jit_ulong;
typedef float jit_float32;
typedef double jit_float64;
typedef long double jit_nfloat;
typedef void *jit_ptr;

/*
 * Opaque structure that represents a context.
 */
typedef struct _jit_context *jit_context_t;

/*
 * Opaque structure that represents a function.
 */
typedef struct _jit_function *jit_function_t;

/*
 * Opaque structure that represents a block.
 */
typedef struct _jit_block *jit_block_t;

/*
 * Opaque structure that represents an instruction.
 */
typedef struct _jit_insn *jit_insn_t;

/*
 * Opaque structure that represents a value.
 */
typedef struct _jit_value *jit_value_t;

/*
 * Opaque structure that represents a type descriptor.
 */
typedef struct _jit_type *jit_type_t;

/*
 * Opaque type that represents an exception stack trace.
 */
typedef struct jit_stack_trace *jit_stack_trace_t;

/*
 * Block label identifier.
 */
typedef jit_nuint jit_label_t;

/*
 * Value that represents an undefined label.
 */
#define	jit_label_undefined	((jit_label_t)~((jit_uint)0))

/*
 * Value that represents an undefined offset.
 */
#define	JIT_NO_OFFSET		(~((unsigned int)0))

/*
 * Function that is used to free user-supplied metadata.
 */
typedef void (*jit_meta_free_func)(void *data);

/*
 * Function that is used to compile a function on demand.
 * Returns zero if the compilation process failed for some reason.
 */
typedef int (*jit_on_demand_func)(jit_function_t func);

/*
 * Function that is used to control on demand compilation.
 * Typically, it should take care of the context locking and unlocking,
 * calling function's on demand compiler, and final compilation.
 */
typedef void *(*jit_on_demand_driver_func)(jit_function_t func);


/*
 * Pre-defined type descriptors.
 */
jit_type_t const jit_type_void;
jit_type_t const jit_type_sbyte;
jit_type_t const jit_type_ubyte;
jit_type_t const jit_type_short;
jit_type_t const jit_type_ushort;
jit_type_t const jit_type_int;
jit_type_t const jit_type_uint;
jit_type_t const jit_type_nint;
jit_type_t const jit_type_nuint;
jit_type_t const jit_type_long;
jit_type_t const jit_type_ulong;
jit_type_t const jit_type_float32;
jit_type_t const jit_type_float64;
jit_type_t const jit_type_nfloat;
jit_type_t const jit_type_void_ptr;

/*
 * Type descriptors for the system "char", "int", "long", etc types.
 * These are defined to one of the above values.
 */
jit_type_t const jit_type_sys_bool;
jit_type_t const jit_type_sys_char;
jit_type_t const jit_type_sys_schar;
jit_type_t const jit_type_sys_uchar;
jit_type_t const jit_type_sys_short;
jit_type_t const jit_type_sys_ushort;
jit_type_t const jit_type_sys_int;
jit_type_t const jit_type_sys_uint;
jit_type_t const jit_type_sys_long;
jit_type_t const jit_type_sys_ulong;
jit_type_t const jit_type_sys_longlong;
jit_type_t const jit_type_sys_ulonglong;
jit_type_t const jit_type_sys_float;
jit_type_t const jit_type_sys_double;
jit_type_t const jit_type_sys_long_double;

/*
 * Type kinds that may be returned by "jit_type_get_kind".
 */
#define	JIT_TYPE_INVALID			-1
#define	JIT_TYPE_VOID				0
#define	JIT_TYPE_SBYTE				1
#define	JIT_TYPE_UBYTE				2
#define	JIT_TYPE_SHORT				3
#define	JIT_TYPE_USHORT				4
#define	JIT_TYPE_INT				5
#define	JIT_TYPE_UINT				6
#define	JIT_TYPE_NINT				7
#define	JIT_TYPE_NUINT				8
#define	JIT_TYPE_LONG				9
#define	JIT_TYPE_ULONG				10
#define	JIT_TYPE_FLOAT32			11
#define	JIT_TYPE_FLOAT64			12
#define	JIT_TYPE_NFLOAT				13
#define	JIT_TYPE_MAX_PRIMITIVE		JIT_TYPE_NFLOAT
#define	JIT_TYPE_STRUCT				14
#define	JIT_TYPE_UNION				15
#define	JIT_TYPE_SIGNATURE			16
#define	JIT_TYPE_PTR				17
#define	JIT_TYPE_FIRST_TAGGED		32

/*
 * Special tag types.
 */
#define	JIT_TYPETAG_NAME			10000
#define	JIT_TYPETAG_STRUCT_NAME		10001
#define	JIT_TYPETAG_UNION_NAME		10002
#define	JIT_TYPETAG_ENUM_NAME		10003
#define	JIT_TYPETAG_CONST			10004
#define	JIT_TYPETAG_VOLATILE		10005
#define	JIT_TYPETAG_REFERENCE		10006
#define	JIT_TYPETAG_OUTPUT			10007
#define	JIT_TYPETAG_RESTRICT		10008
#define	JIT_TYPETAG_SYS_BOOL		10009
#define	JIT_TYPETAG_SYS_CHAR		10010
#define	JIT_TYPETAG_SYS_SCHAR		10011
#define	JIT_TYPETAG_SYS_UCHAR		10012
#define	JIT_TYPETAG_SYS_SHORT		10013
#define	JIT_TYPETAG_SYS_USHORT		10014
#define	JIT_TYPETAG_SYS_INT			10015
#define	JIT_TYPETAG_SYS_UINT		10016
#define	JIT_TYPETAG_SYS_LONG		10017
#define	JIT_TYPETAG_SYS_ULONG		10018
#define	JIT_TYPETAG_SYS_LONGLONG	10019
#define	JIT_TYPETAG_SYS_ULONGLONG	10020
#define	JIT_TYPETAG_SYS_FLOAT		10021
#define	JIT_TYPETAG_SYS_DOUBLE		10022
#define	JIT_TYPETAG_SYS_LONGDOUBLE	10023

/*
 * ABI types for function signatures.
 */
typedef enum
{
	jit_abi_cdecl,			/* Native C calling conventions */
	jit_abi_vararg,			/* Native C with optional variable arguments */
	jit_abi_stdcall,		/* Win32 STDCALL (same as cdecl if not Win32) */
	jit_abi_fastcall		/* Win32 FASTCALL (same as cdecl if not Win32) */

} jit_abi_t;

/*
 * External function declarations.
 */
jit_type_t jit_type_copy(jit_type_t type);
void jit_type_free(jit_type_t type);
jit_type_t jit_type_create_struct
	(jit_type_t *fields, unsigned int num_fields, int incref);
jit_type_t jit_type_create_union
	(jit_type_t *fields, unsigned int num_fields, int incref);
jit_type_t jit_type_create_signature
	(jit_abi_t abi, jit_type_t return_type, jit_type_t *params,
	 unsigned int num_params, int incref);
jit_type_t jit_type_create_pointer(jit_type_t type, int incref);
jit_type_t jit_type_create_tagged
	(jit_type_t type, int kind, void *data,
	 jit_meta_free_func free_func, int incref);
int jit_type_set_names
	(jit_type_t type, char **names, unsigned int num_names);
void jit_type_set_size_and_alignment
	(jit_type_t type, jit_nint size, jit_nint alignment);
void jit_type_set_offset
	(jit_type_t type, unsigned int field_index, jit_nuint offset);
int jit_type_get_kind(jit_type_t type);
jit_nuint jit_type_get_size(jit_type_t type);
jit_nuint jit_type_get_alignment(jit_type_t type);
jit_nuint jit_type_best_alignment(void);
unsigned int jit_type_num_fields(jit_type_t type);
jit_type_t jit_type_get_field
	(jit_type_t type, unsigned int field_index);
jit_nuint jit_type_get_offset
	(jit_type_t type, unsigned int field_index);
const char *jit_type_get_name(jit_type_t type, unsigned int index);
unsigned int jit_type_find_name(jit_type_t type, const char *name);
unsigned int jit_type_num_params(jit_type_t type);
jit_type_t jit_type_get_return(jit_type_t type);
jit_type_t jit_type_get_param
	(jit_type_t type, unsigned int param_index);
jit_abi_t jit_type_get_abi(jit_type_t type);
jit_type_t jit_type_get_ref(jit_type_t type);
jit_type_t jit_type_get_tagged_type(jit_type_t type);
void jit_type_set_tagged_type
	(jit_type_t type, jit_type_t underlying, int incref);
int jit_type_get_tagged_kind(jit_type_t type);
void *jit_type_get_tagged_data(jit_type_t type);
void jit_type_set_tagged_data
	(jit_type_t type, void *data, jit_meta_free_func free_func);
int jit_type_is_primitive(jit_type_t type);
int jit_type_is_struct(jit_type_t type);
int jit_type_is_union(jit_type_t type);
int jit_type_is_signature(jit_type_t type);
int jit_type_is_pointer(jit_type_t type);
int jit_type_is_tagged(jit_type_t type);
jit_type_t jit_type_remove_tags(jit_type_t type);
jit_type_t jit_type_normalize(jit_type_t type);
jit_type_t jit_type_promote_int(jit_type_t type);
int jit_type_return_via_pointer(jit_type_t type);
int jit_type_has_tag(jit_type_t type, int kind);

jit_context_t jit_context_create(void);
void jit_context_destroy(jit_context_t context);

void jit_context_build_start(jit_context_t context);
void jit_context_build_end(jit_context_t context);

void jit_context_set_on_demand_driver(
	jit_context_t context,
	jit_on_demand_driver_func driver);

int jit_context_set_meta
	(jit_context_t context, int type, void *data,
	 jit_meta_free_func free_data);
int jit_context_set_meta_numeric
	(jit_context_t context, int type, jit_nuint data);
void *jit_context_get_meta(jit_context_t context, int type);
jit_nuint jit_context_get_meta_numeric
	(jit_context_t context, int type);
void jit_context_free_meta(jit_context_t context, int type);

/*
 * Standard meta values for builtin configurable options.
 */
#define	JIT_OPTION_CACHE_LIMIT		10000
#define	JIT_OPTION_CACHE_PAGE_SIZE	10001
#define	JIT_OPTION_PRE_COMPILE		10002
#define	JIT_OPTION_DONT_FOLD		10003
#define JIT_OPTION_POSITION_INDEPENDENT	10004
#define JIT_OPTION_CACHE_MAX_PAGE_FACTOR	10005

/*
 * Prototype for closure functions.
 */
typedef void (*jit_closure_func)(jit_type_t signature, void *result,
                                 void **args, void *user_data);

/*
 * Opaque type for accessing vararg parameters on closures.
 */
typedef struct jit_closure_va_list *jit_closure_va_list_t;

/*
 * External function declarations.
 */
void jit_apply(jit_type_t signature, void *func,
               void **args, unsigned int num_fixed_args,
               void *return_value);
void jit_apply_raw(jit_type_t signature, void *func,
                   void *args, void *return_value);
int jit_raw_supported(jit_type_t signature);

void *jit_closure_create(jit_context_t context, jit_type_t signature,
			 jit_closure_func func, void *user_data);

jit_nint jit_closure_va_get_nint(jit_closure_va_list_t va);
jit_nuint jit_closure_va_get_nuint(jit_closure_va_list_t va);
jit_long jit_closure_va_get_long(jit_closure_va_list_t va);
jit_ulong jit_closure_va_get_ulong(jit_closure_va_list_t va);
jit_float32 jit_closure_va_get_float32(jit_closure_va_list_t va);
jit_float64 jit_closure_va_get_float64(jit_closure_va_list_t va);
jit_nfloat jit_closure_va_get_nfloat(jit_closure_va_list_t va);
void *jit_closure_va_get_ptr(jit_closure_va_list_t va);
void jit_closure_va_get_struct(jit_closure_va_list_t va, void *buf, jit_type_t type);

jit_function_t jit_block_get_function(jit_block_t block);
jit_context_t jit_block_get_context(jit_block_t block);
jit_label_t jit_block_get_label(jit_block_t block);
jit_label_t jit_block_get_next_label(jit_block_t block,
				     jit_label_t label);
jit_block_t jit_block_next(jit_function_t func,
			   jit_block_t previous);
jit_block_t jit_block_previous(jit_function_t func,
			       jit_block_t previous);
jit_block_t jit_block_from_label(jit_function_t func,
				 jit_label_t label);
int jit_block_set_meta(jit_block_t block, int type, void *data,
		       jit_meta_free_func free_data);
void *jit_block_get_meta(jit_block_t block, int type);
void jit_block_free_meta(jit_block_t block, int type);
int jit_block_is_reachable(jit_block_t block);
int jit_block_ends_in_dead(jit_block_t block);
int jit_block_current_is_dead(jit_function_t func);

jit_function_t jit_function_create
	(jit_context_t context, jit_type_t signature);
jit_function_t jit_function_create_nested
	(jit_context_t context, jit_type_t signature,
	 jit_function_t parent);
void jit_function_abandon(jit_function_t func);
jit_context_t jit_function_get_context(jit_function_t func);
jit_type_t jit_function_get_signature(jit_function_t func);
int jit_function_set_meta
	(jit_function_t func, int type, void *data,
	 jit_meta_free_func free_data, int build_only);
void *jit_function_get_meta(jit_function_t func, int type);
void jit_function_free_meta(jit_function_t func, int type);
jit_function_t jit_function_next
	(jit_context_t context, jit_function_t prev);
jit_function_t jit_function_previous
	(jit_context_t context, jit_function_t prev);
jit_block_t jit_function_get_entry(jit_function_t func);
jit_block_t jit_function_get_current(jit_function_t func);
jit_function_t jit_function_get_nested_parent(jit_function_t func);
int jit_function_compile(jit_function_t func);
int jit_function_is_compiled(jit_function_t func);
void jit_function_set_recompilable(jit_function_t func);
void jit_function_clear_recompilable(jit_function_t func);
int jit_function_is_recompilable(jit_function_t func);
int jit_function_compile_entry(jit_function_t func, void **entry_point);
void jit_function_setup_entry(jit_function_t func, void *entry_point);
void *jit_function_to_closure(jit_function_t func);
jit_function_t jit_function_from_closure
	(jit_context_t context, void *closure);
jit_function_t jit_function_from_pc
	(jit_context_t context, void *pc, void **handler);
void *jit_function_to_vtable_pointer(jit_function_t func);
jit_function_t jit_function_from_vtable_pointer
	(jit_context_t context, void *vtable_pointer);
void jit_function_set_on_demand_compiler
	(jit_function_t func, jit_on_demand_func on_demand);
jit_on_demand_func jit_function_get_on_demand_compiler(jit_function_t func);
int jit_function_apply
	(jit_function_t func, void **args, void *return_area);
int jit_function_apply_vararg
	(jit_function_t func, jit_type_t signature, void **args, void *return_area);
void jit_function_set_optimization_level
	(jit_function_t func, unsigned int level);
unsigned int jit_function_get_optimization_level
	(jit_function_t func);
unsigned int jit_function_get_max_optimization_level(void);
jit_label_t jit_function_reserve_label(jit_function_t func);
int jit_function_labels_equal(jit_function_t func, jit_label_t label, jit_label_t label2);

void jit_init(void);

int jit_uses_interpreter(void);

int jit_supports_threads(void);

int jit_supports_virtual_memory(void);

int jit_supports_closures(void);

unsigned int jit_get_closure_size(void);
unsigned int jit_get_closure_alignment(void);
unsigned int jit_get_trampoline_size(void);
unsigned int jit_get_trampoline_alignment(void);

/*
 * Descriptor for an intrinsic function.
 */
typedef struct
{
	jit_type_t		return_type;
	jit_type_t		ptr_result_type;
	jit_type_t		arg1_type;
	jit_type_t		arg2_type;

} jit_intrinsic_descr_t;

/*
 * Structure for iterating over the instructions in a block.
 * This should be treated as opaque.
 */
typedef struct
{
	jit_block_t		block;
	int				posn;

} jit_insn_iter_t;

/*
 * Flags for "jit_insn_call" and friends.
 */
#define	JIT_CALL_NOTHROW		(1 << 0)
#define	JIT_CALL_NORETURN		(1 << 1)
#define	JIT_CALL_TAIL			(1 << 2)

int jit_insn_get_opcode(jit_insn_t insn);
jit_value_t jit_insn_get_dest(jit_insn_t insn);
jit_value_t jit_insn_get_value1(jit_insn_t insn);
jit_value_t jit_insn_get_value2(jit_insn_t insn);
jit_label_t jit_insn_get_label(jit_insn_t insn);
jit_function_t jit_insn_get_function(jit_insn_t insn);
void *jit_insn_get_native(jit_insn_t insn);
const char *jit_insn_get_name(jit_insn_t insn);
jit_type_t jit_insn_get_signature(jit_insn_t insn);
int jit_insn_dest_is_value(jit_insn_t insn);

int jit_insn_label(jit_function_t func, jit_label_t *label);
int jit_insn_label_tight(jit_function_t func, jit_label_t *label);

int jit_insn_new_block(jit_function_t func);

jit_value_t jit_insn_load(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_dup(jit_function_t func, jit_value_t value);
int jit_insn_store
	(jit_function_t func, jit_value_t dest, jit_value_t value);
jit_value_t jit_insn_load_relative
	(jit_function_t func, jit_value_t value,
	 jit_nint offset, jit_type_t type);
int jit_insn_store_relative
	(jit_function_t func, jit_value_t dest,
	 jit_nint offset, jit_value_t value);
jit_value_t jit_insn_add_relative
	(jit_function_t func, jit_value_t value, jit_nint offset);
jit_value_t jit_insn_load_elem
	(jit_function_t func, jit_value_t base_addr,
	 jit_value_t index, jit_type_t elem_type);
jit_value_t jit_insn_load_elem_address
	(jit_function_t func, jit_value_t base_addr,
	 jit_value_t index, jit_type_t elem_type);
int jit_insn_store_elem
	(jit_function_t func, jit_value_t base_addr,
	 jit_value_t index, jit_value_t value);
int jit_insn_check_null(jit_function_t func, jit_value_t value);
int jit_insn_nop(jit_function_t func);

jit_value_t jit_insn_add
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_add_ovf
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sub
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sub_ovf
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_mul
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_mul_ovf
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_div
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_rem
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_rem_ieee
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_neg
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_and
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_or
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_xor
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_not
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_shl
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_shr
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ushr
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sshr
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_eq
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ne
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_lt
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_le
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_gt
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ge
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_cmpl
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_cmpg
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_to_bool
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_to_not_bool
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_acos
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_asin
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_atan
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_atan2
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ceil
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_cos
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_cosh
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_exp
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_floor
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_log
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_log10
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_pow
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_rint
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_round
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_sin
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_sinh
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_sqrt
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_tan
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_tanh
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_trunc
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_is_nan
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_is_finite
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_is_inf
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_abs
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_min
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_max
	(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sign
	(jit_function_t func, jit_value_t value1);
int jit_insn_branch
	(jit_function_t func, jit_label_t *label);
int jit_insn_branch_if
	(jit_function_t func, jit_value_t value, jit_label_t *label);
int jit_insn_branch_if_not
	(jit_function_t func, jit_value_t value, jit_label_t *label);
int jit_insn_jump_table
	(jit_function_t func, jit_value_t value,
	 jit_label_t *labels, unsigned int num_labels);
jit_value_t jit_insn_address_of
	(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_address_of_label
	(jit_function_t func, jit_label_t *label);
jit_value_t jit_insn_convert
	(jit_function_t func, jit_value_t value,
	 jit_type_t type, int overflow_check);

jit_value_t jit_insn_call
	(jit_function_t func, const char *name,
	 jit_function_t jit_func, jit_type_t signature,
	 jit_value_t *args, unsigned int num_args, int flags);
jit_value_t jit_insn_call_indirect
	(jit_function_t func, jit_value_t value, jit_type_t signature,
	 jit_value_t *args, unsigned int num_args, int flags);
jit_value_t jit_insn_call_indirect_vtable
	(jit_function_t func, jit_value_t value, jit_type_t signature,
	 jit_value_t *args, unsigned int num_args, int flags);
jit_value_t jit_insn_call_native
	(jit_function_t func, const char *name,
	 void *native_func, jit_type_t signature,
	 jit_value_t *args, unsigned int num_args, int flags);
jit_value_t jit_insn_call_intrinsic
	(jit_function_t func, const char *name, void *intrinsic_func,
	 const jit_intrinsic_descr_t *descriptor,
	 jit_value_t arg1, jit_value_t arg2);
int jit_insn_incoming_reg
	(jit_function_t func, jit_value_t value, int reg);
int jit_insn_incoming_frame_posn
	(jit_function_t func, jit_value_t value, jit_nint frame_offset);
int jit_insn_outgoing_reg
	(jit_function_t func, jit_value_t value, int reg);
int jit_insn_outgoing_frame_posn
	(jit_function_t func, jit_value_t value, jit_nint frame_offset);
int jit_insn_return_reg
	(jit_function_t func, jit_value_t value, int reg);
int jit_insn_setup_for_nested
	(jit_function_t func, int nested_level, int reg);
int jit_insn_flush_struct(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_import
	(jit_function_t func, jit_value_t value);
int jit_insn_push(jit_function_t func, jit_value_t value);
int jit_insn_push_ptr
	(jit_function_t func, jit_value_t value, jit_type_t type);
int jit_insn_set_param
	(jit_function_t func, jit_value_t value, jit_nint offset);
int jit_insn_set_param_ptr
	(jit_function_t func, jit_value_t value, jit_type_t type,
	 jit_nint offset);
int jit_insn_push_return_area_ptr(jit_function_t func);
int jit_insn_pop_stack(jit_function_t func, jit_nint num_items);
int jit_insn_defer_pop_stack
	(jit_function_t func, jit_nint num_items);
int jit_insn_flush_defer_pop
	(jit_function_t func, jit_nint num_items);
int jit_insn_return(jit_function_t func, jit_value_t value);
int jit_insn_return_ptr
	(jit_function_t func, jit_value_t value, jit_type_t type);
int jit_insn_default_return(jit_function_t func);
int jit_insn_throw(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_get_call_stack(jit_function_t func);

jit_value_t jit_insn_thrown_exception(jit_function_t func);
int jit_insn_uses_catcher(jit_function_t func);
jit_value_t jit_insn_start_catcher(jit_function_t func);
int jit_insn_branch_if_pc_not_in_range
	(jit_function_t func, jit_label_t start_label,
	 jit_label_t end_label, jit_label_t *label);
int jit_insn_rethrow_unhandled(jit_function_t func);
int jit_insn_start_finally
	(jit_function_t func, jit_label_t *finally_label);
int jit_insn_return_from_finally(jit_function_t func);
int jit_insn_call_finally
	(jit_function_t func, jit_label_t *finally_label);
jit_value_t jit_insn_start_filter
	(jit_function_t func, jit_label_t *label, jit_type_t type);
int jit_insn_return_from_filter
	(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_call_filter
	(jit_function_t func, jit_label_t *label,
	 jit_value_t value, jit_type_t type);

int jit_insn_memcpy
	(jit_function_t func, jit_value_t dest,
	 jit_value_t src, jit_value_t size);
int jit_insn_memmove
	(jit_function_t func, jit_value_t dest,
	 jit_value_t src, jit_value_t size);
int jit_insn_memset
	(jit_function_t func, jit_value_t dest,
	 jit_value_t value, jit_value_t size);
jit_value_t jit_insn_alloca
	(jit_function_t func, jit_value_t size);

int jit_insn_move_blocks_to_end
	(jit_function_t func, jit_label_t from_label, jit_label_t to_label);
int jit_insn_move_blocks_to_start
	(jit_function_t func, jit_label_t from_label, jit_label_t to_label);

int jit_insn_mark_offset
	(jit_function_t func, jit_int offset);
int jit_insn_mark_breakpoint
	(jit_function_t func, jit_nint data1, jit_nint data2);
int jit_insn_mark_breakpoint_variable
	(jit_function_t func, jit_value_t data1, jit_value_t data2);

void jit_insn_iter_init(jit_insn_iter_t *iter, jit_block_t block);
void jit_insn_iter_init_last
	(jit_insn_iter_t *iter, jit_block_t block);
jit_insn_t jit_insn_iter_next(jit_insn_iter_t *iter);
jit_insn_t jit_insn_iter_previous(jit_insn_iter_t *iter);


/*
 * Perform operations on signed 32-bit integers.
 */
jit_int jit_int_add(jit_int value1, jit_int value2);
jit_int jit_int_sub(jit_int value1, jit_int value2);
jit_int jit_int_mul(jit_int value1, jit_int value2);
jit_int jit_int_div
	(jit_int *result, jit_int value1, jit_int value2);
jit_int jit_int_rem
	(jit_int *result, jit_int value1, jit_int value2);
jit_int jit_int_add_ovf
	(jit_int *result, jit_int value1, jit_int value2);
jit_int jit_int_sub_ovf
	(jit_int *result, jit_int value1, jit_int value2);
jit_int jit_int_mul_ovf
	(jit_int *result, jit_int value1, jit_int value2);
jit_int jit_int_neg(jit_int value1);
jit_int jit_int_and(jit_int value1, jit_int value2);
jit_int jit_int_or(jit_int value1, jit_int value2);
jit_int jit_int_xor(jit_int value1, jit_int value2);
jit_int jit_int_not(jit_int value1);
jit_int jit_int_shl(jit_int value1, jit_uint value2);
jit_int jit_int_shr(jit_int value1, jit_uint value2);
jit_int jit_int_eq(jit_int value1, jit_int value2);
jit_int jit_int_ne(jit_int value1, jit_int value2);
jit_int jit_int_lt(jit_int value1, jit_int value2);
jit_int jit_int_le(jit_int value1, jit_int value2);
jit_int jit_int_gt(jit_int value1, jit_int value2);
jit_int jit_int_ge(jit_int value1, jit_int value2);
jit_int jit_int_cmp(jit_int value1, jit_int value2);
jit_int jit_int_abs(jit_int value1);
jit_int jit_int_min(jit_int value1, jit_int value2);
jit_int jit_int_max(jit_int value1, jit_int value2);
jit_int jit_int_sign(jit_int value1);

/*
 * Perform operations on unsigned 32-bit integers.
 */
jit_uint jit_uint_add(jit_uint value1, jit_uint value2);
jit_uint jit_uint_sub(jit_uint value1, jit_uint value2);
jit_uint jit_uint_mul(jit_uint value1, jit_uint value2);
jit_int jit_uint_div
	(jit_uint *result, jit_uint value1, jit_uint value2);
jit_int jit_uint_rem
	(jit_uint *result, jit_uint value1, jit_uint value2);
jit_int jit_uint_add_ovf
	(jit_uint *result, jit_uint value1, jit_uint value2);
jit_int jit_uint_sub_ovf
	(jit_uint *result, jit_uint value1, jit_uint value2);
jit_int jit_uint_mul_ovf
	(jit_uint *result, jit_uint value1, jit_uint value2);
jit_uint jit_uint_neg(jit_uint value1);
jit_uint jit_uint_and(jit_uint value1, jit_uint value2);
jit_uint jit_uint_or(jit_uint value1, jit_uint value2);
jit_uint jit_uint_xor(jit_uint value1, jit_uint value2);
jit_uint jit_uint_not(jit_uint value1);
jit_uint jit_uint_shl(jit_uint value1, jit_uint value2);
jit_uint jit_uint_shr(jit_uint value1, jit_uint value2);
jit_int jit_uint_eq(jit_uint value1, jit_uint value2);
jit_int jit_uint_ne(jit_uint value1, jit_uint value2);
jit_int jit_uint_lt(jit_uint value1, jit_uint value2);
jit_int jit_uint_le(jit_uint value1, jit_uint value2);
jit_int jit_uint_gt(jit_uint value1, jit_uint value2);
jit_int jit_uint_ge(jit_uint value1, jit_uint value2);
jit_int jit_uint_cmp(jit_uint value1, jit_uint value2);
jit_uint jit_uint_min(jit_uint value1, jit_uint value2);
jit_uint jit_uint_max(jit_uint value1, jit_uint value2);

/*
 * Perform operations on signed 64-bit integers.
 */
jit_long jit_long_add(jit_long value1, jit_long value2);
jit_long jit_long_sub(jit_long value1, jit_long value2);
jit_long jit_long_mul(jit_long value1, jit_long value2);
jit_int jit_long_div
	(jit_long *result, jit_long value1, jit_long value2);
jit_int jit_long_rem
	(jit_long *result, jit_long value1, jit_long value2);
jit_int jit_long_add_ovf
	(jit_long *result, jit_long value1, jit_long value2);
jit_int jit_long_sub_ovf
	(jit_long *result, jit_long value1, jit_long value2);
jit_int jit_long_mul_ovf
	(jit_long *result, jit_long value1, jit_long value2);
jit_long jit_long_neg(jit_long value1);
jit_long jit_long_and(jit_long value1, jit_long value2);
jit_long jit_long_or(jit_long value1, jit_long value2);
jit_long jit_long_xor(jit_long value1, jit_long value2);
jit_long jit_long_not(jit_long value1);
jit_long jit_long_shl(jit_long value1, jit_uint value2);
jit_long jit_long_shr(jit_long value1, jit_uint value2);
jit_int jit_long_eq(jit_long value1, jit_long value2);
jit_int jit_long_ne(jit_long value1, jit_long value2);
jit_int jit_long_lt(jit_long value1, jit_long value2);
jit_int jit_long_le(jit_long value1, jit_long value2);
jit_int jit_long_gt(jit_long value1, jit_long value2);
jit_int jit_long_ge(jit_long value1, jit_long value2);
jit_int jit_long_cmp(jit_long value1, jit_long value2);
jit_long jit_long_abs(jit_long value1);
jit_long jit_long_min(jit_long value1, jit_long value2);
jit_long jit_long_max(jit_long value1, jit_long value2);
jit_int jit_long_sign(jit_long value1);

/*
 * Perform operations on unsigned 64-bit integers.
 */
jit_ulong jit_ulong_add(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_sub(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_mul(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_div
	(jit_ulong *result, jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_rem
	(jit_ulong *result, jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_add_ovf
	(jit_ulong *result, jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_sub_ovf
	(jit_ulong *result, jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_mul_ovf
	(jit_ulong *result, jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_neg(jit_ulong value1);
jit_ulong jit_ulong_and(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_or(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_xor(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_not(jit_ulong value1);
jit_ulong jit_ulong_shl(jit_ulong value1, jit_uint value2);
jit_ulong jit_ulong_shr(jit_ulong value1, jit_uint value2);
jit_int jit_ulong_eq(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_ne(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_lt(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_le(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_gt(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_ge(jit_ulong value1, jit_ulong value2);
jit_int jit_ulong_cmp(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_min(jit_ulong value1, jit_ulong value2);
jit_ulong jit_ulong_max(jit_ulong value1, jit_ulong value2);

/*
 * Perform operations on 32-bit floating-point values.
 */
jit_float32 jit_float32_add
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_sub
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_mul
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_div
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_rem
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_ieee_rem
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_neg(jit_float32 value1);
jit_int jit_float32_eq(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_ne(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_lt(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_le(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_gt(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_ge(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_cmpl(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_cmpg(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_acos(jit_float32 value1);
jit_float32 jit_float32_asin(jit_float32 value1);
jit_float32 jit_float32_atan(jit_float32 value1);
jit_float32 jit_float32_atan2
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_ceil(jit_float32 value1);
jit_float32 jit_float32_cos(jit_float32 value1);
jit_float32 jit_float32_cosh(jit_float32 value1);
jit_float32 jit_float32_exp(jit_float32 value1);
jit_float32 jit_float32_floor(jit_float32 value1);
jit_float32 jit_float32_log(jit_float32 value1);
jit_float32 jit_float32_log10(jit_float32 value1);
jit_float32 jit_float32_pow
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_rint(jit_float32 value1);
jit_float32 jit_float32_round(jit_float32 value1);
jit_float32 jit_float32_sin(jit_float32 value1);
jit_float32 jit_float32_sinh(jit_float32 value1);
jit_float32 jit_float32_sqrt(jit_float32 value1);
jit_float32 jit_float32_tan(jit_float32 value1);
jit_float32 jit_float32_tanh(jit_float32 value1);
jit_float32 jit_float32_trunc(jit_float32 value1);
jit_int jit_float32_is_finite(jit_float32 value);
jit_int jit_float32_is_nan(jit_float32 value);
jit_int jit_float32_is_inf(jit_float32 value);
jit_float32 jit_float32_abs(jit_float32 value1);
jit_float32 jit_float32_min
	(jit_float32 value1, jit_float32 value2);
jit_float32 jit_float32_max
	(jit_float32 value1, jit_float32 value2);
jit_int jit_float32_sign(jit_float32 value1);

/*
 * Perform operations on 64-bit floating-point values.
 */
jit_float64 jit_float64_add
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_sub
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_mul
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_div
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_rem
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_ieee_rem
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_neg(jit_float64 value1);
jit_int jit_float64_eq(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_ne(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_lt(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_le(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_gt(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_ge(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_cmpl(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_cmpg(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_acos(jit_float64 value1);
jit_float64 jit_float64_asin(jit_float64 value1);
jit_float64 jit_float64_atan(jit_float64 value1);
jit_float64 jit_float64_atan2
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_ceil(jit_float64 value1);
jit_float64 jit_float64_cos(jit_float64 value1);
jit_float64 jit_float64_cosh(jit_float64 value1);
jit_float64 jit_float64_exp(jit_float64 value1);
jit_float64 jit_float64_floor(jit_float64 value1);
jit_float64 jit_float64_log(jit_float64 value1);
jit_float64 jit_float64_log10(jit_float64 value1);
jit_float64 jit_float64_pow
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_rint(jit_float64 value1);
jit_float64 jit_float64_round(jit_float64 value1);
jit_float64 jit_float64_sin(jit_float64 value1);
jit_float64 jit_float64_sinh(jit_float64 value1);
jit_float64 jit_float64_sqrt(jit_float64 value1);
jit_float64 jit_float64_tan(jit_float64 value1);
jit_float64 jit_float64_tanh(jit_float64 value1);
jit_float64 jit_float64_trunc(jit_float64 value1);
jit_int jit_float64_is_finite(jit_float64 value);
jit_int jit_float64_is_nan(jit_float64 value);
jit_int jit_float64_is_inf(jit_float64 value);
jit_float64 jit_float64_abs(jit_float64 value1);
jit_float64 jit_float64_min
	(jit_float64 value1, jit_float64 value2);
jit_float64 jit_float64_max
	(jit_float64 value1, jit_float64 value2);
jit_int jit_float64_sign(jit_float64 value1);

/*
 * Perform operations on native floating-point values.
 */
jit_nfloat jit_nfloat_add(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_sub(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_mul(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_div(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_rem(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_ieee_rem
	(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_neg(jit_nfloat value1);
jit_int jit_nfloat_eq(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_ne(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_lt(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_le(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_gt(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_ge(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_cmpl(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_cmpg(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_acos(jit_nfloat value1);
jit_nfloat jit_nfloat_asin(jit_nfloat value1);
jit_nfloat jit_nfloat_atan(jit_nfloat value1);
jit_nfloat jit_nfloat_atan2(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_ceil(jit_nfloat value1);
jit_nfloat jit_nfloat_cos(jit_nfloat value1);
jit_nfloat jit_nfloat_cosh(jit_nfloat value1);
jit_nfloat jit_nfloat_exp(jit_nfloat value1);
jit_nfloat jit_nfloat_floor(jit_nfloat value1);
jit_nfloat jit_nfloat_log(jit_nfloat value1);
jit_nfloat jit_nfloat_log10(jit_nfloat value1);
jit_nfloat jit_nfloat_pow(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_rint(jit_nfloat value1);
jit_nfloat jit_nfloat_round(jit_nfloat value1);
jit_nfloat jit_nfloat_sin(jit_nfloat value1);
jit_nfloat jit_nfloat_sinh(jit_nfloat value1);
jit_nfloat jit_nfloat_sqrt(jit_nfloat value1);
jit_nfloat jit_nfloat_tan(jit_nfloat value1);
jit_nfloat jit_nfloat_tanh(jit_nfloat value1);
jit_nfloat jit_nfloat_trunc(jit_nfloat value1);
jit_int jit_nfloat_is_finite(jit_nfloat value);
jit_int jit_nfloat_is_nan(jit_nfloat value);
jit_int jit_nfloat_is_inf(jit_nfloat value);
jit_nfloat jit_nfloat_abs(jit_nfloat value1);
jit_nfloat jit_nfloat_min(jit_nfloat value1, jit_nfloat value2);
jit_nfloat jit_nfloat_max(jit_nfloat value1, jit_nfloat value2);
jit_int jit_nfloat_sign(jit_nfloat value1);

/*
 * Convert between integer types.
 */
jit_int jit_int_to_sbyte(jit_int value);
jit_int jit_int_to_ubyte(jit_int value);
jit_int jit_int_to_short(jit_int value);
jit_int jit_int_to_ushort(jit_int value);
jit_int jit_int_to_int(jit_int value);
jit_uint jit_int_to_uint(jit_int value);
jit_long jit_int_to_long(jit_int value);
jit_ulong jit_int_to_ulong(jit_int value);
jit_int jit_uint_to_int(jit_uint value);
jit_uint jit_uint_to_uint(jit_uint value);
jit_long jit_uint_to_long(jit_uint value);
jit_ulong jit_uint_to_ulong(jit_uint value);
jit_int jit_long_to_int(jit_long value);
jit_uint jit_long_to_uint(jit_long value);
jit_long jit_long_to_long(jit_long value);
jit_ulong jit_long_to_ulong(jit_long value);
jit_int jit_ulong_to_int(jit_ulong value);
jit_uint jit_ulong_to_uint(jit_ulong value);
jit_long jit_ulong_to_long(jit_ulong value);
jit_ulong jit_ulong_to_ulong(jit_ulong value);

/*
 * Convert between integer types with overflow detection.
 */
jit_int jit_int_to_sbyte_ovf(jit_int *result, jit_int value);
jit_int jit_int_to_ubyte_ovf(jit_int *result, jit_int value);
jit_int jit_int_to_short_ovf(jit_int *result, jit_int value);
jit_int jit_int_to_ushort_ovf(jit_int *result, jit_int value);
jit_int jit_int_to_int_ovf(jit_int *result, jit_int value);
jit_int jit_int_to_uint_ovf(jit_uint *result, jit_int value);
jit_int jit_int_to_long_ovf(jit_long *result, jit_int value);
jit_int jit_int_to_ulong_ovf(jit_ulong *result, jit_int value);
jit_int jit_uint_to_int_ovf(jit_int *result, jit_uint value);
jit_int jit_uint_to_uint_ovf(jit_uint *result, jit_uint value);
jit_int jit_uint_to_long_ovf(jit_long *result, jit_uint value);
jit_int jit_uint_to_ulong_ovf(jit_ulong *result, jit_uint value);
jit_int jit_long_to_int_ovf(jit_int *result, jit_long value);
jit_int jit_long_to_uint_ovf(jit_uint *result, jit_long value);
jit_int jit_long_to_long_ovf(jit_long *result, jit_long value);
jit_int jit_long_to_ulong_ovf(jit_ulong *result, jit_long value);
jit_int jit_ulong_to_int_ovf(jit_int *result, jit_ulong value);
jit_int jit_ulong_to_uint_ovf(jit_uint *result, jit_ulong value);
jit_int jit_ulong_to_long_ovf(jit_long *result, jit_ulong value);
jit_int jit_ulong_to_ulong_ovf(jit_ulong *result, jit_ulong value);

/*
 * Convert a 32-bit floating-point value into various integer types.
 */
jit_int jit_float32_to_int(jit_float32 value);
jit_uint jit_float32_to_uint(jit_float32 value);
jit_long jit_float32_to_long(jit_float32 value);
jit_ulong jit_float32_to_ulong(jit_float32 value);

/*
 * Convert a 32-bit floating-point value into various integer types,
 * with overflow detection.
 */
jit_int jit_float32_to_int_ovf(jit_int *result, jit_float32 value);
jit_int jit_float32_to_uint_ovf(jit_uint *result, jit_float32 value);
jit_int jit_float32_to_long_ovf(jit_long *result, jit_float32 value);
jit_int jit_float32_to_ulong_ovf
	(jit_ulong *result, jit_float32 value);

/*
 * Convert a 64-bit floating-point value into various integer types.
 */
jit_int jit_float64_to_int(jit_float64 value);
jit_uint jit_float64_to_uint(jit_float64 value);
jit_long jit_float64_to_long(jit_float64 value);
jit_ulong jit_float64_to_ulong(jit_float64 value);

/*
 * Convert a 64-bit floating-point value into various integer types,
 * with overflow detection.
 */
jit_int jit_float64_to_int_ovf(jit_int *result, jit_float64 value);
jit_int jit_float64_to_uint_ovf(jit_uint *result, jit_float64 value);
jit_int jit_float64_to_long_ovf(jit_long *result, jit_float64 value);
jit_int jit_float64_to_ulong_ovf
	(jit_ulong *result, jit_float64 value);

/*
 * Convert a native floating-point value into various integer types.
 */
jit_int jit_nfloat_to_int(jit_nfloat value);
jit_uint jit_nfloat_to_uint(jit_nfloat value);
jit_long jit_nfloat_to_long(jit_nfloat value);
jit_ulong jit_nfloat_to_ulong(jit_nfloat value);

/*
 * Convert a native floating-point value into various integer types,
 * with overflow detection.
 */
jit_int jit_nfloat_to_int_ovf(jit_int *result, jit_nfloat value);
jit_int jit_nfloat_to_uint_ovf(jit_uint *result, jit_nfloat value);
jit_int jit_nfloat_to_long_ovf(jit_long *result, jit_nfloat value);
jit_int jit_nfloat_to_ulong_ovf
	(jit_ulong *result, jit_nfloat value);

/*
 * Convert integer types into floating-point values.
 */
jit_float32 jit_int_to_float32(jit_int value);
jit_float64 jit_int_to_float64(jit_int value);
jit_nfloat jit_int_to_nfloat(jit_int value);
jit_float32 jit_uint_to_float32(jit_uint value);
jit_float64 jit_uint_to_float64(jit_uint value);
jit_nfloat jit_uint_to_nfloat(jit_uint value);
jit_float32 jit_long_to_float32(jit_long value);
jit_float64 jit_long_to_float64(jit_long value);
jit_nfloat jit_long_to_nfloat(jit_long value);
jit_float32 jit_ulong_to_float32(jit_ulong value);
jit_float64 jit_ulong_to_float64(jit_ulong value);
jit_nfloat jit_ulong_to_nfloat(jit_ulong value);

/*
 * Convert between floating-point types.
 */
jit_float64 jit_float32_to_float64(jit_float32 value);
jit_nfloat jit_float32_to_nfloat(jit_float32 value);
jit_float32 jit_float64_to_float32(jit_float64 value);
jit_nfloat jit_float64_to_nfloat(jit_float64 value);
jit_float32 jit_nfloat_to_float32(jit_nfloat value);
jit_float64 jit_nfloat_to_float64(jit_nfloat value);

/*
 * Full struction that can hold a constant of any type.
 */
typedef struct
{
	jit_type_t			type;
	union
	{
		void		   *ptr_value;
		jit_int			int_value;
		jit_uint		uint_value;
		jit_nint		nint_value;
		jit_nuint		nuint_value;
		jit_long		long_value;
		jit_ulong		ulong_value;
		jit_float32		float32_value;
		jit_float64		float64_value;
		jit_nfloat		nfloat_value;

	} un;

} jit_constant_t;

/*
 * External function declarations.
 */
jit_value_t jit_value_create(jit_function_t func, jit_type_t type);
jit_value_t jit_value_create_nint_constant
	(jit_function_t func, jit_type_t type, jit_nint const_value);
jit_value_t jit_value_create_long_constant
	(jit_function_t func, jit_type_t type, jit_long const_value);
jit_value_t jit_value_create_float32_constant
	(jit_function_t func, jit_type_t type,
	 jit_float32 const_value);
jit_value_t jit_value_create_float64_constant
	(jit_function_t func, jit_type_t type,
	 jit_float64 const_value);
jit_value_t jit_value_create_nfloat_constant
	(jit_function_t func, jit_type_t type,
	 jit_nfloat const_value);
jit_value_t jit_value_create_constant
	(jit_function_t func, const jit_constant_t *const_value);
jit_value_t jit_value_get_param
	(jit_function_t func, unsigned int param);
jit_value_t jit_value_get_struct_pointer(jit_function_t func);
int jit_value_is_temporary(jit_value_t value);
int jit_value_is_local(jit_value_t value);
int jit_value_is_constant(jit_value_t value);
int jit_value_is_parameter(jit_value_t value);
void jit_value_ref(jit_function_t func, jit_value_t value);
void jit_value_set_volatile(jit_value_t value);
int jit_value_is_volatile(jit_value_t value);
void jit_value_set_addressable(jit_value_t value);
int jit_value_is_addressable(jit_value_t value);
jit_type_t jit_value_get_type(jit_value_t value);
jit_function_t jit_value_get_function(jit_value_t value);
jit_block_t jit_value_get_block(jit_value_t value);
jit_context_t jit_value_get_context(jit_value_t value);
jit_constant_t jit_value_get_constant(jit_value_t value);
jit_nint jit_value_get_nint_constant(jit_value_t value);
jit_long jit_value_get_long_constant(jit_value_t value);
jit_float32 jit_value_get_float32_constant(jit_value_t value);
jit_float64 jit_value_get_float64_constant(jit_value_t value);
jit_nfloat jit_value_get_nfloat_constant(jit_value_t value);
int jit_value_is_true(jit_value_t value);
int jit_constant_convert
	(jit_constant_t *result, const jit_constant_t *value,
	 jit_type_t type, int overflow_check);
