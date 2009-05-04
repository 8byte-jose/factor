namespace factor
{

/* Runtime errors */
typedef enum
{
	ERROR_EXPIRED = 0,
	ERROR_IO,
	ERROR_NOT_IMPLEMENTED,
	ERROR_TYPE,
	ERROR_DIVIDE_BY_ZERO,
	ERROR_SIGNAL,
	ERROR_ARRAY_SIZE,
	ERROR_C_STRING,
	ERROR_FFI,
	ERROR_HEAP_SCAN,
	ERROR_UNDEFINED_SYMBOL,
	ERROR_DS_UNDERFLOW,
	ERROR_DS_OVERFLOW,
	ERROR_RS_UNDERFLOW,
	ERROR_RS_OVERFLOW,
	ERROR_MEMORY,
} F_ERRORTYPE;

void out_of_memory(void);
void fatal_error(char* msg, CELL tagged);
void critical_error(char* msg, CELL tagged);

PRIMITIVE(die);

void throw_error(CELL error, F_STACK_FRAME *native_stack);
void general_error(F_ERRORTYPE error, CELL arg1, CELL arg2, F_STACK_FRAME *native_stack);
void divide_by_zero_error(void);
void memory_protection_error(CELL addr, F_STACK_FRAME *native_stack);
void signal_error(int signal, F_STACK_FRAME *native_stack);
void type_error(CELL type, CELL tagged);
void not_implemented_error(void);

PRIMITIVE(call_clear);
PRIMITIVE(unimplemented);

/* Global variables used to pass fault handler state from signal handler to
user-space */
extern CELL signal_number;
extern CELL signal_fault_addr;
extern F_STACK_FRAME *signal_callstack_top;

void memory_signal_handler_impl(void);
void misc_signal_handler_impl(void);

}