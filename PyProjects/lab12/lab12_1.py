def sortt(ar):
    womens = ""
    chlds = ""
    mans = ""
    captain = ""
    counter_captains = 0
    for i in range(n):
        if ar[i][1] == "women":
            womens += (ar[i][0] + " ")
        if ar[i][1] == "child":
            chlds += (ar[i][0] + " ")
        if ar[i][1] == "man":
            mans += (ar[i][0] + " ")
        if ar[i][1] == "captain":
            captain = ar[i][0]
            counter_captains += 1
    if counter_captains == 1:
        return((womens+chlds+mans+captain).split(" "))
    else:
        print("капитан должен быть один)")
n = int(input("Количество людей: "))
array = [""] * n
for i in range(n):
     array[i] = input().split(' ')
new_array = sortt(array)
for i in range(n):
    print(new_array[i])
