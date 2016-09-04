// Copyright maverick Inc. All Rights Reserved.
// Author : zhangfangjie (f22jay@163.com)
// Date 2016/09/04 10:04:15
// Breif : simple loger
#program once
#include <thread>
#include <cstdio>
#include <ctime>

class Logger
{
 public:
  Logger();
  virtual ~Logger() {}
  void Log(const char* fmt, ...);
  void SetFile(File *file) {file_ = file;}
 private:
  File * file_;
};

extern Logger* g_logger;
#define LOG_INFO(formt, args...) g_logger("%s "format, "info", ##args)
#define LOG_DEBUG(formt, args...) g_logger("%s "format, "debug", ##args)
#define LOG_WARNING(formt, args...) g_logger("%s "format, "warning", ##args)
#define LOG_FATAL(formt, args...) g_logger("%s "format, "fatal", ##args)
