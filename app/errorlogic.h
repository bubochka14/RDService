#pragma once
#include <QString>
class ErrorLogic
{
	QString _errorString;
protected:
	virtual void setErrorString(const QString& error);
public:
	ErrorLogic() = default;
	virtual QString getLastError() const;
	virtual ~ErrorLogic() = default;
};