#include <gatb/gatb_core.hpp>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
  const char *seq = "AAAAACTACATTACCCGTTTGCGAGACAGGTA";

  size_t kmerSize = strlen(seq) - 1;

  // create several graphs multithreadely, each thread creating one graph
  #pragma omp parallel for num_threads(8)
  for (int i = 0; i < 8; i++) {
    std::string graph_name = std::string("graph_") + std::to_string(i);
    std::cout << "Building graph " << graph_name << "..." << std::endl;
    std::string fasta_file = graph_name + ".fa";
    Graph graph = Graph::create(
        new BankStrings(seq, seq, seq, seq, 0),
        "-kmer-size %d  -abundance-min 1 -verbose 0 -out %s -nb-cores 1",
        kmerSize, graph_name.c_str());
  }
}
