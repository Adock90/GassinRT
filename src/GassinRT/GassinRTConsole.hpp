#include <v8.h>
#include <bits/stdc++.h>

#include <GassinRT/GassinRTUtils.hpp>

namespace SystemConsole
{
        void SystemConsoleOut(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		bool first = true;
		
		for (int i = 0; i < args.Length(); i++)
		{
			v8::HandleScope HS(args.GetIsolate());
			if (first)
			{
				first = false;
			}
			else
			{
				std::cout << " ";
			}
			v8::String::Utf8Value str(args.GetIsolate(), args[i]);
			const char* OutString = ToCString(str);
			std::cout << OutString;
		}
		std::cout << std::endl;
		std::cout << std::flush;
	}

	void SystemConsoleIn(const v8::FunctionCallbackInfo<v8::Value>& args)
	{	
		bool first = true;

        for (int i = 0; i < args.Length(); i++)
        {
            v8::HandleScope HS(args.GetIsolate());
            if (first)
            {
                first = false;
            }
            else
            {
                std::cout << " ";
            }
            v8::String::Utf8Value str(args.GetIsolate(), args[i]);
            const char* OutString = ToCString(str);
            std::cout << OutString;
        }
		std::string Input;
		std::cin >> Input;
		args.GetReturnValue().Set(ToV8String(Input.c_str()));
	}	
}

