/*
Copyright (C) 2019 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*/

#include <iostream>
#include <tbb/flow_graph.h>
#include <tbb/tick_count.h>
#include <tbb/compat/thread>


class AsyncActivity {
public:
  ~AsyncActivity() {
    asyncThread.join();
  }

  using node_t = tbb::flow::async_node<int, int>;
  using gateway_t = node_t::gateway_type;
  void run(int input, gateway_t* gateway){
    gateway->reserve_wait();
//w.r.t fig_18_03 this version does not uses a lambda for the thread
//Note that here gateway is a pointer to gateway_t
    asyncThread = std::thread{&AsyncActivity::asynctask,
                              this, input, gateway};
  }
private:
  void asynctask(int input, gateway_t* gateway) {
    std::cout << "World! Input: " << input << '\n';
    int output=++input;
    gateway->try_put(output);
    gateway->release_wait();
  }
  std::thread asyncThread;
};

void async_world() {
  tbb::flow::graph g;
  bool n = false;

  //Source node:
  tbb::flow::source_node<int> in_node{g,
    [&](int& a) {
      if (n) return false;
      std::cout << "Async ";
      a = 10;
      n = true;
      return true;
    },
    false
  };

  //Async node:
  AsyncActivity asyncAct;
  using activity_node_t = tbb::flow::async_node<int, int>;
  using gateway_t = activity_node_t::gateway_type;
  activity_node_t a_node{g, tbb::flow::unlimited,
    [&asyncAct](int const& input, gateway_t& gateway) {
      asyncAct.run(input, &gateway);
    }
  };

  //Output node:
  tbb::flow::function_node<int> out_node{g, tbb::flow::unlimited,
    [](int const& a_num){
      std::cout << "Bye! Received: "<< a_num<< '\n';
    }
  };

  //Edges:
  make_edge(in_node, a_node);
  make_edge(a_node, out_node);

  //Run!
  in_node.activate();
  g.wait_for_all();
}

int main() {
  tbb::tick_count mainStartTime = tbb::tick_count::now();
  async_world();
  auto time = (tbb::tick_count::now() - mainStartTime).seconds();
  std::cout << "Execution time = " << time << " seconds."<< '\n';
  return 0;
}
