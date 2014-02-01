#pragma once

//
// 13.09
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

//
// 13.08
// smart pointer class
// 
class RC {
public:
    RC():m_ref_count(1) { Print(); }

    void AddRef() { InterlockedIncrement(&m_ref_count); Print(); }
    long Release() { long ref = InterlockedDecrement(&m_ref_count); Print(); return ref;}
    void Print() { cout << "RC=" << m_ref_count << endl; }
private:
    long m_ref_count;
};

template <typename t>
class smart_pointer {
public:
    smart_pointer(t * ptr)
        :m_ref(ptr)
    {
        m_ref_count = new RC();
    }

    smart_pointer(smart_pointer<t> const& sptr)
        :m_ref(sptr.m_ref)
        ,m_ref_count(sptr.m_ref_count)

    {
        m_ref_count->AddRef();
    }

    smart_pointer<t> operator=(smart_pointer<t> const& sptr) {
        if (this == &sptr) return *this;

        // if already assigned, we need to release a reference
        Release();

        m_ref = sptr.m_ref;
        m_ref_count = sptr.m_ref_count;
        m_ref_count->AddRef();
        return *this;
    }

    ~smart_pointer() { Release(); }
    t* get() { return m_ref; }

private:
    void Release() {
        if (0 == m_ref_count->Release()) {
            delete m_ref_count;
            delete m_ref;
            m_ref_count = nullptr;
            m_ref = nullptr;
        }
    }
    RC* m_ref_count;
    t* m_ref;
};

//
// 13.10
// 
int ** Alloc2D(int rows, int cols) {
    int header = rows * sizeof(int*);
    int data = rows*cols*sizeof(int);
    
    // C++ way: = new int* [header + data];
    int ** row_ptr = (int **) malloc(header + data);
    if (!row_ptr) return nullptr;

    int * data_ptr = (int*) (row_ptr + rows); // skip to the actual data rows
    for (int i = 0; i < rows; i++) 
        row_ptr[i] = data_ptr + i*cols;

    return row_ptr;
}