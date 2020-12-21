#pragma once

namespace Engine {

	class ERenderer
	{
	public:
		static void Init();
		static void CleanUp();

		static void Begin(const ERef<ECamera>& camera, const ELightMap& lights);
		static void Draw(const ERef<EVertexArray>& vertexArray, const EMat4& transform = EMat4(1.0f));
		static void* Submit(ERenderCommandFn fn, u32 size) { return s_Instance->fCommandQueue.Allocate(fn, size); }
		static void End();

		static ERenderer* Get() { return s_Instance; }

		static void WaitAndRender();

	private:
		static ERenderer* s_Instance;

		ERenderCommandQueue fCommandQueue;


		//TEMP
		ERef<EShader>		fShader;

		glm::mat4 			fViewProjectionMatrix;
		EVec3 				fCameraPosition;
		ELightMap 			fLightMap;
	};

}

#define IN_RENDER_PASTE2(a, b) a ## b
#define	IN_RENDER_PASTE(a, b) IN_RENDER_PASTE2(a, b)
#define IN_RENDER_UNIQUE(x) IN_RENDER_PASTE(x, __LINE__)

#define IN_RENDER(code) \
	struct IN_RENDER_UNIQUE(INRenderCommand) \
	{\
		static void Execute(void*)\
		{\
			code\
		}\
	};\
	{\
		auto mem = Engine::ERenderer::Submit(IN_RENDER_UNIQUE(INRenderCommand)::Execute, sizeof(IN_RENDER_UNIQUE(INRenderCommand)));\
		new (mem) IN_RENDER_UNIQUE(INRenderCommand)();\
	}\

#define IN_RENDER1(arg0, code) \
	struct IN_RENDER_UNIQUE(INRenderCommand) \
	{\
		IN_RENDER_UNIQUE(INRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0)\
		:arg0(arg0) {}\
\
		static void Execute(void* argBuffer)\
		{\
			auto& arg0 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg0; \
			code\
		}\
\
typename std::remove_const<typename std::remove_reference<decltype(arg0)>::type>::type arg0;\
	};\
	{\
		auto mem = Engine::ERenderer::Submit(IN_RENDER_UNIQUE(INRenderCommand)::Execute, sizeof(IN_RENDER_UNIQUE(INRenderCommand)));\
		new (mem) IN_RENDER_UNIQUE(INRenderCommand)(arg0);\
	}


#define IN_RENDER2(arg0, arg1, code) \
	struct IN_RENDER_UNIQUE(INRenderCommand) \
	{\
		IN_RENDER_UNIQUE(INRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0, typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1)\
		:arg0(arg0), arg1(arg1) {}\
\
		static void Execute(void* argBuffer)\
		{\
			auto& arg0 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg0; \
			auto& arg1 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg1; \
			code\
		}\
\
typename std::remove_const<typename std::remove_reference<decltype(arg0)>::type>::type arg0;\
typename std::remove_const<typename std::remove_reference<decltype(arg1)>::type>::type arg1;\
	};\
	{\
		auto mem = Engine::ERenderer::Submit(IN_RENDER_UNIQUE(INRenderCommand)::Execute, sizeof(IN_RENDER_UNIQUE(INRenderCommand)));\
		new (mem) IN_RENDER_UNIQUE(INRenderCommand)(arg0, arg1);\
	}


#define IN_RENDER3(arg0, arg1, arg2, code) \
	struct IN_RENDER_UNIQUE(INRenderCommand) \
	{\
		IN_RENDER_UNIQUE(INRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0, typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1, typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2)\
		:arg0(arg0), arg1(arg1), arg2(arg2) {}\
\
		static void Execute(void* argBuffer)\
		{\
			auto& arg0 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg0; \
			auto& arg1 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg1; \
			auto& arg2 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg2; \
			code\
		}\
\
typename std::remove_const<typename std::remove_reference<decltype(arg0)>::type>::type arg0;\
typename std::remove_const<typename std::remove_reference<decltype(arg1)>::type>::type arg1;\
typename std::remove_const<typename std::remove_reference<decltype(arg2)>::type>::type arg2;\
	};\
	{\
		auto mem = Engine::ERenderer::Submit(IN_RENDER_UNIQUE(INRenderCommand)::Execute, sizeof(IN_RENDER_UNIQUE(INRenderCommand)));\
		new (mem) IN_RENDER_UNIQUE(INRenderCommand)(arg0, arg1, arg2);\
	}


#define IN_RENDER4(arg0, arg1, arg2, arg3, code) \
	struct IN_RENDER_UNIQUE(INRenderCommand) \
	{\
		IN_RENDER_UNIQUE(INRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0, typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1, typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2, typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3)\
		:arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
\
		static void Execute(void* argBuffer)\
		{\
			auto& arg0 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg0; \
			auto& arg1 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg1; \
			auto& arg2 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg2; \
			auto& arg3 = ((IN_RENDER_UNIQUE(INRenderCommand)*)argBuffer)->arg3; \
			code\
		}\
\
typename std::remove_const<typename std::remove_reference<decltype(arg0)>::type>::type arg0;\
typename std::remove_const<typename std::remove_reference<decltype(arg1)>::type>::type arg1;\
typename std::remove_const<typename std::remove_reference<decltype(arg2)>::type>::type arg2;\
typename std::remove_const<typename std::remove_reference<decltype(arg3)>::type>::type arg3;\
	};\
	{\
		auto mem = Engine::ERenderer::Submit(IN_RENDER_UNIQUE(INRenderCommand)::Execute, sizeof(IN_RENDER_UNIQUE(INRenderCommand)));\
		new (mem) IN_RENDER_UNIQUE(INRenderCommand)(arg0, arg1, arg2, arg3);\
	}


#define IN_RENDER_S(code) auto self = this;\
	IN_RENDER1(self, code)

#define IN_RENDER_S1(arg0, code) auto self = this;\
	IN_RENDER2(self, arg0, code)

#define IN_RENDER_S2(arg0, arg1, code) auto self = this;\
	IN_RENDER3(self, arg0, arg1, code)

#define IN_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
	IN_RENDER4(self, arg0, arg1, arg2, code)

