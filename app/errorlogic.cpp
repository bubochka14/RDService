#include "errorlogic.h"
void ErrorLogic::setErrorString(const QString& error)
{
	_errorString = error;
}
QString ErrorLogic::getLastError() const
{
	return _errorString;
}