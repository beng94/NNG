f_dns = open("dns.txt", 'r')
f_decoded = open("decoded_dns.txt", 'r')

dns_str = f_dns.readline()
decoded_str = f_decoded.readline()

print(len(dns_str))
print(len(decoded_str))

for id_ in range(len(dns_str)-1):
    if dns_str[id_] != decoded_str[id_]:
        print("Fuck that", id_, dns_str[id_], decoded_str[id_], dns_str[id_ - 8: id_ + 8], decoded_str[id_ - 8: id_ + 8])

f_dns.close()
f_decoded.close()
