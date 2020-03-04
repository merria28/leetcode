#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/** 424. 替换后的最长重复字符
 ** 题目描述：
	给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。

	注意:
	字符串长度 和 k 不会超过 104。

	示例 1:
	输入:
	s = "ABAB", k = 2
	输出:
	4
	解释:
	用两个'A'替换为两个'B',反之亦然。
	
	示例 2:
	输入:
	s = "AABABBA", k = 1
	输出:
	4
	解释:
	将中间的一个'A'替换为'B',字符串变为 "AABBBBA"。
	子串 "BBBB" 有最长重复字母, 答案为 4。
*/

/// 题解：
/// 题中提到了次数，那么需要统计窗口内出现最多的字符出现了多少次。可以用哈希表，也可以选择数组桶存储出现的次数。
/// 这里选择数组桶，在问题比较单一时，数组桶的效率比较高。
/// 我们把窗口的长度减去出现最多的字符出现的次数，那么就是最少需要修改多少个字符才能把该滑动窗口变为相同的字符。
/// 如果差值大于k，说明我们要修改的字符数多于k，不满足条件，那么把窗口的左边界向右移动到满足该条件为止，移动的同时把因为左边界移动导致的字符离开窗口数-1。

class Solution {
public:
	// 代码中有++count[]与count[s[winStart++] - 'A']，体会一下++i与i++的区别
	// 并且这两者的耗时在这份代码中有所不同，代码中展示的是最优的耗时

	//执行用时：8 ms  内存消耗：9.5 MB
	int characterReplacement(string s, int k) {
		int n = s.size();

		int winStart(0), winEnd(0), maxLength(0), maxCount(0);
		int count[26] = { 0 };

		while (winEnd < n)
		{	
			count[s[winEnd] - 'A']++;
			maxCount = max(maxCount, count[s[winEnd] - 'A']); //当前窗口内的最多字符的个数
			//maxCount = max(maxCount, ++count[s[winEnd] - 'A']);

			winEnd++;

			// 缩小窗口： 需要替换的字符个数大于k时
			// 需要替换的字符个数就是当前窗口的大小减去窗口中数量最多的字符的数量
			while (winEnd-winStart-maxCount>k)
			{				
				//count[s[winStart] - 'A']--;
				//winStart++;
				//相当于下面这一句
				count[s[winStart++] - 'A']--;
			}

			//当窗口内可替换的字符数小于等于k时，我们需要根据该窗口长度来确定是否更新最长子串长度
			maxLength = max(maxLength, winEnd - winStart);
		}

		return maxLength;
	}
};
