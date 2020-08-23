#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include <dxgi1_6.h>
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <wrl.h>

template<typename T>
using Ptr = Microsoft::WRL::ComPtr<T>;

//#define ADD_IF(val, op ,ev) if (val op ev) os << #ev

#define CASE_ADD(dst, ev) case ev : dst += #ev; break
#define CASE_ADD2(dst, ev, custom) case ev : dst += custom; break
#define ADD_IF2(dst, val, op ,ev) if (val op ev) { AddBar(dst); dst += #ev; }
#define ADD_IF3(dst, val, op ,ev, custom) if (val op ev) { AddBar(dst); dst += custom; }
#define ADD_IF4(dst, val, op ,ev, custom, custom1) if (val op ev) { custom1 dst += custom; }
#define ADD_STR(dst,s,x) dst << #x << " = " << s.x << std::endl
#define ADD_STR2(dst,s,x) dst << #x << " = " << s.x 
#define ADD_STR3(dst,s,x,space) dst << #x << space << "= " << s.x << std::endl
#define ADD_STR4(dst,s,x,space) dst << #x << space << "= " << s.x 
#define STR(x) #x
#define ADD_LINE(x) x << std::endl
#define ADD_TAB(x) x << "\t"

void AddBar(std::string& x) { if (!x.empty()) x += " | "; }

#define FW std::setfill('0') << std::setw(2) 

inline std::string GetUUIDString(const uint8_t _uuid[16])
{
    std::stringstream ss;
    ss << std::hex 
        << FW << (uint32_t)_uuid[0]  << FW << (uint32_t)_uuid[1] << FW << (uint32_t)_uuid[2] << FW << (uint32_t)_uuid[3] << "-"
        << FW << (uint32_t)_uuid[4]  << FW << (uint32_t)_uuid[5] << "-"
        << FW << (uint32_t)_uuid[6]  << FW << (uint32_t)_uuid[7] << "-"
        << FW << (uint32_t)_uuid[8]  << FW << (uint32_t)_uuid[9] << "-"
        << FW << (uint32_t)_uuid[10] << FW << (uint32_t)_uuid[11] << FW << (uint32_t)_uuid[12] << FW << (uint32_t)_uuid[13] << FW << (uint32_t)_uuid[14] << FW << (uint32_t)_uuid[15]
        << std::dec;
    return ss.str();
}

inline std::string GetLUIDString(const uint8_t _luid[8])
{
    std::stringstream ss;
    ss << std::hex
        << "Low: "    << FW << (uint32_t)_luid[0] << FW << (uint32_t)_luid[1] << FW << (uint32_t)_luid[2] << FW << (uint32_t)_luid[3]
        << ", High: " << FW << (uint32_t)_luid[4] << FW << (uint32_t)_luid[5] << FW << (uint32_t)_luid[6] << FW << (uint32_t)_luid[7]
        << std::dec;
    return ss.str();
}

#undef FW

#pragma region D3D12_FEATURE_DATA_D3D12_OPTIONS

std::ostream& operator<< (std::ostream& os, D3D12_SHADER_MIN_PRECISION_SUPPORT val)
{
    std::string s;
    ADD_IF2(s, val, ==, D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE);
    ADD_IF2(s, val, &, D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT);
    ADD_IF2(s, val, &, D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT);

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_TILED_RESOURCES_TIER val)
{		
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_TILED_RESOURCES_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_TILED_RESOURCES_TIER_1);
        CASE_ADD(s, D3D12_TILED_RESOURCES_TIER_2);
        CASE_ADD(s, D3D12_TILED_RESOURCES_TIER_3);
        CASE_ADD(s, D3D12_TILED_RESOURCES_TIER_4);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_RESOURCE_BINDING_TIER val)
{		
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_RESOURCE_BINDING_TIER_1);
        CASE_ADD(s, D3D12_RESOURCE_BINDING_TIER_2);
        CASE_ADD(s, D3D12_RESOURCE_BINDING_TIER_3);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_CONSERVATIVE_RASTERIZATION_TIER val)
{		
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_CONSERVATIVE_RASTERIZATION_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_CONSERVATIVE_RASTERIZATION_TIER_1);
        CASE_ADD(s, D3D12_CONSERVATIVE_RASTERIZATION_TIER_2);
        CASE_ADD(s, D3D12_CONSERVATIVE_RASTERIZATION_TIER_3);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_CROSS_NODE_SHARING_TIER val)
{		
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_CROSS_NODE_SHARING_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_CROSS_NODE_SHARING_TIER_1_EMULATED);
        CASE_ADD(s, D3D12_CROSS_NODE_SHARING_TIER_1);
        CASE_ADD(s, D3D12_CROSS_NODE_SHARING_TIER_2);
        CASE_ADD(s, D3D12_CROSS_NODE_SHARING_TIER_3);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_RESOURCE_HEAP_TIER val)
{		
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_RESOURCE_HEAP_TIER_1);
        CASE_ADD(s, D3D12_RESOURCE_HEAP_TIER_2);
    default:
        break;
    }

    return os << s;
}

#pragma endregion D3D12_FEATURE_DATA_D3D12_OPTIONS

#pragma region os operators

std::ostream& operator<< (std::ostream& os, D3D_FEATURE_LEVEL val)
{
    std::string s;
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_1_0_CORE);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_9_1);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_9_2);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_9_3);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_10_0);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_10_1);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_11_0);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_11_1);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_12_0);
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_12_1);

    return os << s;
}
std::ostream& operator<< (std::ostream& os, DXGI_FORMAT val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, DXGI_FORMAT_UNKNOWN);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32A32_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32A32_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32A32_UINT);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32A32_SINT);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32_UINT);
        CASE_ADD(s, DXGI_FORMAT_R32G32B32_SINT);
        CASE_ADD(s, DXGI_FORMAT_R16G16B16A16_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R16G16B16A16_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R16G16B16A16_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R16G16B16A16_UINT);
        CASE_ADD(s, DXGI_FORMAT_R16G16B16A16_SNORM);
        CASE_ADD(s, DXGI_FORMAT_R16G16B16A16_SINT);
        CASE_ADD(s, DXGI_FORMAT_R32G32_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R32G32_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R32G32_UINT);
        CASE_ADD(s, DXGI_FORMAT_R32G32_SINT);
        CASE_ADD(s, DXGI_FORMAT_R32G8X24_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_D32_FLOAT_S8X24_UINT);
        CASE_ADD(s, DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_X32_TYPELESS_G8X24_UINT);
        CASE_ADD(s, DXGI_FORMAT_R10G10B10A2_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R10G10B10A2_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R10G10B10A2_UINT);
        CASE_ADD(s, DXGI_FORMAT_R11G11B10_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R8G8B8A8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R8G8B8A8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_R8G8B8A8_UINT);
        CASE_ADD(s, DXGI_FORMAT_R8G8B8A8_SNORM);
        CASE_ADD(s, DXGI_FORMAT_R8G8B8A8_SINT);
        CASE_ADD(s, DXGI_FORMAT_R16G16_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R16G16_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R16G16_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R16G16_UINT);
        CASE_ADD(s, DXGI_FORMAT_R16G16_SNORM);
        CASE_ADD(s, DXGI_FORMAT_R16G16_SINT);
        CASE_ADD(s, DXGI_FORMAT_R32_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_D32_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R32_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_R32_UINT);
        CASE_ADD(s, DXGI_FORMAT_R32_SINT);
        CASE_ADD(s, DXGI_FORMAT_R24G8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_D24_UNORM_S8_UINT);
        CASE_ADD(s, DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_X24_TYPELESS_G8_UINT);
        CASE_ADD(s, DXGI_FORMAT_R8G8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R8G8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R8G8_UINT);
        CASE_ADD(s, DXGI_FORMAT_R8G8_SNORM);
        CASE_ADD(s, DXGI_FORMAT_R8G8_SINT);
        CASE_ADD(s, DXGI_FORMAT_R16_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R16_FLOAT);
        CASE_ADD(s, DXGI_FORMAT_D16_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R16_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R16_UINT);
        CASE_ADD(s, DXGI_FORMAT_R16_SNORM);
        CASE_ADD(s, DXGI_FORMAT_R16_SINT);
        CASE_ADD(s, DXGI_FORMAT_R8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_R8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R8_UINT);
        CASE_ADD(s, DXGI_FORMAT_R8_SNORM);
        CASE_ADD(s, DXGI_FORMAT_R8_SINT);
        CASE_ADD(s, DXGI_FORMAT_A8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R1_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R9G9B9E5_SHAREDEXP);
        CASE_ADD(s, DXGI_FORMAT_R8G8_B8G8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_G8R8_G8B8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC1_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC1_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC1_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_BC2_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC2_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC2_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_BC3_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC3_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC3_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_BC4_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC4_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC4_SNORM);
        CASE_ADD(s, DXGI_FORMAT_BC5_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC5_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC5_SNORM);
        CASE_ADD(s, DXGI_FORMAT_B5G6R5_UNORM);
        CASE_ADD(s, DXGI_FORMAT_B5G5R5A1_UNORM);
        CASE_ADD(s, DXGI_FORMAT_B8G8R8A8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_B8G8R8X8_UNORM);
        CASE_ADD(s, DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM);
        CASE_ADD(s, DXGI_FORMAT_B8G8R8A8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_B8G8R8X8_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_B8G8R8X8_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_BC6H_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC6H_UF16);
        CASE_ADD(s, DXGI_FORMAT_BC6H_SF16);
        CASE_ADD(s, DXGI_FORMAT_BC7_TYPELESS);
        CASE_ADD(s, DXGI_FORMAT_BC7_UNORM);
        CASE_ADD(s, DXGI_FORMAT_BC7_UNORM_SRGB);
        CASE_ADD(s, DXGI_FORMAT_AYUV);
        CASE_ADD(s, DXGI_FORMAT_Y410);
        CASE_ADD(s, DXGI_FORMAT_Y416);
        CASE_ADD(s, DXGI_FORMAT_NV12);
        CASE_ADD(s, DXGI_FORMAT_P010);
        CASE_ADD(s, DXGI_FORMAT_P016);
        CASE_ADD(s, DXGI_FORMAT_420_OPAQUE);
        CASE_ADD(s, DXGI_FORMAT_YUY2);
        CASE_ADD(s, DXGI_FORMAT_Y210);
        CASE_ADD(s, DXGI_FORMAT_Y216);
        CASE_ADD(s, DXGI_FORMAT_NV11);
        CASE_ADD(s, DXGI_FORMAT_AI44);
        CASE_ADD(s, DXGI_FORMAT_IA44);
        CASE_ADD(s, DXGI_FORMAT_P8);
        CASE_ADD(s, DXGI_FORMAT_A8P8);
        CASE_ADD(s, DXGI_FORMAT_B4G4R4A4_UNORM);
        CASE_ADD(s, DXGI_FORMAT_P208);
        CASE_ADD(s, DXGI_FORMAT_V208);
        CASE_ADD(s, DXGI_FORMAT_V408);
        CASE_ADD(s, DXGI_FORMAT_FORCE_UINT);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS val)
{
    std::string s;
    ADD_IF3(s, val, == , D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE, "NONE");
    ADD_IF3(s, val, & , D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_TILED_RESOURCE, "TILED_RESOURCE");

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D_SHADER_MODEL val)
{
    std::string s;
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_5_1);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_0);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_1);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_2);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_3);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_4);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_5);

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D_ROOT_SIGNATURE_VERSION val)
{
    std::string s;
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1);
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1_0);
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1_1);

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_1);
        CASE_ADD(s, D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_SHADER_CACHE_SUPPORT_FLAGS val)
{
    std::string s;
    ADD_IF2(s, val, == , D3D12_SHADER_CACHE_SUPPORT_NONE);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_LIBRARY);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE);

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_COMMAND_LIST_TYPE val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_DIRECT);
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_BUNDLE);
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_COMPUTE);
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_COPY);
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE);
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS);
        CASE_ADD(s, D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_COMMAND_QUEUE_PRIORITY val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
        CASE_ADD(s, D3D12_COMMAND_QUEUE_PRIORITY_HIGH);
        CASE_ADD(s, D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_COMMAND_LIST_SUPPORT_FLAGS val)
{
    std::string s;
    auto Align = [&]() { if (!s.empty())s += "\n\t         | "; };
    ADD_IF2(s, val, == , D3D12_COMMAND_LIST_SUPPORT_FLAG_NONE);
    ADD_IF2(s, val, &, D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT);
    ADD_IF2(s, val, &, D3D12_COMMAND_LIST_SUPPORT_FLAG_BUNDLE);
    ADD_IF2(s, val, &, D3D12_COMMAND_LIST_SUPPORT_FLAG_COPY);
    ADD_IF2(s, val, &, D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_DECODE);
    ADD_IF2(s, val, &, D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_PROCESS);
    ADD_IF2(s, val, &, D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_ENCODE);

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_VIEW_INSTANCING_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_VIEW_INSTANCING_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_VIEW_INSTANCING_TIER_1);
        CASE_ADD(s, D3D12_VIEW_INSTANCING_TIER_2);
        CASE_ADD(s, D3D12_VIEW_INSTANCING_TIER_3);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0);
        CASE_ADD(s, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_HEAP_SERIALIZATION_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_HEAP_SERIALIZATION_TIER_0);
        CASE_ADD(s, D3D12_HEAP_SERIALIZATION_TIER_10);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_RENDER_PASS_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_RENDER_PASS_TIER_0);
        CASE_ADD(s, D3D12_RENDER_PASS_TIER_1);
        CASE_ADD(s, D3D12_RENDER_PASS_TIER_2);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_RAYTRACING_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_RAYTRACING_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_RAYTRACING_TIER_1_0);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_VARIABLE_SHADING_RATE_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_VARIABLE_SHADING_RATE_TIER_1);
        CASE_ADD(s, D3D12_VARIABLE_SHADING_RATE_TIER_2);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_FORMAT_SUPPORT1 val)
{
    std::string s;
    auto Align = [&]() { if (!s.empty())s += "\n\t         | "; };

    ADD_IF4(s, val, == , D3D12_FORMAT_SUPPORT1_NONE                       , "NONE"                       , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_BUFFER                     , "BUFFER"                     , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_IA_VERTEX_BUFFER           , "IA_VERTEX_BUFFER"           , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_IA_INDEX_BUFFER            , "IA_INDEX_BUFFER"            , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SO_BUFFER                  , "SO_BUFFER"                  , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_TEXTURE1D                  , "TEXTURE1D"                  , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_TEXTURE2D                  , "TEXTURE2D"                  , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_TEXTURE3D                  , "TEXTURE3D"                  , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_TEXTURECUBE                , "TEXTURECUBE"                , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SHADER_LOAD                , "SHADER_LOAD"                , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE              , "SHADER_SAMPLE"              , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON   , "SHADER_SAMPLE_COMPARISON"   , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_MONO_TEXT    , "SHADER_SAMPLE_MONO_TEXT"    , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_MIP                        , "MIP"                        , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_RENDER_TARGET              , "RENDER_TARGET"              , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_BLENDABLE                  , "BLENDABLE"                  , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL              , "DEPTH_STENCIL"              , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RESOLVE        , "MULTISAMPLE_RESOLVE"        , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_DISPLAY                    , "DISPLAY"                    , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_CAST_WITHIN_BIT_LAYOUT     , "CAST_WITHIN_BIT_LAYOUT"     , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET   , "MULTISAMPLE_RENDERTARGET"   , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD           , "MULTISAMPLE_LOAD"           , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SHADER_GATHER              , "SHADER_GATHER"              , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_BACK_BUFFER_CAST           , "BACK_BUFFER_CAST"           , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW, "TYPED_UNORDERED_ACCESS_VIEW", Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON   , "SHADER_GATHER_COMPARISON"   , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_DECODER_OUTPUT             , "DECODER_OUTPUT"             , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_OUTPUT     , "VIDEO_PROCESSOR_OUTPUT"     , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_INPUT      , "VIDEO_PROCESSOR_INPUT"      , Align(); );
    ADD_IF4(s, val, &  , D3D12_FORMAT_SUPPORT1_VIDEO_ENCODER              , "VIDEO_ENCODER"              , Align(); );

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_FORMAT_SUPPORT2 val)
{
    std::string s;
    auto Align = [&]() { if (!s.empty())s += "\n\t         | "; };
    ADD_IF4(s, val,==, D3D12_FORMAT_SUPPORT2_NONE                                        , "NONE"                                        , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD                              , "UAV_ATOMIC_ADD"                              , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS                      , "UAV_ATOMIC_BITWISE_OPS"                      , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE, "UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE", Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE                         , "UAV_ATOMIC_EXCHANGE"                         , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX                , "UAV_ATOMIC_SIGNED_MIN_OR_MAX"                , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX              , "UAV_ATOMIC_UNSIGNED_MIN_OR_MAX"              , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD                              , "UAV_TYPED_LOAD"                              , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE                             , "UAV_TYPED_STORE"                             , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP                      , "OUTPUT_MERGER_LOGIC_OP"                      , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_TILED                                       , "TILED"                                       , Align(); );
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_MULTIPLANE_OVERLAY                          , "MULTIPLANE_OVERLAY"                          , Align(); );

    return os << s;
}
std::ostream& operator<< (std::ostream& os, const GUID& val)
{
    std::string s;
    return os << GetUUIDString(reinterpret_cast<const uint8_t*>(&val));
}
std::ostream& operator<< (std::ostream& os, D3D12_MESH_SHADER_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_MESH_SHADER_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_MESH_SHADER_TIER_1);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_SAMPLER_FEEDBACK_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_SAMPLER_FEEDBACK_TIER_0_9);
        CASE_ADD(s, D3D12_SAMPLER_FEEDBACK_TIER_1_0);
    default:
        break;
    }

    return os << s;
}
std::ostream& operator<< (std::ostream& os, D3D12_FEATURE val)
{
    std::string s;

    switch (val)
    {
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS);
        CASE_ADD(s, D3D12_FEATURE_ARCHITECTURE);
        CASE_ADD(s, D3D12_FEATURE_FEATURE_LEVELS);
        CASE_ADD(s, D3D12_FEATURE_FORMAT_SUPPORT);
        CASE_ADD(s, D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS);
        CASE_ADD(s, D3D12_FEATURE_FORMAT_INFO);
        CASE_ADD(s, D3D12_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT);
        CASE_ADD(s, D3D12_FEATURE_SHADER_MODEL);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS1);
        CASE_ADD(s, D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_SUPPORT);
        CASE_ADD(s, D3D12_FEATURE_ROOT_SIGNATURE);
        CASE_ADD(s, D3D12_FEATURE_ARCHITECTURE1);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS2);
        CASE_ADD(s, D3D12_FEATURE_SHADER_CACHE);
        CASE_ADD(s, D3D12_FEATURE_COMMAND_QUEUE_PRIORITY);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS3);
        CASE_ADD(s, D3D12_FEATURE_EXISTING_HEAPS);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS4);
        CASE_ADD(s, D3D12_FEATURE_SERIALIZATION);
        CASE_ADD(s, D3D12_FEATURE_CROSS_NODE);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS5);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS6);
        CASE_ADD(s, D3D12_FEATURE_QUERY_META_COMMAND);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS7);
        CASE_ADD(s, D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT);
        CASE_ADD(s, D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES);
    default:
        break;
    }

    return os << s;
}


#pragma endregion os operators


class D3D12FeatureViewer
{
public:
    D3D12FeatureViewer()
        : factory{}
        , adapter{}
        , device{}
    {
    }

    ~D3D12FeatureViewer()
    {

    }

    bool Init(UINT adapter_index)
    {
        {
            Ptr<ID3D12Debug> debug_controller;
            if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller))))
            {
                std::cout << "Failed to get debug interface." << std::endl;
                return false;
            }

            debug_controller->EnableDebugLayer();
        }

        if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory))))
        {
            std::cout << "Failed to create dxgi factory." << std::endl;
            return false;
        }

        if (FAILED(factory->EnumAdapters1(adapter_index, &adapter)))
        {
            std::cout << "Failed to enumerate dxgi adapter." << std::endl;
            return false;
        }


        DXGI_ADAPTER_DESC1 desc{};
        adapter->GetDesc1(&desc);
        std::cout << std::endl;
        std::cout << "DXGI_ADAPTER_DESC1: index " << adapter_index << std::endl;
        std::wcout  <<L"\tDescription           = " << desc.Description                                                             << std::endl;
        std::cout   << "\tVendorId              = " << std::hex << desc.VendorId << std::dec                                        << std::endl;
        std::cout   << "\tDeviceId              = " << std::hex << desc.DeviceId << std::dec                                        << std::endl;
        std::cout   << "\tSubSysId              = " << std::hex << desc.SubSysId << std::dec                                        << std::endl;
        std::cout   << "\tRevision              = " << desc.Revision                                                                << std::endl;
        std::cout   << "\tDedicatedVideoMemory  = " << desc.DedicatedVideoMemory                                                    << std::endl;
        std::cout   << "\tDedicatedSystemMemory = " << desc.DedicatedSystemMemory                                                   << std::endl;
        std::cout   << "\tSharedSystemMemory    = " << desc.SharedSystemMemory                                                      << std::endl;
        std::cout   << "\tAdapterLuid           = " << GetLUIDString(reinterpret_cast<const uint8_t*>(&desc.AdapterLuid.LowPart))   << std::endl;
        std::cout   << "\tFlags                 = " << std::hex << desc.Flags << std::dec                                           << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        if (FAILED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_1, IID_PPV_ARGS(&device))))
        {
            std::cout << "Failed to create device." << std::endl;
            return false;
        }

        return true;
    }

    bool CheckFormatSupports(std::ostream& os, bool is_show_msql) 
    {
        os << "D3D12_FEATURE_DATA_FORMAT_SUPPORT/D3D12_FEATURE_DATA_FORMAT_INFO: " << std::endl;

        D3D12_FEATURE f;
        auto CheckHR = [&](HRESULT hr) { if (FAILED(hr)) { os << "Failed to get " << f << '.' << "(or the format was not supported.)"<<std::endl; } };

        D3D12_FEATURE_DATA_FORMAT_SUPPORT format_support{};
        D3D12_FEATURE_DATA_FORMAT_INFO    format_info{};
        D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS multisample_quality_levels{};
        for (int i = 1; i < (int)DXGI_FORMAT_B4G4R4A4_UNORM + 1; i++)
        {
            os << (format_support.Format = format_info.Format = (DXGI_FORMAT)i) << std::endl;
            os << "--------------------------------------------------------------------------------------------------" << std::endl;
            CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_FORMAT_SUPPORT), &format_support, sizeof(D3D12_FEATURE_DATA_FORMAT_SUPPORT)));
            CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_FORMAT_INFO)   , &format_info   , sizeof(D3D12_FEATURE_DATA_FORMAT_INFO)));

            ADD_TAB(os); ADD_STR(os, format_support, Support1);
            ADD_TAB(os); ADD_STR(os, format_support, Support2);
            ADD_TAB(os); ADD_STR(os, (int)format_info, PlaneCount);

            if (is_show_msql)
            {

                os << "D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS: " << std::endl;
                multisample_quality_levels.Format = format_support.Format;
                for (UINT j = 1; j < D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT + 1; j *= 2)
                {
                    multisample_quality_levels.SampleCount = j;
                    for (int k = 0; k < 2; k++)
                    {
                        multisample_quality_levels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS(k);
                        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS), &multisample_quality_levels, sizeof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS)));
                        Trace_D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS(os, multisample_quality_levels);
                    }
                }
            }

            ADD_LINE(os);
        }
        return true;
    }

    bool CheckQueuePrioritySupports(std::ostream& os) 
    {
        auto CheckHR = [&](HRESULT hr) { if (FAILED(hr)) { os << "Failed to get " << D3D12_FEATURE_COMMAND_QUEUE_PRIORITY << '.' << std::endl; } };

        os << "D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY: " << std::endl;
        os << "--------------------------------------------------------------------------------------------------" << std::endl;
        D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY command_queue_priority{};
        for (int i = 0; i < (int)D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE + 1; i++)
        {
            command_queue_priority.CommandListType = D3D12_COMMAND_LIST_TYPE(i);
            for (int j = 0; j < 3; j++)
            {
                switch (j)
                {
                case 0: command_queue_priority.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;          break;
                case 1: command_queue_priority.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;            break;
                case 2: command_queue_priority.Priority = D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME; break;
                default:
                    throw std::exception(); break;
                }
                CheckHR(device->CheckFeatureSupport(D3D12_FEATURE_COMMAND_QUEUE_PRIORITY, &command_queue_priority, sizeof(D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY)));
                Trace_D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY(os, command_queue_priority); ADD_LINE(os);
            }
        }
        return true;
    }

    bool CheckFeatureSupport(std::ostream& os, UINT node_index)
    {
        D3D_FEATURE_LEVEL feature_level_requests[] = { D3D_FEATURE_LEVEL_1_0_CORE
                                                     , D3D_FEATURE_LEVEL_9_1  , D3D_FEATURE_LEVEL_9_2 , D3D_FEATURE_LEVEL_9_3
                                                     , D3D_FEATURE_LEVEL_10_0 , D3D_FEATURE_LEVEL_10_1
                                                     , D3D_FEATURE_LEVEL_11_0 , D3D_FEATURE_LEVEL_11_1
                                                     , D3D_FEATURE_LEVEL_12_0 , D3D_FEATURE_LEVEL_12_1
        };
        D3D12_FEATURE_DATA_D3D12_OPTIONS                            d3d12_options                         {};
        D3D12_FEATURE_DATA_ARCHITECTURE                             architecture                          { node_index };
        D3D12_FEATURE_DATA_FEATURE_LEVELS                           feature_levels                        { _countof(feature_level_requests),feature_level_requests };
        D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT              gpu_virtual_address_support           {};
        D3D12_FEATURE_DATA_SHADER_MODEL                             shader_model                          { D3D_SHADER_MODEL_6_5 };
        D3D12_FEATURE_DATA_D3D12_OPTIONS1                           d3d12_options1                        {};
        D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT       protected_resource_session_support    { node_index };
        D3D12_FEATURE_DATA_ROOT_SIGNATURE                           root_signature                        { D3D_ROOT_SIGNATURE_VERSION_1_1 };
        D3D12_FEATURE_DATA_ARCHITECTURE1                            architecture1                         { node_index };
        D3D12_FEATURE_DATA_D3D12_OPTIONS2                           d3d12_options2                        {};
        D3D12_FEATURE_DATA_SHADER_CACHE                             shader_cache                          {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS3                           d3d12_options3                        {};
        D3D12_FEATURE_DATA_EXISTING_HEAPS                           existing_heaps                        {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS4                           d3d12_options4                        {};
        D3D12_FEATURE_DATA_SERIALIZATION                            serialization                         { node_index };
        D3D12_FEATURE_DATA_CROSS_NODE                               cross_node                            {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS5                           d3d12_options5                        {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS6                           d3d12_options6                        {};
        D3D12_FEATURE_DATA_QUERY_META_COMMAND                       query_meta_command                    {};

        D3D12_FEATURE_DATA_D3D12_OPTIONS7                           d3d12_options7                        {};
        D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT    protected_resource_session_type_count { node_index };
        D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES         protected_resource_session_types      {};
        std::vector<GUID>                                           session_types;

        D3D12_FEATURE f;
        auto CheckHR = [&](HRESULT hr) { if (FAILED(hr)) { os << "Failed to get " << f << '.' << std::endl; } };
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS                     ), &d3d12_options                     , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS                     )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_ARCHITECTURE                      ), &architecture                      , sizeof(D3D12_FEATURE_DATA_ARCHITECTURE                      )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_FEATURE_LEVELS                    ), &feature_levels                    , sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT       ), &gpu_virtual_address_support       , sizeof(D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT       )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_SHADER_MODEL                      ), &shader_model                      , sizeof(D3D12_FEATURE_DATA_SHADER_MODEL                      )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS1                    ), &d3d12_options1                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_SUPPORT), &protected_resource_session_support, sizeof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_ROOT_SIGNATURE                    ), &root_signature                    , sizeof(D3D12_FEATURE_DATA_ROOT_SIGNATURE                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_ARCHITECTURE1                     ), &architecture1                     , sizeof(D3D12_FEATURE_DATA_ARCHITECTURE1                     )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS2                    ), &d3d12_options2                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS2                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_SHADER_CACHE                      ), &shader_cache                      , sizeof(D3D12_FEATURE_DATA_SHADER_CACHE                      )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS3                    ), &d3d12_options3                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS3                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_EXISTING_HEAPS                    ), &existing_heaps                    , sizeof(D3D12_FEATURE_DATA_EXISTING_HEAPS                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS4                    ), &d3d12_options4                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS4                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_SERIALIZATION                     ), &serialization                     , sizeof(D3D12_FEATURE_DATA_SERIALIZATION                     )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_CROSS_NODE                        ), &cross_node                        , sizeof(D3D12_FEATURE_DATA_CROSS_NODE                        )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS5                    ), &d3d12_options5                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS6                    ), &d3d12_options6                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS6                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_QUERY_META_COMMAND                ), &query_meta_command                , sizeof(D3D12_FEATURE_DATA_QUERY_META_COMMAND                )));

        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT), &protected_resource_session_type_count, sizeof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT)));
        session_types.resize(protected_resource_session_type_count.Count);
        protected_resource_session_types.Count  = (UINT)session_types.size();
        protected_resource_session_types.pTypes = session_types.data();
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES     ), &protected_resource_session_types     , sizeof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES     )));

        ADD_LINE(os);
        ADD_LINE(os);

        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS                     (os, d3d12_options);                      ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS1                    (os, d3d12_options1);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS2                    (os, d3d12_options2);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS3                    (os, d3d12_options3);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS4                    (os, d3d12_options4);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS5                    (os, d3d12_options5);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS6                    (os, d3d12_options6);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS7                    (os, d3d12_options7);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_ARCHITECTURE                      (os, architecture);                       ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_ARCHITECTURE1                     (os, architecture1);                      ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_FEATURE_LEVELS                    (os, feature_levels);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT       (os, gpu_virtual_address_support);        ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_SHADER_MODEL                      (os, shader_model);                       ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT(os, protected_resource_session_support); ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_ROOT_SIGNATURE                    (os, root_signature);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_SHADER_CACHE                      (os, shader_cache);                       ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_EXISTING_HEAPS                    (os, existing_heaps);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_SERIALIZATION                     (os, serialization);                      ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_CROSS_NODE                        (os, cross_node);                         ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_QUERY_META_COMMAND                (os, query_meta_command);                 ADD_LINE(os);

        Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT  (os, protected_resource_session_type_count);            ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES       (os, protected_resource_session_types, session_types);  ADD_LINE(os);

        return true;
    }

    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS& d3d12_options)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options, DoublePrecisionFloatShaderOps, "                                              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, OutputMergerLogicOp, "                                                        ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, MinPrecisionSupport, "                                                        ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, TiledResourcesTier, "                                                         ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, ResourceBindingTier, "                                                        ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, PSSpecifiedStencilRefSupported, "                                             ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, TypedUAVLoadAdditionalFormats, "                                              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, ROVsSupported, "                                                              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, ConservativeRasterizationTier, "                                              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, MaxGPUVirtualAddressBitsPerResource, "                                        ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, StandardSwizzle64KBSupported, "                                               ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, CrossNodeSharingTier, "                                                       ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, CrossAdapterRowMajorTextureSupported, "                                       ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options, ResourceHeapTier, "                                                           ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_ARCHITECTURE(std::ostream& os, const D3D12_FEATURE_DATA_ARCHITECTURE& architecture)
    {
        os << "D3D12_FEATURE_DATA_ARCHITECTURE" << std::endl;
        ADD_TAB(os); ADD_STR3(os, architecture, NodeIndex, "         ");
        ADD_TAB(os); ADD_STR3(os, architecture, TileBasedRenderer, " ");
        ADD_TAB(os); ADD_STR3(os, architecture, UMA, "               ");
        ADD_TAB(os); ADD_STR3(os, architecture, CacheCoherentUMA, "  ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_FEATURE_LEVELS(std::ostream& os, const D3D12_FEATURE_DATA_FEATURE_LEVELS& feature_levels)
    {
        os << "D3D12_FEATURE_DATA_FEATURE_LEVELS" << std::endl;
        ADD_TAB(os); ADD_STR(os, feature_levels, MaxSupportedFeatureLevel);

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS(std::ostream& os, const D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS& multisample_quality_levels)
    {
        //os << "D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS" << std::endl;
        ADD_TAB(os); ADD_STR2(os, multisample_quality_levels, NumQualityLevels) << " where: "; ADD_STR2(os, multisample_quality_levels, SampleCount) << ", "; ADD_STR(os, multisample_quality_levels, Flags);

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT(std::ostream& os, const D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT& gpu_virtual_address_support)
    {
        os << "D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT" << std::endl;
        ADD_TAB(os); ADD_STR3(os, gpu_virtual_address_support, MaxGPUVirtualAddressBitsPerResource, " ");
        ADD_TAB(os); ADD_STR3(os, gpu_virtual_address_support, MaxGPUVirtualAddressBitsPerProcess, "  ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_SHADER_MODEL(std::ostream& os, const D3D12_FEATURE_DATA_SHADER_MODEL& shader_model)
    {
        os << "D3D12_FEATURE_DATA_SHADER_MODEL" << std::endl;
        ADD_TAB(os); ADD_STR(os, shader_model, HighestShaderModel);

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS1(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS1& d3d12_options1)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS1" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options1, WaveOps, "                       ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options1, WaveLaneCountMin, "              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options1, WaveLaneCountMax, "              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options1, TotalLaneCount, "                ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options1, ExpandedComputeResourceStates, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options1, Int64ShaderOps, "                ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT(std::ostream& os, const D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT& protected_resource_session_support)
    {
        os << "D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT" << std::endl;
        ADD_TAB(os); ADD_STR3(os, protected_resource_session_support, NodeIndex, " ");
        ADD_TAB(os); ADD_STR3(os, protected_resource_session_support, Support, "   ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_ROOT_SIGNATURE(std::ostream& os, const D3D12_FEATURE_DATA_ROOT_SIGNATURE& root_signature)
    {
        os << "D3D12_FEATURE_DATA_ROOT_SIGNATURE" << std::endl;
        ADD_TAB(os); ADD_STR(os, root_signature, HighestVersion);

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_ARCHITECTURE1(std::ostream& os, const D3D12_FEATURE_DATA_ARCHITECTURE1& architecture1)
    {
        os << "D3D12_FEATURE_DATA_ARCHITECTURE1" << std::endl;
        ADD_TAB(os); ADD_STR3(os, architecture1, NodeIndex, "         ");
        ADD_TAB(os); ADD_STR3(os, architecture1, TileBasedRenderer, " ");
        ADD_TAB(os); ADD_STR3(os, architecture1, UMA, "               ");
        ADD_TAB(os); ADD_STR3(os, architecture1, CacheCoherentUMA, "  ");
        ADD_TAB(os); ADD_STR3(os, architecture1, IsolatedMMU, "       ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS2(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS2& d3d12_options2)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS2" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options2, DepthBoundsTestSupported, "        ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options2, ProgrammableSamplePositionsTier, " ");
        
        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_SHADER_CACHE(std::ostream& os, const D3D12_FEATURE_DATA_SHADER_CACHE& shader_cache)
    {
        os << "D3D12_FEATURE_DATA_SHADER_CACHE" << std::endl;
        ADD_TAB(os); ADD_STR(os, shader_cache, SupportFlags);

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY(std::ostream& os, const D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY& command_queue_priority)
    {
        os << "D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY" << std::endl;        
        ADD_TAB(os); ADD_STR3(os,                               command_queue_priority, CommandListType, "            ");
        ADD_TAB(os); ADD_STR3(os, (D3D12_COMMAND_QUEUE_PRIORITY)command_queue_priority, Priority, "                   ");
        ADD_TAB(os); ADD_STR3(os,                               command_queue_priority, PriorityForTypeIsSupported, " ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS3(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS3& d3d12_options3)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS3" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options3, CopyQueueTimestampQueriesSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options3, CastingFullyTypedFormatSupported, "   ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options3, WriteBufferImmediateSupportFlags, "   ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options3, ViewInstancingTier, "                 ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options3, BarycentricsSupported, "              ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_EXISTING_HEAPS(std::ostream& os, const D3D12_FEATURE_DATA_EXISTING_HEAPS& existing_heaps)
    {
        os << "D3D12_FEATURE_DATA_EXISTING_HEAPS" << std::endl;
        ADD_TAB(os); ADD_STR(os, existing_heaps, Supported);
        
        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS4(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS4& d3d12_options4)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS4" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options4, MSAA64KBAlignedTextureSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options4, SharedResourceCompatibilityTier, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options4, Native16BitShaderOpsSupported, "   ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_SERIALIZATION(std::ostream& os, const D3D12_FEATURE_DATA_SERIALIZATION& serialization)
    {
        os << "D3D12_FEATURE_DATA_SERIALIZATION" << std::endl;
        ADD_TAB(os); ADD_STR3(os, serialization, NodeIndex, "             ");
        ADD_TAB(os); ADD_STR3(os, serialization, HeapSerializationTier, " ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_CROSS_NODE(std::ostream& os, const D3D12_FEATURE_DATA_CROSS_NODE& cross_node)
    {
        os << "D3D12_FEATURE_DATA_CROSS_NODE" << std::endl;
        ADD_TAB(os); ADD_STR3(os, cross_node, SharingTier, "              ");
        ADD_TAB(os); ADD_STR3(os, cross_node, AtomicShaderInstructions, " ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS5(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS5& d3d12_options5)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS5" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options5, SRVOnlyTiledResourceTier3, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options5, RenderPassesTier, "          ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options5, RaytracingTier, "            ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS6(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS6& d3d12_options6)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS6" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options6, AdditionalShadingRatesSupported, "                      ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options6, PerPrimitiveShadingRateSupportedWithViewportIndexing, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options6, VariableShadingRateTier, "                              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options6, ShadingRateImageTileSize, "                             ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options6, BackgroundProcessingSupported, "                        ");

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_QUERY_META_COMMAND(std::ostream& os, const D3D12_FEATURE_DATA_QUERY_META_COMMAND& query_meta_command)
    {
        // TODO: D3D12_FEATURE_DATA_QUERY_META_COMMAND
        os << "D3D12_FEATURE_DATA_QUERY_META_COMMAND" << std::endl;
        ADD_TAB(os); os << "TODO: D3D12_FEATURE_DATA_QUERY_META_COMMAND" << std::endl;

        //ADD_TAB(os); ADD_STR(os, query_meta_command, CommandId);
        //ADD_TAB(os); ADD_STR(os, query_meta_command, NodeMask);
        //ADD_TAB(os); ADD_STR(os, query_meta_command, pQueryInputData);
        //ADD_TAB(os); ADD_STR(os, query_meta_command, QueryInputDataSizeInBytes);
        //ADD_TAB(os); ADD_STR(os, query_meta_command, pQueryOutputData);
        //ADD_TAB(os); ADD_STR(os, query_meta_command, QueryOutputDataSizeInBytes);
        //_In_  GUID                                                          CommandId                 ;
        //_In_  UINT                                                          NodeMask                  ;
        //_Field_size_bytes_full_opt_(QueryInputDataSizeInBytes)  const void* pQueryInputData           ;
        //_In_  SIZE_T                                                        QueryInputDataSizeInBytes ;
        //_Field_size_bytes_full_(QueryOutputDataSizeInBytes)     void*       pQueryOutputData          ;
        //_In_  SIZE_T                                                        QueryOutputDataSizeInBytes;

        return true;
    };
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS7(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS7& d3d12_options7)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS7" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options7, MeshShaderTier, "      ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options7, SamplerFeedbackTier, " ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT(std::ostream& os, const D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT& protected_resource_session_type_count)
    {
        //protected_resource_session_type_count.
        os << "D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT" << std::endl;
        ADD_TAB(os); ADD_STR3(os, protected_resource_session_type_count, NodeIndex, " ");
        ADD_TAB(os); ADD_STR3(os, protected_resource_session_type_count, Count, "     ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES(std::ostream& os, const D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES& protected_resource_session_types, const std::vector<GUID>& session_types)
    {
        os << "D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES" << std::endl;
        ADD_TAB(os); ADD_STR3(os, protected_resource_session_types, Count, "     ");
        size_t count = 0;
        for (auto& i : session_types) { ADD_TAB(os);         os << "pTypes[" << count++ << "] = " << i << std::endl; }

        return true;
    }

private:
    Ptr<IDXGIFactory2> factory;
    Ptr<IDXGIAdapter1> adapter;
    Ptr<ID3D12Device> device;

};

void PrintHelp(const char *argv0) 
{
    std::cout << "\nD3D12FeatureViewer\n\n";

    std::cout << "USAGE: " << argv0 << " [OPTIONS]\n\n";

    std::cout << "OPTIONS:\n";
    std::cout << "-h                        Print this help.\n\n";

    std::cout << "--adapter <node index>    The adapter index to create the device. The default is 0.\n";
    std::cout << "                          Corresponds to IDXGIFactory1::EnumAdapters1::Adapter.\n\n";

    std::cout << "--node <adapter index>    The node index to get feature data. The default is 0.\n";
    std::cout << "                          Corresponds to D3D12_FEATURE_DATA*::NodeIndex(if exists).\n\n";

    std::cout << "--show-queue-priorities   Show all D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY specified for each command list type and each priority.\n\n";
    std::cout << "--show-formats [msql]     Show the format features and multi-sample quality levels(msql) optionally.\n\n";
}

int main(int argc, const char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    {
        UINT adapter                  = 0;
        UINT node                     = 0;
        bool is_show_formats          = false;
        bool is_show_msql             = false;
        bool is_show_queue_priorities = false;

        auto Cmp = [](auto argname, auto arg) { return strncmp(argname, arg, strlen(arg)) == 0; };
        for (int i = 0; i < argc; i++)
        {
            if (Cmp("-h", argv[i]))
            {
                PrintHelp(argv[0]);
                return 0;
            }
            
            else if (Cmp("--adapter", argv[i]))
            {
                if ((i + 1) < argc)
                    adapter = (UINT)atoi(argv[++i]);
            }

            else if (Cmp("--node", argv[i]))
            {
                if ((i + 1) < argc)
                    node = (UINT)atoi(argv[++i]);
            }
            
            else if (Cmp("--show-queue-priorities", argv[i]))
            {
                is_show_queue_priorities = true;
            }

            else if (Cmp("--show-formats", argv[i]))
            {
                is_show_formats = true;
                
                if ((i + 1) < argc && Cmp("msql", argv[++i]))
                    is_show_msql = true;
            }
        }

        D3D12FeatureViewer viewer;
        if (!viewer.Init(adapter))
            return 1;

        viewer.CheckFeatureSupport(std::cout, node);

        if (is_show_queue_priorities)
            viewer.CheckQueuePrioritySupports(std::cout);

        if (is_show_formats)
            viewer.CheckFormatSupports(std::cout, is_show_msql);

    }
    _CrtDumpMemoryLeaks();

    return 0;
}
