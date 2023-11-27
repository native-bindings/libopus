#ifndef NATIVE_BINDINGS_CORE_TYPED_ARRAY_DATA_H_
#define NATIVE_BINDINGS_CORE_TYPED_ARRAY_DATA_H_

#include <nan.h>
#include <cstdlib>

template<typename T>
class TypedArrayContents {
public:
    T* value;
    size_t size;
    explicit TypedArrayContents(T* value = nullptr, size_t size = std::numeric_limits<size_t>::min()) : value(value), size(size) {}
    static TypedArrayContents New(v8::Local<v8::Value> value) {
        Nan::TypedArrayContents<T> contents(value);
        return TypedArrayContents(*contents, contents.length());
    }
};

#endif // NATIVE_BINDINGS_CORE_TYPED_ARRAY_DATA_H_
