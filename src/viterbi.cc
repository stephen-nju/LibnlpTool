#include "viterbi.h"

#include <cstdio>
#include <vector>

using std::vector;

int Viterbi::compute() {
    int states_size = states_.size();
    int observation_size = observations_.size();
    vector<vector<double>> dptable;
    vector<vector<int>> path;

    // 初始化概率
    for (int i = 0; i < states_size; i++) {
        // 初始化概率和路径
        vector<double> init_vec(observation_size, 0);
        init_vec[0] = init_prbo_[i] * emission_matrix_[i][observations_[0]];
        dptable.push_back(init_vec);

        vector<int> init_path(observation_size, 0);
        init_path[0] = i;
        path.push_back(init_path);
    }
    for (int i = 1; i < observation_size; i++) {
        for (int j = 0; j < states_size; j++) {
            double prob = -1;
            for (int k = 0; k < states_size; k++) {
                double p = dptable[k][i - 1] * transistion_matrix_[states_[k]][states_[j]] *
                           emission_matrix_[states_[j]][observations_[i]];
                if (p > prob) {
                    prob = p;
                    dptable[j][i] = prob;
                    path[j][i] = k;
                }
            }
        }
    }
    // 计算结束，回溯最有路径
    double prob = -1;
    int state = 0;
    for (int i = 0; i < states_size; i++) {
        if (dptable[i][observation_size - 1] > prob) {
            prob = dptable[i][observation_size - 1];
            state = states_[i];
        }
    }

    printf("%d\n", state);
    for (int i = observation_size - 1; i >= 0; i--) {
        printf("%d\n", path[state][i]);
        state = path[state][i];
    }

    return 1;
}
int main() {
    printf("start viterbi decode");
    vector<int> states = {0, 1};
    vector<int> obs = {0, 1, 2};
    vector<double> init = {0.6, 0.4};
    vector<vector<double>> transion = {{0.7, 0.3}, {0.4, 0.6}};
    vector<vector<double>> emsion = {
        {0.1, 0.4, 0.5},
        {0.6, 0.3, 0.1},
    };

    Viterbi* viterbi = new Viterbi();
    viterbi->set_emission_matrix(emsion);
    viterbi->set_init_prob(init);
    viterbi->set_transition_matrix(transion);
    viterbi->set_observations(obs);
    viterbi->set_states(states);
    if (viterbi->compute()) {
        printf("sucess ");

    } else {
        printf("error");
    };
}