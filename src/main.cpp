#include <bits/stdc++.h>
using namespace std;

unordered_map<string,string> store;
const string DBFILE = "data.db";

void load_db() {
    ifstream in(DBFILE);
    if (!in) return;
    string line;
    while (getline(in, line)) {
        size_t pos = line.find('\t');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);
        store[key] = val;
    }
    in.close();
}

void persist_db() {
    ofstream out(DBFILE);
    for (auto &p : store) {
        out << p.first << '\t' << p.second << '\n';
    }
    out.close();
}

int main() {
    load_db();
    cout << "MiniStoreDB REPL — Commands: SET key value | GET key | DELETE key | EXIT\n";
    string line;
    while (true) {
        cout << "> " << std::flush;
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        stringstream ss(line);
        string cmd; ss >> cmd;
        if (cmd == "SET") {
            string key; ss >> key;
            string rest;
            getline(ss, rest);
            if (!rest.empty() && rest[0] == ' ') rest.erase(0,1);
            store[key] = rest;
            persist_db();
            cout << "[OK] SET " << key << "\n";
        } else if (cmd == "GET") {
            string key; ss >> key;
            auto it = store.find(key);
            if (it == store.end()) cout << "[NOT FOUND]\n";
            else cout << it->second << "\n";
        } else if (cmd == "DELETE") {
            string key; ss >> key;
            if (store.erase(key)) { persist_db(); cout << "[OK] DELETED\n"; }
            else cout << "[NOT FOUND]\n";
        } else if (cmd == "EXIT") {
            cout << "Bye\n";
            break;
        } else {
            cout << "Unknown command. Use: SET, GET, DELETE, EXIT\n";
        }
    }
    return 0;
}
