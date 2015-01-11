
// --------------------------
// cs371p-ttl/Node.h
// Copyright (C) 2014
// Kevin W. Kenyon
// -------------------------

#ifndef Node_h
#define Node_h

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <queue>

struct results_t {
    int TTL; //Time to live
    int not_reachable;//count of not reachable nodes
    int s; //Starting node
    int c; //Case number
};

class Node {
    private:
        int ttl;
        int id;
        int _ttl_fw;
    public:
        bool tagged;
        Node() {}

        Node(int i) {
            ttl = 0;
            _ttl_fw = 0;
            id = i;
            tagged = false;}

        int get_id() {return id;}
        int get_ttl() {return ttl;}
        void set_ttl_from_whence_i_came(int& ttl_fw){
            _ttl_fw = ttl_fw;
        }
        int get_ttl_fw() const {return _ttl_fw;}
        void set_ttl(int t) {ttl=t;}
};

class Graph {
    private:
        std::map<int,std::vector<Node> > graph;
        std::map<int, Node> node_info;
        int size;

    public:

        Graph() {
            size = 0;
        }

        bool is_empty() {
            return (size == 0);
        }

        void add_node(int A) {
            if (!contains(A)) {
                std::vector<Node> childs;
                graph[A] = childs;
                node_info[A] = Node(A);
                ++size;
            }
        }

        void add_dir_edge(std::pair<int, int> edge) {
            int f = edge.first;
            int s = edge.second;

            if(contains(f)) {
                if(!contains(s))
                    add_node(s);
                graph[f].push_back(node_info[s]);
            } else {
                add_node(f);
                if(!contains(s))
                    add_node(s);
                graph[f].push_back(node_info[s]);
            }

            if(contains(s)) {
                if(!contains(f))
                    add_node(f);
                graph[s].push_back(node_info[f]);
            } else {
                add_node(s);
                if(!contains(f))
                    add_node(f);
                graph[s].push_back(node_info[f]);
            }
        }

        bool contains(int A) {
            return (graph.count(A) == 1);
        }

        //Accessors
        std::vector<Node> get_children(int A) { return graph[A]; }

        Node get_node(int A) {return node_info[A];}
        std::map<int, Node>& get_nodes() {return node_info;}


        void to_string() {
            std::vector<Node> v;
            for(std::map<int, std::vector<Node> >::const_iterator it = graph.begin();
                    it != graph.end(); ++it) {
                std::cout <<  it->first << ": ";
                v = it->second;
                for (int i = 0; i < v.size(); i++) {
                    std::cout << v[i].get_id() << " ";
                }
                std::cout << std::endl;
            }
        }

};


void node_solve(std::istream& r, std::ostream& w);

Graph node_read(std::istream& r);

std::vector<std::pair<int, int> > read_queries(std::istream& r);

void node_eval(Graph& g, results_t& r);

void node_print(results_t& r, std::ostream& w);

int BFS(Graph& g, results_t& r);



#endif //Node_h
