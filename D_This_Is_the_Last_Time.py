n = int(input())

for i in range(n):
    a, k = map(int, input().split())
    casinos = []
    for j in range(a):
        casinos.append(tuple(map(int, input().split())))
    casinos.sort(key=lambda x: x[0])
    for casino in casinos:
        if  k<=casino[1]:
            break
        k = max(k,casino[2]) 
    print(k)
