


#include <bits/stdc++.h>

struct State {
    int value;
};
using Operation = std::function<bool(State&)>; //bool f(State& s);
Operation Add(int x) {
    return [x](State& s) {
        s.value += x;
        return true;
    };
}
Operation Sub(int x) {
    return [x](State& s) {
        s.value -= x;return true;
    };
}
bool ApplyAll(State& s, const std::vector<Operation>& ops) {
    int snapshot = s.value;
    for (const auto& op : ops) {
        if(!op(s)) {
            s.value = snapshot;
            return false;
        }
    }
    return true;
}
