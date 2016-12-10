/*
 * ReflectionAnalyzer.h
 * 
 * This file is part of the XShaderCompiler project (Copyright (c) 2014-2016 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef XSC_REFLECTION_ANALYZER_H
#define XSC_REFLECTION_ANALYZER_H


#include <Xsc/Reflection.h>
#include <Xsc/Targets.h>
#include "ReportHandler.h"
#include "Visitor.h"
#include "Token.h"
#include "Variant.h"


namespace Xsc
{


/*
Code reflection analyzer.
This class collects all meta information that can be optionally retrieved.
*/
class ReflectionAnalyzer : private Visitor
{
    
    public:
        
        ReflectionAnalyzer(Log* log);

        // Collect all reflection data from the program AST.
        void Reflect(Program& program, const ShaderTarget shaderTarget, Reflection::ReflectionData& reflectionData);

    private:
        
        void Warning(const std::string& msg, const AST* ast = nullptr);

        int GetBindingPoint(const std::vector<RegisterPtr>& slotRegisters) const;

        Variant EvaluateConstExpr(Expr& expr);
        float EvaluateConstExprFloat(Expr& expr);

        /* ----- Visitor implementation ----- */

        DECL_VISIT_PROC( Program           );

        DECL_VISIT_PROC( SamplerDecl       );

        DECL_VISIT_PROC( UniformBufferDecl );
        DECL_VISIT_PROC( BufferDeclStmnt   );

        /* --- Helper functions for code reflection --- */

        void ReflectSamplerValue(SamplerValue* ast, Reflection::SamplerState& samplerState);
        void ReflectSamplerValueFilter(const std::string& value, Reflection::Filter& filter, const AST* ast = nullptr);
        void ReflectSamplerValueTextureAddressMode(const std::string& value, Reflection::TextureAddressMode& addressMode, const AST* ast = nullptr);
        void ReflectSamplerValueComparisonFunc(const std::string& value, Reflection::ComparisonFunc& comparisonFunc, const AST* ast = nullptr);

        /* === Members === */

        ReportHandler               reportHandler_;

        ShaderTarget                shaderTarget_   = ShaderTarget::VertexShader;
        Program*                    program_        = nullptr;

        Reflection::ReflectionData* data_           = nullptr;

};


} // /namespace Xsc


#endif



// ================================================================================