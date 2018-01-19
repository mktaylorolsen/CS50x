import cs50

def main():
    # get number from user
    print("Hello! How much change are you owed?")
    change = cs50.get_float()
    #make sure the integer is positive
    if change > 0:
        # print out coin count
        print("Your Coin Count:", end="")
        CoinBreakdown(change)
    else:
        print("Number must be greater than 0.")


# determine how many quarters
def CoinBreakdown(float):
    converted = float * 100
    quartercount = converted // 25
    quartermod = converted % 25
    # determine how many dimes
    dimecount = quartermod // 10
    dimemod = quartermod % 10
    # determine how many nickles
    nicklecount = dimemod // 5
    nicklemod = dimemod % 5
    # detemine how many pennies
    pennycount = nicklemod // 1
    coincount = quartercount + dimecount + nicklecount + pennycount
    print ("{}".format(coincount))

if __name__ == "__main__":
    main()

