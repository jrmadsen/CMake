/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmSetCommand_h
#define cmSetCommand_h

#include "cmConfigure.h"  // IWYU pragma: keep

#include <string>
#include <vector>

#include "cmCommand.h"

class cmExecutionStatus;

/** \class cmSetCommand
 * \brief Set a CMAKE variable
 *
 * cmSetCommand sets a variable to a value with expansion.
 */
class cmSetCommand : public cmCommand
{
public:
    /**
     * This is a virtual constructor for the command.
     */
    cmCommand* Clone() override { return new cmSetCommand; }

    /**
     * This is called when the command is first encountered in
     * the CMakeLists.txt file.
     */
    bool InitialPass(std::vector<std::string> const& args,
                     cmExecutionStatus&              status) override;
};

#endif
