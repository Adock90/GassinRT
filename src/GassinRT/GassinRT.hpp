#include <bits/stdc++.h>
#include <v8.h>
#include <uv.h>
#include <libplatform/libplatform.h>

#include <GassinRT/GassinRTConsole.hpp>
#include <GassinRT/GassinRTFiles.hpp>
#include <GassinRT/GassinRTErrHandle.hpp>

namespace GassinRT
{
	uv_loop_t *GASSINLOOP = uv_default_loop();
	

	void SetCallbackTemplate(v8::Local<v8::ObjectTemplate> global, v8::Isolate* isolate)
	{
		v8::Local<v8::ObjectTemplate> consoleObject = v8::ObjectTemplate::New(isolate);
		v8::Local<v8::ObjectTemplate> fileObject = v8::ObjectTemplate::New(isolate);
		consoleObject->Set(isolate, "log", v8::FunctionTemplate::New(isolate, SystemConsole::SystemConsoleOut));
                consoleObject->Set(isolate, "getinput", v8::FunctionTemplate::New(isolate, SystemConsole::SystemConsoleIn));
                global->Set(isolate, "terminal", consoleObject);

		fileObject->Set(isolate, "read", v8::FunctionTemplate::New(isolate, FileHandle::ReadFile));
		fileObject->Set(isolate, "write", v8::FunctionTemplate::New(isolate, FileHandle::WriteFile));
		global->Set(isolate, "file", fileObject);
	}	

	class GassinRTObj
	{
	private:
		std::unique_ptr<v8::Platform> plat;
		v8::Isolate* isolate;
		v8::Isolate::CreateParams Params;
	//	v8::Global<v8::Context> Context;
	public:
		void GassinRTShutdown();
		void GassinRTInitV8ANDVM(int argc, char *argv[]);
		void GassinRTCreateJSInstance(char* File);
	};

	void GassinRTObj::GassinRTInitV8ANDVM(int argc, char *argv[])
	{
		v8::V8::InitializeICUDefaultLocation(argv[0]);
		v8::V8::InitializeExternalStartupData(argv[0]);
		
		//Initalizes the platform
		plat = v8::platform::NewDefaultPlatform();
		v8::V8::InitializePlatform(plat.get());
		
		//Initalizes V8 Engine
		v8::V8::Initialize();

		//Initalizes Virtual Machine
		Params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
		isolate = v8::Isolate::New(Params);
	}

	void GassinRTObj::GassinRTCreateJSInstance(char* File)
	{
		v8::Isolate::Scope Scope(isolate);
		
		v8::TryCatch try_catch(isolate);
		

		v8::HandleScope HandleScope(isolate);
		v8::ScriptOrigin Origin(v8::String::NewFromUtf8(isolate, File).ToLocalChecked());

		v8::Local<v8::ObjectTemplate> GlobalObject = v8::ObjectTemplate::New(isolate);
		
		SetCallbackTemplate(GlobalObject, isolate);	
		
		v8::Local<v8::Context> LocalContext = v8::Context::New(isolate, NULL, GlobalObject);	
                v8::Context::Scope CScope(LocalContext);

		char* JS = FileHandle::ReadJSFile(File);
		
		v8::Local<v8::String> JSSource = v8::String::NewFromUtf8(isolate, JS).ToLocalChecked();
		v8::Local<v8::Script> Comp;
		if (!v8::Script::Compile(LocalContext, JSSource, &Origin).ToLocal(&Comp))
		{
			GassinException::GassinRTReportException(isolate, &try_catch);
			std::exit(1);
		}

		v8::Local<v8::Value> Res;
	       	if (!Comp->Run(LocalContext).ToLocal(&Res))
		{
			assert(try_catch.HasCaught());
			GassinException::GassinRTReportException(isolate, &try_catch);
		}

		v8::String::Utf8Value utf8(isolate, Res);
		
		

		uv_run(GASSINLOOP, UV_RUN_DEFAULT);
	}
	void GassinRTObj::GassinRTShutdown()
	{
		isolate->Dispose();
		v8::V8::Dispose();
		v8::V8::DisposePlatform();
		delete Params.array_buffer_allocator;
	}	
}
