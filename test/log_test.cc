#include "log.h"
#include <gtest/gtest.h>

TEST_log() {
  for (int i = 0; i < 100; i++) {
    LOG_INFO("hello world");
    LOG_DEBUG("hello world");
    LOG_WARNING("hello world");
    LOG_FATAL("hello world");
  }
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
test_int main(int argc, char *argv[])
{
  return 0;
}
