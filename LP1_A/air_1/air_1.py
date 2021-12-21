import numpy as np
np.random.seed(42)

class Node():
  def __init__(self, state, parent = None, depth = 0):
    self.state = state
    self.parent = parent
    self.depth = depth

  def __eq__(self, other):
    return np.array_equal(self.state, other.state)

class PuzzleSolver():  
  def __init__(self, n = 8):
    self.n = n
    self.side_length = int(np.sqrt(n+1))
    assert self.__check_dims(), "Invalid value of N."
    self.__generate_states()
    # self.initial_state = self.__generate_state()
    # self.final_state = self.__generate_state()
    # final_state = np.array([i+1 if i < n else 0 for i in range(n+1)])
    # self.final_state = np.resize(final_state, (self.side_length,self.side_length))

  def __check_dims(self):
    return self.side_length ** 2 == self.n + 1

  def __generate_state(self):
    state = np.arange(self.n + 1)
    np.random.shuffle(state)
    return np.resize(state, (self.side_length,self.side_length))

  def __generate_states(self):
    state = np.arange(self.n + 1)
    np.random.shuffle(state)
    self.initial_state = np.resize(state, (self.side_length,self.side_length))
    node = Node(self.initial_state)
    for i in range(5):
      node = np.random.choice(self.__generate_moves(node))
      # print(node.state)
    self.final_state = node.state

  def __gscore(self, node):
    return node.depth

  def __hscore(self, node):
    score = 0
    for i in range(self.side_length):
      for j in range(self.side_length):
        if node.state[i][j] != 0 and node.state[i][j] != self.final_state[i][j]:
          score += 1
    return score

  def __fscore(self, node):
    return self.__gscore(node) + self.__hscore(node)

  def __generate_moves(self, node):
    for i in range(self.side_length):
      for j in range(self.side_length):
        if node.state[i][j] == 0: break
      if node.state[i][j] == 0: break
    temp_nodes = [node.state.copy() for _ in range(4)]
    temp_nodes[0][i][j] = temp_nodes[0][i][min(j+1,self.side_length-1)]
    temp_nodes[0][i][min(j+1,self.side_length-1)] = 0
    temp_nodes[1][i][j] = temp_nodes[1][i][max(j-1,0)]
    temp_nodes[1][i][max(j-1,0)] = 0
    temp_nodes[2][i][j] = temp_nodes[2][min(i+1,self.side_length-1)][j]
    temp_nodes[2][min(i+1,self.side_length-1)][j] = 0
    temp_nodes[3][i][j] = temp_nodes[3][max(i-1,0)][j]
    temp_nodes[3][max(i-1,0)][j] = 0
    if node.parent is None:
      nodes = [Node(tn,node,node.depth+1) for tn in temp_nodes if not np.array_equal(tn,node.state)]
    else:
      nodes = [Node(tn,node,node.depth+1) for tn in temp_nodes if not np.array_equal(tn,node.state) and not np.array_equal(tn,node.parent.state)]
    return nodes

  def solve(self):
    root_node = Node(self.initial_state)
    live_nodes = []
    dead_nodes = []
    current_node = root_node
    found_solution = True
    while not np.array_equal(current_node.state, self.final_state):
      best_val = 1e4
      best_node = None
      live_nodes = self.__generate_moves(current_node)
      for node in live_nodes:
        score = self.__fscore(node)
        if score < best_val and node not in dead_nodes:
          best_val = score
          best_node = node
      if best_val == 1e4:
        print("NO SOLUTION.")
        found_solution = False
        break
      dead_nodes.append(current_node)
      current_node = best_node
      # print(best_val)
      # print(current_node.state)
    print("COMPLETE!")
    if found_solution:
      path = [current_node.state.copy()]
      while current_node.parent is not None:
        current_node = current_node.parent
        path.append(current_node.state.copy())
      path.reverse()
      for state in path:
        print(state)

ps = PuzzleSolver()
print(ps.initial_state)
print(ps.final_state)

ps.solve()