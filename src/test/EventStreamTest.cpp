
//          Copyright Sebastian Jeckel 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "EventStreamTest.h"

#include "react/engine/PulseCountEngine.h"
#include "react/engine/TopoSortEngine.h"
#include "react/engine/SubtreeEngine.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace {

using namespace react;

INSTANTIATE_TYPED_TEST_CASE_P(SeqTopoSort, EventStreamTest, TopoSortEngine<sequential>);
INSTANTIATE_TYPED_TEST_CASE_P(ParTopoSort, EventStreamTest, TopoSortEngine<parallel>);
INSTANTIATE_TYPED_TEST_CASE_P(PulseCount, EventStreamTest, PulseCountEngine<parallel>);
INSTANTIATE_TYPED_TEST_CASE_P(Subtree, EventStreamTest, SubtreeEngine<parallel>);

} // ~namespace