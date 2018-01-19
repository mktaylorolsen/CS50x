import cs50
import sys

def main():
    #ensure argument count is 2
    if len (sys.argv) == 2:
        #retrieve the plaintext from the user
        print("plaintext: ", end = "")
        user_message = cs50.get_string()
        #print out the cipher text
        print("ciphertext: ", end = "")
        #deploy the cipher function
        #change the key to an integer
        key = int(sys.argv[1])
        cipher(user_message, key)
        #print new line. just for looks :)
        print()
        exit (0)
    #else alert the user the usage is incorrect
    else:
        print("Incorrect usage. Please enter a key on the command line.")
        exit (1)


#ciphering function
def cipher(str, int):
    #iterate over characters in the string
    for n in str:
        #determine if the character is a letter and it's case
        #transform the letter using the key
        #print letter
        if n.isalpha():
            #change the character into an integer
            char_int = ord(n)
            if n.isupper():
                #compute the move
                upperchar = ((((char_int - 65) + int) % 26) + 65)
                #change the integer back to a character and print new character
                print(chr(upperchar), end = "")
            elif n.islower():
                #compute the move
                lowerchar = ((((char_int - 97) + int) % 26) + 97)
                #change the integer back to a character and print new character
                print(chr(lowerchar), end = "")
        #if not a letter, print the character unchanged
        else:
            print(n, end = "")

if __name__ == "__main__":
    main()