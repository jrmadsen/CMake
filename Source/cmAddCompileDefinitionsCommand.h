/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmAddCompileDefinitionsCommand_h
#define cmAddCompileDefinitionsCommand_h

#include "cmConfigure.h"  // IWYU pragma: keep

#include <string>
#include <vector>

#include "cmCommand.h"

class cmExecutionStatus;

class cmAddCompileDefinitionsCommand : public cmCommand
{
public:
    /**
     * This is a virtual constructor for the command.
     */
    cmCommand* Clone() override { return new cmAddCompileDefinitionsCommand; }

    /**
     * This is called when the command is first encountered in
     * the CMakeLists.txt file.
     */
    bool InitialPass(std::vector<std::string> const& args,
                     cmExecutionStatus&              status) override;
};

#endif
