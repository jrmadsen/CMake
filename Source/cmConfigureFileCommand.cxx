/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include "cmConfigureFileCommand.h"

#include <sstream>

#include "cmMakefile.h"
#include "cmMessageType.h"
#include "cmSystemTools.h"

class cmExecutionStatus;

// cmConfigureFileCommand
bool
cmConfigureFileCommand::InitialPass(std::vector<std::string> const& args,
                                    cmExecutionStatus&)
{
    if(args.size() < 2)
    {
        this->SetError("called with incorrect number of arguments, expected 2");
        return false;
    }

    std::string const& inFile = args[0];
    this->InputFile           = cmSystemTools::CollapseFullPath(
        inFile, this->Makefile->GetCurrentSourceDirectory());

    // If the input location is a directory, error out.
    if(cmSystemTools::FileIsDirectory(this->InputFile))
    {
        std::ostringstream e;
        /* clang-format off */
    e << "input location\n"
      << "  " << this->InputFile << "\n"
      << "is a directory but a file was expected.";
        /* clang-format on */
        this->SetError(e.str());
        return false;
    }

    std::string const& outFile = args[1];
    this->OutputFile           = cmSystemTools::CollapseFullPath(
        outFile, this->Makefile->GetCurrentBinaryDirectory());

    // If the output location is already a directory put the file in it.
    if(cmSystemTools::FileIsDirectory(this->OutputFile))
    {
        this->OutputFile += "/";
        this->OutputFile += cmSystemTools::GetFilenameName(inFile);
    }

    if(!this->Makefile->CanIWriteThisFile(this->OutputFile))
    {
        std::string e = "attempted to configure a file: " + this->OutputFile +
                        " into a source directory.";
        this->SetError(e);
        cmSystemTools::SetFatalErrorOccured();
        return false;
    }
  }
  if (!unknown_args.empty()) {
    std::string msg = "configure_file called with unknown argument(s):\n";
    msg += unknown_args;
    this->Makefile->IssueMessage(MessageType::AUTHOR_WARNING, msg);
  }

    if(!this->ConfigureFile())
    {
        this->SetError("Problem configuring file");
        return false;
    }

    return true;
}

int
cmConfigureFileCommand::ConfigureFile()
{
  return this->Makefile->ConfigureFile(this->InputFile, this->OutputFile,
                                       this->CopyOnly, this->AtOnly,
                                       this->EscapeQuotes, this->NewLineStyle);
}
