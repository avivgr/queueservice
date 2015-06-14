__author__ = 'Aviv Greenberg'
import QueueServiceClient

"""Module docstring.

This serves as a long usage message.
"""
import sys
import getopt

def main():
    address = "127.0.0.1"
    port = 7001

    # parse command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ha:p:", ["help"])
    except getopt.error, msg:
        print msg
        print "for help use --help"
        sys.exit(2)
    # process options
    for o, a in opts:
        if o in ("-h", "--help"):
            print __doc__
            sys.exit(0)
        elif o in ("-a", "--address"):
            address = a
        elif o in ("-p", "--port"):
            port = a

    qsc = QueueServiceClient.QueueServiceClient(address, port)
    qsc.connect()
    id = qsc.create_queue("myqueue")
    qsc.enqueue(id, "test123")

if __name__ == "__main__":
    main()
