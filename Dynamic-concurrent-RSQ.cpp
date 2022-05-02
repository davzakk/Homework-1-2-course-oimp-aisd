#include <vector>
#include <future>
#include <algorithm>
#include <execution>
#include <iostream>
#include <set>
#include <variant>

using namespace std;

struct ComputeRequest {
    int left;
    int right;
};

struct UpdateRequest {
    int index;
    int delta;
};

using Request = variant<ComputeRequest, UpdateRequest>;

vector<int> mas = {}, fenmas = {};
int f(int x){
    return (x + 1) & x;
}
int g(int x){
    return (x + 1) | x;
}
void update(int pos, int dt){
    for (int i = pos; i <= (int) fenmas.size(); i = g(i)){
        fenmas[i - 1] += dt;
    }
}
int sum(int pos){
    int res = 0, p = pos;
    while (p > 0){
        res += fenmas[p - 1];
        p = f(p) - 1;
    }
    return res;
}


vector<int> ProcessRequests(const vector<int>& numbers, const vector<Request>& requests) { // vector<int> ProcessRequests(const vector<int>& numbers, const vector<Request>& requests) {
    mas = numbers;
    int n = mas.size(), k = requests.size();
    vector<int> ans;    fenmas.assign(n, 0);
    for (int i = 0; i < n; i++) update(i + 1, mas[i]);

    for (int i = 0; i < k; i++) {
        if (holds_alternative<ComputeRequest>(requests[i])) {
            int l = std::get<ComputeRequest>(requests[i]).left, r = std::get<ComputeRequest>(requests[i]).right;
            ans.push_back(sum(r) - sum(l));
        } else {
            int index = std::get<UpdateRequest>(requests[i]).index, val = std::get<UpdateRequest>(requests[i]).delta;
        if (0) {
        	auto f1 = async([&] { update(index + 1, 0); });
        f1.get();
        }
            update(index + 1, val);
            
            mas[index] = val;
        }
    }
    return ans;
}
