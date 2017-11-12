
#pragma once

#include "stdio.h"
#include <memory>

class Buffer
{
	uint8_t* buffer = nullptr;
	int      size = 0;

public:

	Buffer()
	{
	};

	Buffer(const char* name)
	{
		Load(name);
	};


	bool Load(const char* name)
	{
		buffer = nullptr;
		size = 0;

		FILE* file = fopen(name, "rb");

		if (file)
		{
			fseek(file, 0, SEEK_END);
			size = ftell(file);
			fseek(file, 0, SEEK_SET);

			buffer = (uint8_t*)malloc(size);
			fread(buffer, size, 1, file);

			fclose(file);

			return true;
		}

		return false;
	}

	~Buffer()
	{
		if (buffer)
		{
			free(buffer);
		}
	}

	uint8_t* GetData()
	{
		return buffer;
	}

	int GetSize()
	{
		return size;
	}
};