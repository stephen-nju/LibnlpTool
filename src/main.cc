#include <sys/types.h>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "ac_automation.h"
#include "leetcode.h"
#include "spdlog/fmt/bundled/core.h"
#include "spdlog/spdlog.h"
#include "tokenizer.h"
#include "utf8proc.h"
#include "utils.h"
using namespace std;

// int fib(int N) {
//     if (N == 1 || N == 2)
//         return 1;
//     return fib(N - 1) + fib(N - 2);
// }
// int test_ac() {
//     Automation* machine = new Automation();

//     const char* word_path = "D:\\Users\\Desktop\\words.txt";
//     FILE* input_file = fopen(word_path, "r");
//     if (input_file != NULL) {
//         char* rawline;
//         size_t len = 1024;
//         rawline = (char*)malloc(sizeof(char) * len);
//         while (nlptools::readline(&rawline, &len, input_file) != -1) {
//             string line = string(rawline);
//             string::iterator sit = line.begin();
//             // while (sit != line.end()) {
//             //     utf8::uint32_t cp = utf8::next(sit, line.end());
//             //     printf("%02x\n", cp);
//             //     /* code */
//             // }
//             // while (*temp!='\0')
//             // {
//             // 	printf("%02x\n",*temp);
//             // 	temp++;
//             // }
//         }
//     } else {
//         perror("open file error");
//         return EXIT_FAILURE;
//     }
//     return 0;
// }

int main() {
    auto start = chrono::system_clock::now();
    // test_ac()
    leetcode::Solution* solution = new leetcode::Solution();
    // string s="aa";
    // string p=".*";
    // bool res=solution->isMatch(s,p);
    // BasicTokenizer* tokenizer = new BasicTokenizer(true);
    // vector<string> out = tokenizer->tokenizer(" c,  我 爱 北 京 天 安门");
    // // for (auto s : out) {
    //     // fmt::print("{}\n", s);
    //     spdlog::info("{}\n", s);
    // }
    // vector<int> vec{1, 3, 2, 0, 10};
    // sort(vec.begin(), vec.end(), std::greater<int>());

    // for (auto s : vec) {
    //     spdlog::info("{}\n", s);
    // }
    // leetcode::Solution* s = new leetcode::Solution()

    int arr[] = {0, 3, 1, 5, 2, 10, 4};
    int len = sizeof(arr) / sizeof(arr[0]);
    solution->quickSort(arr, len);
    for (auto s : arr) {
        printf("%d\n", s);
    }

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fmt::print("{} ms", duration.count());
    sort() printf("==================");
    delete solution;
    // delete tokenizer;
    // const char* path = "E:/MyProject/Cpp/libnlptool/data/data.txt";
    // FILE* pfile = fopen(path, "r");
    // char* raw_line ;
    // size_t len = 1024;
    // if (pfile == NULL) {
    // 	printf("file not found");
    // } {
    // 	raw_line = (char*)malloc(sizeof(char) * len);
    // 	while (libnlptools::readline(&raw_line, &len, pfile) !=-1) {
    // 		absl::string_view line = absl::StripAsciiWhitespace(raw_line);
    // 		vector<absl::string_view> out = absl::StrSplit(line, "=");
    // 		for (auto s : out) {
    // 			printf("%s", s.data());
    // 		}
    // 	}
    // }
    // 字符串长度
    // string  a= u8"woshi 中国人";
    // int len = 0;
    // len = libnlptools::string_utils::utf8len(a.c_str());
    // printf("%d", len);
    //测试切分
    // absl::string_view a = "我是中\t国	人	";
    // vector<string> out = absl::StrSplit(a, "\t");
    // for (string a : out) {
    //	printf("%s\n",a.c_str());
    //}
    return 0;
}