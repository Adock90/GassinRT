#pragma once

#include <v8.h>

v8::Local<v8::String> ToV8String(const char* CStr)
{
	return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), CStr).ToLocalChecked();
}

const char* ToCString(const v8::String::Utf8Value &str)
{
    return *str ? *str : "<str failed>";
}
