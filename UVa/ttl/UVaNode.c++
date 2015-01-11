// --------------------------
// cs371p-ttl/Node.h
// Copyright (C) 2014
// Kevin W. Kenyon
// -------------------------

// --------
// defines
// --------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif


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

void node_solve(std::istream& r, std::ostream& w) {
    int c = 1; //The case count
    results_t res; //A results struct
    results_t *rp = &res; //pointer to the struct
    rp->c = c; //Set the current test case
    while(true) {
        Graph g = node_read(r);
        if (g.is_empty())
            return;
        std::vector<std::pair<int, int> > q = read_queries(r);

        for (int i = 0; i < q.size(); ++i)
        {
            rp->s = q[i].first;
            rp->TTL = q[i].second;
            node_eval(g, res);
            node_print(res, w);

            ++(rp->c);
        }
    }
}

Graph node_read(std::istream& r) {
    Graph g;
    int NC;
    r >> NC;
    //std::cout << NC << std::endl;
    for (int i = 0; i < NC; i++) {
        int A; int B;
        r >> A;
        r >> B;
        g.add_node(A);
        //std::cout << A << " " << B << "   " << std::endl;
        std::pair<int, int> edge(A,B);
        g.add_dir_edge(edge);
    }
    return g;
}

std::vector<std::pair<int, int> > read_queries(std::istream& r) {
    std::vector<std::pair<int, int> > v;
    int s, TTL;

    while (true) {
        r >> s;
        r >> TTL;
        if (s == 0 && TTL == 0)
           return v;
        std::pair<int, int> t(s, TTL);
        //std::cout << s << "  " << TTL << std::endl;
        v.push_back(t);
    }

    return v;
}

void node_eval(Graph& g, results_t& r) {
    results_t* const rp = &r;
    rp->not_reachable = BFS(g,r);
}

void node_print(results_t& res, std::ostream& w) {
    results_t* rp = &res;
    w << "Case " << rp->c << ": " << rp->not_reachable << " nodes not reachable from node " << rp->s << " with TTL = " << rp->TTL << "." << std::endl;
}

int BFS(Graph& g, results_t& r) {
    results_t* const  rp = &r;
    std::map<int, Node> map = g.get_nodes();

    //Get the id of the start node
    int s = rp->s;

    //Get the raw ttl
    int ttl = rp->TTL;

    //Query the graph for data on start node
    //Set the ttl as the beginning ttl
    map[s].set_ttl(ttl);
    map[s].tagged = true;
    --ttl; //Decrement the TTL for values beyond the start node

    //Display the graph
    //g.to_string();

    //Define data structs needed for BFS
    std::set<int> explored;
    std::queue<Node> frontier;

    //Get the first set of nodes leaving from the start s
    //Pass along the ttl
    std::vector<Node> c = g.get_children(s);

    //add the new children to the queue for future exploration
    //adds the proper value to node info
    for (int i = 0; i < c.size(); i++) {
        int id = c[i].get_id();
        Node n = map[id];
        n.set_ttl(ttl);
        int tmp_ttl = ttl+1;
        map[id] = n;
        map[id].tagged = true;
        frontier.push(c[i]);
    }

    //Add s to the list of locations we have explored
    explored.insert(s);

    while (!frontier.empty()) {
        int NODE = frontier.front().get_id();
        //What's my ttl?
        int tmp_ttl = map[NODE].get_ttl();
        //Get my id to see if we've been there
        //But if we have been there, but now find a shorter-path (ttl > curr_ttl)
        if ((explored.count(NODE) == 0)) { //Not in the explored set
            //std::cout << "At Node " << NODE << " with ttl " << tmp_ttl << std::endl;
            c = g.get_children(NODE);
            --tmp_ttl;//Decrement since we are going one step further from this value
            for (int i = 0; i < c.size(); i++) {
                int id = c[i].get_id();
                int curr_ttl = map[id].get_ttl();
                //std::cout << "Current Node " <<  NODE << " with c " << explored.count(id) << id <<": " << curr_ttl <<  " vs. new ttl: " << tmp_ttl << std::endl;
                if( tmp_ttl > curr_ttl && map[id].tagged) {
                    map[id].set_ttl(tmp_ttl);
                } else if (!map[id].tagged) {
                    map[id].set_ttl(tmp_ttl);
                    map[id].tagged = true;
                }

                frontier.push(c[i]);
            }
            explored.insert(NODE);
        }
        frontier.pop();
    }

    int nr = 0;

    //std::cout << map[30].get_ttl() << std::endl;

    for(std::map<int, Node>::const_iterator it = map.begin();
        it != map.end(); ++it) {
        Node n = it->second;

        //std::cout << it-> first << ": " << n.get_ttl() << std::endl;
        if(n.get_ttl()<0)
            ++nr;
    }

    return nr;
}

// --------
// main
// --------

int main()
{
    using namespace std;
    node_solve(cin, cout);
    return 0;
}
