text = input("Text: ")
l = 0
w = 1
s = 0

# Count letters, words, sentences
for i in text:
    letter = ord(i)
    if (letter > 64 and letter < 91) or (letter > 96 and letter < 123):
        l += 1;
    elif letter == 32:
        w += 1
    elif (letter == 33 or letter == 46) or letter == 63:
        s += 1

# Calc CL index
L = l * 100.0 / w
S = s * 100.0 / w
index = round(0.0588 * L - 0.296 * S - 15.8)

if index > 15:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")