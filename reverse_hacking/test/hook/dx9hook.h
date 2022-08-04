#include <functional>

namespace Dx9Hook
{
    struct ConfigData
    {
        void* gameWindow;
        std::function<void(void)> renderFun;
    };

    void start(const ConfigData& config);
}