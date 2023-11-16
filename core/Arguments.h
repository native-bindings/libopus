#ifndef NATIVE_BINDINGS_CORE_ARGUMENTS_H
#define NATIVE_BINDINGS_CORE_ARGUMENTS_H

#include <nan.h>

class Arguments {
public:
    using ArgumentsType = Nan::NAN_METHOD_ARGS_TYPE;
    [[nodiscard]] Arguments(ArgumentsType& info,std::string&& name);
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
    [[nodiscard]] bool Convert(
        int index,
        uint16_t&
    ) const;
    [[nodiscard]] bool Convert(
        int index,
        uint32_t&
    ) const;
    template<typename T> [[nodiscard]] bool Unwrap(
            int index,
            T*& out
    ) const {
        if(!AssertArgumentIndex(index)) {
            return false;
        }
        return Unwrap(info[index], out, "argument number " + std::to_string(index + 1));
    }
    template<typename T> [[nodiscard]] bool Unwrap(T*& out) const {
        return Unwrap(info.This(), out);
    }
    template<typename T> [[nodiscard]] bool Unwrap(v8::Local<v8::Value> value, T*& out, std::string label = "instance") const {
        if(!value->IsObject()){
            ThrowError("Expected " + label + " to be of type " + std::string(T::className) + ".");
            return false;
        }
        out = nullptr;
        out = Nan::ObjectWrap::Unwrap<T>(Nan::To<v8::Object>(value).ToLocalChecked());
        if(out == nullptr) {
            ThrowError("Expected instance to be of type " + std::string(T::className) + ".");
            return false;
        }
        return true;
    }
    [[nodiscard]] static bool Get(const uint64_t&, v8::Local<v8::Value>& out);
    [[nodiscard]] static bool Get(const uint32_t&, v8::Local<v8::Value>& out);
    [[nodiscard]] static bool Get(const time_t&, v8::Local<v8::Value>& out);
    [[nodiscard]] static bool IsUint32(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsInt32(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsString(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsNumber(const v8::Local<v8::Value>&);
    [[nodiscard]] static bool IsBoolean(const v8::Local<v8::Value>&);
    [[nodiscard]] bool AssertArgumentType(int index, const std::function<bool(const v8::Local<v8::Value>&)>& assert, std::string&& expectedType) const;
    [[nodiscard]] bool HasArgument(int index) const;
private:
    std::string name;
    ArgumentsType& info;
    [[nodiscard]] bool AssertArgumentIndex(int index) const;
    static void ThrowError(std::string&&);
};

#endif //NATIVE_BINDINGS_CORE_ARGUMENTS_H
