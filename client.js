console.log("Hello world")

var space_down = false

document.addEventListener("keydown", function (event) {
    if (event.key = " ") {
        space_down = true
    } else {
        console.log(event.key)
    }
})

document.addEventListener("keyup", function (event) {
    if (event.key = " ") {
        space_down = false
    } else {
        console.log(event.key)
    }
})

function main_loop() {
    if (space_down) {
        console.log("Space")
        fetch("https://192.168.80.172/space").then(console.log)
    }
}

setInterval(main_loop, 100);