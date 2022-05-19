
#include "tokenizer.h"

#include <cstring>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "spdlog/spdlog.h"
#include "utf8proc.h"
#include "utils.h"

namespace nlptools {
namespace tokenizer {
Vocab load_vocab(const char* vocab_file) {
    Vocab vocab;
    FILE* input_file = fopen(vocab_file, "r");
    if (input_file != nullptr) {
        char* rawline;
        size_t index = 0;
        size_t len = 1024;
        rawline = (char*)malloc(sizeof(char) * len);
        while (nlptools::readline(&rawline, &len, input_file) != -1) {
            absl::string_view line = absl::StripTrailingAsciiWhitespace(rawline);
            string word = string(line);
            vocab[word] = index;
            index++;
        }
        fclose(input_file);
    } else {
        printf("vocab file open failed");
        exit(1);
    }
    return vocab;
}

bool BasicTokenizer::_is_whitespace(int c) const {
    const char* cat = utf8proc_category_string(c);
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        return true;
    }
    // Unicode中，每个字符都有Category的属性
    return cat[0] == 'Z' && cat[1] == 's';
}

bool BasicTokenizer::_is_control(int c) const {
    const char* cat = utf8proc_category_string(c);
    if (c == '\t' || c == '\n' || c == '\r') {
        return false;
    }
    return 'C' == *cat;
}

bool BasicTokenizer::_is_chinese_char(int cp) const {
    // This defines a "chinese character" as anything in the CJK Unicode block:
    //   https://en.wikipedia.org/wiki/CJK_Unified_Ideographs_(Unicode_block)
    //
    // Note that the CJK Unicode block is NOT all Japanese and Korean characters,
    // despite its name. The modern Korean Hangul alphabet is a different block,
    // as is Japanese Hiragana and Katakana. Those alphabets are used to write
    // space-separated words, so they are not treated specially and handled
    // like the all of the other languages.
    return (cp >= 0x4E00 && cp <= 0x9FFF) || (cp >= 0x3400 && cp <= 0x4DBF) || (cp >= 0x20000 && cp <= 0x2A6DF) ||
           (cp >= 0x2A700 && cp <= 0x2B73F) || (cp >= 0x2B740 && cp <= 0x2B81F) || (cp >= 0x2B820 && cp <= 0x2CEAF) ||
           (cp >= 0xF900 && cp <= 0xFAFF) || (cp >= 0x2F800 && cp <= 0x2FA1F);
}

bool BasicTokenizer::_is_punctuation(int cp) const {
    // We treat all non-letter/number ASCII as punctuation.
    // Characters such as "^", "$", and "`" are not in the Unicode
    // Punctuation class but we treat them as punctuation anyways, for
    // consistency.
    const char* cat = utf8proc_category_string(cp);

    if ((cp >= 33 && cp <= 47) || (cp >= 58 && cp <= 64) || (cp >= 91 && cp <= 96) || (cp >= 123 && cp <= 126)) {
        return true;
    }
    return 'P' == *cat;
}

bool BasicTokenizer::_is_accents_char(int cp) const {
    const char* cat = utf8proc_category_string(cp);
    if (strcmp(cat, "Mn") == 0) {
        return true;
    }
    return false;
}

vector<string> BasicTokenizer::tokenizer(const string& text) const {
    vector<string> output;
    // 去除前后空格
    absl::string_view s = absl::StripAsciiWhitespace(text);
    const char* text_data = s.data();

    if (do_lower_case_) {
        // unicode 字符标准化
        text_data = (const char*)utf8proc_NFD((const utf8proc_uint8_t*)text_data);
    }

    size_t word_bytes = std::strlen(text_data);

    size_t pos = 0;
    int codepoint;
    char dst[4];
    bool start_new_word = true;
    while (pos < std::strlen(text_data)) {
        int len = utf8proc_iterate((const utf8proc_uint8_t*)text_data + pos, -1, &codepoint);
        if (len < 0) {
            spdlog::info("Decode UTF-8 Error");
            break;
        }
        if (do_lower_case_) {
            codepoint = utf8proc_tolower(codepoint);
        }

        if (!this->_is_whitespace(codepoint) && !this->_is_accents_char(codepoint)) {
            // 跳过空格和重音字符
            size_t dst_len = utf8proc_encode_char(codepoint, (utf8proc_uint8_t*)dst);
            if (this->_is_chinese_char(codepoint) || this->_is_punctuation(codepoint)) {
                // 按照中文字符和标点符号切分
                output.emplace_back(dst, dst_len);
                start_new_word = true;
            } else {
                if (start_new_word) {
                    output.emplace_back(dst, dst_len);
                    start_new_word = false;
                } else {
                    output.at(output.size() - 1).append(dst, dst_len);
                }
            }
        }

        pos += len;
    }
    return output;
}

vector<string> WordpieceTokenizer::tokenizer_word(const string& token) const {
    vector<string> output;
    // 返回vector使用了移动语义
    if (token.size() > max_input_chars_per_word_) {
        output.emplace_back(unk_token_);
        return output;
    }

    bool is_bad = false;
    // 判断该词能否拆分
    for (size_t start = 0; start < token.size();) {
        // 用于记录该词是否可用wordspiece表示，如果不能表示则用unk表示

        size_t end = token.size();
        string cur_substr;

        while (start < end) {
            string substr = (start > 0) ? "##" + token.substr(start, end - start) : token.substr(start, end - start);

            if (this->vocab_.count(substr)) {
                cur_substr = substr;
                break;
            }

            end--;
        }

        if (cur_substr.empty()) {
            is_bad = true;
            break;
        }
        output.emplace_back(cur_substr);
        start = end;
    }

    if (is_bad) {
        output.clear();
        // 如果不能完成拆分，清除前面结果，用UNK代替
        output.emplace_back(unk_token_);
    }

    return output;
}

vector<string> FullTokenizer::tokenize(const string& text) const {
    vector<string> result;
    vector<string> token_list = this->basic_tokenizer_.tokenizer(text);
    for (string token : token_list) {
        vector<string> subtokens = this->wordpiece_tokenizer_.tokenizer_word(token);
        for (string subtoken : subtokens) {
            result.emplace_back(subtoken);
        }
    }
    return result;
}

std::unique_ptr<BertTokenizer> BertTokenizer::from_pretrained(const char* vocab_file) {
    Vocab vocab = load_vocab(vocab_file);
    return std::unique_ptr<BertTokenizer>(new BertTokenizer(vocab, true));
}
vector<string> BertTokenizer::tokenize(const string& text) {
    vector<string> out;
    out = full_tokenizer_.tokenize(text);
    return out;
}

}  // namespace tokenizer
}  // namespace nlptools