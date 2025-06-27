#include <stdint.h>
#include <stddef.h>
#include "base_kernel.h"

static int mem_report_ext_id = -1;

const char* memory_stick_art[] = {
    "  .------------------.",
    " | .----------------. |",
    " | |                | |",
    " | |   MEMORY       | |",
    " | |                | |",
    " | '----------------' |",
    " | :::::::::::::::::: |",
    " '------------------'",
    NULL
};

extern uint32_t kmem_get_total_bytes();
extern uint32_t kmem_get_used_bytes();
extern void int_to_str(int n, char* str);

void cmd_memreport(const char* args) {
    for (int i = 0; memory_stick_art[i] != NULL; i++) {
        terminal_writestring(memory_stick_art[i]);
        terminal_writestring("\n");
    }
    terminal_writestring("\n");

    terminal_writestring("--- Core-Kernel Memory Report ---\n");

    if (ext_is_loaded("KMEM")) {
        uint32_t total_mem_bytes = kmem_get_total_bytes();
        uint32_t used_mem_bytes = kmem_get_used_bytes();
        uint32_t free_mem_bytes = total_mem_bytes - used_mem_bytes;

        char num_buf[20];

        terminal_writestring("Total Memory: ");
        int_to_str(total_mem_bytes / 1024, num_buf);
        terminal_writestring(num_buf);
        terminal_writestring(" KB\n");

        terminal_writestring("Used Memory:  ");
        int_to_str(used_mem_bytes / 1024, num_buf);
        terminal_writestring(num_buf);
        terminal_writestring(" KB\n");

        terminal_writestring("Free Memory:  ");
        int_to_str(free_mem_bytes / 1024, num_buf);
        terminal_writestring(num_buf);
        terminal_writestring(" KB\n");

        terminal_writestring("\n");
        terminal_writestring("Usage Bar:\n");

        int bar_width = 20;
        int fill_chars = (int)(((float)used_mem_bytes / total_mem_bytes) * bar_width);
        if (fill_chars > bar_width) fill_chars = bar_width;
        if (total_mem_bytes == 0) fill_chars = 0;

        terminal_writestring("[");
        for (int i = 0; i < fill_chars; i++) {
            terminal_putchar('#');
        }
        for (int i = fill_chars; i < bar_width; i++) {
            terminal_putchar('-');
        }
        terminal_writestring("]\n");

    } else {
        terminal_writestring("Memory Manager (KMEM) extension not loaded or unavailable.\n");
        terminal_writestring("Memory stats are not accessible.\n");
    }

    terminal_writestring("------------------------------\n");
}

int mem_report_extension_init(void) {
    register_command("memreport", cmd_memreport, "Display ASCII art memory usage report", mem_report_ext_id);
    terminal_writestring("MEM_REPORT: Extension Initialized. Use 'memreport'.\n");
    return 0;
}

void mem_report_extension_cleanup(void) {
    terminal_writestring("MEM_REPORT: Cleaning up...\n");
    terminal_writestring("MEM_REPORT: Cleanup complete.\n");
}

__attribute__((section(".ext_register_fns")))
void __mem_report_auto_register(void) {
    mem_report_ext_id = register_extension("MEM_REPORT", "1.0",
                                         mem_report_extension_init,
                                         mem_report_extension_cleanup);
    if (mem_report_ext_id >= 0) {
        load_extension(mem_report_ext_id);
    } else {
        terminal_writestring("Failed to register Memory Report Extension (auto)!\n");
    }
}
