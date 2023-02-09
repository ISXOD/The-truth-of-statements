#include <iostream>
#include <vector>
#include <string>

using namespace std;
void Print_ex(long long num, long long stak_new, int size) {
    long long k;
    for (int i = 0; i < 4; i++) {
        k = num >> (i*16);
        for (int j = 0; j < size; j++){
            cout << ((k >> j) & 1);
        }
        cout << " <=> "<< ((stak_new >> i) & 1) << endl;
    }
}
template <typename T>
bool finded(vector <T> vec, T elem) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == elem) {
            return true;
        }
    }
    return false;
}
template <typename T>
int find_index(vector <T> vec, T elem) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == elem) {
            return i;
        }
    }
    return -1;
}
template <typename T>
void Print(T num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        if ((i+1) % 4 == 0) {
            cout << "|";
        }
        cout << ((num >> i) & 1);
    }
    cout << endl;
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
    vector <char> operators = { '(', '-', '|', '&', '!' };
    vector <string> operators_string = { "(", "-", "|", "&", "!" };
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
    vector <string> out_arr;
    vector <char> stak;
    vector <string> var_arr;
    for (i = 0; i < st.size(); i++) {
        if (!(st[i] == operators[0] || st[i] == operators[1] || st[i] == operators[2] || st[i] == operators[3] ||
              st[i] == operators[4] || st[i] == ')')) {
            var += st[i];
        }
        else {
            if (!var.empty()) {
                out_arr.push_back(var);
                if (!finded(var_arr, var)) {
                    var_arr.push_back(var);
                }
                var = "";
            }
            if (st[i] == ')') {
                while (stak[stak.size() - 1] != '(') {
                    string h = "";
                    h += stak[stak.size() - 1];
                    out_arr.push_back(h);
                    stak.pop_back();
                }
                stak.pop_back();
            }
            else if (stak.empty() || st[i] == '(')
                stak.push_back(st[i]);
            else if (find_index(operators, st[i]) > find_index(operators, stak[stak.size() - 1])) {
                stak.push_back(st[i]);
            }
            else if (find_index(operators, st[i]) == find_index(operators, stak[stak.size() - 1]) && st[i] == '!') {
                stak.pop_back();
            }
            else if (find_index(operators, st[i]) == find_index(operators, stak[stak.size() - 1]) && st[i] == '-') {
                stak.push_back(st[i]);
            }
            else {
                while (!stak.empty()) {
                    if ((find_index(operators, st[i]) > find_index(operators, stak[stak.size() - 1])) || (find_index(operators, st[i]) == find_index(operators, stak[stak.size() - 1]) && st[i] == '-'))
                        break;
                    string h = "";
                    h += stak[stak.size() - 1];
                    out_arr.push_back(h);
                    stak.pop_back();
                }
                stak.push_back(st[i]);
            }
        }
    }
    if (var.size() != 0) {
        out_arr.push_back(var);
        if (!finded(var_arr, var)) {
            var_arr.push_back(var);
        }
        var = "";
    }
    if (!stak.empty()) {
        while (!stak.empty()) {
            string h = "";
            h += stak[stak.size() - 1];
            out_arr.push_back(h);
            stak.pop_back();
        }
    }
    //------------------------------------
    int max_count_var = var_arr.size();
    int count = 1;
    vector <vector <string> > stak_named;
    vector <string> new_var_arr;
    while (count != 0) {
        count = 0;
        stak_named.clear();
        new_var_arr.clear();
        for (int i = 0; i < out_arr.size(); i++) {
            if (finded(var_arr, out_arr[i])) {
                stak_named.push_back(vector <string>());
                stak_named[stak_named.size() - 1].push_back(out_arr[i]);
            }
            else if (out_arr[i] == "!") {
                if (stak_named[stak_named.size() - 1][stak_named[stak_named.size() - 1].size() - 1] == "!") {
                    stak_named[stak_named.size() - 1].pop_back();
                }
                else if (stak_named[stak_named.size() - 1][0] == "0" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named[stak_named.size() - 1].clear();
                    stak_named[stak_named.size() - 1].push_back("1");
                }
                else if (stak_named[stak_named.size() - 1][0] == "1" && stak_named[stak_named.size() - 1].size() == 1) {
                    stak_named[stak_named.size() - 1].clear();
                    stak_named[stak_named.size() - 1].push_back("0");
                }
                else {
                    stak_named[stak_named.size() - 1].push_back("!");
                }
            }
            else if (out_arr[i] == "&") {
                if (stak_named[stak_named.size() - 1] == stak_named[stak_named.size() - 2]) {
                    stak_named.pop_back();
                }
                else if (stak_named[stak_named.size() - 1][0] == "0" && stak_named[stak_named.size() - 1].size() == 1 || stak_named[stak_named.size() - 2][0] == "0" && stak_named[stak_named.size() - 2].size() == 1) {
                    stak_named[stak_named.size() - 2].clear();
                    stak_named[stak_named.size() - 2].push_back("0");
                    stak_named.pop_back();
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
                    cout << "!" << ((stak_new >> ((size - 1) * 4)) & 15) << " = " << ((~(stak_new >> ((size - 1) * 4))) & 15) << endl;
                    stak_new = stak_new + (((~(stak_new >> ((size - 1) * 4))) & 15) << ((size - 1) * 4)) - (((stak_new >> ((size - 1) * 4)) & 15) << ((size - 1) * 4));
                }
                else if (out_arr[j] == "&") {
                    cout << ((stak_new >> ((size - 1) * 4)) & 15) << " & " << ((stak_new >> ((size - 2) * 4)) & 15) << " = " << (((stak_new >> ((size - 1) * 4)) & (stak_new >> ((size - 2) * 4))) & 15) << endl;
                    stak_new = stak_new + ((((stak_new >> ((size - 1) * 4)) & (stak_new >> ((size - 2) * 4))) & 15) << ((size -2) * 4)) - (((stak_new >> ((size - 2) * 4)) & 15) << ((size - 2) * 4));
                    size--;
                    stak_new = stak_new & ((k << (size * 4)) - 1);
                }
                else if (out_arr[j] == "|") {
                    cout << ((stak_new >> ((size - 1) * 4)) & 15) << " | " << ((stak_new >> ((size - 2) * 4)) & 15) << " = " << (((stak_new >> ((size - 1) * 4)) | (stak_new >> ((size - 2) * 4))) & 15) << endl;
                    stak_new = stak_new + ((((stak_new >> ((size - 1) * 4)) | (stak_new >> ((size - 2) * 4))) & 15) << ((size - 2) * 4)) - (((stak_new >> ((size - 2) * 4)) & 15) << ((size - 2) * 4));
                    size--;
                    stak_new = stak_new & ((k << (size * 4)) - 1);
                }
                else if (out_arr[j] == "-") {
                    cout << ((stak_new >> ((size - 1) * 4)) & 15) << " -> " << ((stak_new >> ((size - 2) * 4)) & 15) << " = " << (((~(stak_new >> ((size - 1) * 4))) | (stak_new >> ((size - 2) * 4))) & 15) << endl;
                    stak_new = stak_new + ((((~(stak_new >> ((size - 1) * 4))) | (stak_new >> ((size - 2) * 4))) & 15) << ((size - 2) * 4)) - (((stak_new >> ((size - 2) * 4)) & 15) << ((size - 2) * 4));
                    size--;
                    stak_new = stak_new & ((k << (size * 4)) - 1);
                }
            }
            for ( int j = 0; j < var_arr.size(); j++){
                cout << var_arr[j][0];
            }
            cout << endl;
            Print_ex(n, stak_new, var_arr.size());
            //Print(n);
            //Print(stak_new);
            cout << endl;
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