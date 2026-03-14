#pragma once

#include <v8.h>
#include <bits/stdc++.h>

#include <GassinRT/GassinRTUtils.hpp>

namespace GassinException
{
	void GassinRTReportException(v8::Isolate *isolate, v8::TryCatch *try_catch)
	{
		v8::HandleScope hs(isolate);
		v8::String::Utf8Value exception(isolate, try_catch->Exception());
		const char* CFormatException = ToCString(exception);
		v8::Local<v8::Message> msg = try_catch->Message();

		if (msg.IsEmpty())
		{
			std::cerr << CFormatException << std::endl;
		}
		else
		{
			v8::String::Utf8Value filename(isolate, msg->GetScriptOrigin().ResourceName());
			v8::Local<v8::Context> Context(isolate->GetCurrentContext());
			const char* CFormatFilename = ToCString(filename);
			int ErrorLine = msg->GetLineNumber(Context).FromJust();
			std::cerr << CFormatFilename << "> on line: " << ErrorLine << "\n\tError: " << CFormatException << std::endl;
			int Start = msg->GetStartColumn(Context).FromJust();
			for (int i = 0; i < Start; i++)
			{
				std::cerr << " ";
			}
			int End = msg->GetEndColumn(Context).FromJust();
			for (int j = Start; j < End; j++)
			{
				std::cerr << "*";
			}
			std::cerr << std::endl;

			v8::Local<v8::Value> StackTrace;
			if (try_catch->StackTrace(Context).ToLocal(&StackTrace) && StackTrace->IsString() && StackTrace.As<v8::String>()->Length() > 0)
			{
				v8::String::Utf8Value ActualStackTrace(isolate, StackTrace);
				const char* CFormatError = ToCString(ActualStackTrace);
				std::cerr << CFormatError << std::endl;
			}
		}
	}
}
