#include<iostream>
#include<string>
#include<time.h>
#include<list>
#include<vector>
#include<cstring>
#include<cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include "args.hxx"
#include"Util.h"
#include"preProcess.h"
#include"MVQBP.h" 

#define FILELEN 1024

int curBest;
MVQBPack debug;

void MVQB_FORCE(MVQBPack cur, vector<vector<int> >&E) {
    if (curBest >= cur.validSize()) return ;
    if (cur.SL.size() + cur.CL.size() < cur.thetaL || cur.SR.size() + cur.CR.size() < cur.thetaR) return ;
    if (cur.JudgeBiclique()) {
        curBest = cur.validSize();
        debug = cur;
        return ;
    }

    int UBL, UBR, LBL, LBR, minSL, minSR;
    cur.CalcLimit(UBL, UBR, LBL, LBR, minSL, minSR);
    LBL = cur.SL.size();
    LBR = cur.SR.size();
    UBL = cur.SL.size() + cur.CL.size();
    UBR = cur.SR.size() + cur.CR.size();
    if (minSL < (int)ceil(cur.alpha * LBR) || minSR < (int)ceil(cur.beta * LBL)) return;

    cur = cur.Prune_Force(LBL, LBR, E);
    if (curBest >= cur.validSize()) return ; 
    if (cur.SL.size() + cur.CL.size() < cur.thetaL || cur.SR.size() + cur.CR.size() < cur.thetaR) return ; 
    if (cur.JudgeBiclique()) {
        curBest = cur.validSize();
        debug = cur;
        return ;
    }

    cur.CalcLimit(UBL, UBR, LBL, LBR, minSL, minSR);
    LBL = cur.SL.size();
    LBR = cur.SR.size();
    UBL = cur.SL.size() + cur.CL.size();
    UBR = cur.SR.size() + cur.CR.size();
    if (minSL < (int)ceil(cur.alpha * LBR) || minSR < (int)ceil(cur.beta * LBL)) return;

    if (rand() % 2 && !cur.CL.empty()) {
        int wL = cur.CL.back();
        MVQBPack nex = cur.Branch2Add(wL, 1, E);
        MVQB_FORCE(nex, E);
        nex = cur.Branch2Del(wL, 1, E);
        MVQB_FORCE(nex, E);
    } else {
        if (cur.CR.empty()) return ;
        int wR = cur.CR.back();
        MVQBPack nex = cur.Branch2Add(wR, 0, E);
        MVQB_FORCE(nex, E);
        nex = cur.Branch2Del(wR, 0, E);
        MVQB_FORCE(nex, E);
    }
}

const int MAX_RUNTIME_SECONDS = 30000;

void timerFunction()
{
    std::this_thread::sleep_for(std::chrono::seconds(MAX_RUNTIME_SECONDS));
    std::cout << "Program exiting due to timeout." << std::endl;
    exit(0);
}


int main(int argc, char** argv) {

    // freopen("te.out", "w", stdout);

	char filepath[1024] = ".........";

	double alpha = 0.0, beta = 0.0;

    int k=0;  //禁用

	args::ArgumentParser parser(
        "An algorithm for computing the maximum quasi-biclique\n");

    args::HelpFlag help(parser, "help", "Display this help menu",
                        {'h', "help"});
    args::Group required(parser, "", args::Group::Validators::All);

    args::ValueFlag<std::string> benchmark_file(
        parser, "benchmark", "Path to benchmark", {'f', "file"},
        "");

    args::ValueFlag<int> Threshold_l(parser, "Lower Bound", "The lower bound of the size of quasi-biclique", {'u', "u"}, 1);

    args::ValueFlag<int> Threshold_r(parser, "Lower Bound", "The lower bound of the size of quasi-biclique", {'v', "v"}, 1);

    args::ValueFlag<double> Alpha(parser, "para alpha", "The parameter alpha", {'a', "alpha"}, 1);
    
    args::ValueFlag<double> Beta(parser, "para beta", "The parameter beta", {'b', "beta"}, 1);

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help) {
        std::cout << parser;
        return 0;
    } catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 0;
    } catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 0;
    }

	strncpy(filepath, args::get(benchmark_file).c_str(), FILELEN);
    ofstream file("./enum.txt", ios::app);
    streambuf *coutbuf = cout.rdbuf(); // 保存 cout 的缓冲区指针
    cout.rdbuf(file.rdbuf()); // 将 cout 的缓冲区指针指向文件流的缓冲区

	alpha = args::get(Alpha);
    beta = args::get(Beta);
    int theta_l = args::get(Threshold_l);
    int theta_r = args::get(Threshold_r);
    if(alpha<=0.5 || beta<=0.5){
        cout<<"alpha and beta should be larger than 0.5"<<endl;
        exit(-1);
    }


	Util util;
	int bi=0;
    int *degree=NULL;
    int **Graph=NULL;
    int graph_size=util.ReadGraph(filepath,Graph,degree,bi);
    std::thread timerThread(timerFunction);
    time_t s1 = clock();
    CorePack corepack(Graph, degree, graph_size,bi,ceil(theta_r*alpha),ceil(theta_l*beta));
    CorePack cur = corepack.FindBiCore(corepack.lowL, corepack.lowR);
    time_t s3 = clock();
    curBest = 0;
    MVQBPack st(cur.E, alpha, beta, cur.bipartite, cur.graphSize, theta_l, theta_r);
    for (int i = 0; i < 5; ++i) {
        random_shuffle(st.CL.begin(), st.CL.end());
        random_shuffle(st.CR.begin(), st.CR.end());
    }
    // printf("%d\n", st.validSize());
    MVQB_FORCE(st, cur.E);
    time_t s2 = clock();
    cout<<"---------------"<<filepath<<" a,b,lb_L,lb_R,r: "<<alpha<<" "<<beta<<" "<<theta_l<<" "<<theta_r<<" "<<"--------------"<<endl 
    << debug.validSize() << endl
    <<"Running Time: "<<((double)(s2-s1)/CLOCKS_PER_SEC)<<" sec"<<endl;

    cout.rdbuf(coutbuf);

    // 关闭文件流
    file.close();
    exit(0);
    timerThread.join();
	return 0;
}