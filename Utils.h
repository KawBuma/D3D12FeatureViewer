#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include <dxgi1_6.h>
#include <d3d12.h>

//#define ADD_IF(val, op ,ev) if (val op ev) os << #ev

#define CASE_ADD(dst, ev) case ev : dst += #ev; break
#define CASE_ADD2(dst, ev, custom) case ev : dst += custom; break
#define CASE_ADD3(dst, ev) case ev : dst << #ev; break
#define CASE_ADD4(dst, ev, custom) case ev : dst << custom; break
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

inline void AddBar(std::string& x) { if (!x.empty()) x += " | "; }

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

inline std::ostream& operator<< (std::ostream& os, D3D12_SHADER_MIN_PRECISION_SUPPORT val)
{
    std::string s;
    ADD_IF2(s, val, ==, D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE);
    ADD_IF2(s, val, &, D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT);
    ADD_IF2(s, val, &, D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT);

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_TILED_RESOURCES_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_RESOURCE_BINDING_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_CONSERVATIVE_RASTERIZATION_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_CROSS_NODE_SHARING_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_RESOURCE_HEAP_TIER val)
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

inline std::ostream& operator<< (std::ostream& os, D3D_FEATURE_LEVEL val)
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
    ADD_IF2(s, val, &, D3D_FEATURE_LEVEL_12_2);

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, DXGI_FORMAT val)
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
        CASE_ADD(s, DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE);
        CASE_ADD(s, DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE);
        CASE_ADD(s, DXGI_FORMAT_FORCE_UINT);
    default:
        break;
    }

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS val)
{
    std::string s;
    ADD_IF3(s, val, == , D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE, "NONE");
    ADD_IF3(s, val, & , D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_TILED_RESOURCE, "TILED_RESOURCE");

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D_SHADER_MODEL val)
{
    std::string s;
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_5_1);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_0);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_1);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_2);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_3);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_4);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_5);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_6);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_7);
    ADD_IF2(s, val, &, D3D_SHADER_MODEL_6_8);

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D_ROOT_SIGNATURE_VERSION val)
{
    std::string s;
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1);
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1_0);
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1_1);
    ADD_IF2(s, val, &, D3D_ROOT_SIGNATURE_VERSION_1_2);

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_SHADER_CACHE_SUPPORT_FLAGS val)
{
    std::string s;
    ADD_IF2(s, val, == , D3D12_SHADER_CACHE_SUPPORT_NONE);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_LIBRARY);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_SHADER_CONTROL_CLEAR);
    ADD_IF2(s, val, &, D3D12_SHADER_CACHE_SUPPORT_SHADER_SESSION_DELETE);

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_COMMAND_LIST_TYPE val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_COMMAND_QUEUE_PRIORITY val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_COMMAND_LIST_SUPPORT_FLAGS val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_VIEW_INSTANCING_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0);
        CASE_ADD(s, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1);
        CASE_ADD(s, D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_2);
    default:
        break;
    }

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_HEAP_SERIALIZATION_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_RENDER_PASS_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_RAYTRACING_TIER val)
{
    std::string s;
    switch (val)
    {
        CASE_ADD(s, D3D12_RAYTRACING_TIER_NOT_SUPPORTED);
        CASE_ADD(s, D3D12_RAYTRACING_TIER_1_0);
        CASE_ADD(s, D3D12_RAYTRACING_TIER_1_1);
    default:
        break;
    }

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_VARIABLE_SHADING_RATE_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_FORMAT_SUPPORT1 val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_FORMAT_SUPPORT2 val)
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
    ADD_IF4(s, val, &, D3D12_FORMAT_SUPPORT2_SAMPLER_FEEDBACK                            , "SAMPLER_FEEDBACK"                            , Align(); );

    return os << s;
}
inline std::ostream& operator<< (std::ostream& os, const GUID& val)
{
    std::string s;
    return os << GetUUIDString(reinterpret_cast<const uint8_t*>(&val));
}
inline std::ostream& operator<< (std::ostream& os, D3D12_MESH_SHADER_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_SAMPLER_FEEDBACK_TIER val)
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
inline std::ostream& operator<< (std::ostream& os, D3D12_WAVE_MMA_TIER val)
{
    switch (val)
    {
        CASE_ADD3(os, D3D12_WAVE_MMA_TIER_NOT_SUPPORTED);
        CASE_ADD3(os, D3D12_WAVE_MMA_TIER_1_0);
    default:
        break;
    }

    return os;
}
inline std::ostream& operator<< (std::ostream& os, D3D12_FEATURE val)
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
        CASE_ADD(s, D3D12_FEATURE_DISPLAYABLE);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS6);
        CASE_ADD(s, D3D12_FEATURE_QUERY_META_COMMAND);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS7);
        CASE_ADD(s, D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT);
        CASE_ADD(s, D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS8);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS9);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS10);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS11);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS12);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS13);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS14);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS15);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS16);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS17);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS18);
        CASE_ADD(s, D3D12_FEATURE_D3D12_OPTIONS19);
    default:
        break;
    }

    return os << s;
}


#pragma endregion os operators
