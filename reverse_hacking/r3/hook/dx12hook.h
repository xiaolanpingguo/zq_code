#include <functional>

namespace Dx12Hook
{
    struct ConfigData
    {
        void* gameWindow;
        std::function<void(void)> renderFun;
    };

    void start(const ConfigData& config);
}