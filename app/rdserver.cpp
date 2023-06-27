#include "rdserver.h"

AbstractRDServer::AbstractRDServer(const QString& hostname, QObject* parent)
	:QObject(parent)
	, _hostname(hostname)
{
}
QString AbstractRDServer::hostname() const
{
	return _hostname;
}
AbstractRDServer::~AbstractRDServer()
{}