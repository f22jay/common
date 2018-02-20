/* -*- C++ -*- */
// Copyright maverick Inc. All Rights Reserved.
// Author : zhangfangjie (f22jay@163.com)
// Date 2018/02/11 18:06:27
// Breif :

#ifndef __HTTP_UTIL_H__
#define __HTTP_UTIL_H__
#include <curl/curl.h>
#include <string>
#include "log.h"

namespace common
{

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  size_t len = size * nmemb;
  std::string *str = (std::string*)(userdata);
  str->append((char*)ptr, len);
  return len;
}

static int debug_callback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr)
{
  std::string* str = (std::string*)(userptr);
  switch (type)
  {
    case CURLINFO_HEADER_IN:
    case CURLINFO_HEADER_OUT:
#ifdef __HTTP_DATA_OUT_DEBUG__
	case CURLINFO_DATA_IN:
    case CURLINFO_DATA_OUT:
#endif
      str->append((char*)data, size);
      break;
    default:
      break;
  }
  return 0;
}

class HttpClient
{
 public:
  HttpClient(): _curl(NULL),
                _headers(NULL)
  {}

  int doInvoke(std::string& content, const std::string& url,
               const std::string& post = "", int64_t timeoutMs = 10000L);

  int addHead(const char* head_name, const char* head_value);

 private:
  CURL* _curl;
  struct curl_slist* _headers;
};

int HttpClient::doInvoke(std::string& content,
                         const std::string& url,
                         const std::string& post,
                         int64_t timeoutMs) {
  _curl = curl_easy_init();
  if (!_curl)
  {
    LOG_FATAL("curl_easy_init fail");
    return -1;
  }

  std::string debug;
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &content);
  curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(_curl, CURLOPT_DEBUGFUNCTION, debug_callback);
  curl_easy_setopt(_curl, CURLOPT_DEBUGDATA, &debug);
  curl_easy_setopt(_curl, CURLOPT_TIMEOUT_MS, timeoutMs);
  curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
  if (!post.empty())
  {
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDSIZE, post.length());
    curl_easy_setopt(_curl, CURLOPT_COPYPOSTFIELDS, post.data());
  }
  _headers = curl_slist_append(_headers, "Expect:");
  if (_headers != NULL)
  {
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _headers);
  }
  int ret = 0;
  do
  {
    CURLcode code = curl_easy_perform(_curl);
    if (code != CURLE_OK)
    {
      LOG_FATAL("curl_easy_perform fail, code:[%d], msg:[%s]"
                , code, curl_easy_strerror(code));
      ret = -1;
      break;
    }

    long status = 0;
    code = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &status);
    if (code != CURLE_OK)
    {
      LOG_FATAL("curl_easy_getinfo fail, code:[%d], msg:[%s]"
	            , code, curl_easy_strerror(code));
      ret = -1;
      break;
    }
    if (status != 200)
    {
      LOG_FATAL("http response status not 200, status:[%ld], debug:[%s]",
                status, debug.c_str());
      ret = -1;
      break;
    }
  } while(0);

  if (ret == 0)
  {
    LOG_INFO("http invoke succ, debug:[%s]", debug.c_str());
  }
  curl_slist_free_all(_headers);
  curl_easy_cleanup(_curl);
  return ret;
}

int HttpClient::addHead(const char* head_name, const char* head_value)
{
  char buf[300];
  snprintf(buf, sizeof(buf), "%s: %s", head_name, head_value);
  _headers = curl_slist_append(_headers, buf);
  if (_headers == NULL)
  {
    LOG_FATAL("curl_easy_append fail");
    return -1;
  }
  return 0;
}
}  // util

#endif
