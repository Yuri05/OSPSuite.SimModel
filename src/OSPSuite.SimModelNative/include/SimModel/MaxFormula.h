#ifndef _MaxFormula_H_
#define _MaxFormula_H_

#include "SimModel/Formula.h"

namespace SimModelNative
{

class MaxFormula : 	
	public Formula
{
	private:
		Formula * m_FirstArgument;
		Formula * m_SecondArgument;
	
	public:
		MaxFormula ();
		~MaxFormula ();

		virtual void LoadFromXMLNode (const XMLNode & pNode);
		virtual void XMLFinalizeInstance (const XMLNode & pNode, Simulation * sim);
		virtual void SetQuantityReference (const QuantityReference & quantityReference);
		virtual double DE_Compute (const double * y, const double time, ScaleFactorUsageMode scaleFactorMode);
		virtual void DE_Jacobian (double * * jacobian, const double * y, const double time, const int iEquation, const double preFactor);
		virtual Formula * DE_Jacobian(const int iEquation);
		virtual Formula * clone();
		virtual Formula * RecursiveSimplify();

		virtual void Finalize();

		virtual bool IsZero(void);

		virtual void AppendUsedVariables(std::set<int> & usedVariablesIndices, const std::set<int> & variablesIndicesUsedInSwitchAssignments);
		virtual void AppendUsedParameters(std::set<int> & usedParameterIDs);

		virtual void UpdateIndicesOfReferencedVariables();
	
	protected:
		virtual void WriteFormulaMatlabCode (std::ostream & mrOut);
		virtual void WriteFormulaCppCode (std::ostream & mrOut);
};


}//.. end "namespace SimModelNative"


#endif //_MaxFormula_H_

