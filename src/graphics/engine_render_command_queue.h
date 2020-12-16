#pragma once

namespace Engine {
	typedef void(*ERenderCommandFn)(void*);

	class ERenderCommandQueue
	{
	public:
		ERenderCommandQueue();
		~ERenderCommandQueue();

		void* Allocate(ERenderCommandFn func, u32 size);

		void Execute();
	private:
		byte* fCommandBuffer;
		byte* fCommandBufferPtr;
		u32 fCommandCount = 0;
	};

}