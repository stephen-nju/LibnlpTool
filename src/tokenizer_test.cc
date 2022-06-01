
#include "tokenizer.h"

#include <memory>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "boost/filesystem.hpp"
#include "commom.h"
#include "gtest/gtest.h"
#include "testharness.h"

#ifdef OS_WIN
ABSL_FLAG(std::string, test_srcdir, "..\\data", "Data directory.");
#else
ABSL_FLAG(std::string, test_srcdir, "../data", "Data directory.");
#endif

ABSL_FLAG(std::string, test_tmpdir, "test_tmp", "Temporary directory.");

// 创建测试文件夹

using std::string;
using std::vector;

TEST(WordpieceTokenizerTest, TokenizerWordTest) {
    nlptools::tokenizer::Vocab v{{"[UNK]", 1},
                                 {"[CLS]", 1},
                                 {"[SEP]", 1},
                                 {"want", 1},
                                 {"##want", 1},
                                 {"##ed", 1},
                                 {"wa", 1},
                                 {"un", 1},
                                 {"runn", 1},
                                 {"##ing", 1}};

    nlptools::tokenizer::WordpieceTokenizer* wtokenizer = new nlptools::tokenizer::WordpieceTokenizer(v);
    vector<string> result;

    result = wtokenizer->tokenizer_word("unwantedX");
    EXPECT_EQ(result[0], "[UNK]");

    result = wtokenizer->tokenizer_word("unwanted");
    EXPECT_EQ(result[0], "un");
    EXPECT_EQ(result[1], "##want");

    delete wtokenizer;
}
TEST(FullTokenizerTest, TokenizeTest) {
    nlptools::tokenizer::Vocab v{{"[UNK]", 1},
                                 {"[CLS]", 1},
                                 {"[SEP]", 1},
                                 {"want", 1},
                                 {"##want", 1},
                                 {"##ed", 1},
                                 {"wa", 1},
                                 {"un", 1},
                                 {"runn", 1},
                                 {"##ing", 1},
                                 //{",", 1},
                                 {"中", 1}};

    nlptools::tokenizer::FullTokenizer* tokenizer = new nlptools::tokenizer::FullTokenizer(v);
    vector<string> result;

    result = tokenizer->tokenize("UNwant\u00E9d,中running");
    EXPECT_EQ(result[0], "un");
    EXPECT_EQ(result[1], "##want");
    EXPECT_EQ(result[2], "##ed");
    EXPECT_EQ(result[3], ",");
    EXPECT_EQ(result[4], "中");
    EXPECT_EQ(result[5], "runn");
    EXPECT_EQ(result[6], "##ing");

    delete tokenizer;
}
//
TEST(BertTokenizerTest, TokenizeTest) {
    // #ifdef OS_WIN
    //     _mkdir(absl::GetFlag(FLAGS_test_tmpdir).c_str());
    // #else
    //     mkdir(absl::GetFlag(FLAGS_test_tmpdir).c_str(),S_IRUSR | S_IWUSR | S_IXUSR);
    //     // mkdir("mydir", S_IRUSR | S_IWUSR | S_IXUSR);
    // #endif

    boost::filesystem::create_directory(absl::GetFlag(FLAGS_test_tmpdir));
    nlptools::tokenizer::Vocab v{{"[UNK]", 1},
                                 {"[CLS]", 1},
                                 {"[SEP]", 1},
                                 {"want", 1},
                                 {"##want", 1},
                                 {"##ed", 1},
                                 {"wa", 1},
                                 {"un", 1},
                                 {"runn", 1},
                                 {"##ing", 1},
                                 {",", 1},
                                 {"中", 1}};

    FILE* output_file;
    string path = absl::GetFlag(FLAGS_test_tmpdir) + "/" + "vocab_file.txt";
    output_file = fopen(path.c_str(), "w");

    for (auto& s : v) {
        fputs(s.first.c_str(), output_file);
        fputs("\n", output_file);
    };
    fclose(output_file);

    std::unique_ptr<nlptools::tokenizer::BertTokenizer> tokenizer =
        nlptools::tokenizer::BertTokenizer::from_pretrained(path.c_str());
    vector<string> result;

    result = tokenizer->tokenize("UNwant\u00E9d,中running");
    EXPECT_EQ(result[0], "un");
    EXPECT_EQ(result[1], "##want");
    EXPECT_EQ(result[2], "##ed");
    EXPECT_EQ(result[3], ",");
    EXPECT_EQ(result[4], "中");
    EXPECT_EQ(result[5], "runn");
    EXPECT_EQ(result[6], "##ing");
}
// int main() {
//     // BasicTokenizer* tokenizer = new BasicTokenizer(true);
//     // vector<string> out = tokenizer->tokenizer(" a,  我 爱 北 京 天 安门");
//     // for (auto s : out) {
//     //     // fmt::print("{}\n", s);
//     //     spdlog::info("{}\n", s);
//     // }
//     Vocab v{{"[UNK]", 1},
//             {"[CLS]", 1},
//             {"[SEP]", 1},
//             {"want", 1},
//             {"##want", 1},
//             {"##ed", 1},
//             {"wa", 1},
//             {"un", 1},
//             {"runn", 1},
//             {"##ing", 1}};

//     WordpieceTokenizer* wtokenizer = new WordpieceTokenizer(v);
// vector<string> o = wtokenizer->tokenizer_word("unwantedX");
// for (auto s : o) {
//    spdlog::info("{}\n", s);
//}
//}
