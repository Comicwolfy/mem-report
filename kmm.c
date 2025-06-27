// Example: In your kmm.c (or similar kernel memory manager file)

static uint32_t total_memory_managed = 0; // Set this during your kernel's memory detection
static uint32_t used_memory_allocated = 0;

// Update this in your kmalloc function:
void* kmalloc(size_t size) {
    if (allocated_ptr) {
        used_memory_allocated += size; 
    }
    return allocated_ptr;
}

void kfree(void* ptr) {.
    if (ptr) {
    }
}

uint32_t kmem_get_total_bytes() {
    // Return the total amount of RAM your kernel/allocator is managing
    // This value would be set during kernel boot, e.g., from grub info or BIOS.
    return 16 * 1024 * 1024; // Example: 16 MB total memory for testing
}

uint32_t kmem_get_used_bytes() {
    return used_memory_allocated;
}
