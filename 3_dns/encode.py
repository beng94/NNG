def char_to_bin (char):
    return {
        'A': '00',
        'C': '01',
        'G': '10',
        'T': '11'
    } [char]

f_o = open("encoded_dns.txt", 'w')
#f_o.write(chr(2).decode('ascii'))
with open("dns.txt", 'r') as f:
    dna_string = f.readline()

    utf_char = ""

    for char in dna_string:
        if char == '\n':
            break

        utf_char = str(char_to_bin(char)) + utf_char

        #UTF-32 max 21 bit
        if len(utf_char) == 8:
            print utf_char, int(utf_char, 2), unichr(int(utf_char, 2)).encode('latin-1')
            #f_o.write(utf_char + " ")
            #f_o.write(str(int(utf_char, 2)) + " ")
            f_o.write(unichr(int(utf_char, 2)).encode('latin-1'))
            utf_char = ""

f_o.close()

