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

	void* ERenderCommandQueue::Allocate(ERenderCommandFn fn, uint size)
	{
		*(ERenderCommandFn*)fCommandBufferPtr = fn;
		fCommandBufferPtr += sizeof(ERenderCommandFn);

		*(uint*)fCommandBufferPtr = size;
		fCommandBufferPtr += sizeof(uint);

		void* memory = fCommandBufferPtr;
		fCommandBufferPtr += size;

		fCommandCount++;
		return memory;
	}

	void ERenderCommandQueue::Execute()
	{
		byte* buffer = fCommandBuffer;

		for (uint i = 0; i < fCommandCount; i++)
		{
			ERenderCommandFn function = *(ERenderCommandFn*)buffer;
			buffer += sizeof(ERenderCommandFn);

			uint size = *(uint*)buffer;
			buffer += sizeof(uint);
			function(buffer);
			buffer += size;
		}

		fCommandBufferPtr = fCommandBuffer;
		fCommandCount = 0;
	}
}