// In your includes/base_kernel.h:

// From KMEM (Kernel Memory Manager) extension
// These functions need to be implemented in your KMEM module (e.g., kmm.c)
extern uint32_t kmem_get_total_bytes(); // Function to get total available memory in bytes
extern uint32_t kmem_get_used_bytes();  // Function to get currently used/allocated memory in bytes

// (Ensure int_to_str is declared as it's used for printing numbers)
void int_to_str(int n, char* str);
