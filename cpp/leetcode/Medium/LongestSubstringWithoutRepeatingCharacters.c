int lengthOfLongestSubstring(char * s) {
		int slength = -1;
		while (s[++slength]);
		if ( slength < 2)
			return slength;
		int longestLenth = 1;
		for (int i = 0; i < slength; i++)
		{
			int subLenth = 1;
			for (int j = i + 1; j < slength; j++)
			{
				int repeated = 0;
				for (int k = i; k < j; k++)
				{
					if (s[j] == s[k])
					{
						repeated = 1;
						break;
					}
				}
				if (repeated)
				{
					break;
				}
				else
				{
					subLenth += 1;
				}
			}
			longestLenth = longestLenth < subLenth ? subLenth : longestLenth;
		}
		return longestLenth;
	}
