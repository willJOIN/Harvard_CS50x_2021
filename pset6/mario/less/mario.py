from cs50 import get_int

def main():
    size()

def size():
    # Positive integer 1 =< 8 inclusive, half pyramid height
    height = get_int("Height: ")
    if height < 1 or height > 8:
        main()
    else:
        # Row
        for i in range(height):
            # Column
            for j in range(height):
                if i + j < height - 1:
                    print(" ", end="")
                else:
                    print("#", end="")
            print()

main()
