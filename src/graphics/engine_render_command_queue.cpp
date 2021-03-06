#include "Engine.h"
namespace Engine {

	ERenderCommandQueue::ERenderCommandQueue()
	{
	}

	ERenderCommandQueue::~ERenderCommandQueue()
	{
		
	}
	
	void ERenderCommandQueue::AddRenderCommand(ERenderCommand* renderCommand) 
	{
		fCommandQueue.push(renderCommand);
	}

	void ERenderCommandQueue::Execute()
	{
		while (fCommandQueue.size() > 0)
        {
            fCommandQueue.front()->Execute();
            delete fCommandQueue.front();
            fCommandQueue.pop();
        }
	}
}