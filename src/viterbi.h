#ifndef NLPTOOL_VITERBI_H
#define NLPTOOL_VITERBI_H

#include <vector>

using std::vector;

class Viterbi {
public:
    int compute();

public:
    void set_observations(vector<int>& obervation) {
        this->observations_ = obervation;
    };
    void set_states(vector<int>& states) {
        this->states_ = states;
    };
    void set_init_prob(vector<double>& init_prbo) {
        this->init_prbo_ = init_prbo;
    };
    void set_transition_matrix(vector<vector<double>>& transition_matrix) {
        this->transistion_matrix_ = transition_matrix;
    };
    void set_emission_matrix(vector<vector<double>>& emission_matrix) {
        this->emission_matrix_ = emission_matrix;
    };

private:
    vector<int> observations_;
    vector<int> states_;
    vector<double> init_prbo_;
    vector<vector<double>> transistion_matrix_;
    vector<vector<double>> emission_matrix_;

public:
    Viterbi(){};
    // 构造函数
    ~Viterbi(){};
    // 析构函数
};

#endif