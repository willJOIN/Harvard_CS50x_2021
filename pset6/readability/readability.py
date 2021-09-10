from cs50 import get_string

def main():
    start()

def start():
    text = get_string("Text: ")
    numberLetters = count_letters(text)
    numberWords = count_words(text)
    numberSentences = count_sentences(text)
    L = float(numberLetters * 100.0 / numberWords)
    S = float(numberSentences * 100.0 / numberWords)
    index = int((0.0588 * L - 0.296 * S - 15.8) + 0.5)
    if index <= 15 and index >= 1:
        grade = round(index)
        print(f"Grade {grade}")
        print()
    elif index > 15:
        print("Grade 16+", end="")
        print()
    elif index < 1:
        print("Before Grade 1", end="")
        print()

def count_letters(text):
    numberLetters = 0
    for letter in range(len(text)):
        if text[letter].isalpha():
            numberLetters += 1
    return numberLetters

def count_words(text):
    numberWords = 1
    for letter in range(len(text)):
        if text[letter].isspace():
            numberWords += 1
    return numberWords

def count_sentences(text):
    numberSentences = 0
    for letter in range(len(text)):
        if text[letter] in ['!', '?', '.']:
            numberSentences += 1
    return numberSentences

main()
