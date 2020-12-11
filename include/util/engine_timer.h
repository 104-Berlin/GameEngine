#pragma once

namespace Engine {
    class ETimer
    {
    public:
        ETimer();
        float Reset();
    private:
        std::chrono::steady_clock::time_point last;
    };
}