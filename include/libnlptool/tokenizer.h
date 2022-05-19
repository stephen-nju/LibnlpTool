#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstdio>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using std::map;
using std::string;
using std::unordered_map;
using std::vector;

namespace nlptools {

namespace tokenizer {
using Vocab = unordered_map<string, size_t>;
using InvVocab = unordered_map<size_t, string>;

Vocab load_vocab(const char* vocab_file);

class BasicTokenizer {
public:
    // explicit 禁止构造函数类型转换
    explicit BasicTokenizer(bool do_lower_case = true) : do_lower_case_(do_lower_case){};
    // 不能被拷贝
    BasicTokenizer(const BasicTokenizer& other) = delete;
    virtual ~BasicTokenizer() = default;

    vector<string> tokenizer(const string& text) const;
    bool _is_whitespace(int c) const;
    bool _is_control(int c) const;
    bool _is_punctuation(int cp) const;
    bool _is_chinese_char(int cp) const;
    // 判断重音符号
    bool _is_accents_char(int cp) const;

private:
    const bool do_lower_case_;
};

class WordpieceTokenizer {
public:
    explicit WordpieceTokenizer(Vocab vocab, string unk_token = "[UNK]", const int max_input_chars_per_word = 100)
        : vocab_(vocab),
          unk_token_(unk_token),
          max_input_chars_per_word_(max_input_chars_per_word) {}

    WordpieceTokenizer(const WordpieceTokenizer& other) = delete;
    vector<string> tokenizer_word(const string& token) const;
    virtual ~WordpieceTokenizer() = default;

private:
    const Vocab vocab_;
    const string unk_token_;
    const int max_input_chars_per_word_;
};

/**
 * Full tokenizer for bert(组合类)
 */
class FullTokenizer {
public:
    explicit FullTokenizer(Vocab vocab, bool do_lower_case = true)
        : basic_tokenizer_(do_lower_case),
          wordpiece_tokenizer_(vocab) {}

    // FullTokenizer(const FullTokenizer& other) = delete;

    virtual ~FullTokenizer() {}

    vector<string> tokenize(const string& text) const;

private:
    BasicTokenizer basic_tokenizer_;
    WordpieceTokenizer wordpiece_tokenizer_;
};

/*
bert tokenizer基类 采用Named Constructor Idiom
*/

class BertTokenizer {
protected:
    // 保证能够派生
    BertTokenizer(Vocab vocab, bool do_lower_case = true) : vocab_(vocab), full_tokenizer_(vocab, do_lower_case) {
        for (auto s : vocab) {
            inv_vocab_[s.second] = s.first;
        }
    };
    // ~BertTokenizer(){};

private:
    Vocab vocab_;
    InvVocab inv_vocab_;
    FullTokenizer full_tokenizer_;

public:
    static std::unique_ptr<BertTokenizer> from_pretrained(const char* vocab_file);
    // BertTokenizer(const BertTokenizer& other) = delete;
    vector<string> tokenize(const string& text);
};

}  // namespace tokenizer

}  // namespace nlptools
#endif  // tokenizers header
