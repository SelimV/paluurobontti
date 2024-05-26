from pynput.keyboard import Key, Listener
from time import sleep
import socket
import sys

IPS_ARDUINO = ["192.168.80.172", "192.168.80.97"]
PORT_ARDUINO = 1234


class State:
    running = True
    space_pressed = False
    shift_l_pressed = False
    up_pressed = False
    down_pressed = False
    left_pressed = False
    right_pressed = False
    speed = 0
    turn = 0
    horn = 0


def main(ip_arduino):
    state = State()

    def key_press(key):
        match key:
            case Key.delete:
                state.running = False
            case Key.space:
                state.space_pressed = True
            case Key.shift_l:
                state.shift_l_pressed = True
            case Key.up:
                state.up_pressed = True
            case Key.down:
                state.down_pressed = True
            case Key.left:
                state.left_pressed = True
            case Key.right:
                state.right_pressed = True
            case Key.shift_r:
                state.horn = 1

    def key_lift(key):
        match key:
            case Key.space:
                state.space_pressed = False
            case Key.shift_l:
                state.shift_l_pressed = False
            case Key.up:
                state.up_pressed = False
            case Key.down:
                state.down_pressed = False
            case Key.left:
                state.left_pressed = False
            case Key.right:
                state.right_pressed = False
            case Key.shift_r:
                state.horn = 0

    listener = Listener(on_press=key_press, on_release=key_lift)
    listener.start()

    socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while state.running:

        if state.up_pressed:
            state.speed = 0.5
        if state.down_pressed:
            state.speed = -0.5
        if state.up_pressed == state.down_pressed:
            state.speed = 0
        if state.right_pressed:
            state.turn = 0.5
        if state.left_pressed:
            state.turn = -0.5
        if state.right_pressed == state.left_pressed:
            state.turn = 0
        if state.shift_l_pressed:
            state.speed *= 2
        if state.space_pressed:
            state.turn *= 2

        command = f"{state.speed}/{state.turn}/{state.horn}\0"
        print(command)
        socket_udp.sendto(bytes(command, "utf-8"), (ip_arduino, PORT_ARDUINO))
        sleep(0.1)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        ip_arduino = IPS_ARDUINO[int(sys.argv[1])]
    else:
        ip_arduino = IPS_ARDUINO[0]
    print(f"Print connecting to {ip_arduino}")
    main(ip_arduino)
