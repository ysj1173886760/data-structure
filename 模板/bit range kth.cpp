//Ȩֵbit   
bit[];
int find_range_kth(int k)
{
	int ans=0,now=0;
	for(int i=log2(n);i>=0;i--)
	{
		ans+=(1<<i);
		if(ans>n||now+bit[ans]>=k)ans-=(1<<i);		///���ڵ���k�����þ��Ƿ�ֹ�ظ�Ԫ�ء��������k�ڳ����ظ�Ԫ�ص�����¾ͻ���� 
		else cnt+=c[ans];
	}
	return ans++
}
