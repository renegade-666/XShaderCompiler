/*
 * Parser.h
 * 
 * This file is part of the "HLSL Translator" (Copyright (c) 2014 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef HTLIB_PARSER_H
#define HTLIB_PARSER_H


#include "HT/Log.h"
#include "HLSLScanner.h"
#include "Visitor.h"
#include "Token.h"

#include <vector>
#include <map>
#include <string>


namespace HTLib
{


// Syntax parser base class.
class Parser
{
    
    public:
        
        virtual ~Parser();

    protected:
        
        using Tokens = Token::Types;

        /* === Functions === */

        Parser() = default;

        virtual Scanner& GetScanner() = 0;

        void Error(const std::string& msg);
        void ErrorUnexpected();
        void ErrorUnexpected(const std::string& hint);

        TokenPtr Accept(const Tokens type);
        TokenPtr Accept(const Tokens type, const std::string& spell);
        TokenPtr AcceptIt();

        // Ignores the next tokens if they are white spaces and optionally new lines.
        void IgnoreWhiteSpaces(bool includeNewLines = true);
        void IgnoreNewLines();

        // Makes a new shared pointer of the specified AST node class.
        template <typename T, typename... Args>
        std::shared_ptr<T> Make(Args&&... args)
        {
            return std::make_shared<T>(GetScanner().Pos(), args...);
        }

        // Returns the current token.
        inline const TokenPtr& Tkn() const
        {
            return tkn_;
        }

        // Returns the type of the next token.
        inline Tokens Type() const
        {
            return Tkn()->Type();
        }

        // Returns true if the next token is from the specified type.
        inline bool Is(const Tokens type) const
        {
            return Type() == type;
        }

        // Returns true if the next token is from the specified type and has the specified spelling.
        inline bool Is(const Tokens type, const std::string& spell) const
        {
            return Type() == type && Tkn()->Spell() == spell;
        }

        /* === Members === */

    private:

        TokenPtr tkn_;

};


} // /namespace HTLib


#endif



// ================================================================================