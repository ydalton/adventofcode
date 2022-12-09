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
        firstCompartiment = rucksack[:int(len(rucksack)/2)]
        secondCompartiment = rucksack[int(len(rucksack)/2):]
        # print(firstCompartiment)
        # print(secondCompartiment)
        for fletter in firstCompartiment:
            for sletter in secondCompartiment:
                if fletter == sletter and fletter not in littleList:
                    littleList.append(fletter)
        commonLetters.append(littleList)
        rucksack = f.readline().rstrip()
    # print(commonLetters)
    sum = 0
    for letter in commonLetters:
        sum += priority(letter[0])
    print(sum)
    