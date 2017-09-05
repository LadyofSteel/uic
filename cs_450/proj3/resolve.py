"""
resolve.py: a recursive resolver built using dnspython
"""

import argparse

import dns.message
import dns.name
import dns.query
import dns.rdata
import dns.rdataclass
import dns.rdatatype

FORMATS = (("CNAME", "{alias} is an alias for {name}"),
           ("A", "{name} has address {address}"),
           ("AAAA", "{name} has IPv6 address {address}"),
           ("MX", "{name} mail is handled by {preference} {exchange}"))

# current as of 23 February 2017
ROOT_SERVERS = ("198.41.0.4",
                "192.228.79.201",
                "192.33.4.12",
                "199.7.91.13",
                "192.203.230.10",
                "192.5.5.241",
                "192.112.36.4",
                "198.97.190.53",
                "192.36.148.17",
                "192.58.128.30",
                "193.0.14.129",
                "199.7.83.42",
                "202.12.27.33")

domain_cache = {}


def collect_results(name: str) -> dict:
    """
    This function parses final answers into the proper data structure that
    print_results requires. The main work is done within the `lookup` function.
    """
    full_response = {}
    cnames = []
    arecords = []
    aaaarecords = []
    mxrecords = []

    target_name = dns.name.from_text(name)

    # lookup CNAME
    response = lookup(target_name, dns.rdatatype.CNAME)

    if response is not None:
        for answers in response.answer:
            for answer in answers:
                cnames.append({"name": answer, "alias": name})

                # Use CNAME answer for the remaining lookups
                target_name = str(answer)[:-1]

    # lookup A
    response = lookup(target_name, dns.rdatatype.A)

    if response is not None:
        for answers in response.answer:
            a_name = answers.name
            for answer in answers:
                if answer.rdtype == 1:  # A record
                    arecords.append({"name": a_name, "address": str(answer)})

    # lookup AAAA
    response = lookup(target_name, dns.rdatatype.AAAA)

    if response is not None:
        for answers in response.answer:
            aaaa_name = answers.name
            for answer in answers:
                if answer.rdtype == 28:  # AAAA record
                    aaaarecords.append(
                        {"name": aaaa_name, "address": str(answer)})

    # lookup MX
    response = lookup(target_name, dns.rdatatype.MX)

    if response is not None:
        for answers in response.answer:
            mx_name = answers.name
            for answer in answers:
                if answer.rdtype == 15:  # MX record
                    mxrecords.append({"name": mx_name,
                                      "preference": answer.preference,
                                      "exchange": str(answer.exchange)})

    full_response["CNAME"] = cnames
    full_response["A"] = arecords
    full_response["AAAA"] = aaaarecords
    full_response["MX"] = mxrecords

    return full_response


# Get IPv4 address
def get_address(string):

    tokens = string.split()
    address = []
    for t in tokens:
        if t == 'A':
            address += [tokens[-1]]

    return address


def _lookup(target_name, qtype, servers_list):
    """
    Recursive DNS resolver function.
    """
    if not servers_list:
        return None

    outbound_query = dns.message.make_query(target_name, qtype)

    for server in servers_list:
        try:
            response = dns.query.udp(outbound_query, server, 3)
        except:
            # print("DNS query died. Querying another server.\n")
            continue

        # If we don't get an aswer
        if response.answer == []:
            addresses = []

            # If we don't get an additional
            if response.additional == []:
                ns_names = []

                # Go through authority section
                for auth_list in response.authority:
                    # Get nameserver name
                    for auth in auth_list:
                        if auth.rdtype == 6:
                            # SOA record, dead end
                            return None
                        ns_names += [str(auth)[:-1]]

                    for ns_name in ns_names:
                        # Get the address of the nameserver using its name
                        ns_response = _lookup(ns_name, 1, ROOT_SERVERS)

                        # If we get any response, we should try to query
                        if ns_response is not None:
                            for answer in ns_response.answer:
                                ns_address = get_address(str(answer))

                                ns_response2 = _lookup(target_name,
                                                       qtype, ns_address)
                                if ns_response2 is not None:
                                    return ns_response2

                        # Otherwise keep trying other nameservers

            else:
                # Get whatever we can from additional section
                for additional in response.additional:
                    addresses += get_address(str(additional))

                return _lookup(target_name, qtype, addresses)

        else:
            # Go through answers
            for answers in response.answer:
                for answer in answers:
                    target_name = str(answer)[:-1]

                    # Make sure we got what we asked for
                    if answer.rdtype == qtype:
                        return response
                    else:
                        if answer.rdtype == 5:
                            return _lookup(target_name, qtype, ROOT_SERVERS)


def lookup(target_name: dns.name.Name,
           qtype: dns.rdata.Rdata) -> dns.message.Message:
    """
    This function uses a recursive resolver to find the relevant answer to the
    query.
    """
    return _lookup(target_name, qtype, ROOT_SERVERS)


def print_results(results: dict) -> None:
    """
    Take the results of a `lookup` and print them to the screen like the host
    program would.
    """

    for rtype, fmt_str in FORMATS:
        for result in results.get(rtype, []):
            print(fmt_str.format(**result))


def main():
    """
    if run from the command line, take args and call
    printresults(lookup(hostname))
    """
    argument_parser = argparse.ArgumentParser()
    argument_parser.add_argument("name", nargs="+",
                                 help="DNS name(s) to look up")
    argument_parser.add_argument("-v", "--verbose",
                                 help="increase output verbosity",
                                 action="store_true")
    program_args = argument_parser.parse_args()
    for a_domain_name in program_args.name:
        if a_domain_name in domain_cache:
            print_results(domain_cache[a_domain_name])
        else:
            domain_cache[a_domain_name] = collect_results(a_domain_name)
            print_results(domain_cache[a_domain_name])

if __name__ == "__main__":
    main()
