// Copyright maverick Inc. All Rights Reserved.
// Author : zhangfangjie (f22jay@163.com)
// Date 2018/02/11 21:04:59
// Breif :
#include "HttpUtil.h"
#include "log.h"

int main(int argc, char *argv[])
{
    common::HttpClient client;
    std::string content;
    std::string url = argv[1];
    common::LOG_INFO("%s\n", url.c_str());
    std::string post;
    client.doInvoke(content, url, post, 10000);

    return 0;
}
