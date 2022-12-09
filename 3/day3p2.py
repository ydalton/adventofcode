def priority(_letter):
    if _letter >= 'a':
        return ord(_letter) - ord('a') + 1
    if _letter >= 'A':
        return ord(_letter) - ord('A') + 27


with open("input.txt") as f:
    rucksack = f.readline().rstrip()
    commonLetters = []
    while(rucksack):
        littleList = []
        firstElf = rucksack
        secondElf = f.readline().rstrip()
        thirdElf = f.readline().rstrip()
        # print(firstCompartiment)
        # print(secondCompartiment)
        for fletter in firstElf:
            for sletter in secondElf:
                for tletter in thirdElf:
                    if fletter == sletter == tletter and fletter not in littleList:
                        littleList.append(fletter)
        commonLetters.append(littleList)
        rucksack = f.readline().rstrip()
    # print(commonLetters)
    sum = 0
    for letter in commonLetters:
        sum += priority(letter[0])
    print(sum)
    