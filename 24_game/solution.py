import operator
import itertools

class Solution:
    """
    @param nums: 4 cards
    @return: whether they could get the value of 24
    """
    def balance_eval(self, leafs, ops):
        for i in range(8):
            bin = "{0:{fill}3b}".format(i, fill='0')
            try:
                if bin[0] == '0':
                    a = ops[0](leafs[0], leafs[1])
                else:
                    a = ops[0](leafs[1], leafs[0])
                if bin[1] == '0':
                    b = ops[1](leafs[2], leafs[3])
                else:
                    b = ops[1](leafs[3], leafs[2])
                if bin[2] == '0':
                    c = ops[2](a, b)
                else:
                    c = ops[2](b, a)
                if abs(c - 24) < 1e-8:
                    return True
            except:
                pass
        return False
    
    def imbalance_eval(self, leafs, ops):
        for i in range(8):
            bin = "{0:{fill}3b}".format(i, fill='0')
            try:
                if bin[0] == '0':
                    a = ops[0](leafs[0], leafs[1])
                else:
                    a = ops[0](leafs[1], leafs[0])
                if bin[1] == '0':
                    b = ops[1](a, leafs[2])
                else:
                    b = ops[1](leafs[2], a)
                if bin[2] == '0':
                    c = ops[2](b, leafs[3])
                else:
                    c = ops[2](leafs[3], b)
                if abs(c - 24) < 1e-8:
                    return True
            except:
                pass
        return False
    
    def is_valid(self, leafs, ops):
        return self.balance_eval(leafs, ops) or self.imbalance_eval(leafs, ops)
    

    
    def compute24(self, nums):
        # write your code here
        list_ops = [operator.add, operator.sub, operator.mul, operator.truediv]
        all_leafs = set(itertools.permutations(nums, len(nums)))
        all_ops = set(itertools.product(list_ops, list_ops, list_ops))
        for leafs in all_leafs:
            for ops in all_ops:
                if (self.is_valid(leafs, ops)):
                    return True
        return False

if __name__ == '__main__':
    solution = Solution()
    nums = [3, 3, 8, 8]
    print(solution.compute24(nums))
    # leafs = [8, 3, 3, 8]
    # ops = [operator.truediv, operator.sub, operator.truediv]
    # solution.imbalance_eval(leafs, ops)