/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include <sc-memory/cpp/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "FindingOfLakesWithBiggerAreaAgent.generated.hpp"

using namespace std;

namespace exampleModule
{

class FindingOfLakesWithBiggerAreaAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_find_lake_with_bigger_area, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

    bool isLakeBigger(const ScAddr &lake, double currentSquare, const ScAddr &answer);
    string getLinkContent(const ScAddr &link);

};

} // namespace exampleModule
