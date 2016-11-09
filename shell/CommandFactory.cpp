/*
 * CommandFactory.cpp
 * 
 * This file is part of the "HLSL Translator" (Copyright (c) 2014 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "CommandFactory.h"


namespace HTLib
{

namespace Util
{


const CommandFactory& CommandFactory::Instance()
{
    static const CommandFactory instance;
    return instance;
}

Command* CommandFactory::Get(const std::string& name, Command::Identifier* cmdIdent) const
{
    for (const auto& cmd : commands_)
    {
        for (const auto& ident : cmd->Idents())
        {
            auto identLen = ident.name.size();
            if ( ( !ident.includesValue && name == ident.name ) ||
                 ( ident.includesValue && name.size() >= identLen && name.substr(0, identLen) == ident.name ) )
            {
                if (cmdIdent)
                    *cmdIdent = ident;
                return cmd.get();
            }
        }
    }
    return nullptr;
}


/*
 * ======= Private: =======
 */

CommandFactory::CommandFactory()
{
    MakeCommand< EntryCommand       >();
    MakeCommand< TargetCommand      >();
    MakeCommand< VersionInCommand   >();
    MakeCommand< VersionOutCommand  >();
    MakeCommand< IndentCommand      >();
    MakeCommand< PrefixCommand      >();
    MakeCommand< OutputCommand      >();
    MakeCommand< WarnCommand        >();
    MakeCommand< BlanksCommand      >();
    MakeCommand< LineMarksCommand   >();
    MakeCommand< DumpASTCommand     >();
    MakeCommand< PPOnlyCommand      >();
    MakeCommand< CommentsCommand    >();
    MakeCommand< MacroCommand       >();
    MakeCommand< PauseCommand       >();
    MakeCommand< PresettingCommand  >();
    MakeCommand< VersionCommand     >();
    MakeCommand< HelpCommand        >();
    MakeCommand< IncludePathCommand >();
}

template <typename T, typename... Args>
void CommandFactory::MakeCommand(Args&&... args)
{
    auto cmd = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    helpPrinter_.AppendCommandHelp(*cmd);
    commands_.emplace_back(std::move(cmd));
}


} // /namespace Util

} // /namespace HTLib



// ================================================================================
