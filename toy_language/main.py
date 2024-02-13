import re

tape = []
for i in range(0, 30000-1):
    tape.append(0)
ptr = 0

yn = input("Do you want to (1) read from file or (2) read from stdin? ")
if yn == "1":
    f = open(input("Filename: "))
    text = f.read()
else:
    text = input("> ")

openloops = []
loops = {} # first num is pos of '[', second is pos of closing ']'
for i in range(0, len(text)-1):
    if text[i] == "[":
        openloops.append(i)
for opening in openloops:
    wait = 0
    for i in range(opening+1, len(text)-1):
        if text[i] == "[":
            wait += 1
        elif text[i] == "]":
            if wait == 0:
                loops[opening] = i
                break
            else: wait -= 1
revloops = dict(zip(list(loops.values()), list(loops.keys())))

print(loops)

pc = 0
while pc < len(text)-1:
    if re.search("\.|\,|\+|\-|\<|\>|", text[pc]):
        skip = False
        #print(f"pc: {pc}\nptr: {ptr}\ntape[ptr]: {tape[ptr]}\n")
        match text[pc]:
            case "+":
                tape[ptr] += 1
            case "-":
                tape[ptr] -= 1
            case ">":
                ptr += 1
            case "<":
                ptr -= 1
            case ".":
                print(f"{chr(tape[ptr])}", end = "", flush = True)
            case ",":
                tape[ptr] = ord(input()[0])
            case "[":
                if tape[ptr] == 0:
                    pc = loops[pc] + 1
                    skip = True
            case "]":
                if tape[ptr] != 0:
                    pc = revloops[pc]
                    skip = True
    if not skip: pc += 1 
