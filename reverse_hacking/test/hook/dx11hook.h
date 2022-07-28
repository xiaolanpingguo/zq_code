#include <functional>

namespace Dx11Hook
{
    struct ConfigData
    {
        void* gameWindow;
        std::function<void(void)> renderFun;
    };

    bool start(const ConfigData& config);
    bool shutdown();
}