// Copyright maverick Inc. All Rights Reserved.
// Author : zhangfangjie (f22jay@163.com)
// Date 2016/09/04 11:29:06
// Breif :

#include "log.h"

Logger::Logger(File *file)  : file_(file) {}
void Logger::Log(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  char buf[500];
  char* limit = buf + 500;
  std::thread::id thread_id = std::this_thread::get_id();
  std::time_t now;
  time(&now);

  // try twice, if buffer is not enough ,then bigger
  for (int i = 0; i < 2; i++) {
    if (i == 1) {
      buf = new char[20000];
      limit = buf + 20000;
    }
    char *p = buffer;
    p += snprintf(p, "%l-%s:%s-%l :",
                  ctime(&now),
                  __FILE__,
                  __LINE__,
                  thread_id
                  );
    va_list backup = ap;
    va_copy(backup, ap);
    p += std::vsnprintf(p, limit - p, fmt, backup);
  }

  //buf is full
  if (p >= limit) {
    if (i == 0) {
      continue;
    } else {
      p = limit - 1;
      //truncate log msg
    }
  }

  fwrite(buf, sizeof(char), p - buf, file_);
}

File *g_log_file = stdout;
Logger * g_logger = new Logger(g_log_file);
