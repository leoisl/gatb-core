/*****************************************************************************
 *   GATB : Genome Assembly Tool Box                                         *
 *   Copyright (c) 2013                                                      *
 *                                                                           *
 *   GATB is free software; you can redistribute it and/or modify it under   *
 *   the CECILL version 2 License, that is compatible with the GNU General   *
 *   Public License                                                          *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 *   CECILL version 2 License for more details.                              *
 *****************************************************************************/

/**\page snippets_page How to use the library ?
 *
 * \subpage compilation         \n
 * \subpage snippets_graph      \n
 * \subpage snippets_bank       \n
 * \subpage snippets_kmer       \n
 * \subpage snippets_iterators  \n
 *
 *************************************************************************************
 *************************************************************************************
 * \page compilation Compilation instructions
 ************************************************************************************
 *
 * \section compilation_library Compiling the library (and other artifacts)
 *
 * The gatb::core library is generated by the cmake tool.
 *
 * In the following, we will call GATB the main directory of the gatb core project (ie.
 * the root directory of the source archive).
 *
 * You have then to do the following:
 *
 * \code
 * cd GATB; mkdir build ; cd build ; cmake .. ; make
 * \endcode
 *
 * Several artifacts are generated:
 *
 *  - the gatb core library is available in the generated <tt>build/lib</tt> directory
 *  - the HTML documentation is available from <tt>build/doc/html/index.html</tt>
 *  - the unit tests binary is available in <tt>build/test/GatbToolsTest</tt>
 *
 * About the unit tests binary, you can launch it with
 * \code
 * bin/gatb-core-cppunit
 * \endcode
 * You can use the exit status code of the command to know the success status (0 for success)
 *
 ************************************************************************************
 * \section compilation_snippets Compiling the snippets
 *
 * A directory named 'examples' holds some snippets that show how to use services provided by the library.
 *
 * In order to compile them, you will first need to compile the library.
 *
 * Then, you can use the following command for compiling one snippet:
 * \code
 * g++ examples/debruijn/debruijn15.cpp -Iinclude -Llib -lgatbcore -ldl -lpthread -lz -lhdf5 -std=c++0x -O3
 * \endcode
 * \n
 *
 ************************************************************************************
 ************************************************************************************
 * \page snippets_iterators Iterators snippets
 ************************************************************************************
 *************************************************************************************
 *
 * \section snippets_iterators_snippet1 Iterate a list
 *
 * This snippet shows how to iterate a STL list with our iterator design.
 *
 *\snippet iterators1.cpp  snippet1
 *
 ************************************************************************************
 * \section snippets_iterators_snippet2 Iterate the Cartesian product of two lists
 *
 * This snippet shows how to iterate the Cartesian product of two lists:
 *
 *  1) Declare two iterators \n
 *  2) Declare one Cartesian iterator configured with the two iterators \n
 *  3) Iterate the Cartesian iterator. \n
 *
 * The current item of the iteration is a pair, so one should retrieve the couple of
 * values with methods 'first' and 'second'.
 *
 *\snippet iterators2.cpp  snippet1
 *
 ************************************************************************************
 * \section snippets_iterators_snippet3 Truncating an iteration
 *
 * This snippet shows how to truncate the iteration of some iterator.
 *
 *\snippet iterators3.cpp  snippet1
 *
 *
 ************************************************************************************
 * \section snippets_iterators_snippet4 Iterate a list with progress feedback
 *
 * This snippet shows how to iterate a STL list and being notified as a listener about
 * its progression.
 *
 * The idea is to use a SubjectIterator instance that refers the actual iterator we want
 * to iterate.
 *
 * Then, it is possible to subscribe some callback function (here as a functor) to the
 * SubjectIterator instance.
 *
 * The listener will then receive at regular interval the number of currently iterated
 * items.
 *
 *\snippet iterators4.cpp  snippet1
 *
 ************************************************************************************
 * \section snippets_iterators_snippet5 Iterate a list and filter out some items
 *
 * This snippet shows how to iterate a STL list while filtering out some items that
 * don't check some condition.
 *
 *\snippet iterators5.cpp  snippet1
 *
 *
 ************************************************************************************
 ************************************************************************************
 * \page snippets_bank Bank snippets
 ************************************************************************************
 ************************************************************************************
 *
 * \section snippets_bank_snippet1 Parsing a single FASTA bank without checks
 *
 * This snippet shows how to read one FASTA bank in a simple way. No check is done about
 * the correctness of the FASTA bank file path.
 *
 * Some information of each iterated sequence are diplayed as output.
 *
 *\snippet bank1.cpp  snippet1
 *
 ************************************************************************************
 * \section snippets_bank_snippet2 Parsing several FASTA banks
 *
 * This snippet shows how to read one ore more FASTA banks in a simple way.
 * A check is done about the correctness of the FASTA bank file path.
 *
 * Some information of each iterated sequence are diplayed as output.
 *
 *\snippet bank2.cpp  snippet1
 *
 *************************************************************************************
 * \section snippets_bank_snippet3 Parsing a FASTA bank in a different way
 *
 * This snippet shows how to read one or more FASTA banks in a "push" model;
 * it means that the sequence iterator calls some function for each sequence.
 *
 * This is another way to iterate items and opposite to the "pull" model where the
 * iterator is called to provide the current item, instead of calling some function to
 * do as we do in this sample.
 *
 *\snippet bank3.cpp  snippet1
 *
 **************************************************************************************
 * \section snippets_bank_snippet4 Parsing a FASTA bank and getting progress information
 *
 * This snippet shows how to create an iterator on something (here sequences from a FASTA
 * file) and encapsulate it with another iterator that adds the possibility to notify some
 * listener every 10 iterated sequences (used here for showing some progression during the
 * iteration).
 *
 * Note: the "notifying" iterator is generic and could be reused to send progress notification
 * with any kind of iterator, not only on sequences.
 *
 *\snippet bank4.cpp  snippet1
 *
 **************************************************************************************
 * \section snippets_bank_snippet5 Parsing a FASTA bank and getting percentage progress information
 *
 * This snippet shows how to read one or more FASTA banks and get a percentage progress
 * information during the iteration.
 *
 * In order to get a percentage, we need to know the number of sequences in the bank to be
 * parsed. We get an estimation of this number with the estimateNbSequences() method
 * and configure our progression functor accordingly.
 *
 *\snippet bank5.cpp  snippet1
 *
 * \n
 *
 **************************************************************************************
 * \section snippets_bank_snippet6 Output a FASTA file with data line of given size
 *
 * This snippet provides a small utility for cutting lines of data with a given size.
 *
 *\snippet bank6.cpp  snippet1
 *
 * \n
 *
 **************************************************************************************
 * \section snippets_bank_snippet7 Filter sequences with a given data size
 *
 * This snippet shows how to parse a bank with a functor used to filter out some items.
 *
 *\snippet bank7.cpp  snippet1
 *
 * \n
 *
 **************************************************************************************
 * \section snippets_bank_snippet8 Conversion of a FASTA bank to a binary format
 *
 * This snippet shows how to parse a nucleic bank and convert it to a binary format.
 *
 *\snippet bank8.cpp  snippet1
 *
 * \n
 *
 ************************************************************************************
 ************************************************************************************
 * \page snippets_kmer Kmer snippets
 ************************************************************************************
 *************************************************************************************
 *
 * \section snippets_kmer_snippet1 Using a kmer model
 *
 * This snippet shows how to create kmer models.
 *
 * We use different integer types for holding kmer values. For instance, we can use:
 *  - native integers (like u_int64_t)
 *  - integers supporting huge values (ttmath::Uint for instance)
 *
 *\snippet kmer1.cpp  snippet1
 * \n
 *
 ************************************************************************************
 * \section snippets_kmer_snippet2 Computing kmers with a model
 *
 * This snippet shows how to get kmers from a model.
 *
 *\snippet kmer2.cpp  snippet1
 * \n
 *
 ************************************************************************************
 * \section snippets_kmer_snippet3 Iterating kmers from a sequence
 *
 * This snippet shows how to iterate the kmers from a sequence, for a given model.
 *
 *\snippet kmer3.cpp  snippet1
 * \n
 *
 ************************************************************************************
 * \section snippets_kmer_snippet4 Iterating kmers from one or several banks
 *
 * This snippet shows how to iterate the kmers from banks. In particular, we use two
 * iterators and two loops:
 *      - outer loop on sequences of the bank
 *      - inner loop on kmer on the current sequence from the outer loop
 *
 *\snippet kmer4.cpp  snippet1
 * \n
 *
 ************************************************************************************
 * \section snippets_kmer_snippet5 Iterating kmers from one or several banks with progress information
 *
 * This snippet shows how to iterate the kmers from banks.
 *
 * It shows how to use a single compound iterator that is equivalent to two iterators (one inner, one outer).
 *
 * Although this is a kmer iterator, we add a progress listener on the outer sequences iteration.
 *
 * This snippet is rather complex but shows how we can develop few material (basically bank and kmer iterators)
 * and get in return several advantages through the iterator helpers.
 *
 *\snippet kmer5.cpp  snippet1
 * \n
 *
 ************************************************************************************
 * \section snippets_kmer_snippet6 Comparing kmers from a FASTA bank and a binary bank
 *
 * This snippet shows that kmers from a FASTA bank or a binary bank are the same.
 *
 *\snippet kmer6.cpp  snippet1
 * \n
 *
 ************************************************************************************
 *************************************************************************************
 * \page snippets_system Operating System snippets
 *************************************************************************************
 ************************************************************************************
 *
 * \section snippets_system_snippet1 to be done
 *
 * \n
 *
 ************************************************************************************
 *************************************************************************************
 * \page snippets_graph De Bruijn graph snippets
 *************************************************************************************
 *************************************************************************************
 *
 *\tableofcontents
 *
 * We propose here a few snippets related to De Bruijn graphs.
 *
 ************************************************************************************
 * \section snippets_dbg_1  Build / Load De Bruijn graphs
 ************************************************************************************
 * \subsection snippets_kmer_dbg_1  Building a De Bruijn graph from command line options
 *
 * This snippet shows how to create a Graph object thanks to command line options with at
 * least a mandatory FASTA file URI.
 *
 * The first thing to do is to get a parser that analyzes the command line options
 * from (argc,argv). Such a parser can be retrieved with a static method from Graph class.
 *
 * Then, the parsed options can be provided to the Graph::create method and then we get
 * a Graph object on which we can do anything we want.
 *
 * The only mandatory option is '-in fastafile'. All other options have default values if not
 * set through command line.
 *
 * In this snippet, we dump information about the Graph object building with Graph::getInfo method.
 *
 * \remark This snippet essentially does the same job as the \b dbgh5 tool provided by the
 * gatb-core project: it takes a set of reads (as a FASTA file) and generates the corresponding
 * De Bruijn graph as a HDF5 file.
 *
 *\snippet debruijn1.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_2  Building a De Bruijn graph from a command-line-like string
 *
 * Like the previous snippet, we create a Graph object with command line options, but
 * here the options are directly provided as a string.
 *
 * \snippet debruijn2.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_3  Building a De Bruijn graph from a bank object
 *
 * Here, we create a Graph object by providing a bank object, more precisely a IBank
 * object.
 *
 * It is therefore possible to provide a Bank instance (ie a FASTA bank), or
 * another kind of bank that implements the IBank interface.
 *
 * Note in the example that we can provide additional options after the bank object.
 *
 * \snippet debruijn3.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_4  Building a De Bruijn graph from a fake bank object
 *
 * Like the previous snippet, we create a Graph object by providing a bank object, but
 * here this is a 'fake' bank built "on the fly".
 *
 * Such banks are often useful for testing purposes.
 *
 * In such a case, the output file for the graph will be named "noname", unless a specific
 * name is set through the command line option "-out mygraph".
 *
 * \snippet debruijn4.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_5  Load a De Bruijn graph from a graph file
 *
 * Once we have built a graph, it is saved as a file (likely a HDF5 file).
 *
 * This snippet shows how to load such a file to get a Graph object.
 *
 * \snippet debruijn5.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 ************************************************************************************
 * \section snippets_dbg_2  Iterating nodes
 *************************************************************************************
 *
 * \subsection snippets_kmer_dbg_6  Iterate the nodes of a De Bruijn graph
 *
 * This snippet shows how to iterate all the nodes of a graph (the graph is loaded
 * from a graph file).
 *
 * The idea is to get an iterator from the graph and use it to get each node of the graph.
 *
 * Here, the nodes are retrieved regardless of any edges between them.
 *
 * \snippet debruijn6.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_7  Iterate the nodes of a De Bruijn graph in a multithread way
 *
 * As the previous example, this snippet shows how to iterate all the nodes of a graph.
 *
 * The difference here is that the iteration is parallelized, using all possible available
 * cores, which should speed up the iteration.
 *
 * WARNING ! don't forget this is parallel execution, so you have be careful if you want to
 * modify the same object in different thread execution contexts.
 *
 * Note: lambda expressions are used here to have code conciseness (which suppose to use
 * an up-to-date compiler). You can have some information at
 * http://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11
 *
 * \snippet debruijn7.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 ************************************************************************************
 * \section snippets_dbg_3  Neighborhoods
 *************************************************************************************
 *
 * \subsection snippets_kmer_dbg_9  Working with neighborhoods of nodes in the De Bruijn graph
 *
 * This snippet shows how to use some methods related to neighbors in a graph.
 *
 * We use a fake bank with one sequence of size 5 and use a kmer size of 4, so we will have 2 possible
 * nodes in the graph.
 *
 * We iterate these two nodes, and for one of them, we ask for its neighbors with the Graph::successors method.
 * We can then check that the retrieved neighbor is the correct one by analyzing the node string representations.
 *
 * In this example, we use the successors method, but note it is possible to get the incoming neighbors with the
 * Graph::predecessors method. By the way, it is possible to know the in and out degree of a given node with the two
 * corresponding methods Graph::indegree and Graph::outdegree
 *
 * \snippet debruijn9.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_10  Working with neighborhoods of nodes in the De Bruijn graph (continued)
 *
 * This snippet shows how to use some methods related to neighbors in a graph.
 *
 * We do the same work as the previous example. The only difference is that we retrieve the neighbors as
 * Edge objects rather than Node objects, so we will have the full information about each transition between
 * the source node and the retrieved neighbors (including the transition nucleotide for instance).
 *
 * In particular, we use some of the Edge attributes (Edge::to, Edge::nt)
 *
 * \snippet debruijn10.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_11  Working with a specific neighbor for a specific node
 *
 * This snippet shows how to get a specific neighbor for a specific node.
 *
 * Sometimes, it is interesting to ask the graph for only one neighbor for a given node.
 * It may happen when one has already got neighbors information through a Graph::neighbors
 * call and memorized only the transition nucleotides for valid neighbors.
 *
 * The Graph::neighbor fulfills this need. This method has two forms, with or without check
 * to graph membership, according to performance considerations.
 *
 * \snippet debruijn11.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 ************************************************************************************
 * \section snippets_dbg_4  Branching nodes
 ************************************************************************************
 *
 * In the De Bruijn graph, we can define two types of nodes:
 *  - a node N is 'simple'    <=> indegree(N)==1 && outdegree(N)
 *  - a node N is 'branching' <=> N is not simple
 *
 * Branching nodes set is an important subset in the whole nodes set of the De Bruijn graph, so it is of most
 * interest to have some graph methods that work on such nodes. In particular, we can:
 *  - iterate all the branching nodes of the De Bruijn graph
 *  - get the branching neighbors of some node
 *
 * \remarks - With this definition, a branching node may have 0 outcoming neighbors or 0 incoming neighbors.
 *
 * \remarks - Since we are considering assembly matters, we should have few branching nodes compared to the simple
 * nodes.
 *
 * \subsection snippets_kmer_dbg_8  Iterate the branching nodes of a De Bruijn graph
 *
 * This snippet shows how to iterate the branching nodes of a graph (the graph is loaded
 * from a graph file).
 *
 * The idea is to get an iterator from the graph and use it to get each branching node of the graph.
 *
 * \snippet debruijn8.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_16  Working with branching neighbors of a node
 *
 * This snippet shows how to get the branching neighbors of a node. Such neighbors are
 * computed as follow:
 *      - the immediate neighbors of the node are retrieved
 *      - a simple path is done from each neighbor in order to reach the first non simple node
 *
 * Here, we use directly the Graph::successors<BranchingNode> method that encapsulates
 * this behavior.
 *
 * \snippet debruijn16.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_17  Working with branching neighbors of a node (continued)
 *
 * This snippet shows how to get the branching neighbors of a node.
 *
 * It is similar to the previous snippet. The difference here is that we retrieve BranchingEdge
 * objects. A BranchingEdge object is made of:
 *  - the source branching node
 *  - the target branching node
 *  - the direction of the neighbors (in/out coming)
 *  - the nucleotide of the transition between the initial branching node and the first neighbor
 *    on the simple path between the two branching nodes.
 *  - the number of transitions that link the two branching nodes.
 *
 * \snippet debruijn17.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 * ************************************************************************************
 * \section snippets_dbg_5  Simple path
 ************************************************************************************
 *
 * \subsection snippets_kmer_dbg_14  Iterating simple path from a node
 *
 * As we saw previously, a simple node is defined as having indegree==1 and outdegree==1.
 * It is often useful to iterate successive simple nodes in order to build some path in the De Bruijn graph.
 *
 * This snippet shows how to iterate such a simple path. Here, the iterated items are the
 * successive nodes of the path.
 *
 * \snippet debruijn14.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 *************************************************************************************
 * \subsection snippets_kmer_dbg_15  Iterating simple path from a node (continued)
 *
 * Like the previous example, this snippet shows how to iterate a simple path.
 * Here, the iterated items are the successive edges of the path. If we note E an edge
 * in this path, we will have:
 *  - outdegree(E.from)==1  &&  indegree(E.to)==1
 *
 * \snippet debruijn15.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 ************************************************************************************
 * \section snippets_dbg_6  Miscellanous
 *************************************************************************************
 * \subsection snippets_kmer_dbg_12  Playing with node strands
 *
 * A Node object is fully defined by a kmer value and a strand that disambiguates how to
 * interpret the kmer.
 *
 * It is often required to change the reading strand of a node. This can be done with the
 * Graph::reverse method.
 *
 * \snippet debruijn12.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *************************************************************************************
 * \subsection snippets_kmer_dbg_13  Playing with fake nodes
 *
 * Sometimes, it is useful to build "fake" nodes from a simple sequence, without having
 * a graph holding true data.
 *
 * It is possible to get an empty Graph object (its kmer size must be nevertheless specified),
 * and then use the Graph::buildNode to get a node based on a Data object.
 *
 * \snippet debruijn13.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 * \n
 *
 ************************************************************************************
 * \section snippets_dbg_7  To go further...
 *************************************************************************************
 *
 * \subsection snippets_kmer_dbg_18  Getting branching nodes statistics in a parallel way
 *
 * This example is a little bit harder than the previous ones. Its purpose is to show how
 * to use the graph API for extracting some information. In particular, we will try to
 * take care about time execution by using available cores.
 *
 * The idea here is to compute information about branching nodes and their in and out degrees.
 * For instance, we want to know how many branching nodes have indegree==2 and outdegree=3.
 * We compute therefore the number of branching nodes having indegree==X and outdegree==Y,
 * with X and Y in [0..4] and the constraint that we can't have X==Y==1 (otherwise the node
 * wouldn't be a branching one).
 *
 * We can do it easily by using the methods:
 *  - Graph::successors<BranchingNode>
 *  - Graph::predecessors<BranchingNode>
 *
 * Moreover, we want to do it in a parallel way in order to speed up the computation. The idea is
 * to get an iterator over the branching nodes and iterate it through a Dispatcher object; such a
 * dispatcher will create as many threads as wanted and will feed each threads with branching nodes.
 * Note that this scheme can work here because the processing of one branching node is independant of
 * the others.
 *
 * We need also some container for the in/out degrees statistics. A natural choice is to use a map,
 * with the key being a unique identifier for a couple (indegree/outdegree) and the value the number
 * of occurrences for the key. The idea is to use one map per thread and to merge the N maps into a global
 * one after the parallel iteration of the branching nodes. We use here a ThreadObject object
 * that allows to do it in a simple way. This object clones N time the global map and each clone is used in
 * a specific thread. The ThreadObject class allows to hide many cumbersome points for the parallelization.
 *
 * In this example, we also use progress notification feature (with ProgressIterator) in order to have
 * some user feedback during the iteration of the branching nodes.
 *
 * \snippet debruijn18.cpp  snippet1
 * [go back to \ref snippets_graph "top"]
 *
 */
