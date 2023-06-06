#include "Utils.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <wrl.h>
template<typename T>
using Ptr = Microsoft::WRL::ComPtr<T>;

/// @brief D3D12FeatureViewer 指定の D3D12 Agility SDK バージョン
extern "C" __declspec(dllexport) const UINT D3D12SDKVersion = 610;

/// @brief D3D12FeatureViewer 指定の D3D12 Agility SDK ライブラリへのパス
extern "C" __declspec(dllexport) const char* D3D12SDKPath = ".\\D3D12\\";

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
        std::cout << "D3D12FeatureViewer" << std::endl;

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

        if (FAILED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_1, IID_PPV_ARGS(&device))))
        {
            std::cout << "Failed to create device." << std::endl;
            return false;
        }

        Microsoft::WRL::ComPtr<ID3D12DeviceConfiguration> device_config;
        if (SUCCEEDED(device.As(&device_config)))
        {
            auto config_desc = device_config->GetDesc();
            std::cout << "Agility SDK Version: " << config_desc.SDKVersion << std::endl;
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
        constexpr int FORMAT_COUNT = (int)DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE + 1;
        for (int i = 1; i < FORMAT_COUNT; i++)
        {
            auto format = (DXGI_FORMAT)i;
            if (!IsKnownFromat(format))
                continue;

            os << (format_support.Format = format_info.Format = format) << std::endl;
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
                                                     , D3D_FEATURE_LEVEL_12_0 , D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_2
        };
        D3D12_FEATURE_DATA_D3D12_OPTIONS                            d3d12_options                         {};
        D3D12_FEATURE_DATA_ARCHITECTURE                             architecture                          { node_index };
        D3D12_FEATURE_DATA_FEATURE_LEVELS                           feature_levels                        { _countof(feature_level_requests),feature_level_requests };
        D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT              gpu_virtual_address_support           {};
        D3D12_FEATURE_DATA_SHADER_MODEL                             shader_model                          { D3D_HIGHEST_SHADER_MODEL };
        D3D12_FEATURE_DATA_D3D12_OPTIONS1                           d3d12_options1                        {};
        D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT       protected_resource_session_support    { node_index };
        D3D12_FEATURE_DATA_ROOT_SIGNATURE                           root_signature                        { D3D_ROOT_SIGNATURE_VERSION_1_2 };
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

        D3D12_FEATURE_DATA_DISPLAYABLE                              displayable                           {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS8                           d3d12_options8                        {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS9                           d3d12_options9                        {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS10                          d3d12_options10                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS11                          d3d12_options11                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS12                          d3d12_options12                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS13                          d3d12_options13                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS14                          d3d12_options14                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS15                          d3d12_options15                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS16                          d3d12_options16                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS17                          d3d12_options17                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS18                          d3d12_options18                       {};
        D3D12_FEATURE_DATA_D3D12_OPTIONS19                          d3d12_options19                       {};

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

        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS7                    ), &d3d12_options7                    , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS7                    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT), &protected_resource_session_type_count, sizeof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT)));
        session_types.resize(protected_resource_session_type_count.Count);
        protected_resource_session_types.Count  = (UINT)session_types.size();
        protected_resource_session_types.pTypes = session_types.data();
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES     ), &protected_resource_session_types     , sizeof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES     )));

        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_DISPLAYABLE    ), &displayable    , sizeof(D3D12_FEATURE_DATA_DISPLAYABLE    )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS8 ), &d3d12_options8 , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS8 )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS9 ), &d3d12_options9 , sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS9 )));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS10), &d3d12_options10, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS10)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS11), &d3d12_options11, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS11)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS12), &d3d12_options12, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS12)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS13), &d3d12_options13, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS13)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS14), &d3d12_options14, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS14)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS15), &d3d12_options15, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS15)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS16), &d3d12_options16, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS16)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS17), &d3d12_options17, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS17)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS18), &d3d12_options18, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS18)));
        CheckHR(device->CheckFeatureSupport((f = D3D12_FEATURE_D3D12_OPTIONS19), &d3d12_options19, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS19)));

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
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS8                    (os, d3d12_options8 );                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS9                    (os, d3d12_options9 );                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS10                   (os, d3d12_options10);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS11                   (os, d3d12_options11);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS12                   (os, d3d12_options12);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS13                   (os, d3d12_options13);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS14                   (os, d3d12_options14);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS15                   (os, d3d12_options15);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS16                   (os, d3d12_options16);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS17                   (os, d3d12_options17);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS18                   (os, d3d12_options18);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS19                   (os, d3d12_options19);                    ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_ARCHITECTURE                      (os, architecture);                       ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_ARCHITECTURE1                     (os, architecture1);                      ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_FEATURE_LEVELS                    (os, feature_levels);                     ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT       (os, gpu_virtual_address_support);        ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_SHADER_MODEL                      (os, shader_model);                       ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT(os, protected_resource_session_support); ADD_LINE(os);
        Trace_D3D12_FEATURE_DATA_DISPLAYABLE                       (os, displayable);                        ADD_LINE(os);
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
    bool Trace_D3D12_FEATURE_DATA_DISPLAYABLE(std::ostream& os, const D3D12_FEATURE_DATA_DISPLAYABLE& displayable)
    {
        os << "D3D12_FEATURE_DATA_DISPLAYABLE" << std::endl;
        ADD_TAB(os); ADD_STR3(os, displayable, DisplayableTexture, "              ");
        ADD_TAB(os); ADD_STR3(os, displayable, SharedResourceCompatibilityTier, " ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS8(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS8& d3d12_options8)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS8" << std::endl;
        ADD_TAB(os); ADD_STR(os, d3d12_options8, UnalignedBlockTexturesSupported);

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS9(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS9& d3d12_options9)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS9" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options9, MeshShaderPipelineStatsSupported, "                  ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options9, MeshShaderSupportsFullRangeRenderTargetArrayIndex, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options9, AtomicInt64OnTypedResourceSupported, "               ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options9, AtomicInt64OnGroupSharedSupported, "                 ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options9, DerivativesInMeshAndAmplificationShadersSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options9, WaveMMATier, "                                       ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS10(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS10& d3d12_options10)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS10" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options10, VariableRateShadingSumCombinerSupported, "    ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options10, MeshShaderPerPrimitiveShadingRateSupported, " ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS11(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS11& d3d12_options11)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS11" << std::endl;
        ADD_TAB(os); ADD_STR(os, d3d12_options11, AtomicInt64OnDescriptorHeapResourceSupported);

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS12(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS12& d3d12_options12)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS12" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options12, MSPrimitivesPipelineStatisticIncludesCulledPrimitives, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options12, EnhancedBarriersSupported, "                             ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options12, RelaxedFormatCastingSupported, "                         ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS13(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS13& d3d12_options13)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS13" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options13, UnrestrictedBufferTextureCopyPitchSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options13, UnrestrictedVertexElementAlignmentSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options13, InvertedViewportHeightFlipsYSupported, "       ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options13, InvertedViewportDepthFlipsZSupported, "        ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options13, TextureCopyBetweenDimensionsSupported, "       ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options13, AlphaBlendFactorSupported, "                   ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS14(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS14& d3d12_options14)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS14" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options14, AdvancedTextureOpsSupported, "                    ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options14, WriteableMSAATexturesSupported, "                 ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options14, IndependentFrontAndBackStencilRefMaskSupported, " ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS15(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS15& d3d12_options15)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS15" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options15, TriangleFanSupported, "                ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options15, DynamicIndexBufferStripCutSupported, " ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS16(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS16& d3d12_options16)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS16" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options16, DynamicDepthBiasSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options16, GPUUploadHeapSupported, "    ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS17(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS17& d3d12_options17)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS17" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options17, NonNormalizedCoordinateSamplersSupported, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options17, ManualWriteTrackingResourceSupported, "     ");

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS18(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS18& d3d12_options18)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS18" << std::endl;
        ADD_TAB(os); ADD_STR(os, d3d12_options18, RenderPassesValid);

        return true;
    }
    bool Trace_D3D12_FEATURE_DATA_D3D12_OPTIONS19(std::ostream& os, const D3D12_FEATURE_DATA_D3D12_OPTIONS19& d3d12_options19)
    {
        os << "D3D12_FEATURE_DATA_D3D12_OPTIONS19" << std::endl;
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, MismatchingOutputDimensionsSupported, "           ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, SupportedSampleCountsWithNoOutputs, "             ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, PointSamplingAddressesNeverRoundUp, "             ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, RasterizerDesc2Supported, "                       ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, NarrowQuadrilateralLinesSupported, "              ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, AnisoFilterWithPointMipSupported, "               ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, MaxSamplerDescriptorHeapSize, "                   ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, MaxSamplerDescriptorHeapSizeWithStaticSamplers, " ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, MaxViewDescriptorHeapSize, "                      ");
        ADD_TAB(os); ADD_STR3(os, d3d12_options19, ComputeOnlyCustomHeapSupported, "                 ");

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
    std::cout << "-h                            Print this help message.\n\n";

    std::cout << "--adapter <adapter index>     The adapter index to create the device. The default is 0.\n";
    std::cout << "                              Corresponds to IDXGIFactory1::EnumAdapters1::Adapter.\n\n";

    std::cout << "--node <node index>           The node index to get feature data. The default is 0.\n";
    std::cout << "                              Corresponds to D3D12_FEATURE_DATA*::NodeIndex (if exists).\n\n";

    std::cout << "--show-queue-priorities       Show all D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY specified for each command list type and each priority.\n\n";
    std::cout << "--show-formats [msql]         Show the format features and multi-sample quality levels(msql) optionally.\n\n";
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
                    adapter = (UINT)atoi(argv[i + 1]);
            }

            else if (Cmp("--node", argv[i]))
            {
                if ((i + 1) < argc)
                    node = (UINT)atoi(argv[i + 1]);
            }

            else if (Cmp("--show-queue-priorities", argv[i]))
            {
                is_show_queue_priorities = true;
            }

            else if (Cmp("--show-formats", argv[i]))
            {
                is_show_formats = true;

                if ((i + 1) < argc && Cmp("msql", argv[i + 1]))
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
