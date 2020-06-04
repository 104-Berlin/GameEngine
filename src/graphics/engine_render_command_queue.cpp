#include "Engine.h"

//10mb buffersize
#define COMMAND_BUFFER_SIZE (10 * 1024 * 1024)

namespace Engine {

	ERenderCommandQueue::ERenderCommandQueue()
	{
		fCommandBuffer = new byte[COMMAND_BUFFER_SIZE];
		fCommandBufferPtr = fCommandBuffer;
		memset(fCommandBuffer, 0, COMMAND_BUFFER_SIZE);
	}

	ERenderCommandQueue::~ERenderCommandQueue()
	{
		delete[] fCommandBuffer;
	}

	void* ERenderCommandQueue::Allocate(ERenderCommandFn fn, u32 size)
	{
		*(ERenderCommandFn*)fCommandBufferPtr = fn;
		fCommandBufferPtr += sizeof(ERenderCommandFn);

		*(u32*)fCommandBufferPtr = size;
		fCommandBufferPtr += sizeof(u32);

		void* memory = fCommandBufferPtr;
		fCommandBufferPtr += size;

		fCommandCount++;
		return memory;
	}

	void ERenderCommandQueue::Execute()
	{
		byte* buffer = fCommandBuffer;

		for (u32 i = 0; i < fCommandCount; i++)
		{
			ERenderCommandFn function = *(ERenderCommandFn*)buffer;
			buffer += sizeof(ERenderCommandFn);

			u32 size = *(u32*)buffer;
			buffer += sizeof(u32);
			function(buffer);
			buffer += size;
		}

		fCommandBufferPtr = fCommandBuffer;
		fCommandCount = 0;
	}
}