/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmExternalMakefileProjectGenerator_h
#define cmExternalMakefileProjectGenerator_h

#include "cmConfigure.h"  // IWYU pragma: keep

#include <string>
#include <vector>

class cmGlobalGenerator;
class cmMakefile;

/** \class cmExternalMakefileProjectGenerator
 * \brief Base class for generators for "External Makefile based IDE projects".
 *
 * cmExternalMakefileProjectGenerator is a base class for generators
 * for "external makefile based projects", i.e. IDE projects which work
 * an already existing makefiles.
 * See cmExtraEclipseCDT4Generator as an example.
 * After the makefiles have been generated by one of the Makefile
 * generators, the Generate() method is called and this generator
 * can iterate over the local generators and/or projects to produce the
 * project files for the IDE.
 */
class cmExternalMakefileProjectGenerator
{
public:
    virtual ~cmExternalMakefileProjectGenerator() {}

    virtual void EnableLanguage(std::vector<std::string> const& languages,
                                cmMakefile*, bool optional);

    ///! set the global generator which will generate the makefiles
    virtual void SetGlobalGenerator(cmGlobalGenerator* generator)
    {
        this->GlobalGenerator = generator;
    }

    ///! Return the list of global generators supported by this extra generator
    const std::vector<std::string>& GetSupportedGlobalGenerators() const
    {
        return this->SupportedGlobalGenerators;
    }

    /** Create a full name from the given global generator name and the
     * extra generator name
     */
    static std::string CreateFullGeneratorName(
        const std::string& globalGenerator, const std::string& extraGenerator);

    ///! Generate the project files, the Makefiles have already been generated
    virtual void Generate() = 0;

    void        SetName(const std::string& n) { Name = n; }
    std::string GetName() const { return Name; }

    virtual bool Open(const std::string& bindir, const std::string& projectName,
                      bool dryRun);

protected:
    ///! Contains the names of the global generators support by this generator.
    std::vector<std::string> SupportedGlobalGenerators;
    ///! the global generator which creates the makefiles
    const cmGlobalGenerator* GlobalGenerator = nullptr;

    std::string Name;
};

class cmExternalMakefileProjectGeneratorFactory
{
public:
    cmExternalMakefileProjectGeneratorFactory(const std::string& n,
                                              const std::string& doc);
    virtual ~cmExternalMakefileProjectGeneratorFactory();

    std::string              GetName() const;
    std::string              GetDocumentation() const;
    std::vector<std::string> GetSupportedGlobalGenerators() const;
    std::vector<std::string> Aliases;

    virtual cmExternalMakefileProjectGenerator*
    CreateExternalMakefileProjectGenerator() const = 0;

    void AddSupportedGlobalGenerator(const std::string& base);

private:
    std::string              Name;
    std::string              Documentation;
    std::vector<std::string> SupportedGlobalGenerators;
};

template <class T>
class cmExternalMakefileProjectGeneratorSimpleFactory
: public cmExternalMakefileProjectGeneratorFactory
{
public:
    cmExternalMakefileProjectGeneratorSimpleFactory(const std::string& n,
                                                    const std::string& doc)
    : cmExternalMakefileProjectGeneratorFactory(n, doc)
    {}

    cmExternalMakefileProjectGenerator* CreateExternalMakefileProjectGenerator()
        const override
    {
        T* p = new T;
        p->SetName(GetName());
        return p;
    }
};

#endif
