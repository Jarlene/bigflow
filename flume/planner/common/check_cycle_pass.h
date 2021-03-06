/***************************************************************************
 *
 * Copyright (c) 2014 Baidu, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **************************************************************************/
// Author: Wang Cong <bigflow-opensource@baidu.com>

#ifndef FLUME_PLANNER_COMMON_CHECK_CYCLE_PASS_H_
#define FLUME_PLANNER_COMMON_CHECK_CYCLE_PASS_H_

#include <set>
#include <utility>
#include <vector>

#include "flume/planner/common/data_flow_analysis.h"
#include "flume/planner/pass.h"
#include "flume/planner/pass_manager.h"

namespace baidu {
namespace flume {
namespace planner {

class Plan;
class Unit;

/**
* @brief    For one scope, if any flow streamed out of it streames back into it,
*           we call it a scope cycle.
*
*           For example, in the plan shown below, a cycle exists for scope s1:
*
*             +-------+
*             | node3 |----------------+
*             |       |                |
*             +-------+                |
*                 ^                    |
*           +-----|--------------------|------+
*           |     |                   \/      |
*           | +-------+            +--------+ |
*           | | node2 |            | shuffle| |
*           | |       |            |  node  | |
*           | +-------+            +--------+ |
*           |     ^                           |
*           |     |                           |
*           | +-------+     Scope s1          |
*           | | node1 |                       |
*           | |       |                       |
*           | +-------+                       |
*           +---------------------------------+
*
*           This pass stops the process if such cycle is found, for cycle is not
*           supported(yet).
*
*/
class CheckCyclePass : public Pass {
    RELY_PASS(DataFlowAnalysis);
    PRESERVE_BY_DEFAULT();

public:
    virtual bool Run(Plan* plan);
};

}  // namespace planner
}  // namespace flume
}  // namespace baidu

#endif  // FLUME_PLANNER_COMMON_CHECK_CYCLE_PASS_H_
