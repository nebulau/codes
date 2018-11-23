k=int(input())
i=1
m=(k-1)/2+1
while (i<=2*m):
	print(' '*int(abs(i-m))+"*"*int(m-abs(i-m))*2)
	i=i+1