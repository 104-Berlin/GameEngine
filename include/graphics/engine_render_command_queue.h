#pragma once

namespace Engine {
	typedef void(*ERenderCommandFn)(void*);

	class ERenderCommandQueue
	{
	public:
		ERenderCommandQueue();
		~ERenderCommandQueue();

		void* Allocate(ERenderCommandFn func, uint size);

		void Execute();
	private:
		byte* fCommandBuffer;
		byte* fCommandBufferPtr;
		uint fCommandCount = 0;
	};

}