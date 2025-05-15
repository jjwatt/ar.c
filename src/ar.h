#define STBDS_NO_SHORT_NAMES
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#define ar_shift(a)        (stbds_header(a)->length--)
#define ar_put(a,v)      (stbds_arrmaybegrow(a,1), (a)[stbds_header(a)->length++] = (v))
#define ar_free(a)       ((void) ((a) ? STBDS_FREE(NULL,stbds_header(a)) : (void)0), (a)=NULL)
#define ar_len(a)        ((a) ? (ptrdiff_t) stbds_header(a)->length : 0)
#define ar_push          stbds_arrput  // synonym

#define STBDS_HEADER(a) ((stbds_array_header *)a - 1)

// --- Generic Implementation Function for Ordered Pop at Index ---
// This function performs the core logic: copying the value and shifting elements.
// It operates on void* pointers and requires the element size.
// The macro wrapper handles type information and length decrement.
static void stbds_arpop_at_ordered_impl(void* a, size_t elem_size, ptrdiff_t len, ptrdiff_t index, void* out_value) {
    char* base = (char*)a; // Work with byte pointers

    // Basic bounds checking (rely on assert like other stb_ds ops in debug)
    assert(index >= 0 && index < len && "Index out of bounds in stbds_arpop_at_ordered_impl");
    assert(a != NULL && "Array is NULL in stbds_arpop_at_ordered_impl");

    // Copy the element to the output buffer using its size
    memcpy(out_value, base + index * elem_size, elem_size);

    // Shift elements to the left to fill the gap
    // Use memmove for safety in case of overlapping memory regions
    if (index < len - 1) { // Only shift if not popping the last element
        memmove(base + index * elem_size, base + (index + 1) * elem_size, (len - 1 - index) * elem_size);
    }

    // Length decrement is handled by the calling macro
}

// --- Macro Magic for Argument Counting and Dispatch ---

// Helper macro to count arguments (up to 2)
#define STBDS_COUNT_ARGUMENTS(...) STBDS_GET_MACRO_(__VA_ARGS__, 2, 1)
#define STBDS_GET_MACRO_(_1, _2, COUNT, ...) COUNT

// Main user-facing macro: AR_POP
// Dispatches based on argument count to different helper macros
#define ar_pop(...) \
    STBDS_POP_DISPATCH(STBDS_COUNT_ARGUMENTS(__VA_ARGS__), __VA_ARGS__)

// Helper to route based on count
#define STBDS_POP_DISPATCH(count, ...) \
    STBDS_POP_DISPATCH_(count, __VA_ARGS__)

// Final dispatch based on the count number itself
// Calls ar_pop_1 or ar_pop_2
#define STBDS_POP_DISPATCH_(count, ...) \
    ar_pop_##count(__VA_ARGS__)

// --- Helper Macros for Each Case ---

// Case 1: One argument (just the array 'a'). Behaves like original ar_pop.
// This works generically due to how stb_ds.h handles array indexing and header access.
#define ar_pop_1(a) (STBDS_HEADER(a)->length--, (a)[STBDS_HEADER(a)->length])

// Case 2: Two arguments (array 'a' and 'index'). Performs ordered indexed pop.
#define ar_pop_2(a, index) ({ \
    /* Declare a temporary variable of the array's element type */ \
    /* __typeof__ is a common extension; consider alternatives if strict C89/C99 without extensions is needed. */ \
    __typeof__(*a) temp_value; \
    /* Get current length before modifying the array */ \
    ptrdiff_t current_len = ar_len(a); \
    /* Call the generic implementation function to copy value and shift */ \
    /* Use the revised implementation function name */ \
    stbds_arpop_at_ordered_impl((void*)a, sizeof(*a), current_len, index, &temp_value); \
    /* Decrement length using the header access macro */ \
    STBDS_HEADER(a)->length--; \
    /* Return the saved value from the temporary variable */ \
    temp_value; \
})


