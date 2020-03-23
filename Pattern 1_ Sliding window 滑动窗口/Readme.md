# 使用时的注意事项

1. 滑动窗口使用双指针的情况：

	左边界left默认为数组的开始索引值0

	窗口右边界rigght遍历整个数组范围：不断更新右边界以满足条件 （扩大窗口）

	当满足条件时，此时右边界固定为上一步结果，更新左边界：向右移动一位 （缩小窗口），直到窗口中不再符合要求，left 不再继续移动，跳到上一步扩大窗口
	

2. 监视输入数组内容的同时还需要监视内容的数量时，可以选择使用哈希表unordered_map<type, int>

	或者选择创建一个数组桶监视数量
	
	
3. 注意缩小窗口的条件，每个题目不同


	

## 伪代码示例
```bash
string s, t;

int left = 0, right = 0;

string res = s;

while(right < s.size()) {

	window.add(s[right]);
	
	right++;
	
	// 如果符合要求，移动 left 缩小窗口
	
	while (window 符合要求) {
	
		// 如果这个窗口的子串更短，则更新 res
		
		res = minLen(res, window);
		
		window.remove(s[left]);
		
		left++;
	}
}
return res;
```


## leetcode题目链接

-  [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/)

-  [76. 最小覆盖字串](https://leetcode-cn.com/problems/minimum-window-substring/)

-  [438. 找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/description/)

-  [3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

-  [239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)

-  [424. 替换后的最长重复字符](https://leetcode-cn.com/problems/longest-repeating-character-replacement/)

-  [480. 滑动窗口中位数](https://leetcode-cn.com/problems/sliding-window-median/) 第480和295题的操作方式溜溜的

-  [295. 数据流的中位数](https://leetcode-cn.com/problems/find-median-from-data-stream/) 对于第480题不理解的可以看295题，有详细的解释，这一题对于新涉及到的数据类型更基础一些

-  [567. 字符串的排列](https://leetcode-cn.com/problems/permutation-in-string/)

-  [978. 最长湍流子数组](https://leetcode-cn.com/problems/longest-turbulent-subarray/)




