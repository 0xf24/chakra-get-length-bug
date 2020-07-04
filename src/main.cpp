//
// Created by louie on 7/3/2020.
//

#include <ChakraCore.h>
#include <cstdio>

#define CONST_STR(str) str, sizeof(str)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define FAIL_AT __FILE__ ":" TOSTRING(__LINE__)
#define HANDLE_JS_ERROR(cmd) if (handleJsError(cmd, FAIL_AT)) return -1

bool handleJsError(JsErrorCode, const char * at);

int main() {

    JsRuntimeHandle runtime;
    JsContextRef context;

    int sourceContext = 0;

    HANDLE_JS_ERROR(JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime));

    HANDLE_JS_ERROR(JsCreateContext(runtime, &context));

    HANDLE_JS_ERROR(JsSetCurrentContext(context));

    JsValueRef obj;

    HANDLE_JS_ERROR(JsCreateObject(&obj));

    JsPropertyIdRef fooProp;
    JsPropertyIdRef barProp;
    JsPropertyIdRef lengthProp;

    JsValueRef intValue;
    JsValueRef strValue;

    HANDLE_JS_ERROR(JsCreatePropertyId(CONST_STR("foo"), &fooProp));
    HANDLE_JS_ERROR(JsCreatePropertyId(CONST_STR("bar"), &barProp));
    HANDLE_JS_ERROR(JsCreatePropertyId(CONST_STR("length"), &lengthProp));

    HANDLE_JS_ERROR(JsIntToNumber(12, &intValue));
    HANDLE_JS_ERROR(JsCreateString(CONST_STR("test"), &strValue));

    HANDLE_JS_ERROR(JsSetProperty(obj, fooProp, intValue, true));

    HANDLE_JS_ERROR(JsSetProperty(obj, barProp, strValue, true));

    JsValueRef props;

    HANDLE_JS_ERROR(JsGetOwnPropertyNames(obj, &props));

    JsValueRef length;

    HANDLE_JS_ERROR(JsGetProperty(props, lengthProp, &length));

    JsValueType type;

    HANDLE_JS_ERROR(JsGetValueType(length, &type));

    printf("type: %X\r\n", type);

    int length_value;

    HANDLE_JS_ERROR(JsNumberToInt(length, &length_value));

    printf("length %d\r\n", length_value);

    HANDLE_JS_ERROR(JsSetCurrentContext(JS_INVALID_REFERENCE));

    HANDLE_JS_ERROR(JsDisposeRuntime(runtime));

    return 0;
}


bool handleJsError(JsErrorCode code, const char * at) {
    if (code != JsNoError) {

        printf("JsError[%X] -> %s\r\n", code, at);

        return true;
    }
    return false;
}