// https://www.lintcode.com/problem/kth-largest-element/description

class Solution {
public:
    /**
     * @param n: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    int quickSelect(vector<int> &nums, int start, int end, int n) {
        if (start == end) {
            return nums[start];
        }
        int pivot = nums[(start + end) / 2];
        int i = start, j = end;
        while (i <= j) {
            while (i <= j && nums[i] > pivot) {
                i++;
            }
            while (i <= j && nums[j] < pivot) {
                j--;
            }
            if (i <= j) {
                swap(nums[i], nums[j]);
                i++;
                j--;
            }
        }
        
        if (j - start + 1 >= n) {
            return quickSelect(nums, start, j, n);
        }
        if (i - start + 1 <= n) {
            return quickSelect(nums, i, end, n - (i - start));
        }
        return nums[j + 1];
    }
    int kthLargestElement(int n, vector<int> &nums) {
        // write your code here
        if (nums.size() == 0) {
            return -1;
        }
        return quickSelect(nums, 0, nums.size() - 1, n);
    }
};
