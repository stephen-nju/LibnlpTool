#ifndef SRC_TESTHARNESS_H
#define SRC_TESTHARNESS_H
#ifndef OS_WIN
#    include <sys/stat.h>
#    include <unistd.h>
#else
#    include <direct.h>
#endif

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

ABSL_DECLARE_FLAG(std::string, test_tmpdir);
ABSL_DECLARE_FLAG(std::string, test_srcdir);

#endif