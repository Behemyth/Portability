#pragma once

#if defined(__clang__) || defined(__GNUC__)
#define PORT_ASM_FENCE_REGISTER(value) __asm__ __volatile__("" : : "r"(value))
#define PORT_ASM_FENCE_MEMORY(value)   __asm__ __volatile__("" : : "m"(value) : "memory")
#define PORT_ASM_CLOBBER_MEMORY()      __asm__ __volatile__("" : : : "memory")
#else
#define PORT_ASM_FENCE_REGISTER(value)
#define PORT_ASM_FENCE_MEMORY(value)
#define PORT_ASM_CLOBBER_MEMORY()
#endif
