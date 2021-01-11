/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-memory/cpp/sc_stream.hpp>
#include <sc-kpm/sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/AgentUtils.hpp>

#include <sc-memory/cpp/sc_link.hpp>

#include "FindingOfLakesWithBiggerAreaAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace exampleModule
{

SC_AGENT_IMPLEMENTATION(FindingOfLakesWithBiggerAreaAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!param.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  double currentSquare;
    ScTemplate templ1;
    templ1.Triple(
            param,
            ScType::EdgeDCommonVar >> "edge",
    ScType::Link >> "area");
    templ1.Triple(
            Keynodes::area,
            ScType::EdgeAccessVarPosPerm,
            "edge");

    ScTemplateSearchResult result;
    ms_context->HelperSearchTemplate(templ1, result);
    if (result.Size()==0) currentSquare = 0;
    string area = getLinkContent(result[0]["area"]);
    if (area.empty()) currentSquare = 0;

    try
    {
        area.erase(0,1);
        currentSquare = atof(area.c_str());
    } catch (...)
    {
        currentSquare = 0;
    }

    ScTemplate templ;
    templ.Triple(
            ScType::NodeVar >> "lake",
            ScType::EdgeDCommonVar >> "edge",
            Keynodes::Lake);
    templ.Triple(
            Keynodes::instance_of,
            ScType::EdgeAccessVarPosPerm >> "pos",
            "edge");

    ScTemplateSearchResult lakes;
    ms_context->HelperSearchTemplate(templ, lakes);

    for (size_t a = 0; a < lakes.Size(); a++)
    {
        if (isLakeBigger(lakes[a]["lake"], currentSquare, answer))
        {
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, lakes[a]["edge"]);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, lakes[a]["pos"]);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::Lake);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::instance_of);
        }
    }

  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}

bool FindingOfLakesWithBiggerAreaAgent::isLakeBigger(const ScAddr &lake, double currentSquare,const ScAddr &answer) {
    ScTemplate templ;
    templ.Triple(
            lake,
            ScType::EdgeDCommonVar >> "edge",
            ScType::Link >> "area");
    templ.Triple(
            Keynodes::area,
            ScType::EdgeAccessVarPosPerm >> "pos",
            "edge");

    ScTemplateSearchResult result;
    ms_context->HelperSearchTemplate(templ, result);
    if (result.Size()==0) return false;
    string area = getLinkContent(result[0]["area"]);
    if (area.empty()) return false;
    try
    {
        area.erase(0,1);
        double square = atof(area.c_str());
        if (square > currentSquare) {
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, lake);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, result[0]["edge"]);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, result[0]["area"]);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::area);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, result[0]["pos"]);
            return true;
        }
    }
    catch (...)
    {}
    return false;
}

string FindingOfLakesWithBiggerAreaAgent::getLinkContent(const ScAddr &link)
{
    ScStream stream;
    try
    {
        ms_context->GetLinkContent(link, stream);
    }
    catch (...)
    {
        return "";
    }

    size_t size = stream.Size();
    auto *text = new sc_char[size + 1];
    stream.Read(text, size, size);
    text[size] = '\0';
    string res(text);

    return res;
}
}
