#pragma once


enum __log_type 
{
	LOG_TYPE_ERROR,
	LOG_TYPE_DUMP,
	LOG_TYPE_INFO
};

void logPrint(__log_type type, const char* fmt, ...);


#define LOG_ERROR(format, ...) logPrint(LOG_TYPE_ERROR," [%s:%d] " format , __func__, __LINE__, __VA_ARGS__)
#define LOG_DUMP(format, ...)  logPrint(LOG_TYPE_DUMP," [%s:%d] " format , __func__, __LINE__, __VA_ARGS__)
#define LOG_INFO(format, ...)  logPrint(LOG_TYPE_INFO," [%s:%d] " format , __func__, __LINE__, __VA_ARGS__)