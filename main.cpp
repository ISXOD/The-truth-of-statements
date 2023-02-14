#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* magic numbers:
'(' '-' '|' '&'  '!' 'False' 'True'
16  17   18  19  20    21      22
 */

template <typename T>
int find_index(T vec[], T elem, int size_arr_var) {
    for (int i = 0; i < size_arr_var; i++) {
        if (vec[i] == elem) {
            return i;
        }
    }
    return -1;
}

template <typename T>
bool comparing_arrays (T arr1[], T arr2[], int size1, int size2){
    if (size1 != size2)
        return false;
    for (int i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]){
            return false;
        }
    }
    return true;
}

template <typename T>
void assign_array(T arr1[], T arr2[], int *size1, int size2){
    for(int i = 0; i < size2; i++){
        arr1[i] = arr2[i];
    }
    *size1 = size2;
}
vector <string> srez(vector <string> arr, int begin, int end) {
    vector <string> res;
    for (int i = begin; i < end; i++) {
        res.push_back(arr[i]);
    }
    return res;
}

vector <string> add_vectors(vector <string> vec1, vector <string> vec2) {
    for (int i = 0; i < vec2.size(); i++) {
        vec1.push_back(vec2[i]);
    }
    return vec1;
}
int main() {
    char operators[] = { '(', '-', '|', '&', '!' };
    int index_operators[] = {16, 17, 18, 19, 20};
    string operators_string[] = { "(", "-", "|", "&", "!" };
    string enter;
    cin >> enter;
    string st;
    st = "";
    int i = 0;
    while (i < enter.size()) {
        if (!(enter[i] == ' ' || enter[i] == '\t')) {
            st += enter[i];
            if (enter[i] == '-') {
                i++;
            }
            i++;
        }
    }
    string var;
    var = "";
    int out_arr[256];
    int stak[128];
    int size_stak = 0, size_out_arr = 0;
    string var_arr[16];
    int int_var_arr[16];
    int size_var_arr = 0;
    int zamena;
    for (int i = 0; i < 16; i++){
        int_var_arr[i] = i;
    }
    for (i = 0; i < st.size(); i++) {
        if (!(st[i] == operators[0] || st[i] == operators[1] || st[i] == operators[2] || st[i] == operators[3] ||
              st[i] == operators[4] || st[i] == ')')) {
            var += st[i];
        }
        else {
            if (!var.empty()) {
                zamena = find_index(var_arr, var, size_var_arr);
                if (zamena == -1) {
                    var_arr[size_var_arr] = var;
                    zamena = size_var_arr;
                    size_var_arr++;
                }
                out_arr[size_out_arr] = zamena;
                size_out_arr++;
                var = "";
            }
            if (st[i] == ')') {
                while (stak[size_stak - 1] != 16) {
                    out_arr[size_out_arr] = stak[size_stak - 1];
                    size_stak--;
                }
                size_stak--;
            }
            else if (size_stak == 0 || st[i] == '(') {
                stak[size_stak] = 20;
                size_stak++;
            }
            else if (find_index(operators, st[i], 5) > find_index(index_operators, stak[size_stak - 1], 5)) {
                stak[size_stak] = index_operators[find_index(operators, st[i], 5)];
                size_stak++;
            }
            else if (find_index(operators, st[i], 5) == find_index(index_operators, stak[size_stak - 1], 5) && st[i] == '!') {
                size_stak--;
            }
            else if (find_index(operators, st[i], 5) == find_index(index_operators, stak[size_stak - 1], 5) && st[i] == '-') {
                stak[size_stak] = index_operators[find_index(operators, st[i], 5)];
                size_stak++;
            }
            else {
                while (size_stak != 0) {
                    if ((find_index(operators, st[i], 5) > find_index(index_operators, stak[size_stak - 1], 5)) || (find_index(operators, st[i], 5) == find_index(index_operators, stak[size_stak - 1], 5) && st[i] == '-'))
                        break;
                    out_arr[size_out_arr] = stak[size_stak - 1];
                    size_out_arr++;
                    size_stak--;
                }
                stak[size_stak] = index_operators[find_index(operators, st[i], 5)];
                size_stak++;
            }
        }
    }
    if (!var.empty()) {
        zamena = find_index(var_arr, var, size_var_arr);
        if (zamena == -1) {
            var_arr[size_var_arr] = var;
            zamena = size_var_arr;
            size_var_arr++;
        }
        out_arr[size_out_arr] = zamena;
        size_out_arr++;
        var = "";
    }
    while (size_stak != 0) {
        out_arr[size_out_arr] = stak[size_stak - 1];
        size_out_arr++;
        size_stak--;
    }
    //------------------------------------
    int max_count_var = size_var_arr;
    int count = 1;
    int stak_named[50][200];
    int size_named = 0;
    int size_stak_named[56];
    int new_var_arr[16];
    int size_new_var_arr = 0;
    while (count != 0) {
        count = 0;
        for (int i = 0; i < 56; i++){
            size_stak_named[i] = 0;
        }
        size_named = 0;
        size_new_var_arr = 0;
        for (int i = 0; i < size_out_arr; i++) {
            if (find_index(int_var_arr, out_arr[i], size_var_arr) != -1) {
                stak_named[size_named][size_stak_named[size_named]] = out_arr[i];
                size_stak_named[size_named]++;
                size_named++;

            }
            else if (out_arr[i] == 17) {
                if (stak_named[size_named - 1][size_stak_named[size_named] - 1] == 17) {
                    size_stak_named[size_named - 1] = 0;
                    size_named--;
                }
                else if (stak_named[size_named - 1][0] == 21 && size_stak_named[size_named - 1] == 1) {
                    stak_named[size_named - 1][0] = 22;
                }
                else if (stak_named[size_named - 1][0] == 22 && size_stak_named[size_named - 1] == 1) {
                    stak_named[size_named - 1][0] = 21;
                }
                else {
                    stak_named[size_named - 1][size_stak_named[size_named - 1]] = 17;
                }
            }
            else if (out_arr[i] == 18) {
                if (comparing_arrays(stak_named[size_named - 1], stak_named[size_named - 2], size_stak_named[size_named - 1], size_stak_named[size_named - 2])){
                    size_stak_named[size_named - 1] = 0;
                    size_named--;
                }
                else if (stak_named[size_named - 1][0] == 21 && size_stak_named[size_named - 1] == 1 || stak_named[size_named - 2][0] == 21 && size_stak_named[size_named - 1] == 1){
                    size_stak_named[size_named - 1] = 0;
                    size_named--;
                    size_stak_named[size_named - 1] = 1;
                    stak_named[size_named - 1][0] = 21;
                }
                else if (stak_named[size_named - 2][0] == 22 && size_stak_named[size_named - 1] == 1){
                    assign_array(stak_named[size_named - 2], stak_named[size_named - 1], &size_stak_named[size_named - 1], size_stak_named[size_named - 2]);
                    size_stak_named[size_named - 1] = 0;
                    size_named--;

                }
                else if (stak_named[stak_named.size() - 2][0] == "1" && stak_named[stak_named.size() - 2].size() == 1) {
                    stak_named[stak_named.size() - 2] = stak_named[stak_named.size() - 1];
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 1][0] == "1" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2] == srez(stak_named[stak_named.size() - 1], 0, stak_named[stak_named.size() - 1].size() - 1) || stak_named[stak_named.size() - 1] == srez(stak_named[stak_named.size() - 2], 0, stak_named[stak_named.size() - 2].size() - 1)) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("0");
                    stak_named.pop_back();
                }
                else {
                    stak_named[stak_named.size() - 2] = add_vectors(stak_named[stak_named.size() - 2], stak_named[stak_named.size() - 1]);
                    stak_named[stak_named.size() - 2].push_back("&");
                    stak_named.pop_back();
                }
            }
            else if (out_arr[i] == "|") {
                if (stak_named[stak_named.size() - 1] == stak_named[stak_named.size() - 2]) {
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2][0] == "0" && stak_named[stak_named.size() - 2].size() == 1) {
                    stak_named[stak_named.size() - 2] = stak_named[stak_named.size() - 1];
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 1][0] == "0" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2][0] == "1" && stak_named[stak_named.size() - 2].size() == 1 || stak_named[stak_named.size() - 1][0] == "1" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("1");
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2] == srez(stak_named[stak_named.size() - 1], 0, stak_named[stak_named.size() - 1].size() - 1) || stak_named[stak_named.size() - 1] == srez(stak_named[stak_named.size() - 2], 0, stak_named[stak_named.size() - 2].size() - 1)) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("1");
                    stak_named.pop_back();
                }
                else {
                    stak_named[stak_named.size() - 2] = add_vectors(stak_named[stak_named.size() - 2], stak_named[stak_named.size() - 1]);
                    stak_named[stak_named.size() - 2].push_back("|");
                    stak_named.pop_back();
                }
            }
            else if (out_arr[i] == "-") {
                if (stak_named[stak_named.size() - 1] == stak_named[stak_named.size() - 2]) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("1");
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2][0] == "1" && stak_named[stak_named.size() - 2].size() == 1) {
                    stak_named[stak_named.size() - 2] = stak_named[stak_named.size() - 1];
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 1][0] == "1" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("1");
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2][0] == "0" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("1");
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 1][0] == "0") {
                    stak_named[stak_named.size() - 2].push_back("!");
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 2] == srez(stak_named[stak_named.size() - 1], 0, stak_named[stak_named.size() - 1].size() - 1)) {
                    stak_named[stak_named.size() - 2] = stak_named[stak_named.size() - 1];
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 1] == srez(stak_named[stak_named.size() - 2], 0, stak_named[stak_named.size() - 2].size() - 1)) {
                    stak_named.pop_back();
                }
                else {
                    stak_named[stak_named.size() - 2] = add_vectors(stak_named[stak_named.size() - 2], stak_named[stak_named.size() - 1]);
                    stak_named[stak_named.size() - 2].push_back("-");
                    stak_named.pop_back();
                }
            }
        }
        if (out_arr != stak_named[0]) {
            count = 1;
            out_arr = stak_named[0];
            for (int i = 0; i < out_arr.size(); i++) {
                if (!finded(operators_string, out_arr[i]) && !finded(new_var_arr, out_arr[i])) {
                    new_var_arr.push_back(out_arr[i]);
                }
            }
            var_arr = new_var_arr;
        }
    }
    //------------------------------------

    if (out_arr.size() == 1) {
        if (out_arr[0] == "1")
            cout << "Valid";
        else if (out_arr[0] == "0")
            cout << "Unsatisfiable";
        else
            cout << "Satisfiable and invalid, " << ((2 << (max_count_var-1)) / 2) << " true and " << ((2 << (max_count_var - 1)) / 2) << " false cases";
    }
        //------------------------------------
    else {
        int count_true = 0;
        int number_of_combinations = 1 << (var_arr.size());
        long long stak_new;
        int size;
        long long n, k, res;
        int t;
        for (long long i = 0; i < number_of_combinations; i += 4) {
            n = ((i + 3) << 48) + ((i + 2) << 32) + ((i + 1) << 16) + i;
            stak_new = 0;
            size = 0;
            for (int j = 0; j < out_arr.size(); j++) {
                k = 1;
                if (finded(var_arr, out_arr[j])) {
                    t = find_index(var_arr, out_arr[j]);
                    k = (k << t);
                    res = ((n & k) >> t) + ((n & (k << 16)) >> (t + 15)) + ((n & (k << 32)) >> (t + 30)) + ((n & (k << 48)) >> (t + 45));
                    stak_new += (res << (4 * size));
                    size++;
                }
                else if (out_arr[j] == "!") {
                    stak_new = stak_new + (((~(stak_new >> ((size - 1) * 4))) & 15) << ((size - 1) * 4)) - (((stak_new >> ((size - 1) * 4)) & 15) << ((size - 1) * 4));
                }
                else if (out_arr[j] == "&") {
                    stak_new = stak_new + ((((stak_new >> ((size - 1) * 4)) & (stak_new >> ((size - 2) * 4))) & 15) << ((size -2) * 4)) - (((stak_new >> ((size - 2) * 4)) & 15) << ((size - 2) * 4));
                    size--;
                    stak_new = stak_new & ((k << (size * 4)) - 1);
                }
                else if (out_arr[j] == "|") {
                    stak_new = stak_new + ((((stak_new >> ((size - 1) * 4)) | (stak_new >> ((size - 2) * 4))) & 15) << ((size - 2) * 4)) - (((stak_new >> ((size - 2) * 4)) & 15) << ((size - 2) * 4));
                    size--;
                    stak_new = stak_new & ((k << (size * 4)) - 1);
                }
                else if (out_arr[j] == "-") {
                    stak_new = stak_new + ((((~(stak_new >> ((size - 2) * 4))) | (stak_new >> ((size - 1) * 4))) & 15) << ((size - 2) * 4)) - (((stak_new >> ((size - 2) * 4)) & 15) << ((size - 2) * 4));
                    size--;
                    stak_new = stak_new & ((k << (size * 4)) - 1);
                }
            }
            count_true = count_true + (stak_new & 1) + ((stak_new >> 1) & 1) + ((stak_new >> 2) & 1) + ((stak_new >> 3) & 1);
        }
        if (count_true == number_of_combinations) {
            cout << "Valid";
        }
        else if (count_true == 0) {
            cout << "Unsatisfiable";
        }
        else {
            cout << "Satisfiable and invalid, " << count_true * (1 << (max_count_var - var_arr.size())) << " true and " << (number_of_combinations - count_true) * (1 << (max_count_var - var_arr.size())) << " false cases";
        }
    }
    return 0;
}