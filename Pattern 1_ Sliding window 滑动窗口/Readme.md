# 使用时的注意事项

1. 滑动窗口使用双指针的情况：

	左边界left默认为数组的开始索引值0

	窗口右边界rigght遍历整个数组范围：不断更新右边界以满足条件 （扩大窗口）

	当满足条件时，此时右边界固定为上一步结果，更新左边界：向右移动一位 （缩小窗口），直到窗口中不再符合要求，left 不再继续移动，跳到上一步扩大窗口
	

2. 监视输入数组内容的同时还需要监视内容的数量时，可以选择使用哈希表unordered_map<type, int>

	或者选择创建一个数组桶监视数量
	
	
3. 注意缩小窗口的条件，每个题目不同


	

## 伪代码示例

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



## leetcode题目

index 209. 长度最小的子数组[https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/]

index 76. 最小覆盖字串[https://leetcode-cn.com/problems/minimum-window-substring/]

index 438. 找到字符串中所有字母异位词[https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/description/]

index 3. 无重复字符的最长子串[https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/]

index 239. 滑动窗口最大值[https://leetcode-cn.com/problems/sliding-window-maximum/]

index 424. 替换后的最长重复字符[https://leetcode-cn.com/problems/longest-repeating-character-replacement/]








