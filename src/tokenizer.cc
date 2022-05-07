
#include "tokenizer.h"

#include <cstring>

#include "spdlog/spdlog.h"
#include "utf8proc.h"
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

vector<string> BasicTokenizer::tokenizer(const string& text) const {
    vector<string> output;
    const char* text_data = text.c_str();
    if (do_lower_case) {
        // unicode 字符标准化
        text_data = (const char*)utf8proc_NFD((const utf8proc_uint8_t*)text_data);
    }

    size_t word_bytes = std::strlen(text_data);

    size_t pos = 0;
    int codepoint;
    char dst[4];
    while (pos < std::strlen(text_data)) {
        int len = utf8proc_iterate((const utf8proc_uint8_t*)text_data + pos, -1, &codepoint);
        if (len < 0) {
            spdlog::info("Decode UTF-8 Error");
            break;
        }
        if (do_lower_case) {
            codepoint = utf8proc_tolower(codepoint);
        }

        if (!_is_whitespace(codepoint)) {
            size_t dst_len = utf8proc_encode_char(codepoint, (utf8proc_uint8_t*)dst);
            if (_is_chinese_char(codepoint) || _is_punctuation(codepoint)) {
                output.emplace_back(dst, dst_len);
            } else if (!output.empty()) {
                output.at(output.size() - 1).append(dst, dst_len);
            } else {
                output.emplace_back(dst, dst_len);
            }
        }
        pos += len;
    }
    return output;

    // while (word_bytes > 0) {
    //     int len = utf8proc_iterate((const utf8proc_uint8_t*)text_data + subpos, -1, &codepoint);
    //     if (len < 0) {
    //         // 输出错误和异常
    //         break;
    //     }
    //     if (do_lower_case) {
    //         codepoint = utf8proc_tolower(codepoint);
    //     }

    //     const char* cat = utf8proc_category_string(codepoint);

    //     if (codepoint == 0 || codepoint == 0xfffd || this->_is_control(codepoint)) {
    //         // pass
    //     }

    //     else if (do_lower_case && cat[0] == 'M' && cat[1] == 'n') {
    //         // pass
    //     } else if (this->_is_whitespace(codepoint)) {
    //         new_token = true;
    //     } else {
    //         size_t dst_len = len;
    //         const char* dst_ptr = text_data + subpos;
    //         if (do_lower_case) {
    //             dst_len = utf8proc_encode_char(codepoint, (utf8proc_uint8_t*)dst);
    //             dst_ptr = dst;
    //         }
    //         if (this->_is_punctuation(codepoint) || this->_is_chinese_char(codepoint)) {
    //             output.emplace_back(dst_ptr, dst_len);
    //             new_token = true;
    //         } else {
    //             if (new_token) {
    //                 output.emplace_back(dst_ptr, dst_len);
    //                 new_token = false;
    //             } else {
    //                 output.at(output.size() - 1).append(dst_ptr, dst_len);
    //             }
    //         }
    //     }

    //     word_bytes = word_bytes - len;
    //     subpos = subpos + len;
    // }
    // return output;
}
