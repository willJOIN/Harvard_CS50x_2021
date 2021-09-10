from cs50 import get_float

def main():
    change()

def change():
    # Non negative float
    dollars = get_float("Change owed: ")
    if dollars < 0:
        main()
    else:
        coins = 0
        cents = int(round(dollars * 100))
        while cents >= 25:
            cents = cents - 25
            coins += 1
        while cents < 25 and cents >= 10:
            cents = cents - 10
            coins += 1
        while cents < 10 and cents >= 5:
            cents = cents - 5
            coins += 1
        while cents < 5 and cents >= 1:
            cents = cents - 1
            coins += 1
        print(coins)

main()
