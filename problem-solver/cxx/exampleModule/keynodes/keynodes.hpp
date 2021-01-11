/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include "sc-memory/cpp/sc_addr.hpp"
#include "sc-memory/cpp/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace exampleModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:

  SC_PROPERTY(Keynode("question_find_subdividing"), ForceCreate)
  static ScAddr question_find_subdividing;
    SC_PROPERTY(Keynode("question_find_lake_with_bigger_area"), ForceCreate)
    static ScAddr question_find_lake_with_bigger_area;

  SC_PROPERTY(Keynode("nrel_subdividing"), ForceCreate)
  static ScAddr nrel_subdividing;

  SC_PROPERTY(Keynode("nrel_sc_text_translation"), ForceCreate)
  static ScAddr nrel_sc_text_translation;

    SC_PROPERTY(Keynode("instance_of"), ForceCreate)
    static ScAddr instance_of;

    SC_PROPERTY(Keynode("area"), ForceCreate)
    static ScAddr area;

    SC_PROPERTY(Keynode("Lake"), ForceCreate)
    static ScAddr Lake;

};

} // namespace exampleModule
