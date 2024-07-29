#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <set>
#include <thread>
using namespace std;
using PII = pair<int, int>;
using MIVI = unordered_map<int, vector<int>>;

/// enumerate all recursive graph traversal orderings
/// random update to save time, vector/matrix operation

/// large complexity for brute force method
/// term current root dfs if long time no updating

/// 当前path长度变化率与当前root调用dfs节点数的变化率之间的关系
/// 支持配置从root开始搜索

#define CIC__UTF8_CHINESE_SIZE 3

#define CIC__RAND_ENV      \
    random_device rd; \
    mt19937 rng(rd());

void shuffle(vector<int>& v) {
    CIC__RAND_ENV
    shuffle(v.begin(), v.end(), rng);
}
void shuffle(const vector<PII>::iterator& bg, const vector<PII>::iterator& ed) {
    CIC__RAND_ENV
    shuffle(bg, ed, rng);
}
void dsortShuffle(vector<PII>& v, const int k) {
    sort(v.begin(), v.end(), [](const auto& l, const auto& r)->bool{return l.second > r.second;});
    const int n = min(k, int(v.size()));
    shuffle(v.begin(), v.begin() + n);
    shuffle(v.begin() + n, v.end());
}

void clipVector(vector<int>& res, const int ma, const int mi) {
    for (auto& r : res) {
        r = min(ma,max(r, mi));
    }
}

vector<int> squareDecVector(const int n, int b) {
    vector<int> res(n, 0);
    --b;
    generate(res.rbegin(), res.rend(), [&]{++b; return b * b;});
    return res;
}
vector<int> linearVectorF(const int n, const float k, const float b) {
    vector<int> res(n, 0);
    float y = b - k;
    generate(res.begin(), res.end(), [&]{ y += k; return ceil(y);});
    return res;
}
vector<int> linearVector(const int n, const int k, const int b) {
    vector<int> res(n, 0);
    int y = b - k;
    generate(res.begin(), res.end(), [&]{y += k; return y;});
    return res;
}
vector<int> idVector(const int n) {
    return linearVector(n, 1, 0);
}
vector<int> idVector(const int n, const int start) {
    return linearVector(n, 1, start);
}
vector<int> inVector(const int n, const int end) {
    const int start = n - 1 + end;
    return linearVector(n, -1, start);
}
vector<int> randomVector(const int n) {
    vector<int> res(idVector(n));
    shuffle(res);
    return res;
}

PII randomChoose(const vector<int>& number, const vector<int>& frequency) {
    CIC__RAND_ENV
    const int sum = accumulate(frequency.begin(), frequency.end(), 0);
    if (sum < 1) return make_pair(0, number[0]);
    uniform_int_distribution<int> distr(0, sum-1);
    const int res = distr(rng);
    int prev_sum = 0;
    for (int i = 0; i < number.size(); ++i) {
        prev_sum += frequency[i];
        if (res < prev_sum) return make_pair(i, number[i]);
    }
    return make_pair(0, number[0]);
}///randomChoose
PII randomChooseConst(const vector<int>& number) {
    vector<int> frequency(number.size(), 1);
    return randomChoose(number, frequency);
}
PII randomChooseLinear(const vector<int>& number) {
    vector<int> frequency(idVector(number.size(), 1));
    return randomChoose(number, frequency);
}
bool randomChoose(const int f, const int g) {
    const auto res = randomChoose({1, 0}, {f, g});
    return 1 == res.second;
}
bool randomChooseSquare(const int f, const int g) {
    const auto res = randomChoose({1, 0}, {f*f, g*g});
    return 1 == res.second;
}
bool randomChoose(const float ratio) {
    const int N = 10000;
    const int first = N * ratio;
    const int second = N - first;
    return randomChoose(first, second);
}
PII randomChoose(const float f, const float g, const float h) {
    const int N = 10000;
    return randomChoose({0, 1, 2}, {f*N, g*N, h*N});
}

class CIC {
protected:
    unordered_map<string, int> idiom_to_number_;
    unordered_map<int, string> number_to_idiom_;
    unordered_map<int, vector<int>> next_idioms_;

    unordered_map<int, int> pheromone_;
    MIVI local_long_path_;
    vector<int> global_long_path_;
    vector<int> cur_global_long_path_;

    int N_;
    int MODE_;
    int DEBUG_INFO_;
    int ITER_NUM_;
    int NO_UPDATE_TERM_NUM_;
    int GENE_PATH_LENGTH_THRESH_;
    float GENE_PATH_LENGTH_INC_RATIO_;
    float GENE_CACHE_LOCAL_MUTATION_GLOBAL_RATIO_;
    float GENE_CACHE_LOCAL_MUTATION_CUR_GLOBAL_RATIO_;
    float GENE_CACHE_COMBINATION_RATIO_;
    bool ANT_ENABLE_;
    int ANT_PHEROMONE_MIN_;
    int ANT_PHEROMONE_MAX_;
    float ANT_PHEROMONE_DECAY_RATIO_;
    bool BACKTRACK_ENABLE_;
    int SEARCH_SIZE_MULTIPLIER_;
    float INSTANT_SEARCH_RATIO_;
    int PRIMARY_GUARD_NEXT_NUM_THRESH_;
    int WRITE_PATH_LENGTH_THRESH_;
    bool WRITE_CACHE_ENABLE_;

    vector<string> DIGIT_CHAR_;
    vector<string> FREESTYLE_CHAR_;

private:
    int debug_k_;
    int debug_dfs_root_;
    int debug_dfs_cnt_;
    int debug_else_cnt_;
    int debug_cache_write_cnt_;
    int debug_cache_write_diff_cnt_;
    int debug_cache_read_cnt_;
    int debug_gene_comb_cnt_;
    void showDebugL() {
        cout << "k=" << debug_k_;
        cout << " root="; showIdiom(debug_dfs_root_);
        cout << " dfscnt=" << debug_dfs_cnt_;
        cout << " else=" << debug_else_cnt_;
        cout << " cachewrite=" << debug_cache_write_cnt_;
        cout << " cachewritediff=" << debug_cache_write_diff_cnt_;
        cout << " cacheread=" << debug_cache_read_cnt_;
        cout << " genecomb=" << debug_gene_comb_cnt_;
        cout << "\n";
    }
    
protected:
    void writeLocal() {
        MIVI* cp = new MIVI(local_long_path_);
        if (nullptr == cp) {
            cout << "copy local failed!\n";
            return;
        }
        cout << "write local size " << cp->size() << "\n";
        if (BACKTRACK_ENABLE_) {
            thread{[](const MIVI* p){
                ofstream outfile("cache.txt");
                outfile << "size: " << p->size() << "\n";
                for (const auto& [key, val] : *p) {
                     outfile << key << ":";
                    for (const auto v : val) {
                        outfile << v << " ";
                    }
                    outfile << "\n";
                }///for
                outfile.close();
                delete p;
            }, cp}.detach();
        }///if backtrace enable
        else {///else backtrace disable
            thread{[](const MIVI* p){
                ofstream outfile("cache.txt");
                outfile << "size: " << p->size() << "\n";
                for (const auto& [key, val] : *p) {
                     outfile << key << ":";
                    for (const auto v : val) {
                        outfile << v << " ";
                    }
                    outfile << "\n";
                }///for
                outfile.close();
                delete p;
            }, cp}.join();
        }///else backtrace disable
    }///writeLocal
    bool readLastLocal() {
        const string file("cache.txt");
        ifstream infile(file);
        if (!infile.is_open()) {
            cout << "open " << file << " failed!\n";
            return false;
        }
        string line;
        getline(infile, line);
        while (getline(infile, line)) {
            //cout << "line="<< line << "\n";
            int i = 0;
            while (line[i] != ':') ++i;
            const int key = stoi(line.substr(0, i));
            //cout << "key=" << key << "\n";
            vector<int> val;
            ++i;
            int j = i;
            while (j < line.size()) {
                if (' ' == line[j]) {
                    const int v = stoi(line.substr(i, j - i));
                    val.push_back(v);
                    //cout << "v=" << v << "\n";
                    ++j; i = j;
                } else {
                    ++j;
                }
            }
            local_long_path_[key] = val;
            //val.push_back(stoi(line.substr(i, j - i)));
        }
        trimLocal();
        cout << "read local size: " << local_long_path_.size() << "\n";
        initCurGlobal();
        return true;
    }
    void trimLocal() {
        MIVI tmp;
        for (const auto& [key, val] : local_long_path_) {
            if (val.size() > 1) {
                tmp[key] = val;
            }
        }
        cout << "trim size: " << (local_long_path_.size() - tmp.size()) << "\n";
        tmp.swap(local_long_path_);
    }
    void initCurGlobal() {
        cur_global_long_path_ = {0};
        for (const auto& [key, val] : local_long_path_) {
            if (val.size() >= GENE_PATH_LENGTH_THRESH_) {
                cur_global_long_path_ = val;
                break;
            }
        }
    }
    void writeGlobal() {
        if (global_long_path_.size() < WRITE_PATH_LENGTH_THRESH_) return;
        showPath(global_long_path_);
        cout << "write global size " << global_long_path_.size() << " of "; showIdiomL(global_long_path_[0]);
        ofstream outfile("result.txt");
        outfile << "size: " << global_long_path_.size() << "\n";
        for (int i = 0; i < global_long_path_.size() - 1; ++i) {
            const int number = global_long_path_[i];
            const string& idiom = number_to_idiom_[number];
            outfile << idiom << "->";
        }
        outfile << number_to_idiom_[*(global_long_path_.rbegin())] << "\n";
        outfile.close();
        //showDebugL();
    }
    void showPheromone() {
        int size = 0;
        for (const auto& [key, val] : pheromone_) {
            const auto& idiom = number_to_idiom_[key];
            if (val > ANT_PHEROMONE_MIN_) {
                ++size;
                cout << idiom << ":" << val << " ";
            }
        }
        cout << "\npheromone size: " << size << "\n";
    }
    void showIdiom(const string& idiom) const {
        /*for (int i = 0; i < idiom.size(); i += CIC__UTF8_CHINESE_SIZE) {
              cout << idiom.substr(i, CIC__UTF8_CHINESE_SIZE);
          }*/
        cout << idiom;
    }
    void showIdiom(const int number) {
        showIdiom(number_to_idiom_[number]);
    }
    void showIdiomL(const int number) {
        showIdiom(number);
        cout << "\n";
    }
    void showPath(const vector<int>& path) {
        for (const auto number : path) {
            showIdiom(number);
            cout << "-> ";
        }
        cout << "\npath size: " << path.size() << "\n";
    }
public:
    CIC() {
        readConfig();
        readData();
        readLastGlobal();
        readLastLocal();
        build();
        cout << "graph constructed!\n";
    }

    void run() {
        debug_else_cnt_ = 0;
        debug_cache_write_cnt_ = 0;
        debug_cache_write_diff_cnt_ = 0;
        debug_cache_read_cnt_ = 0;
        debug_gene_comb_cnt_ = 0;

        for (int idiom = 0; idiom < N_; ++idiom) {
            pheromone_[idiom] = ANT_PHEROMONE_MIN_;
        }
        
        for (int k = 0; k < ITER_NUM_; ++k) {
            cout << "k=" << k << " search...\n";
            debug_k_ = k;
            vector<int> RVEC(randomVector(N_));
            vector<int> visited(N_, 0);
            for (int n = 0; n < N_; ++n) {
                const int start = RVEC[n];
                debug_dfs_root_ = start;
                if (visited[start]) continue;
                cout << "k,n=" << k << "," << n << " start "; showIdiomL(start);
                debug_dfs_cnt_ = 0;
                NO_UPDATE_TERM_NUM_ = max(NO_UPDATE_TERM_NUM_, int(global_long_path_.size()) * SEARCH_SIZE_MULTIPLIER_);
                const int prev_start_length = local_long_path_.count(start) ? local_long_path_.at(start).size() : 0;
                visited[start] = 1;
                vector<int> path;
                path.push_back(start);
                dfs(start, path, visited);
                if (BACKTRACK_ENABLE_) visited[start] = 0;
                if (ANT_ENABLE_) {
                    const int cur_start_length = local_long_path_.count(start) ? local_long_path_.at(start).size() : 0;
                    const int inc_length = cur_start_length - prev_start_length;
                    updatePheromone(local_long_path_.at(start), inc_length);
                }

                if (WRITE_CACHE_ENABLE_) writeLocal();
            }///for n
        }///for k
        writeLocal();
    }///run

protected:
    void updatePheromone(const vector<int>& path, const int increase_length=1) {
        const int n = path.size();
        if (increase_length > 0) {
            const float d = (n >= GENE_PATH_LENGTH_THRESH_) ? 1.0f : sqrt(n) / n;
            vector<int> add_vec(linearVectorF(n, d, d));
            for (int i = 0; i < n; ++i) {
                pheromone_[path[i]] = min(ANT_PHEROMONE_MAX_, pheromone_[path[i]] + add_vec[i]);
            }
        } else if (increase_length == 0) {
            for (const auto vertex : path) {
                pheromone_[vertex] = max(ANT_PHEROMONE_MIN_, int(pheromone_[vertex] * ANT_PHEROMONE_DECAY_RATIO_));
            }
        } else {
            const float d = n < GENE_PATH_LENGTH_THRESH_ ? 1 : sqrt(n) / n;
            vector<int> dec_vec(linearVectorF(n, d, d));
            for (int i = 0; i < n; ++i) {
                pheromone_[path[i]] = max(ANT_PHEROMONE_MIN_, pheromone_[path[i]] - dec_vec[i]);
            }
        }
        //if(DEBUG_INFO_) showPheromone();
    }
    void update(const vector<int>& path) {
        updateLongPath(path);
        if (ANT_ENABLE_) updatePheromone(path);
    }
    void updateLongPath(const vector<int>& path) {
        updateLocalLongPath(path);
        updateGlobalLongPath(path);
    }
    void updateGlobalLongPath(const vector<int>& path) {
        //if(DEBUG_INFO_)cout << "begin global\n";
        if (path.size() >= cur_global_long_path_.size()) {
            cur_global_long_path_ = path;
        }
        if (path.size() >= global_long_path_.size()) {
            debug_dfs_cnt_ = 0;
            global_long_path_ = path;
            writeGlobal();
            GENE_PATH_LENGTH_THRESH_ = GENE_PATH_LENGTH_THRESH_ * (1.0f - GENE_PATH_LENGTH_INC_RATIO_) + global_long_path_.size() * GENE_PATH_LENGTH_INC_RATIO_ + 1;
            cout << "update gene path length thresh: " << GENE_PATH_LENGTH_THRESH_ << "\n";
        }
        //if(DEBUG_INFO_)cout << "end global\n";
    }
    vector<int> getGeneCombination(const vector<int>& pp, const vector<int>& p) {
        /// TODO
        unordered_map<int, int> mp;
        for (int i = 0; i < p.size(); ++i) {
            mp[p[i]] = i;
        }
        int j = 1;
        for (; j < pp.size(); ++j) {
            if (mp.count(pp[j])) break;
        }
        if (j == pp.size()) {
            ++debug_cache_write_cnt_;
            return pp;
        }

        vector<int> res;
        const int k = mp[pp[j]];
        if (j <= k) {
            res.assign(p.begin(), p.begin() + k + 1);
            set<int> prev(res.begin(), res.end());
            for (int t = j + 1; t < pp.size(); ++t) {
                if (prev.count(pp[t])) break;
                res.push_back(pp[t]);
            }
        } else {
            res.assign(pp.begin(), pp.begin() + j + 1);
            set<int> prev(res.begin(), res.end());
            for (int t = k + 1; t < p.size(); ++t) {
                if (prev.count(p[t])) break;
                res.push_back(p[t]);
            }
        }
        ++debug_gene_comb_cnt_;
        return res;
    }
    void updateLocalLongPath(const vector<int>& path) {
        //if(DEBUG_INFO_) cout << "begin local\n";
        const float gene_cache_local_ratio = 1.0f - GENE_CACHE_LOCAL_MUTATION_GLOBAL_RATIO_ - GENE_CACHE_LOCAL_MUTATION_CUR_GLOBAL_RATIO_;
        const auto choose_res = randomChoose(GENE_CACHE_LOCAL_MUTATION_GLOBAL_RATIO_, GENE_CACHE_LOCAL_MUTATION_CUR_GLOBAL_RATIO_, gene_cache_local_ratio);
        const vector<int>* choose_path = &path;
        if (0 == choose_res.first) {
            choose_path = &global_long_path_;
        } else if (1 == choose_res.first) {
            choose_path = &cur_global_long_path_;
        }

        const auto truncate = randomChooseConst(*choose_path);
        //if(DEBUG_INFO_)cout << "local truncate=" << truncate.first << "\n";
        const int truncate_size = choose_path->size() - truncate.first;
        if (truncate_size <= 2) return;
        const int cache_size = (local_long_path_.count(truncate.second)) ? local_long_path_.at(truncate.second).size() : 0;
        const bool res = randomChooseSquare(truncate_size, cache_size);
        if (res) {
            const vector<int> truncate_path(choose_path->begin()+truncate.first, choose_path->end());
            if (DEBUG_INFO_) {cout << "update local "; showIdiom(truncate.second);}
            if (0 == cache_size) ++debug_cache_write_diff_cnt_;
            const bool comb = randomChoose(GENE_CACHE_COMBINATION_RATIO_);
            if (!comb || !local_long_path_.count(truncate.second)) {
                local_long_path_[truncate.second] = truncate_path;
                ++debug_cache_write_cnt_;
                if (DEBUG_INFO_) {cout << " replsize " << cache_size << "<-" << truncate_size << "\n";}
            } else {
                local_long_path_[truncate.second] = getGeneCombination(truncate_path, local_long_path_[truncate.second]);
                if (DEBUG_INFO_) {cout << " combsize " << cache_size  << "<-" << local_long_path_[truncate.second].size() << "\n";}
            }
        }
        //if(DEBUG_INFO_) cout << "end local\n";
    }
    int getUniqueIndex(const vector<int>& cache, const vector<int>& path) {
        set<int> path_set(path.begin(), path.end());
        int end_index = 1;
        while (end_index < cache.size()) {
            if (path_set.count(cache[end_index])) break;
            ++end_index;
        }
        return end_index;
    }
    void showVisitedS(const vector<int>& visited) {
        const int cnt = count(visited.begin(), visited.end(), 1);
        cout << "visited cnt: " << cnt << "/" << N_ << "  ";
    }
    void showVisitedL(const vector<int>& visited) {
        showVisitedS(visited);
        cout << "\n";
    }
    void showGlobalL() {
        cout << "global size: " << cur_global_long_path_.size() << "/" << global_long_path_.size() << "\n";
    }
    void dfs(const int cur, vector<int>& path, vector<int>& visited) {
        if (debug_dfs_cnt_ >= NO_UPDATE_TERM_NUM_) return;/// return immediately from the recursive stack
        if(DEBUG_INFO_){cout << "begin dfs "; showIdiom(cur); showDebugL(); showVisitedS(visited); showGlobalL();}
        ++debug_dfs_cnt_;
        update(path);
        const bool else_flag = randomChoose(INSTANT_SEARCH_RATIO_);
        if (!else_flag && local_long_path_.count(cur)) {
            const int end_index = getUniqueIndex(local_long_path_[cur], path);
            if (end_index >= 3) {

                vector<int> unique_vec(local_long_path_[cur].begin()+1, local_long_path_[cur].begin()+end_index);
                vector<int> choice_vec(unique_vec.begin()+1, unique_vec.end());
                ///const auto& choice = randomChooseLinear(choice_vec);
                const auto& choice = randomChooseConst(choice_vec);
                
                ///if (choice.first >= 1) {
                    ++debug_cache_read_cnt_;

                    vector<int> truncate_vec(unique_vec.begin(), unique_vec.begin()+choice.first+2);
                    cout << "if shortcut: " << path.size() << " "; showPath(truncate_vec);
                    path.insert(path.end(), truncate_vec.begin(), truncate_vec.end());
                    for (const auto vertex : truncate_vec) {
                        visited[vertex] = 1;
                    }
                    const int next = *(truncate_vec.rbegin());
                    dfs(next, path, visited);
                    for (const auto vertex : truncate_vec) {
                        if (BACKTRACK_ENABLE_) visited[vertex] = 0;
                        path.pop_back();
                    }
                ///}///if choice
            }///if end index
        } ///if
        /// else
            if (DEBUG_INFO_) { cout << "else cur "; showIdiomL(cur); }
            ++debug_else_cnt_;

            if (ANT_ENABLE_) {
                vector<PII> next_pairs;
                for (const auto next : next_idioms_[cur]) {
                    if (visited[next]) continue;
                    next_pairs.emplace_back(make_pair(next, pheromone_[next]));
                }///for next
                //if(DEBUG_INFO_){cout << "next size: " << next_pairs.size() << "\n";}
                if (0 == next_pairs.size()) {
                    //if(DEBUG_INFO_)cout << "end dfs "; showIdiomL(cur); showDebugL();
                    return;
                }
                dsortShuffle(next_pairs, PRIMARY_GUARD_NEXT_NUM_THRESH_);
                for (const auto& next_pair : next_pairs) {
                    const auto next = next_pair.first;
                    path.push_back(next);
                    visited[next] = 1;
                    dfs(next, path, visited);
                    if (BACKTRACK_ENABLE_) visited[next] = 0;
                    path.pop_back();
                }///for next_pair
            }///ant enable
            else {
                vector<int> nexts;
                for (const auto next : next_idioms_[cur]) {
                    if (!visited[next]) {
                        nexts.push_back(next);
                    }
                }
                shuffle(nexts);
                for (const auto next : nexts) {
                    path.push_back(next);
                    visited[next] = 1;
                    dfs(next, path, visited);
                    if (BACKTRACK_ENABLE_) visited[next] = 0;
                    path.pop_back();
                }
            }///ant disable
        ///else
        //if(DEBUG_INFO_){cout << "end dfs "; showIdiomL(cur); showDebugL();}
    }///dfs

protected:
    bool build() {
        int cnt = 0;
        for (const auto& _1 : idiom_to_number_) {
            const string& idiom1 = _1.first;
            const int number1 = _1.second;
            for (const auto& _2 : idiom_to_number_) {
                const string& idiom2 = _2.first;
                const int number2 = _2.second;
                if (number2 == number1) continue;
                int size1 = idiom1.size(), size2 = idiom2.size();
                //cout << idiom1 << " " << size1 << " : " << idiom2 << " " << size2 << "\n";
                if (idiom1[size1-1]==idiom2[2] && idiom1[size1-2]==idiom2[1] && idiom1[size1-3]==idiom2[0]) { 
                    //if (DEBUG_INFO_ && cnt % 10 == 1) cout << idiom1 << " -> " << idiom2 << "\n";
                    next_idioms_[number1].push_back(number2);
                    ++cnt;
                }
            }///for2
        }///for1
        cout << "build " << cnt << " connections!\n";
    }///build

    bool readLastGlobal() {
        const string file("result.txt");
        ifstream in(file);
        if (!in.is_open()) {
            cout << "Error open " << file << "!\n";
            return false;
        }
        string line;
        if(!getline(in, line)) {
            cout << "Error parse " << file << "!\n";
            return false;
        }
        if (!getline(in, line)) {
            cout << "Error parse " << file << "!\n";
            return false;
        }
        string idiom;
        for (int i = 0; i < line.size(); ) {
            if ('-' == line[i]) {
                const int number = idiom_to_number_[idiom];
                global_long_path_.push_back(number);
                idiom = "";
                i += 2;
            } else {
                idiom += line.substr(i, CIC__UTF8_CHINESE_SIZE);
                i += CIC__UTF8_CHINESE_SIZE;
            }
        }
        const int number = idiom_to_number_[idiom];
        global_long_path_.push_back(number);
        in.close();
        cout << "read last global size: " << global_long_path_.size() << "\n";
        return true;
    }
    bool readData() {
        const string file("data.json");
        Json::Reader reader;
        Json::Value root;
        ifstream in(file, ios::binary);
        if (!in.is_open()) {
            cout << "Error opening " << file << "!\n";
            return false;
        }
        if (!reader.parse(in, root)) {
            cout << "Error parse " << file << "!\n";
            return false;
        }
        N_ = 0;
        for (int i = 0; i < root.size(); ++i) {
            const Json::Value& obj = root[i];
            const string& idiom = obj["word"].asString();
            if (0 == MODE_) {
                idiom_to_number_[idiom] = N_;
                number_to_idiom_[N_] = idiom;
                ++N_;
            } else if (1 == MODE_) {
                if (12 == idiom.size()) {
                    idiom_to_number_[idiom] = N_;
                    number_to_idiom_[N_] = idiom;
                    ++N_;
                }
            } else if (2 == MODE_ || 3 == MODE_) {
                const auto& str_vec = 2 == MODE_ ? DIGIT_CHAR_ : FREESTYLE_CHAR_;
                bool contain = false;
                for (int j = 0; j < idiom.size(); j += CIC__UTF8_CHINESE_SIZE) {
                    for (const auto& str : str_vec) {
                        if (str == idiom.substr(j, CIC__UTF8_CHINESE_SIZE)) {
                            contain = true;
                            break;
                        }
                    }
                    if (contain) break;
                }
                if (contain) {
                    idiom_to_number_[idiom] = N_;
                    number_to_idiom_[N_] = idiom;
                    ++N_;
                }
            }///MODE2 or MODE3
        }///for
        in.close();
        cout << "graph vertices: " << N_ << "\n";
        return true;
    }///readData

    bool readConfig() {
        const string file("config.json");
        Json::Reader reader;
        Json::Value root;
        ifstream in(file, ios::binary);
        if (!in.is_open()) {
            cout << "Error opening " << file << "!\n";
            return false;
        }
        if (!reader.parse(in, root)) {
            cout << "Error parse " << file << "!\n";
            return false;
        }

        MODE_ = root["mode"].asInt();
        DEBUG_INFO_ = root["debug_info"].asInt();
        ITER_NUM_ = root["iter_num"].asInt();
        NO_UPDATE_TERM_NUM_ = root["no_update_term_num"].asInt();
        GENE_PATH_LENGTH_THRESH_ = root["gene_path_length_init_thresh"].asInt();
        GENE_PATH_LENGTH_INC_RATIO_ = root["gene_path_length_inc_ratio"].asFloat();
        GENE_CACHE_LOCAL_MUTATION_GLOBAL_RATIO_ = root["gene_cache_local_mutation_global_ratio"].asFloat();
        GENE_CACHE_LOCAL_MUTATION_CUR_GLOBAL_RATIO_ = root["gene_cache_local_mutation_cur_global_ratio"].asFloat();
        GENE_CACHE_COMBINATION_RATIO_ = root["gene_cache_combination_ratio"].asFloat();
        ANT_ENABLE_ = root["ant_enable"].asBool();
        ANT_PHEROMONE_MIN_ = root["ant_pheromone_min"].asInt();
        ANT_PHEROMONE_MAX_ = root["ant_pheromone_max"].asInt();
        ANT_PHEROMONE_DECAY_RATIO_ = root["ant_pheromone_decay_ratio"].asFloat();
        BACKTRACK_ENABLE_ = root["backtrack_enable"].asBool();
        SEARCH_SIZE_MULTIPLIER_ = root["search_size_multiplier"].asInt();
        INSTANT_SEARCH_RATIO_ = root["instant_search_ratio"].asFloat();
        PRIMARY_GUARD_NEXT_NUM_THRESH_ = root["primary_guard_next_num_thresh"].asInt();
        WRITE_PATH_LENGTH_THRESH_ = root["write_path_length_thresh"].asInt();
        WRITE_CACHE_ENABLE_ = root["write_cache_enable"].asBool();
        in.close();

        if (!BACKTRACK_ENABLE_) {
            WRITE_CACHE_ENABLE_ = false;
        }

        switch(MODE_) {
        case 0:
            WRITE_PATH_LENGTH_THRESH_ = 4000;
            break;
        case 1:
            WRITE_PATH_LENGTH_THRESH_ = 4000;
            break;
        case 2:
            WRITE_PATH_LENGTH_THRESH_ = 100;
            break;
        case 3:
            WRITE_PATH_LENGTH_THRESH_ = 10;
            readFreestyle();
            break;
        default:
            WRITE_PATH_LENGTH_THRESH_ = 4000;
        }

        DIGIT_CHAR_ = {"一","二","三","四","五","六",
        "七","八","九","十","百","千","万","亿","壹","贰","叁","肆","伍",
        "陆","柒","捌","玖","拾","佰","仟","萬","廿","卅","卌","圩"};

        return true;
    }///readConfig

    bool readFreestyle() {
        const string file("freestyle.json");
        Json::Reader reader;
        Json::Value root;
        ifstream in(file, ios::binary);
        if (!in.is_open()) {
            cout << "Error opening " << file << "!\n";
            return false;
        }
        if (!reader.parse(in, root)) {
            cout << "Error parse " << file << "!\n";
            return false;
        }

        const string tmp = root["set"].asString();
        for (int i = 0; i < tmp.size(); i += CIC__UTF8_CHINESE_SIZE) {
            FREESTYLE_CHAR_.emplace_back(tmp.substr(i, CIC__UTF8_CHINESE_SIZE));
        }
        in.close();
        return true;
    }///readFreestyle

    void showConfig() {
        cout << "n: " << N_ << "\n";
        cout << "mode: " << MODE_ << "\n";
        cout << "iter_num: " << ITER_NUM_ << "\n";
        cout << "no_update_term_num: " << NO_UPDATE_TERM_NUM_ << "\n";
        cout << "gene_path_length_thresh: " << GENE_PATH_LENGTH_THRESH_ << "\n";
        cout << "gene_path_length_inc_ratio: " << GENE_PATH_LENGTH_INC_RATIO_ << "\n";
        cout << "gene_cache_local_mutation_global_ratio: " << GENE_CACHE_LOCAL_MUTATION_GLOBAL_RATIO_ << "\n";
        cout << "gene_cache_local_mutation_cur_global_ratio: " << GENE_CACHE_LOCAL_MUTATION_CUR_GLOBAL_RATIO_ << "\n";
        cout << "gene_cache_combination_ratio: " << GENE_CACHE_COMBINATION_RATIO_ << "\n";
        cout << "ant_enable: " << ANT_ENABLE_ << "\n";
        cout << "ant_pheromone_min: " << ANT_PHEROMONE_MIN_ << "\n";
        cout << "ant_pheromone_max: " << ANT_PHEROMONE_MAX_ << "\n";
        cout << "ant_pheromone_decay_ratio: " << ANT_PHEROMONE_DECAY_RATIO_ << "\n";
        cout << "backtrack_enable: " << BACKTRACK_ENABLE_ << "\n";
        cout << "search_size_multiplier: " << SEARCH_SIZE_MULTIPLIER_ << "\n";
        cout << "instant_search_ratio: " << INSTANT_SEARCH_RATIO_ << "\n";
        cout << "primary_guard_next_num_thresh: " << PRIMARY_GUARD_NEXT_NUM_THRESH_ << "\n";
        cout << "write_path_length_thresh: " << WRITE_PATH_LENGTH_THRESH_ << "\n";
        cout << "write_cache_enable: " << WRITE_CACHE_ENABLE_ << "\n";
    }
};///class CIC

int main() {
    ios::sync_with_stdio(false);
    CIC cic;
    cic.run();
    return 0;
}
