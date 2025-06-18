# Caesar Cipher implementation

def caesar_cipher(text, shift, mode='encrypt'):
    result = ''
    for char in text:
        if char.isalpha():
            base = ord('A') if char.isupper() else ord('a')
            if mode == 'encrypt':
                result += chr((ord(char) - base + shift) % 26 + base)
            elif mode == 'decrypt':
                result += chr((ord(char) - base - shift) % 26 + base)
        else:
            result += char  # Leave non-alphabet characters unchanged
    return result

# Example usage:
plaintext = "Hello, World"
ciphertext = caesar_cipher(plaintext, shift=3)
print("Encrypted cipher version:", ciphertext)

decrypted = caesar_cipher(ciphertext, shift=3, mode='decrypt')
print("Decrypted version:", decrypted)
