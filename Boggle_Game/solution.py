class TrieNode:
    def __init__(self):
        self.is_end = False
        self.children = {}
        
class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word):
        cur_node = self.root
        for c in word:
            next_node = cur_node.children.get(c, None)
            if next_node is None:
                next_node = TrieNode()
                cur_node.children[c] = next_node
            cur_node = next_node
        cur_node.is_end = True
    
    def iterate(self, node, char):
        return node.children.get(char, None)
    
class Solution:
    """
    @param: board: a list of lists of character
    @param: words: a list of string
    @return: an integer
    """
    def is_valid(self, board, row, col):
        return row >= 0 and row < len(board) and col >= 0 and col < len(board[row])
        
    def dfs(self, board, vis, trie, row, col, cur_node, num_word, threshold):
        next_node = trie.iterate(cur_node, board[row][col])
        if next_node is None:
            return False
        vis[row][col] = True
        if next_node.is_end:
            if num_word + 1 >= threshold:
                return True
            for i in range(len(board)):
                for j in range(len(board[i])):
                    if vis[i][j] == False:
                        if(self.dfs(board, vis, trie, i, j, trie.root, num_word + 1, threshold)):
                            return True
            return False
        
        for dx, dy in zip([-1, 0, 1, 0], [0, 1, 0, -1]):
            next_row = row + dx
            next_col = col + dy
            if (self.is_valid(board, next_row, next_col) and vis[next_row][next_col] == False):
                if(self.dfs(board, vis, trie, next_row, next_col, next_node, num_word, threshold)):
                    return True
        
        vis[row][col] = False
        return False
    
    def boggleGame(self, board, words):
        # write your code here
        trie = Trie()
        for word in words:
            trie.insert(word)
        num_board = sum([len(row) for row in board])
        for threshold in range(num_board):
            vis = [None] * len(board)
            flag = False
            for i in range(len(board)):
                for j in range(len(board[i])):
                    for k in range(len(board)):
                        vis[k] = [False] * len(board[k])
                    flag = flag or self.dfs(board, vis, trie, i, j, trie.root, 0, threshold)
                    if flag:
                        break
            if flag == False:
                return max(0, threshold - 1)
        return num_board
        
if __name__ == '__main__':
    solution = Solution()

    board = ["lintcodeisnice","lintcodeisgood","uilwowwwwowwqw","poiuywqaazxcvw"]
    words = {"a","lint","code","ccode","poiy","ppty","cvbwwd","ngoo","uilow"}

    # board = ["abcdefg","huyuyww","ghihjui","wuiiuww"]
    # words = {"efg","defi","gh","iuw","ww","iw","ghih","dasf","aaa"}

    # board = ["a","f","gi"]
    # words = {"abc","defi","gh"}
    print(solution.boggleGame(board, words))