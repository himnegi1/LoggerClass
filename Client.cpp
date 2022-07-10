#include "logger.h"

int main()
{
	const string name = "MainFunction";
	//first initialize loggerClass 
	LoggerInitializer();
	
	//Below calls can be from different thread too
	LOG_TRACE("Trace :", name);
	LOG_DEBUG("Debug :", name);
	LOG_INFO("Info :", name);
	LOG_WARN("Warn :", name);
	LOG_ERROR("Error :", name);
	LOG_CRITICAL("Critical :", name);
	
	return 0;
}
