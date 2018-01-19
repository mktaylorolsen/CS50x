import cs50

def main():

    #retrieve the pyramid height from the user
    print("What height of pyramid do you want?")
    height = cs50.get_int()
    #ensure height is not 0
    #ensure height is greater than 1 and less than 23
    if height < 0 or height > 23 or height == 0:
        print("Height needs to be greater than 0 and less than 23.")
    else:
        #determine number of rows
        for i in range(height):
            #determine number of spaces
            for s in range(height - i - 1):
                #print spaces
                print(" ", end="")
            #determine number of hashtags
            for h in range(i+2):
                #print hashtags
                print("#", end="")
            #print new line
            print()

if __name__ == "__main__":
    main()