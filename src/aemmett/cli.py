import sys
import argparse

from granian import Granian
from granian.constants import Interfaces


def run_app():
    parser = argparse.ArgumentParser()
    parser.add_argument("-w", "--worker", dest="wrk", help="process", type=int, default=1)
    parser.add_argument("-t", "--threads", dest="thr", help="threads", type=int, default=1)
    parser.add_argument("--interface", type=Interfaces, default="rsgi")

    required, extra = parser.parse_known_args(sys.argv[1:])

    Granian(
        "aemmett.rsgi:app",
        workers=required.wrk,
        threads=required.thr,
        interface=required.interface,
        reload=True,
    ).serve()
