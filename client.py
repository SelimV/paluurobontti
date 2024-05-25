from pynput.keyboard import Key, Listener
from time import sleep
import socket
import sys

IPS_ARDUINO = ["192.168.80.172", "192.168.80.97"]
PORT_ARDUINO = 1234


class State:
    running = True
    space_down = False


def main(ip_arduino):
    state = State()

    def key_press(key):
        match key:
            case Key.delete:
                state.running = False
            case Key.space:
                state.space_down = True

    def key_lift(key):
        match key:
            case Key.space:
                state.space_down = False

    listener = Listener(on_press=key_press, on_release=key_lift)
    listener.start()

    socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    i = 0
    while state.running:
        if state.space_down:
            i += 1
            print(i)
        else:
            i = 0

        socket_udp.sendto(
            bytes(f"Spaces in a row {i}\0", "utf-8"), (ip_arduino, PORT_ARDUINO)
        )
        sleep(0.1)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        ip_arduino = IPS_ARDUINO[int(sys.argv[1])]
    else:
        ip_arduino = IPS_ARDUINO[0]
    print(f"Print connecting to {ip_arduino}")
    main(ip_arduino)
