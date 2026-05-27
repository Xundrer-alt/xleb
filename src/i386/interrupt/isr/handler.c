#include "debug.h"
#include "interrupt/idt/mod.h"
#include "halt.h"
#include "test.h"

void isr_handler(regs_t *r) {
    static const char *ex_names[32] = {
        "Division by Zero", "Debug", "Non-Maskable Interrupt", "Breakpoint", "Overflow", "Bound Range Exceeded", "Invalid Opcode", "Device Not Available",
        "Double Fault", "Coprocessor Segment Overrun", "Invalid TSS", "Segment Not Present", "Stack Segment Fault", "General Protection Fault", "Page Fault", "Reserved",
        "x87 FPU Error", "Alignment Check", "Machine Check", "SIMD Exception", "Virtualization Exception", "Control Protection Exception", "Reserved", "Reserved",
        "Reserved", "Reserved", "Reserved", "Reserved", "Hypervisor Injection Exception", "VMM Communication Exception", "Security Exception", "Reserved"
    };
    if (r->int_no == 1 || r->int_no == 3) {
        DEBUG("Debug exception %d: %s", r->int_no, ex_names[r->int_no]);
        DEBUG("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x", r->eax, r->ebx, r->ecx, r->edx);
        DEBUG("EIP: 0x%x, CS: 0x%x, EFLAGS: 0x%x", r->eip, r->cs, r->eflags);
        return;
    }
#ifdef ENABLE_TESTS
    if (must_caught_exception) {
        must_caught_exception = 0;
        DEBUG("Exception %d: %s. Error code: 0x%x", r->int_no, ex_names[r->int_no], r->err_code);
        DEBUG("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x", r->eax, r->ebx, r->ecx, r->edx);
        DEBUG("EIP: 0x%x, CS: 0x%x, EFLAGS: 0x%x", r->eip, r->cs, r->eflags);
        DEBUG("It's okay, continuing test");
        r->eip += 2;
        r->eflags &= ~0x401;
        return;
    }
#endif
    ERROR("Exception %d: %s. Error code: 0x%x", r->int_no, ex_names[r->int_no], r->err_code);
    ERROR("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x", r->eax, r->ebx, r->ecx, r->edx);
    ERROR("EIP: 0x%x, CS: 0x%x, EFLAGS: 0x%x", r->eip, r->cs, r->eflags);
    halt();
}
