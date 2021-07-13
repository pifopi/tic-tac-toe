#pragma once

#include <array>
#include <cstdint>

namespace TicTacToe
{
    using U8 = uint8_t;
    using U16 = uint16_t;
    using U32 = uint32_t;
    using U64 = uint64_t;

    using S8 = int8_t;
    using S16 = int16_t;
    using S32 = int32_t;
    using S64 = int64_t;

    enum class Player
    {
        Empty,
        Cross,
        Nought
    };

    namespace
    {
        constexpr U8 k_sizeGrid = 3;
    }

    class NonCopyable
    {
    private:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    class NonMoveable
    {
    private:
        NonMoveable(const NonMoveable&) = delete;
        NonMoveable(NonMoveable&&) = delete;
    };
}
