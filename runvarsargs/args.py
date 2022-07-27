# some_script.py
import argparse

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('N', type=int)
    parser.add_argument('pid', type=int)
    parser.add_argument('--with-candles', action='store_true')

    args = parser.parse_args()
    ...

if __name__ == '__main__':
    main()
