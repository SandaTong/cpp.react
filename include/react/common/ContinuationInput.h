
//          Copyright Sebastian Jeckel 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "react/Defs.h"

#include <functional>
#include <memory>
#include <mutex>

#include "tbb/concurrent_vector.h"

/***************************************/ REACT_IMPL_BEGIN /**************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////
/// ContinuationInput
///////////////////////////////////////////////////////////////////////////////////////////////////
class ContinuationInput
{
public:
    using InputClosureT = std::function<void()>;
    using InputVectT    = tbb::concurrent_vector<InputClosureT>;
    
    // Note: Shouldn't this be generated by default? Apparently it isn't.
    inline ContinuationInput& operator=(ContinuationInput&& other)
    {
        bufferedInputsPtr_ = std::move(other.bufferedInputsPtr_);
        return *this;
    }

    inline bool IsEmpty() const { return bufferedInputsPtr_ == nullptr; }

    template <typename F>
    void Add(F&& input)
    {
        std::call_once(bufferedInputsInit_, [this] {
            bufferedInputsPtr_.reset(new InputVectT());
        });
        bufferedInputsPtr_->push_back(std::forward<F>(input));
    }

    inline void Execute()
    {
        if (bufferedInputsPtr_ != nullptr)
        {
            for (auto f : *bufferedInputsPtr_)
                f();
            bufferedInputsPtr_->clear();
        }
    }

private:
    std::once_flag                  bufferedInputsInit_;
    std::unique_ptr<InputVectT>     bufferedInputsPtr_ = nullptr;
};

/****************************************/ REACT_IMPL_END /***************************************/