
#define TEX_DEFINE(name, slot)											\
			Texture2D name##Texture : register(t##slot);				\
			SamplerState name##Sampler : register(s##slot);

#define TEX_ARG(name)													\
			Texture2D name, SamplerState name##Sampler

#define TEX_PASS_ARG(name)												\
			name, name##Sampler

#define FXAA_ARG(name)													\
			FxaaTex name;												\
			name.smpl = name##Sampler;									\
			name.tex = name##Texture;

#if defined(__VERT__)
#define CONSTANTS_START(n) cbuffer VsConstants : register(b0) {
#else  // __FRAG__
#define CONSTANTS_START(n) cbuffer PsConstants : register(b0) {
#endif

#define CONSTANTS_END };
#define CONSTANT_DECL(type, name, i) type name : packoffset(c##i)
#define CONSTANT_ARRAY_DECL(type, name, size, i) type name[size] : packoffset(c##i)

#define UINT4 uint4

#define SV_TARGET SV_Target
#define SV_TARGET1 SV_Target1
#define SV_POSITION SV_Position
#define VPOS SV_Position

#define MUL(x, y) mul((x), (y))

