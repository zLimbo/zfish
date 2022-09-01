
n = int(input())
adj = [dict() for _ in range(n)]
for i in range(n - 1):
    line = input()
    u, v = list(map(int, line.split()))
#     print(u, v)
    adj[u][v] = 0
    adj[v][u] = 0
    
def dfs(u, p):
    sum = 1
    for v in adj[u].keys():
        if v == p:
            continue
        if adj[u][v] == 0:
            adj[u][v] = dfs(v, u)
        sum += adj[u][v]
    return sum

for i in range(n):
    dfs(i, -1)
    
vmax, cmax = 0, 0
res = dict()
for i in range(n):
    prod = 1
    for cnt in adj[i].values():
        prod *= cnt
    if prod not in res:
        res[prod] = 0
    res[prod] += 1
    if res[prod] > cmax:
        cmax = res[prod]
        vmax = prod
        
print(cmax, vmax % (10**9 + 7))