#pragma once

//
//
//
void * aligned_malloc(size_t required_bytes, size_t alignment) {
    assert((alignment & (alignment-1)) == 0);
    int offset = alignment - 1 + sizeof(void*);
    // somewhere in the next aligned-1 bytes is an aligned value
    void* p = (void*) malloc(required_bytes+offset);
    if (!p) return nullptr;

    // jump the pointer offset forward 
    void* p_offset = (void*) ((size_t) (p) + offset);

    // back it up to the last aligned value. Note that this works only for
    // powers of two. If were want a generalized solution then we should do
    // (void**) ((((size_t) p_offset) / alignment) * alignment);
    void** p_aligned = (void**) (((size_t) p_offset) & ~(alignment -1));
    p_aligned[-1] = p;
    return p_aligned;
}

void aligned_free(void * p_aligned) {
    void * p = ((void**)p_aligned)[-1];
    free(p);
}
