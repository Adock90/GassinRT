#include <v8.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>

#include <GassinRT/GassinRTUtils.hpp>
#include <GassinRT/GassinRTErrHandle.hpp>

namespace FileHandle
{
	char* ReadJSFile(char* filename)
	{
		FILE* fptr = fopen(filename, "r");
		if (fptr == NULL)
		{
			std::cout << "Internal Error: Failed to open file" << std::endl;
			exit(1);
		}
		fseek(fptr, 0, SEEK_END);
		size_t fsize = ftell(fptr);
		rewind(fptr);
		char* JSScript = new char[fsize + 1];
		JSScript[fsize] = '\0';
		
		for (size_t i = 0; i < fsize; i+=0)
		{
			i += fread(&JSScript[i], 1, fsize - i, fptr);
		}
		fclose(fptr);

		return JSScript;
	}

	void ReadFile(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		FILE* FilePtr;

		v8::Isolate* isolate = args.GetIsolate();
		if (args.Length() != 1)
		{
			isolate->ThrowError("Bad Params");
			exit(1);
		}

		v8::String::Utf8Value Filename(isolate, args[0]);
		if (*Filename == nullptr)
		{
			isolate->ThrowError("Error Loading File");
			exit(1);
		}
		
		FilePtr = fopen(*Filename, "r");
		if (FilePtr == NULL)
		{
			isolate->ThrowError("Error Loading File");
			exit(1);
		}

		fseek(FilePtr, 0, SEEK_END);
		size_t FileSize = ftell(FilePtr);
		rewind(FilePtr);
		char* Buffer = new char[FileSize + 1];
		Buffer[FileSize] = '\0';
		for (size_t i = 0; i < FileSize;)
		{
			i += fread(&Buffer[i], 1, FileSize - i, FilePtr);
			if (ferror(FilePtr))
			{
				fclose(FilePtr);
				exit(1);
			}
		}
		fclose(FilePtr);
		args.GetReturnValue().Set(ToV8String(Buffer));
		delete[] Buffer;
	}

	void WriteFile(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		FILE* FilePtr;

                v8::Isolate* isolate = args.GetIsolate();
                if (args.Length() != 2)
                {
                        isolate->ThrowError("Bad Params");
                        exit(1);
                }

                v8::String::Utf8Value Filename(isolate, args[0]);
                if (*Filename == nullptr)
                {
                        isolate->ThrowError("Error Loading File");
                        exit(1);
                }

                FilePtr = fopen(*Filename, "w");
                if (FilePtr == NULL)
                {
                        isolate->ThrowError("Error Loading File");
                        exit(1);
                }
		
		v8::String::Utf8Value str(isolate, args[1]);	
		const char* ContentCFormat = ToCString(str);
		fprintf(FilePtr, "%s", ContentCFormat);

		fclose(FilePtr);
	}
}
