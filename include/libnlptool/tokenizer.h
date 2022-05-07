#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

using Vocab = unordered_map<string, size_t>;
using InvVocab = unordered_map<size_t, string>;

class BasicTokenizer {
public:
    // explicit 禁止构造函数类型转换
    explicit BasicTokenizer(bool do_lower_case = true) : do_lower_case(do_lower_case){};
    // 不能被拷贝
    BasicTokenizer(const BasicTokenizer& other) = delete;
    virtual ~BasicTokenizer() = default;

    vector<string> tokenizer(const string& text) const;
    bool _is_whitespace(int c) const;
    bool _is_control(int c) const;
    bool _is_punctuation(int cp) const;
    bool _is_chinese_char(int cp) const;

private:
    const bool do_lower_case;
};

// class WordpieceTokenizer {
// public:
//     explicit WordpieceTokenizer(Vocab* vocab, std::string unk_token = "[UNK]") : vocab(vocab), unk_token(unk_token)
//     {}

//     WordpieceTokenizer(const WordpieceTokenizer& other) = delete;
//     virtual ~WordpieceTokenizer() = default;
//     void tokenize(const std::string& text, std::vector<std::string>* output_tokens);

// private:
//     const Vocab* vocab;
//     const string unk_token;
// };

/**
 * Runs end-to-end tokenziation.
 */
// class FullTokenizer
// {
// public:
//     explicit FullTokenizer(const char *vocab_file, bool do_lower_case = true)
//     {
//         vocab = new std::unordered_map<std::string, uint64_t>();
//         load_vocab(vocab_file, vocab);

//         basic_tokenizer = new BasicTokenizer(do_lower_case);
//         wordpiece_tokenizer = new WordpieceTokenizer(vocab);
//     }

//     FullTokenizer(const FullTokenizer &other) = delete;

//     virtual ~FullTokenizer()
//     {
//         delete wordpiece_tokenizer;
//         delete basic_tokenizer;
//         delete vocab;
//     }

//     void tokenize(const char *text, std::vector<std::string> *output_tokens, size_t max_length);

//     inline uint64_t convert_token_to_id(const std::string &token)
//     {
//         auto item = vocab->find(token);
//         if (item == vocab->end())
//         {
//             std::cerr << "vocab missing key: " << token << std::endl;
//             return 0;
//         }
//         else
//         {
//             return item->second;
//         }
//     }

//     void convert_tokens_to_ids(const std::vector<std::string> &tokens, uint64_t *ids);

// private:
//     std::unordered_map<std::string, uint64_t> *vocab;
//     BasicTokenizer *basic_tokenizer;
//     WordpieceTokenizer *wordpiece_tokenizer;
// };
// }
#endif  // tokenizers header