
//          Copyright Sebastian Jeckel 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef REACT_DETAIL_EVENTBASE_H_INCLUDED
#define REACT_DETAIL_EVENTBASE_H_INCLUDED

#pragma once

#include "react/detail/Defs.h"

#include <utility>

#include "react/detail/ReactiveBase.h"
#include "react/detail/ReactiveInput.h"
#include "react/detail/graph/EventNodes.h"

/***************************************/ REACT_IMPL_BEGIN /**************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////
/// EventStreamBase
///////////////////////////////////////////////////////////////////////////////////////////////////
template
<
    typename D,
    typename E
>
class EventStreamBase : public ReactiveBase<EventStreamNode<D,E>>
{
public:
    EventStreamBase() = default;
    EventStreamBase(const EventStreamBase&) = default;

    template <typename T>
    explicit EventStreamBase(T&& ptr) :
        EventStreamBase::ReactiveBase( std::forward<T>(ptr) )
    {}

protected:
    template <typename T>
    void emit(T&& e) const
    {
        InputManager<D>::AddInput(
            *reinterpret_cast<EventSourceNode<D,E>*>(this->ptr_.get()),
            std::forward<T>(e));
    }
};

/****************************************/ REACT_IMPL_END /***************************************/

#endif // REACT_DETAIL_EVENTBASE_H_INCLUDED