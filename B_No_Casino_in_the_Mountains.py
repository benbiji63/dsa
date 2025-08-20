n = int(input())

for i in range(n):
    days,duration = map(int,input().split())
    weather = input().replace(" ", "")
    count = 0
    while weather:
        try:
            index = weather.index("0" * duration)
        except ValueError:
            break
        count += 1
        weather = weather[index+duration+1:]
    print(count)