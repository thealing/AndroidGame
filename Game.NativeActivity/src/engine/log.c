#include "log.h"

#include "platform.h"

void log_info(const char* format, ...)
{
	va_list args;

	va_start(args, format);

	__android_log_vprint(ANDROID_LOG_INFO, TAG, format, args);

	va_end(args);
}

void log_warning(const char* format, ...)
{
	va_list args;

	va_start(args, format);

	__android_log_vprint(ANDROID_LOG_WARN, TAG, format, args);

	va_end(args);
}

void log_error(const char* format, ...)
{
	va_list args;

	va_start(args, format);

	__android_log_vprint(ANDROID_LOG_ERROR, TAG, format, args);

	va_end(args);
}
