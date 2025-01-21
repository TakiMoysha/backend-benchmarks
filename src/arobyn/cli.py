import sys
import argparse


def run_app():
    from arobyn.app import create_app

    parser = argparse.ArgumentParser()
    parser.add_argument("-H", "--host", dest="host", default="0.0.0.0")
    parser.add_argument("-p", "--port", dest="port", type=int, default=8000)
    parser.add_argument("-t", "--threads", dest="thr", type=int, default=1)
    parser.add_argument("-w", "--workers", dest="wrk", type=int, default=1)

    required, extra = parser.parse_known_args(sys.argv[1:])

    app = create_app()
    app.start(host=required.host, port=required.port)
