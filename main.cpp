#include <array>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "MaaFramework/MaaAPI.h"
#include "MaaToolkit/MaaToolkitAPI.h"

#include "conf.h"

MaaController* create_adb_controller();
MaaController* create_win32_controller();

int main([[maybe_unused]] int argc, char** argv)
{
    std::string user_path = "./";
    MaaToolkitConfigInitOption(user_path.c_str(), "{}");

    auto controller_handle = create_adb_controller();
    // auto controller_handle = create_win32_controller();
    auto ctrl_id = MaaControllerPostConnection(controller_handle);

    auto resource_handle = MaaResourceCreate(nullptr, nullptr);
    std::string resource_dir = R"(/Volumes/Data/Workspace/MaaFramework/sample/resource)";
    auto res_id = MaaResourcePostBundle(resource_handle, resource_dir.c_str());

    MaaControllerWait(controller_handle, ctrl_id);
    MaaResourceWait(resource_handle, res_id);

    auto tasker_handle = MaaTaskerCreate(nullptr, nullptr);
    MaaTaskerBindResource(tasker_handle, resource_handle);
    MaaTaskerBindController(tasker_handle, controller_handle);

    auto destroy = [&]() {
        MaaTaskerDestroy(tasker_handle);
        MaaResourceDestroy(resource_handle);
        MaaControllerDestroy(controller_handle);
    };

    if (!MaaTaskerInited(tasker_handle)) {
        std::cout << "Failed to init MAA" << std::endl;

        destroy();
        return -1;
    }

    auto task_id = MaaTaskerPostTask(tasker_handle, "MyTask", "{}");
    MaaTaskerWait(tasker_handle, task_id);

    destroy();

    return 0;
}

MaaController* create_adb_controller()
{
    auto list_handle = MaaToolkitAdbDeviceListCreate();
    auto destroy = [&]() {
        MaaToolkitAdbDeviceListDestroy(list_handle);
    };

    MaaToolkitAdbDeviceFind(list_handle);

    size_t size = MaaToolkitAdbDeviceListSize(list_handle);
    if (size == 0) {
        std::cout << "No device found" << std::endl;

        destroy();
        return nullptr;
    }

    const int kIndex = 0; // for demo, we just use the first device
    auto device_handle = MaaToolkitAdbDeviceListAt(list_handle, kIndex);

    std::string agent_path = "share/MaaAgentBinary";
    auto controller_handle = MaaAdbControllerCreate(
        MaaToolkitAdbDeviceGetAdbPath(device_handle),
        MaaToolkitAdbDeviceGetAddress(device_handle),
        MaaToolkitAdbDeviceGetScreencapMethods(device_handle),
        MaaToolkitAdbDeviceGetInputMethods(device_handle),
        MaaToolkitAdbDeviceGetConfig(device_handle),
        agent_path.c_str(),
        nullptr,
        nullptr);

    destroy();

    return controller_handle;
}

MaaController* create_win32_controller()
{
    void* hwnd = nullptr; // It's a HWND, you can find it by yourself without MaaToolkit API

    auto list_handle = MaaToolkitDesktopWindowListCreate();
    auto destroy = [&]() {
        MaaToolkitDesktopWindowListDestroy(list_handle);
    };

    MaaToolkitDesktopWindowFindAll(list_handle);

    size_t size = MaaToolkitDesktopWindowListSize(list_handle);

    if (size == 0) {
        std::cout << "No window found" << std::endl;

        destroy();
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i) {
        auto window_handle = MaaToolkitDesktopWindowListAt(list_handle, i);
        std::string class_name = MaaToolkitDesktopWindowGetClassName(window_handle);
        std::string window_name = MaaToolkitDesktopWindowGetWindowName(window_handle);

        if (window_name == "原神") {
            hwnd = MaaToolkitDesktopWindowGetHandle(window_handle);
            break;
        }
    }

    // create controller by hwnd
    auto controller_handle =
        MaaWin32ControllerCreate(hwnd, MaaWin32ScreencapMethod_DXGI_DesktopDup, MaaWin32InputMethod_Seize, nullptr, nullptr);

    destroy();
    return controller_handle;
}
