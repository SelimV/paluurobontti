from pynput.keyboard import Key, Listener
from time import sleep


class State:
    running = True
    space_down = False


def main():
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

    i = 0
    while state.running:
        if state.space_down:
            i += 1
            print(i)
        sleep(0.1)


if __name__ == "__main__":
    print("Hello")
    main()
