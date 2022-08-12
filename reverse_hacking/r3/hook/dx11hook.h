#include <functional>

namespace Dx11Hook
{
    struct ConfigData
    {
        void* gameWindow;
        std::function<void(void)> renderFun;
    };

    void start(const ConfigData& config);
}