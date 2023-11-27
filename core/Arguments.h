#ifndef NATIVE_BINDINGS_CORE_ARGUMENTS_H
#define NATIVE_BINDINGS_CORE_ARGUMENTS_H

#include "TypedArrayContents.h"

#include <nan.h>
#include <iostream>

class Arguments {
public:
    using ArgumentsType = Nan::NAN_METHOD_ARGS_TYPE;
    [[nodiscard]] Arguments(ArgumentsType& info,std::string&& name);
    template<typename T> [[nodiscard]] bool ConvertCustom(int index, T& out, std::function<bool(const v8::Local<v8::Value>&, T&)>&& extractor) const {
        v8::Local<v8::Value> arg;
        if(!GetArgument(index, arg)) {
            return false;
        }
        return extractor(arg, out);
    }
    /**
     * Convert the argument at the given index to the given type if it is not undefined.
     * If the argument is undefined it will return false and not throw an error like Convert does.
     * If false is returned, then `out` is not touched at all.
     * @tparam T type to convert to
     * @param index index of the argument
     * @param out output parameter
     * @return whether the conversion was successful
     */
    template<typename T> [[nodiscard]] bool ConvertOptional(int index, T& out) const {
        if(!HasArgument(index) || info[index]->IsUndefined()) {
            return false;
        }
        return Convert(index, out);
    }
    [[nodiscard]] bool Convert(
        int index,
        std::string&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        bool&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        uint64_t&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        double&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        int64_t&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        int32_t&
    ) const;

    template<typename T, typename U>
    [[nodiscard]] static bool SafeCast(const T& a, U& b, const std::string& it = "?") {
        static_assert(std::is_integral_v<T> && std::is_integral_v<U>, "SafeCast only supports integer types");

        // Check if 'T' is within the range of 'U'
        if ((std::is_signed_v<T> == std::is_signed_v<U>) || (a >= T{}) == (U{} < U(-1))) {
            if (a < static_cast<T>(std::numeric_limits<U>::min()) || a > static_cast<T>(std::numeric_limits<U>::max())) {
                // Handle error: 'a' is outside the range that 'U' can represent
                ThrowError(it + " is outside the range of type " + typeid(U).name());
                return false;
            }
        } else {
            if ((a < T{}) != (static_cast<U>(a) < U{})) {
                // Handle error: Sign change or 'a' is outside the range of 'U'
                ThrowError(it + " sign change or outside the range of type " + typeid(U).name());
                return false;
            }
        }

        b = static_cast<U>(a);
        return true;
    }

    /**
     * @tparam T
     * @param index
     * @param out
     * @return the pointer to the data in the v8::BackingStore of the TypedArray
     */
    template<typename T> [[nodiscard]] bool ConvertTypedArrayContents(
        const int&& index,
        TypedArrayContents<T>& out
    ) const {
        v8::Local<v8::Value> arg;
        if(!GetArgument(index, arg)) {
            return false;
        }
        return ConvertTypedArrayContents(arg, out, "argument number " + std::to_string(index + 1));
    }
    /**
     * @tparam T
     * @param index
     * @param out
     * @return the pointer to the data in the v8::BackingStore of the TypedArray
     */
    template<typename T> [[nodiscard]] static bool ConvertTypedArrayContents(
        v8::Local<v8::Value> arg,
        TypedArrayContents<T>& out,
        std::string && label = "value"
    ) {
        if(!arg->IsTypedArray()) {
            ThrowError("Expected " + label + " to be a TypedArray instance.");
            return false;
        }
        Nan::TypedArrayContents<T> contents(arg);
        out.value = *contents;
        out.size = contents.length();
        return true;
    }
    /**
     * Convert the argument at the given index to a TypedArray of the given type.
     * @tparam T type of the vector of buffer
     * @param index index of the argument
     * @param buffer buffer that is going to receive the cloned data
     * @return
     */
    template<typename T> [[nodiscard]] bool CopyTypedArrayContents(
        int index,
        std::vector<T>& buffer
    ) const {
        TypedArrayContents<T> data(buffer);
        if(!ConvertTypedArrayContents<T>(index, data)) {
            return false;
        }
        buffer.resize(data.size);
        std::memcpy(buffer.data(), data.value, data.size * sizeof(T));
        return true;
    }
    template<typename T> [[nodiscard]] bool To(int index, v8::Local<T>& out) {
        if(!AssertArgumentIndex(index)) {
            return false;
        }
        if(!info[index]->IsObject()) {
            ThrowError("Expected argument number " + std::to_string(index + 1) + " to be an object.");
            return false;
        }
        out = Nan::To<T>(info[index]).ToLocalChecked();
        return true;
    }
    [[nodiscard]] bool Convert(
        int index,
        uint16_t&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        v8::Local<v8::Function>&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        uint32_t&
    ) const;
    template<typename T> [[nodiscard]] bool Unwrap(
        const int index,
        T*& out
    ) const {
        v8::Local<v8::Value> value;
        if(!GetArgument(index, value)) {
            return false;
        }
        return Unwrap(value, out, "argument number " + std::to_string(index + 1));
    }
    template<typename T> [[nodiscard]] bool Unwrap(T*& out) const {
        return Unwrap(info.This(), out);
    }
    template<typename T> [[nodiscard]] bool Unwrap(v8::Local<v8::Value> value, T*& out, std::string&& label = "instance") const {
        if(!value->IsObject()){
            ThrowError("Expected " + label + " to be of type " + std::string(T::ClassName) + ".");
            return false;
        }
        out = nullptr;
        out = Nan::ObjectWrap::Unwrap<T>(Nan::To<v8::Object>(value).ToLocalChecked());
        if(out == nullptr) {
            ThrowError("Expected instance to be of type " + std::string(T::ClassName) + ".");
            return false;
        }
        return true;
    }
    [[nodiscard]] static bool Get(const uint64_t&, v8::Local<v8::Value>& out);
    [[nodiscard]] static bool Get(const int64_t&, v8::Local<v8::Value>& out);
    [[nodiscard]] static bool Get(const uint32_t&, v8::Local<v8::Value>& out);
    // [[nodiscard]] static bool Get(const time_t&, v8::Local<v8::Value>& out);
    [[nodiscard]] static bool IsUint32(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsInt32(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsFunction(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsString(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsNumber(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsBoolean(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsInt16Array(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsUint8Array(const v8::Local<v8::Value>&);
    /**
     * Get the argument at the given index. A JavaScript error will be thrown if the argument is not present.
     * @param index index of the argument
     * @param out output parameter
     * @return the argument at the given index
     */
    [[nodiscard]] bool GetArgument(int index, v8::Local<v8::Value>& out) const;
    [[nodiscard]] bool AssertArgumentType(int index, const std::function<bool(const v8::Local<v8::Value>&)>& assert, std::string&& expectedType) const;
    [[nodiscard]] bool HasArgument(int index) const;
private:
    std::string name;
    ArgumentsType& info;
    [[nodiscard]] bool AssertArgumentIndex(int index) const;
    static void ThrowError(const std::string&&);

};

#endif //NATIVE_BINDINGS_CORE_ARGUMENTS_H
