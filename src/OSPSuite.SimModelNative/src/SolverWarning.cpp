#include "SimModel/SolverWarning.h"

namespace SimModelNative
{

using namespace std;

SolverWarning::SolverWarning(double time, string message)
{
	_time = time;
	_message = message;
}

SolverWarning::SolverWarning(string message)
{
	_time = 0.0;
	_message = message;
}

double SolverWarning::Time() const
{
	return _time;
}

std::string SolverWarning::Message() const
{
	return _message;
}


}//.. end "namespace SimModelNative"
