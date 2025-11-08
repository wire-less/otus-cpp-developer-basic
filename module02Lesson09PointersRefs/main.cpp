#include <iostream>
#include <format>

void pointers_basics() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int x = 42;
    // size
    // address
    // value

    std::cout << std::format(
        "   x size: {}, address: {:p}, value: {}\n",
        sizeof(x), static_cast<void*>(&x), x
    );

    int* pInt = &x;
    std::cout << std::format(
        "pInt size: {}, address: {:p}, value: {:p}, points to: {}\n",
        sizeof(pInt), static_cast<void*>(&pInt), static_cast<void*>(pInt), *pInt
    );

    // switch to other variable:
    int y = 43;
    std::cout << std::format(
        "   y size: {}, address: {:p}, value: {}\n",
        sizeof(y), static_cast<void*>(&y), y
    );

    pInt = &y;
    std::cout << std::format(
        "pInt size: {}, address: {:p}, value: {:p}, points to: {}\n",
        sizeof(pInt), static_cast<void*>(&pInt), static_cast<void*>(pInt), *pInt
    );

    // change variable via ptr:
    *pInt = 100;
    std::cout << std::format(
        "pInt size: {}, address: {:p}, value: {:p}, points to: {}\n",
        sizeof(pInt), static_cast<void*>(&pInt), static_cast<void*>(pInt), *pInt
    );

    std::cout << std::format(
        "   y size: {}, address: {:p}, value: {}\n",
        sizeof(y), static_cast<void*>(&y), y
    );

    // pointer to null
    pInt = nullptr;
    std::cout << std::format(
        "pInt size: {}, address: {:p}, value: {:p}\n",
        sizeof(pInt), static_cast<void*>(&pInt), static_cast<void*>(pInt)
    );
}

void references_basics() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int x = 42;

    std::cout << std::format(
        "   x size: {}, address: {:p}, value: {}\n",
        sizeof(x), static_cast<void*>(&x), x
    );

    int& xRef = x;

    std::cout << std::format(
        "xRef size: {}, address: {:p}, value: {}, refs to: {}\n",
        sizeof(xRef), static_cast<void*>(&xRef), xRef, xRef
    );

    int y = 43;
    xRef = y;

    std::cout << std::format(
        "xRef size: {}, address: {:p}, value: {}, refs to: {}\n",
        sizeof(xRef), static_cast<void*>(&xRef), xRef, xRef
    );
}

void pointer_constness() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int a = 42, b = 43;
    {
        // pointer to const
        const int* pInt = &a;
//  int const* pInt = &a;  // the same

//     *pInt = 100;  // deprecated
        pInt = &b;
    }

    {
        // const pointer
//      int* const pInt; // deprecated, requires initializer
        int* const pInt = &a;
        *pInt = 100;
//       pInt = &b;  // deprecated
    }

    {
        const int* const pInt = &a;
//      *pInt = 100;
//      pInt = &b;
    }
}

void ref_constness() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int a = 42;
    const int& aRef = a;
//  aRef = 43;  // deprecated
}

void dangling_pointers() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int* pInt;
    {
        int x = 42;
        pInt = &x;
    }

    int* pInt1 = new int(42);
    std::cout << *pInt1 << '\n';
    // ...
    delete pInt1;

    std::cout << *pInt1 << '\n';
}

int& do_dangling_ref() {
    int x = 42;
    return x;
}

void dangling_refs() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int& xRef = do_dangling_ref();
    std::cout << std::format("xRef value: {}\n", xRef);
} 

void pointers_arithmetic() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    for (int i = 0; i < 5; ++i) {
        std::cout << std::format("*(ptr + {}) = {}\n", i, *(ptr + i));
    }
    
    ptr = arr;
    for (int i = 0; i < 5; ++i) {
        std::cout << std::format("*ptr: {}, address: {:p}\n", *ptr, static_cast<void*>(ptr));
        ++ptr;
    }

    char char_arr[] = {'a', 'b', 'c', 'd'};
    char* cPtr = char_arr;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::format("\n*ptr: {}, address: {:p}\n", *cPtr, static_cast<void*>(cPtr));
        ++cPtr;
    }
}

void pointer_2_pointer() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    int value = 42;
    int* ptr = &value;
    int** ptrToPtr = &ptr;  // Pointer to pointer

    std::cout << std::format(
        "ptr address: {:p}, ptr value: {}\n",
        static_cast<void*>(ptr), *ptr
    ); 

    std::cout << "Value: " << value << std::endl;
    std::cout << "Through pointer: " << *ptr << std::endl;
    std::cout << "Through pointer to pointer: " << **ptrToPtr << std::endl;
    
    // Addresses
    std::cout << "Address of value: " << &value << std::endl;
    std::cout << "Address stored in ptr: " << ptr << std::endl;
    std::cout << "Address of ptr: " << &ptr << std::endl;
    std::cout << "Address stored in ptrToPtr: " << ptrToPtr << std::endl;
    
    // Modifying through pointer to pointer
    **ptrToPtr = 100;
    std::cout << "After modifying through ptrToPtr: " << value << std::endl;
    
    // Practical example: dynamic allocation
    int** matrix = new int*[3];
    for (int i = 0; i < 3; ++i) {
        matrix[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = i * 3 + j;
        }
    }
    
    std::cout << "2D array using pointer to pointer:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Cleanup
    for (int i = 0; i < 3; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// reference to pointer
void ref_2_pointer() {
    std::cout << std::format("\n=== {} ===\n", __func__);
    
    int value = 42;
    int* ptr = &value;
    int*& refToPtr = ptr;  // Reference to pointer
    
    std::cout << "Value through pointer: " << *ptr << std::endl;
    std::cout << "Value through reference to pointer: " << *refToPtr << std::endl;
    
    // Modifying what the pointer points to through reference
    *refToPtr = 100;
    std::cout << "After modification: " << value << std::endl;
    
    // Changing what the pointer points to through reference
    int anotherValue = 200;
    refToPtr = &anotherValue;  // This changes ptr itself
    std::cout << "ptr now points to: " << *ptr << std::endl;
    
    // Practical example: function that modifies a pointer
    auto modifyPointer = [](int*& ptrRef, int newValue) {
        if (ptrRef != nullptr) {
            *ptrRef = newValue;
        }
    };
    
    int testValue = 50;
    int* testPtr = &testValue;
    std::cout << "Before function call: " << *testPtr << std::endl;
    modifyPointer(testPtr, 75);
    std::cout << "After function call: " << *testPtr << std::endl;
}

int main() {
    pointers_basics();
    references_basics();

    pointer_constness();
    ref_constness();

    dangling_pointers();
    dangling_refs();

    pointers_arithmetic();

    pointer_2_pointer();
    ref_2_pointer();

    return 0;
}